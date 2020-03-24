#include "StorePassMaterial.h"
#include "KBuffer.h"

#include "API\Code\Includes.h"

void GetViewportWidthAndHeight( Uint32& _OutWidth, Uint32& _OutHeight, const ae::Camera& _Camera )
{
	const ae::FloatRect& ViewportRect = _Camera.GetViewport();

	_OutWidth = Cast( Uint32, ViewportRect.GetWidth() );
	_OutHeight = Cast( Uint32, ViewportRect.GetHeight() );
}

int main()
{
	// Call once to initialize everything.
	Aero;
    Aero.SetPathToEngineData( "../../../Data/Engine/" );

	ae::Camera Camera( ae::Camera::ProjectionType::Perspective );
	Camera.SetName( "Camera" );
	Camera.SetPosition( 0.0f, 0.5f, 3.0f );
	Camera.SetControlToOrbit( ae::Vector3( 0.0f, 0.5f, 0.0f ) );
	Camera.SetOrbitDistance( 3.0f );
	Camera.SetNear( 1.0f );
	Camera.SetFar( 30.0f );
	Aero.SetCamera( Camera );

	ae::Window MyWindow;
	MyWindow.Create();
	MyWindow.SetWindowTitle( "K-Buffer" );


	
	// Setup scene.


	// Translucent dragon.
	
	StorePassMaterial DragonMat;
	DragonMat.SetName( "Dragon Material" );
	DragonMat.GetIsTranslucent().SetValue( True );
	DragonMat.GetBaseColor().SetValue( ae::Color::Black );
	DragonMat.GetTranslucentColor().SetValue( ae::Color( 0.3f, 0.7f, 0.1f ) );
	DragonMat.GetMaxTranslucentThickness().SetValue( 0.02f );

	ae::MeshStatic Dragon( "../../../Data/KBuffer/Dragon/dragon.obj" );
	Dragon.SetName( "Dragon" );
	Dragon.SetPosition( 0.75f, 0.3f, 0.0f );
	Dragon.SetRotation( 0.0f, ae::Math::PiDivBy2(), 0.0f );
	Dragon.SetMaterial( DragonMat );


	// Transparent shader ball.
	
	StorePassMaterial ShaderBallMat;
	ShaderBallMat.SetName( "Shader Ball Material" );
	ShaderBallMat.GetBaseColor().SetValue( ae::Color( 0.7f, 0.0f, 0.7f, 0.3f ) );

	ae::MeshStatic ShaderBall( "../../../Data/KBuffer/ShaderBall/ShaderBall.obj" );
	ShaderBall.SetName( "Shader Ball" );
	ShaderBall.SetPosition( -0.75f, 0.001f, 0.0f );
	ShaderBall.SetRotation( 0.0f, -ae::Math::PiDivBy2(), 0.0f );
	ShaderBall.SetMaterial( ShaderBallMat );


	// Opaque ground.

	StorePassMaterial PlaneMat;
	PlaneMat.SetName( "Plane Material" );
	PlaneMat.GetBaseColor().SetValue( ae::Color::Yellow );

	ae::Shape::PlaneStatic Plane( 5.0f );
	Plane.SetName( "Plane" );
	Plane.SetMaterial( PlaneMat );



	// Setup the K-Buffer.

	Uint32 ViewportWidth;
	Uint32 ViewportHeight;
	GetViewportWidthAndHeight( ViewportWidth, ViewportHeight, Camera );

	KBuffer kBuffer( ViewportWidth, ViewportHeight, 16 );
	kBuffer.SetStorePassMaterialCount( StorePassMaterial::GetStorePassMaterialCount() );
	kBuffer.SetName( "K-Buffer" );

	kBuffer.Bind();
	kBuffer.SetCullingMode( ae::CullingMode::NoCulling );
	kBuffer.SetDepthMode( ae::DepthMode::NoDepthTest );
	kBuffer.Unbind();
	


	ae::UI::InitImGUI( MyWindow );
	ae::Editor Editor;	
	Editor.SetMSAASamplesCount( 0 );

	while( Aero.Update() )
	{
		// Update editor viewport.
		Editor.UpdateViewportSize();

		// Update K Buffer size.
		GetViewportWidthAndHeight( ViewportWidth, ViewportHeight, Camera );
		kBuffer.Resize( ViewportWidth, ViewportHeight );
		

		kBuffer.Bind();

		// Clear pass.
		kBuffer.ClearPass();

		// Store pass.
		kBuffer.Draw( Plane );
		kBuffer.Draw( Dragon );
		kBuffer.Draw( ShaderBall );

		kBuffer.Unbind();
		
		// Resolve pass.
		kBuffer.Resolve( Editor.GetViewport(), True, ae::Color::White );


		// Finalize viewport rendering.

		MyWindow.Clear( ae::Color::Black );
		ae::UI::NewFrame();
		Editor.Update();
		Editor.Show();
		ae::UI::RenderFrame();
		MyWindow.Render();
	}

	MyWindow.Destroy();

}