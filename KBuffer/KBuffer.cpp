#include "KBuffer.h"

#include "KBufferToEditor.h"

#include <API/Code/Graphics/Drawable/Drawable.h>
#include <API/Code/Graphics/Camera/Camera.h>
#include <API/Code/Aero/Aero.h>
#include <API/Code/Debugging/Debugging.h>


KBuffer::KBuffer( Uint32 _Width, Uint32 _Height, Uint32 _K ) :
	ae::Framebuffer( _Width, _Height, AttachementPreset::Depth_Float ),
	m_K( ae::Math::Clamp( 1u, 16u, _K ) ),
	m_StorePassShader( "../../../Data/KBuffer/Shaders/StorePassVertex.glsl", "../../../Data/KBuffer/Shaders/StorePassFragment.glsl" ),
	m_ResolvePassShader( "../../../Data/KBuffer/Shaders/ResolvePassVertex.glsl", "../../../Data/KBuffer/Shaders/ResolvePassFragment.glsl" ),
	m_Semaphores( _Width, _Height, ae::TexturePixelFormat::Red_U32_NOTNORM ),
	m_Counts( _Width, _Height, ae::TexturePixelFormat::Red_U8 ),
	m_MaterialIndices( _Width, _Height, m_K, ae::TexturePixelFormat::Red_U8 ),
	m_Depths( _Width, _Height, m_K, ae::TexturePixelFormat::Red_F32 ),
	m_Positions( _Width, _Height, m_K, ae::TexturePixelFormat::RGBA_F16 ),
	m_Materials( 1, 3, ae::TexturePixelFormat::RGBA_F16 ),
	m_FullscreenSprite( *this ),

	m_IsToneMapped( False ),
	m_Exposure( 1.0f ),
	m_IsGammaCorrected( False ),
	m_Gamma( 2.2f )
{
	m_Semaphores.SetName( "K-Buffer Semaphores Image" );
	m_Semaphores.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_Semaphores.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_Counts.SetName( "K-Buffer Counts Image" );
	m_Counts.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_Counts.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_MaterialIndices.SetName( "K-Buffer Material Indices Image" );
	m_MaterialIndices.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_MaterialIndices.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_Depths.SetName( "K-Buffer Depths Image" );
	m_Depths.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_Depths.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_Positions.SetName( "K-Buffer Positions Image" );
	m_Positions.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_Positions.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_Materials.SetName( "K-Buffer Materials Image" );
	m_Materials.SetFilterMode( ae::TextureFilterMode::Nearest );
	m_Materials.SetWrapMode( ae::TextureWrapMode::ClampToEdge );

	m_FullscreenSprite.SetName( "K-Buffer Fullscreen Quad" );

	ae::Texture* DepthTexture = GetAttachementTexture( ae::FramebufferAttachement::Type::Depth );
	if( DepthTexture != nullptr )
		DepthTexture->SetName( "K-Buffer Depth Attachement" );

	m_StorePassShader.SetName( "K-Buffer Store Pass Shader" );
	m_ResolvePassShader.SetName( "K-Buffer Resolve Pass Shader" );
}

Uint32 KBuffer::GetK() const
{
	return m_K;
}

void KBuffer::SetK( Uint32 _K )
{
	Uint32 NewK = ae::Math::Clamp( 1u, 16u, _K );
	if( m_K == NewK )
		return;

	m_K = NewK;

	m_MaterialIndices.Resize( GetWidth(), GetHeight(), m_K );
	m_Depths.Resize( GetWidth(), GetHeight(), m_K );
	m_Positions.Resize( GetWidth(), GetHeight(), m_K );
}

Bool KBuffer::IsToneMapped() const
{
	return m_IsToneMapped;
}

void KBuffer::SetIsToneMapped( Bool _IsToneMapped )
{
	m_IsToneMapped = _IsToneMapped;
}

float KBuffer::GetExposure() const
{
	return m_Exposure;
}

void KBuffer::SetExposure( float _Exposure )
{
	m_Exposure = ae::Math::Max( _Exposure, 0.0f );
}

Bool KBuffer::IsGammaCorrected() const
{
	return m_IsGammaCorrected;
}

