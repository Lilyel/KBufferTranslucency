#version 450 core

#define MAX_SIZE 16

out vec4 Color;

layout(binding = 0, r32ui) coherent uniform uimage2D Semaphores;
layout(binding = 1, r8ui) coherent uniform uimage2D Counts;
layout(binding = 2, r8ui) coherent uniform uimage2DArray MaterialIndices;
layout(binding = 3, r32f) coherent uniform image2DArray Depths;
layout(binding = 4, rgba16f) coherent uniform image1DArray Materials;
layout(binding = 5, rgba16f) coherent uniform image2DArray Positions;


uniform vec4 BackgroundColor;

uniform vec3 CameraPosition;
uniform float CameraNear;
uniform float CameraFar;

uniform bool ToneMap;
uniform float Exposure;

uniform bool GammaCorrection;
uniform float Gamma;

// Data common to several fragments.
struct MaterialData
{
	bool m_IsMaterialSet;
	vec4 m_BaseColor;
	bool m_IsTranslucent;
	vec3 m_TranslucentColor;
	float m_MaxTranslucentThickness;
};

// Per fragment dependent data.
struct FragmentData
{
	float m_Depth;
	uint m_MaterialIndex;
	vec3 m_Position;
	bool m_IsFacingCamera;
};

void RetrieveMaterialsIndicesAndDepths( uint _Count, ivec2 _Pixel, out FragmentData _OrdoredDatas[MAX_SIZE] );
void InsertionSort( uint _Count, inout FragmentData _OrdoredDatas[MAX_SIZE] );
vec4 Resolve( uint _Count, ivec2 _Pixel, FragmentData _OrdoredDatas[MAX_SIZE] );


void main()
{
	ivec2 Pixel = ivec2( gl_FragCoord.xy );

	uint Count = imageLoad( Counts, Pixel ).r;

	if( Count == 0 )
		discard;

	FragmentData OrdoredDatas[MAX_SIZE];
	RetrieveMaterialsIndicesAndDepths( Count, Pixel, OrdoredDatas );

	// Sort the pixel from the farest to the nearest.
	InsertionSort( Count, OrdoredDatas );

	// Accumulate all stored fragment to find the final pixel color.
	Color = Resolve( Count, Pixel, OrdoredDatas );
}

// Retrieve the fragments datas.
void RetrieveMaterialsIndicesAndDepths( uint _Count, ivec2 _Pixel, out FragmentData _OrdoredDatas[MAX_SIZE] )
{
	for( uint p = 0; p < _Count; p++ )
	{
		ivec3 Pixel3D = ivec3( _Pixel, p );
		_OrdoredDatas[p].m_MaterialIndex = imageLoad( MaterialIndices, Pixel3D ).r;
		_OrdoredDatas[p].m_Depth = imageLoad( Depths, Pixel3D ).r;

		vec4 PositionAndFacing = imageLoad( Positions, Pixel3D );
		_OrdoredDatas[p].m_Position = PositionAndFacing.rgb;
		_OrdoredDatas[p].m_IsFacingCamera = PositionAndFacing.a == 1;
	}
}



void Swap( int _A, int _B, inout FragmentData _OrdoredDatas[MAX_SIZE] );

// Sort the fragment according to their depth.
void InsertionSort( uint _Count, inout FragmentData _OrdoredDatas[MAX_SIZE] )
{
	// https://en.wikipedia.org/wiki/Insertion_sort

	int i = 1;
	while( i < _Count )
	{
		int j = i;

		while( j > 0 && _OrdoredDatas[j - 1].m_Depth < _OrdoredDatas[j].m_Depth )
		{
			Swap( j, j - 1, _OrdoredDatas );
			j--;	
		}

		i++;
	}
}


MaterialData GetMaterialData( uint _MatIndex );
vec3 AlphaBlend( vec3 _FrontColor, vec3 _BackColor, float _Aplha );
vec3 GetTranslucentColor( FragmentData _FragData, MaterialData _MatData, float _BackDepth, vec3 _BackColor );

