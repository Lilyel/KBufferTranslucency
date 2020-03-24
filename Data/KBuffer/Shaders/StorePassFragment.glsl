#version 450 core

layout(early_fragment_tests) in;

layout(binding = 0, r32ui) coherent uniform uimage2D Semaphores;
layout(binding = 1, r8ui) coherent uniform uimage2D Counts;
layout(binding = 2, r8ui) coherent uniform uimage2DArray MaterialIndices;
layout(binding = 3, r32f) coherent uniform image2DArray Depths;
layout(binding = 4, rgba16f) coherent uniform image1DArray Materials;
layout(binding = 5, rgba16f) coherent uniform image2DArray Positions;

in vec3 VS_Position;

// Material datas.
uniform int MaterialIndex;
uniform vec4 BaseColor;
uniform bool IsTranslucent;
uniform vec4 TranslucentColor;
uniform float MaxTranslucentThickness;

// K-Buffer max capacity.
uniform int K;


struct FragmentData
{
	bool m_IsMaterialSet;
	uint m_MaterialIndex;
	vec4 m_BaseColor;
	bool m_IsTranslucent;
	vec4 m_TranslucentColor;
	float m_MaxTranslucentThickness;
	float m_Depth;
	vec3 m_Position;
	bool m_IsFacingCamera;
};


void InsertEmpty( uint _Count, ivec2 _Pixel );
void InsertFull( uint _Count, ivec2 _Pixel );

bool EarlyCulling( ivec2 _Pixel );

bool LockSemaphore( ivec2 _Pixel );
void FreeSemaphore( ivec2 _Pixel );

void main()
{
	ivec2 Pixel = ivec2( gl_FragCoord.xy );	

	// Culling : Skip when the array is full and the new fragment is further than the head.
	if( EarlyCulling( Pixel ) )
		discard;

	bool StayInLoop = true;
	while( StayInLoop )
	{
		// Wait until the fragment is available.
		// Once the semaphore passed, we are sure that we can read and write the textures on the pixel location safely.
		if( LockSemaphore( Pixel ) )
		{
			// Check if the fragments array is full.
			uint Count = imageLoad( Counts, Pixel ).r;
			bool IsNotFull = Count < K;	

			// If the array is not full, just add the fragment at the end.
			if( IsNotFull )
				InsertEmpty( Count, Pixel );

			// Otherwise replace the furthest stored fragments with the new fragment.
			else
				InsertFull( Count, Pixel );


			// Free the access to the pixel to let the other threads store their fragment too.
			FreeSemaphore( Pixel );
			StayInLoop = false;
		}
	}

	discard;
}

bool EarlyCulling( ivec2 _Pixel )
{
	bool IsFull = imageLoad( Counts, _Pixel ).r >= K;
	bool IsFurtherThanHead = gl_FragCoord.z > imageLoad( Depths, ivec3( _Pixel, 0 ) ).r;
	
	return IsFull && IsFurtherThanHead;
}

bool LockSemaphore( ivec2 _Pixel )
{
	// Quick check to see if the pixel is available.
	if( imageLoad( Semaphores, _Pixel ).r == 1 )
		return false;

	return imageAtomicExchange( Semaphores, _Pixel, 1 ) == 0;
}

void FreeSemaphore( ivec2 _Pixel )
{
	imageStore( Semaphores, _Pixel, uvec4( 0 ) );
}



bool IsMaterialSet()
{
	ivec2 MatOtherData = ivec2( MaterialIndex, 3 );
	return imageLoad( Materials, MatOtherData ).r == 1;
}

FragmentData GetFragmentData( ivec2 _Pixel, uint _Depth )
{
	FragmentData Data;

	ivec3 Pixel3D = ivec3( _Pixel, _Depth );
	Data.m_MaterialIndex = imageLoad( MaterialIndices, Pixel3D ).r;
	Data.m_Depth = imageLoad( Depths, Pixel3D ).r;

	vec4 PositionAndFacing = imageLoad( Positions, Pixel3D );
	Data.m_Position = PositionAndFacing.rgb;
	Data.m_IsFacingCamera = PositionAndFacing.a == 1.0;

	ivec2 MatBaseColor = ivec2( Data.m_MaterialIndex, 0 );
	Data.m_BaseColor = imageLoad( Materials, MatBaseColor );

	ivec2 MatTranslucentColor = ivec2( Data.m_MaterialIndex, 1 );
	Data.m_TranslucentColor = imageLoad( Materials, MatTranslucentColor );

	ivec2 MatOtherData = ivec2( Data.m_MaterialIndex, 2 );
	vec4 OtherDatas = imageLoad( Materials, MatOtherData );
	Data.m_IsMaterialSet = OtherDatas.r == 1;
	Data.m_IsTranslucent = OtherDatas.g == 1;
	Data.m_MaxTranslucentThickness = OtherDatas.b;

	return Data;
}