void KBuffer::SetIsGammaCorrected( Bool _IsGammaCorrected )
{
	m_IsGammaCorrected = _IsGammaCorrected;
}

float KBuffer::GetGamma() const
{
	return m_Gamma;
}

void KBuffer::SetGamma( float _Gamma )
{
	m_Gamma = ae::Math::Max( _Gamma, ae::Math::Epsilon() );
}

void KBuffer::SetStorePassMaterialCount( Int32 _Count )
{
	Uint32 NewMaterialCount = Cast( Uint32, ae::Math::Max( 1, _Count ) );

	if( m_Materials.GetWidth() == NewMaterialCount )
		return;

	m_Materials.Resize( NewMaterialCount, 3 );
}

void KBuffer::Resize( Uint32 _Width, Uint32 _Height )
{
	if( GetWidth() == _Width && GetHeight() == _Height )
		return;

	ae::Framebuffer::Resize( _Width, _Height );

	m_Semaphores.Resize( _Width, _Height );
	m_Counts.Resize( _Width, _Height );
	m_MaterialIndices.Resize( _Width, _Height, m_K );
	m_Depths.Resize( _Width, _Height, m_K );
	m_Positions.Resize( _Width, _Height, m_K );
}


void KBuffer::ClearPass()
{
	glClearTexSubImage( m_Semaphores.GetTextureID(), 0, 0, 0, 0, m_Semaphores.GetWidth(), m_Semaphores.GetHeight(), 1, 
						ae::ToGLFormat( m_Semaphores.GetFormat() ), ae::ToGLType( m_Semaphores.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();


	glClearTexSubImage( m_Counts.GetTextureID(), 0, 0, 0, 0, m_Counts.GetWidth(), m_Counts.GetHeight(), 1,
						ae::ToGLFormat( m_Counts.GetFormat() ), ae::ToGLType( m_Counts.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();


	glClearTexSubImage( m_MaterialIndices.GetTextureID(), 0, 0, 0, 0, m_MaterialIndices.GetWidth(), m_MaterialIndices.GetHeight(), m_MaterialIndices.GetDepth(),
						ae::ToGLFormat( m_MaterialIndices.GetFormat() ), ae::ToGLType( m_MaterialIndices.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();


	float DepthClear = 1.0f;
	glClearTexSubImage( m_Depths.GetTextureID(), 0, 0, 0, 0, m_Depths.GetWidth(), m_Depths.GetHeight(), m_Depths.GetDepth(),
						ae::ToGLFormat( m_Depths.GetFormat() ), ae::ToGLType( m_Depths.GetFormat() ),  &DepthClear );
	AE_ErrorCheckOpenGLError();


	glClearTexSubImage( m_Positions.GetTextureID(), 0, 0, 0, 0, m_Positions.GetWidth(), m_Positions.GetHeight(), m_Positions.GetDepth(),
						ae::ToGLFormat( m_Positions.GetFormat() ), ae::ToGLType( m_Positions.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();


	glClearTexSubImage( m_Materials.GetTextureID(), 0, 0, 0, 0, m_Materials.GetWidth(), m_Materials.GetDepth(), 1,
						ae::ToGLFormat( m_Materials.GetFormat() ), ae::ToGLType( m_Materials.GetFormat() ), nullptr );
	AE_ErrorCheckOpenGLError();


	glClear( GL_DEPTH_BUFFER_BIT );
	AE_ErrorCheckOpenGLError();

	// Be sure the textures are ready before starting store pass.
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();
}

void KBuffer::Draw( const ae::Drawable& _Object, ae::Camera* _Camera )
{
	if( !_Object.IsEnabled() )
		return;

	if( !CheckCountPrimitive( _Object.GetIndicesCount(), _Object.GetPrimitiveType() ) )
	{
		AE_LogWarning( "Count of indices do not fit with the primitive. Object will not be drawn." );
		return;
	}


	if( _Camera == nullptr && !Aero.HasCamera() )
	{
		AE_LogWarning( "No valid camera to use for rendering. Object will not be drawn." );
		return;
	}

	ae::Camera& CurrentCamera = _Camera != nullptr ? *_Camera : Aero.GetCamera();

	const ae::Material& ObjectMaterial = _Object.GetMaterial();

	// Call user event.
	_Object.OnDrawBegin( *this );

	// Use the store pass shader to store the K nearest fragment into the 3D textures..
	m_StorePassShader.Bind();

	// Apply the camera settings.
	CurrentCamera.SendToShader( m_StorePassShader );

	// Attach the K-Buffer textures.
	m_Semaphores.BindAsImage( 0 );
	m_Counts.BindAsImage( 1 );
	m_MaterialIndices.BindAsImage( 2 );
	m_Depths.BindAsImage( 3 );
	m_Materials.BindAsImage( 4 );
	m_Positions.BindAsImage( 5 );

	// Send K value to the shader.
	m_StorePassShader.SetInt( m_StorePassShader.GetUniformLocation( "K" ), Cast( Int32, m_K ) );

	// Attach the material shader to OpenGL and send its parameters.
	Uint32 TextureUnit = 0;
	Uint32 ImageUnit = 7;
	ObjectMaterial.SendParametersToShader( m_StorePassShader, TextureUnit, ImageUnit );

	// Send object transform if there is.
	_Object.SendTransformToShader( m_StorePassShader );

	
	// Draw the object with the bound shader.
	DrawVertexArray( _Object, _Object.GetPrimitiveType() );


	// Clear the shader from OpenGL.
	m_StorePassShader.Unbind();


	// Call user event.
	_Object.OnDrawEnd( *this );
}

void KBuffer::Resolve( ae::Framebuffer& _Target, Bool _ClearTarget, const ae::Color& _BackgroundColor, ae::Camera* _Camera )
{
	if( _Camera == nullptr && !Aero.HasCamera() )
	{
		AE_LogWarning( "No valid camera to use for clear pass." );
		return;
	}

	// Be sure the store pass is finished before start the resolve pass.
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
	AE_ErrorCheckOpenGLError();

	_Target.Bind();

	if( _ClearTarget )
		_Target.Clear( _BackgroundColor );

	// Sort the fragment and process the final color the pixel.
	m_ResolvePassShader.Bind();

	// Apply the camera settings.
	ae::Camera& CurrentCamera = _Camera != nullptr ? *_Camera : Aero.GetCamera();
	CurrentCamera.SendToShader( m_ResolvePassShader );

	// Attach the K-Buffer textures.
	m_Semaphores.BindAsImage( 0, ae::TextureImageBindMode::ReadOnly );
	m_Counts.BindAsImage( 1, ae::TextureImageBindMode::ReadOnly );
	m_MaterialIndices.BindAsImage( 2, ae::TextureImageBindMode::ReadOnly );
	m_Depths.BindAsImage( 3, ae::TextureImageBindMode::ReadOnly );
	m_Materials.BindAsImage( 4, ae::TextureImageBindMode::ReadOnly );
	m_Positions.BindAsImage( 5, ae::TextureImageBindMode::ReadOnly );


	// Other needed data for the final color processing.

	m_ResolvePassShader.SetColor( m_ResolvePassShader.GetUniformLocation( "BackgroundColor" ), _BackgroundColor );

	m_ResolvePassShader.SetBool( m_ResolvePassShader.GetUniformLocation( "ToneMap" ), m_IsToneMapped );
	m_ResolvePassShader.SetFloat( m_ResolvePassShader.GetUniformLocation( "Exposure" ), m_Exposure );

	m_ResolvePassShader.SetBool( m_ResolvePassShader.GetUniformLocation( "GammaCorrection" ), m_IsGammaCorrected );
	m_ResolvePassShader.SetFloat( m_ResolvePassShader.GetUniformLocation( "Gamma" ), m_Gamma );
	

	// Draw a fullscreen quad to process stored fragments.
	DrawVertexArray( m_FullscreenSprite, m_FullscreenSprite.GetPrimitiveType() );

	m_ResolvePassShader.Unbind();

	_Target.Unbind();
}

void KBuffer::ToEditor()
{
	ae::Resource::ToEditor();
	KBufferToEditor( *this );
}