// Blend the fragments.
vec4 Resolve( uint _Count, ivec2 _Pixel, FragmentData _OrdoredDatas[MAX_SIZE] )
{
	vec3 ResolvedColor = BackgroundColor.rgb;
	float BackDepth = 1.0;

	for( int p = 0; p < _Count; p++ )
	{
		MaterialData CurrentData = GetMaterialData( _OrdoredDatas[p].m_MaterialIndex );

		vec3 CurrentColor;

		if( CurrentData.m_IsTranslucent )
		{
			CurrentColor = GetTranslucentColor( _OrdoredDatas[p], CurrentData, BackDepth, ResolvedColor );
			BackDepth = _OrdoredDatas[p].m_Depth;
		}
		else
			CurrentColor = CurrentData.m_BaseColor.rgb;
		
		
		ResolvedColor = AlphaBlend( CurrentColor, ResolvedColor, CurrentData.m_BaseColor.a );
	}
	

	if( ToneMap )
		ResolvedColor = vec3( 1.0 ) - exp( -ResolvedColor * Exposure );

	if( GammaCorrection )
		ResolvedColor = pow( ResolvedColor, vec3( 1.0 / Gamma ) );


	return vec4( ResolvedColor, 1.0 );
}




void Swap( int _A, int _B, inout FragmentData _OrdoredDatas[MAX_SIZE] )
{
	FragmentData DataA = _OrdoredDatas[_A];
	FragmentData DataB = _OrdoredDatas[_B];
	
	_OrdoredDatas[_A] = DataB;
	_OrdoredDatas[_B] = DataA;
}


MaterialData GetMaterialData( uint _MatIndex )
{
	MaterialData Data;

	ivec2 MatBaseColor = ivec2( _MatIndex, 0 );
	Data.m_BaseColor = imageLoad( Materials, MatBaseColor );

	ivec2 MatTranslucentColor = ivec2( _MatIndex, 1 );
	Data.m_TranslucentColor = imageLoad( Materials, MatTranslucentColor ).rgb;

	ivec2 MatOtherData = ivec2( _MatIndex, 2 );
	vec4 OtherDatas = imageLoad( Materials, MatOtherData );
	Data.m_IsMaterialSet = OtherDatas.r == 1;
	Data.m_IsTranslucent = OtherDatas.g == 1;
	Data.m_MaxTranslucentThickness = OtherDatas.b;

	return Data;
}



vec3 AlphaBlend( vec3 _FrontColor, vec3 _BackColor, float _Aplha )
{
	return vec3( _FrontColor * _Aplha + _BackColor * ( 1.0 - _Aplha ) );
}



// Translucency functions.

float LinearizeDepth( in float _Depth, in float _Near, in float _Far ) 
{
    float Z = _Depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * _Near * _Far ) / (_Far + _Near - Z * (_Far - _Near));	
}

float GetThickness( float _FrontDepth, float _BackDepth )
{
	float LinearFrontDepth = LinearizeDepth( _FrontDepth, CameraNear, CameraFar );
	float LinearBackDepth = LinearizeDepth( _BackDepth, CameraNear, CameraFar );

	return max( 0.0001, LinearBackDepth - LinearFrontDepth );
}

vec3 GetPhysicalExtinction( float _MaxThickness, vec3 _TargetColor )
{
	return max( vec3(0.001), -log( _TargetColor ) ) / _MaxThickness;
}

vec3 GetTransmittedColor( FragmentData _FragData, MaterialData _MatData, float _BackDepth, vec3 _ViewDirection )
{
	float Thickness = GetThickness( _FragData.m_Depth, _BackDepth );
	vec3 PhysicalExtinction = GetPhysicalExtinction( _MatData.m_MaxTranslucentThickness, _MatData.m_TranslucentColor );

	return exp( -PhysicalExtinction * Thickness );
}

vec3 GetTranslucentColor( FragmentData _FragData, MaterialData _MatData, float _BackDepth, vec3 _BackColor )
{	
	vec3 ViewDirection = normalize( CameraPosition - _FragData.m_Position );

	// Fragment at the other side of the object : we just need to return the color behing them.
	if( !_FragData.m_IsFacingCamera )
		return _BackColor;


	vec3 SurfaceColor = _MatData.m_BaseColor.rgb;

	// Transmitted color according to the object thickness.
	vec3 Transmitted = GetTransmittedColor( _FragData, _MatData, _BackDepth, ViewDirection );

	// Translucent color : surface color + background filtered by the transmitted color.
	vec3 TranslucentColor = SurfaceColor + Transmitted * _BackColor;

	return TranslucentColor;
}
