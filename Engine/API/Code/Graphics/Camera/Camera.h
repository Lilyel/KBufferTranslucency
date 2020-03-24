#ifndef _CAMERA_AERO_H_
#define _CAMERA_AERO_H_

#include "../../Toolbox/Toolbox.h"

#include "../../Maths/Transform/Transform.h"
#include "../../Maths/Primitives/TRect.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../World/WorldObject/WorldObject.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Represent a 3D camera.<para/>
	/// A camera represent a point of view. It also holds the projection 
	/// matrix that we use for the rendering.<para/>
	/// The rendering can change according to the settings of the camera 
	/// (field of view, aspect ratio, type of projection ... ).
	/// </summary>
	class AERO_CORE_EXPORT Camera : public Transform, public WorldObject
	{
	public:
		/// <summary>Type of projection to use in the camera.</summary>
		enum class ProjectionType : Uint8
		{
			/// <summary>3D perspective project. Classic for 3D rendering.</summary>
			Perspective,

			/// <summary>Orthographic project. Classic for 2D rendering.</summary>
			Orthographic
		};

        /// <summary>Type of control of the camera (constraints on rotation, orbit, total freedom ...).</summary>
        enum class ControlType : Uint8
        {
            /// <summary>No constraints on movement.</summary>
            Free,

            /// <summary>Roll rotation will always be 0.</summary>
            FPS,

            /// <summary>Will rotate around a position and move around it. No roll rotation.</summary>
            Orbit
        };

		/// <summary>
		/// Projection settings for the camera. <para/>
		/// The field of view is an angle in radians representing the "opening" of the camera cone. <para/>
		/// The aspect is the ratio width / height of the camera frame. <para/>
		/// The near distance is the closest distance at which the camera can see objects. <para/>
		/// The far distance is the farest distance at which the camera can see ojects.
		/// </summary>
		struct AERO_CORE_EXPORT ProjectionSettings
		{
			/// <summary>
			/// Default settings. <para/>
			/// Set the field of view to 45 degrees, the aspect to 1 (square),
			/// the near distance to 1 and the far distance to 1000.
			/// </summary>
			ProjectionSettings() :
				FieldOfView( ae::Math::DegToRad_Const( 45.0f ) ),
				Aspect( 1.0f ),
				Near( 1.0f ),
				Far( 1000.0f )
			{
			}

			/// <summary>Constructor with user settings.</summary>
			/// <param name="_FieldOfView">Angle in radians of the field of view.</param>
			/// <param name="_Aspect">The aspect ratio of the camera frame (width / height).</param>
			/// <param name="_Near">The closest distance at which the camera can see objects.</param>
			/// <param name="_Far">The farest distance at which the camera can see objects.</param>
			ProjectionSettings( float _FieldOfView, float _Aspect, float _Near, float _Far ) :
				FieldOfView( _FieldOfView ),
				Aspect( _Aspect ),
				Near( _Near ),
				Far( _Far )
			{
			}


			/// <summary>Angle in radians representing the "opening" of the camera cone.</summary>
			float FieldOfView;

			/// <summary>Ratio width / height of the camera frame.</summary>
			float Aspect;

			/// <summary>Closest distance at which the camera can see objects.</summary>
			float Near;

			/// <summary>Farest distance at which the camera can see ojects.</summary>
			float Far;
		};

	public:        
        /// <summary>
        /// Default constructor.<para/>
        /// If <paramref name="_ProjectionType"/> is specified, the default settings for 
        /// projection type will be applied. <para/>
        /// Perspective : 45° FoV, Window viewport if it's already created, 0.001 near and 1000 far distance. <para/>
        /// Orthographic : Window viewport if it's already created, 0.001 near and 10 far distance <para/>
        /// </summary>
        /// <param name="_ProjectionType">Type of projection of the new camera.</param>
        Camera( ProjectionType _ProjectionType = ProjectionType::Perspective );

        /// <summary>Build a camera from several settings like a viewport, type of projection and the projection settings.</summary>
        /// <param name="_Viewport">Determine the size of the camera screen.</param>
        /// <param name="_ProjectionType">The type of the projection (orthographic or perspective).</param>
        /// <param name="_Settings">Settings for the projection.</param>
		Camera( const FloatRect& _Viewport, const ProjectionType& _ProjectionType, const ProjectionSettings& _Settings = ProjectionSettings() );

        /// <summary>
        /// Create perspective camera with default parameters. <para/>
        /// ( 45° FoV, Window viewport if it's already created, 0.001 near and 1000 far distance ).
        /// </summary>
        void SetToDefaultPerspectiveCamera();

        /// <summary>
        /// Create orthographic camera with default parameters.<para/>
        /// (Window viewport if it's already created, 0.001 near and 10 far distance ).
        /// </summary>
        void SetToDefaultOrthographicCamera();

        /// <summary>Change the field of view of the camera (angle in radians).</summary>
        /// <param name="_FieldOfView">New value for the field of view (angle in radians).</param>
		void SetFieldOfView( float _FieldOfView );

		/// <summary>Retrieve the field of view of the camera (angle in radians).</summary>
		/// <returns>The field of view of the camera (angle in radians).</returns>
		float GetFieldOfView() const;


		/// <summary>Change the aspect ratio avec the camera (width / height).</summary>
		/// <param name="_Aspect">The new aspect ratio of the camera.</param>
		void SetAspect( float _Aspect );
		
		/// <summary>Retrieve the aspect ratio avec the camera (width / height).</summary>
		/// <returns>The aspect ratio avec the camera (width / height).</returns>
		float GetAspect() const;

		/// <summary>
		/// Change nearest distance at which the camera can see. <para/>
		/// Objects nearer to this distance will not be visible.
		/// </summary>
		/// <param name="_Near">The new minimum distance for camera to see objects.</param>
		void SetNear( float _Near );

		/// <summary>
		/// Retrieve the nearest distance at which the camera can see. <para/>
		/// Objects nearer to this distance will not be visible.
		/// </summary>
		/// <returns>The minimum distance for camera to see objects.</returns>
		float GetNear() const;


		/// <summary>
		/// Change farest distance at which the camera can see. <para/>
		/// Objects further to this distance will not be visible.
		/// </summary>
		/// <param name="_Far">The new maximum distance for camera to see objects.</param>
		void SetFar( float _Far );

		/// <summary>
		/// Retrieve the farest distance at which the camera can see. <para/>
		/// Objects further to this distance will not be visible.
		/// </summary>
		/// <returns>The maximum distance for camera to see objects.</returns>
		float GetFar() const;

		/// <summary>
		/// Retrieve the projection settings of the camera. 
		/// (Aspect ratio, field of view, near distance, far distance).
		/// </summary>
		/// <returns>The camera projection settings.</returns>
		const ProjectionSettings& GetProjectionSettings() const;

		/// <summary>
		/// Change the projection settings of the camera.
		/// (Aspect ratio, field of view, near distance, far distance).
		/// </summary>
		/// <param name="_Settings">The camera projection settings to apply.</param>
		void SetProjectionSettings( const ProjectionSettings& _Settings );


		/// <summary>
		/// Change the viewport of the camera. <para/>
		/// The viewport is the "frame" of the camera. (Shape and size). <para/>
		/// Aspect will automaticaly be updated with the given <paramref name="_Viewport"/>.
		/// </summary>
		/// <param name="_Viewport">The new viewport to apply.</param>
		void SetViewport( const FloatRect& _Viewport );

		/// <summary>
		/// Retrieve the viewport of the camera. <para/>
		/// The viewport is the "frame" of the camera. (Shape and size).
		/// </summary>
		/// <returns>The current viewport of the camera.</returns>
		const FloatRect& GetViewport() const;


		/// <summary>Change the type of projection of the camera.</summary>
		/// <param name="_Type">The new type of projection to apply.</param>
		void SetProjectionType( ProjectionType _Type );

		/// <summary>Retrieve the current type of projection of the camera.</summary>
		/// <returns>The current type of projection of the camera.</returns>
		ProjectionType GetProjectionType() const;

		/// <summary>Retrieve the current projection matrix of the camera.</summary>
		/// <returns>The current projection matrix of the camera.</returns>
		const Matrix4x4& GetProjectionMatrix();

		/// <summary>
		/// Retrieve the current look at matrix of the camera. <para/>
		/// This matrix represent the orientation of the camera.
		/// </summary>
		/// <returns>The current look at matrix of the camera.</returns>
		const Matrix4x4& GetLookAtMatrix();


        /// <summary>Set the camera control to ControlType::Free.</summary>
        void SetControlToFree();

        /// <summary>Set the camera control to ControlType::FPS.</summary>
        void SetControlToFPS();

        /// <summary>Set the camera control to ControlType::Orbit.</summary>
        /// <param name="_OrbitCenter">
        /// The orbite center of the camera.<para/>
        /// The camera will rotate and move around this position.
        /// </param>
        void SetControlToOrbit( const Vector3& _OrbitCenter );

        /// <summary>Retrieve the type of control applied to the camera.</summary>
        /// <returns>Camera's control type.</returns>
        ControlType GetControlType() const;

        /// <summary>Retrieve the distance between the camera and the orbit center.</summary>
        /// <returns>The distance between the camera and the orbit center.</returns>
        float GetOrbitDistance() const;

        /// <summary>Set the distance between the camera and the orbit center.</summary>
        /// <param name="_Distance">The new distance between the camera and the orbit center to respect.</param>
        void SetOrbitDistance( float _Distance );

		/// <summary>
		/// Retrieve the point that the camera look at.<para/>
		/// </summary>
		/// <returns>Orbit center if camera is set to orbit, closest point in front of the camera otherwise.</returns>
		Vector3 GetLookAtPoint();
		
        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor() override;

		/// <summary>
		/// Set shader uniform with camera composant. <para/>
		/// Set the OpenGL viewport with the camera viewport.</summary>
		/// <param name="_Shader">The shader to send the camera to.</param>
		void SendToShader( const class Shader& _Shader );

	protected:
		/// <summary>
		/// Callback implemented from Transform. <para/>
		/// It signals that the tranform (position, rotation or scale) has changed. <para/>
		/// Here, we simply add a signal that the look at matrix must be updated too.
		/// </summary>
		void OnTransformChanged() override;

		/// <summary>
		/// Callback implemented from Transform. <para/>
		/// It signals that the tranform is now up to date. <para/>
		/// If the transform has changed, we update the look at matrix.
		/// </summary>
		void OnTransformUpdated() override;

	private:
		/// <summary>Update the projection matrix with the current settings.</summary>
		void UpdateProjectionMatrix();
		/// <summary>Update the look at matrix with the current transform.</summary>
		void UpdateLookAtMatrix();

	private:
		/// <summary>
		/// Settings that define the projection
		/// (aspect ratio, field of view, nearest distance, farest distance). <para/>
		/// We use theses settings to build the projection matrix.
		/// </summary>
		ProjectionSettings m_Settings;
		/// <summary>Rectangle that define the shape and the size of the camera.</summary>
		FloatRect m_Viewport;
		/// <summary>Define the type of projection of the camera (also used to build the projection matrix).</summary>
		ProjectionType m_ProjectionType;

        /// <summary>Type of control of the camera.</summary>
        ControlType m_ControlType;

		/// <summary>Signal to know if we must rebuild the projection matrix before returning it.</summary>
		Bool m_UpdateProjectionMatrix;
		/// <summary>Matrix that hold the projection with the current settings.</summary>
		Matrix4x4 m_ProjectionMatrix;

		/// <summary>Signal to know if we must rebuild the look at matrix once the transform is updated.</summary>
		Bool m_UpdateLookAtMatrix;
		/// <summary>Matrix that hold the orientation of the camera.</summary>
		Matrix4x4 m_LookAtMatrix;

        /// <summary>Point to look at when camera is set to orbit.</summary>
        Vector3 m_OrbitCenter;

        /// <summary>Distance to respect between the camera and the orbit center.</summary>
        float m_OrbitDistance;
	};

} // ae

#endif