FragmentData SetupFragmentData( bool _IsMaterialSet )
{
	FragmentData Data;

	Data.m_MaterialIndex = MaterialIndex;
	Data.m_BaseColor = BaseColor;
	Data.m_TranslucentColor = TranslucentColor;
	Data.m_IsMaterialSet = _IsMaterialSet;
	Data.m_IsTranslucent = IsTranslucent;
	Data.m_MaxTranslucentThickness = MaxTranslucentThickness;
	Data.m_Depth = gl_FragCoord.z;
	Data.m_Position = VS_Position;
	Data.m_IsFacingCamera = gl_FrontFacing;

	return Data;
}

void SetFragmentData( FragmentData _Data, ivec2 _Pixel, uint _Depth )
{
	ivec3 Pixel3D = ivec3( _Pixel, _Depth );
	imageStore( MaterialIndices, Pixel3D, uvec4( _Data.m_MaterialIndex ) );
	imageStore( Depths, Pixel3D, vec4( _Data.m_Depth ) );
	imageStore( Positions, Pixel3D, vec4( _Data.m_Position, _Data.m_IsFacingCamera ? 1.0 : 0.0 ) );

	if( !_Data.m_IsMaterialSet )
	{
		_Data.m_IsMaterialSet = true;

		ivec2 MatBaseColor = ivec2( _Data.m_MaterialIndex, 0 );
		imageStore( Materials, MatBaseColor, _Data.m_BaseColor );

		ivec2 MatTranslucentColor = ivec2( _Data.m_MaterialIndex, 1 );
		imageStore( Materials, MatTranslucentColor, _Data.m_TranslucentColor );

		ivec2 MatOtherData = ivec2( _Data.m_MaterialIndex, 2 );
		vec4 OtherDatas;
		OtherDatas.r = _Data.m_IsMaterialSet ? 1.0 : 0.0;
		OtherDatas.g = _Data.m_IsTranslucent ? 1.0 : 0.0;
		OtherDatas.b = _Data.m_MaxTranslucentThickness;
		OtherDatas.a = 0.0;
		imageStore( Materials, MatOtherData, OtherDatas );	
	}
}


void InsertEmpty( uint _Count, ivec2 _Pixel )
{
	FragmentData CurrentData = SetupFragmentData( IsMaterialSet() );
	FragmentData HeadData = GetFragmentData( _Pixel, 0 );
	
	// If the new fragment is further than the head, replace the head to keep the furthest fragment into it.
	if( _Count == 0 || CurrentData.m_Depth > HeadData.m_Depth )
	{
		SetFragmentData( CurrentData, _Pixel, 0 );

		// Change current value to place the previous head in the array.		
		CurrentData = HeadData;
	}

	// Insert color and depth of the fragment at the end of array.
	// Skipped for the first insertion since we placed it in the head.
	if( _Count > 0 )
		SetFragmentData( CurrentData, _Pixel, _Count );

	// Update fragments count.
	imageStore( Counts, _Pixel, uvec4( _Count + 1 ) );
}



// Find the furthest fragment index after the head.
int NextFurthestFragment( out float _FurthestValue, uint _Count, ivec2 _Pixel )
{
	int CurrentMaxID = 0; // If K is 1, the head will be taken.
	float CurrentMaxDepth = -1.0;
	for( int p = 1; p < _Count; p++ )
	{
		ivec3 Pixel3D = ivec3( _Pixel, p );
		float CurrentDepth = imageLoad( Depths, Pixel3D ).r;

		if( CurrentDepth > CurrentMaxDepth )
		{
			CurrentMaxID = p;
			CurrentMaxDepth = CurrentDepth;
		}
	}

	_FurthestValue = CurrentMaxDepth;
	return CurrentMaxID;
}

// Take the second furthest data after the head and place it at head.
void ReplaceHead( int _FurthestIndex, ivec2 _Pixel )
{
	FragmentData FurthestData = GetFragmentData( _Pixel, _FurthestIndex );
	SetFragmentData( FurthestData, _Pixel, 0 );
}


void ReplaceWithCurrentData( int _Index, ivec2 _Pixel )
{
	FragmentData CurrentData = SetupFragmentData( IsMaterialSet() );
	SetFragmentData( CurrentData, _Pixel, _Index);
}

void InsertFull( uint _Count, ivec2 _Pixel )
{
	ivec3 Pixel3DHead = ivec3( _Pixel, 0 );
	float HeadDepth = imageLoad( Depths, Pixel3DHead ).r;

	// If the new fragment is further that our furthest stored, skip it.
	if( gl_FragCoord.z > HeadDepth )
		return;

	// Find the furthest fragment, the head is ignored since we are going to replace it.
	float FurthestDepth = 0.0;
	int FurthestIndex = NextFurthestFragment( FurthestDepth, _Count, _Pixel );

	// K == 1 : just put the current data in the head.
	// If the new fragment is the new furthest of the array, put it in the head.
	if( FurthestIndex == 0 || gl_FragCoord.z > FurthestDepth )
		ReplaceWithCurrentData( 0, _Pixel );

	else
	{
		// Place the furthest fragment in the head of the array.
		ReplaceHead( FurthestIndex, _Pixel );

		// Place the current fragment at the place of the previous furthest fragment (that is now at the head of the array).
		ReplaceWithCurrentData( FurthestIndex, _Pixel );
	}
}


