#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"
#include "../Matrix/Matrix4x4.h"

namespace ae
{
	/// \ingroup math
	/// <summary>
	/// Represent a rotation in 3D space.<para/>
	/// Contains angles on each 3D axis and the director hand ( Look, Up, Right ).<para/>
	/// Follow the Right Handed rules.
	/// </summary>
	class AERO_CORE_EXPORT Rotator
	{
	public:
		/// <summary>Default constructor.</summary>
		Rotator();

		/// <summary>Construct a rotation with 3 angles.</summary>
		/// <param name="_Pitch">Angle to apply around the Right of the rotator.</param>
		/// <param name="_Yaw">Angle to apply around the Up of the rotator.</param>
		/// <param name="_Roll">Angle to apply around the Look of the rotator.</param>
		Rotator( float _Pitch, float _Yaw, float _Roll );

		/// <summary>Reset Angles and replace the Right, Up and Look to the world axis corresponding.</summary>
		void Reset();

		/// <summary>Get the Right axis of the rotator.</summary>
		/// <returns>Right of the rotator.</returns>
		const Vector3& GetRight() const;

		/// <summary>Get the Up axis of the rotator.</summary>
		/// <returns>Up of the rotator.</returns>
		const Vector3& GetUp() const;
		
		/// <summary>Get the Look axis of the rotator ( also called Forward ).</summary>
		/// <returns>Look of the rotator.</returns>
		const Vector3& GetLook() const;

		
		/// <summary>Apply a rotation around the Right of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the Right.</param>
		void Pitch( float _Angle );
		

		/// <summary>Apply a rotation around the Up of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the Up.</param>
		void Yaw( float _Angle );
		
		/// <summary>Apply a rotation around the Look of the rotator.</summary>
		/// <param name="_Angle">Angle to apply around the Look.</param>
		void Roll( float _Angle );

		/// <summary>
		/// Override current rotation, and apply new angles.<para/>
		/// Apply X, Y then Z. <para/>
		/// Experiemental. Not tested.
		/// </summary>
		/// <param name="_Angles">Angles to apply around on each axis ( X = Right, Y = Up, Z = Look ).</param>
		void SetAngles( const Vector3& _Angles );
		
		/// <summary>Retrieve angles on each axis.</summary>
		/// <returns>Vector containing all angles ( X = Pitch, Y = Yaw, Z = Roll ).</returns>
		const Vector3& GetAngles() const;


		/// <summary>Retrieve the matrix representing the rotation.</summary>
		/// <returns>Rotation matrix.</returns>
		Matrix4x4 GetMatrix();
		
		/// <summary>Retrieve the transposed matrix representing the rotation.</summary>
		/// <returns>Transposed rotation matrix.</returns>
		Matrix4x4 GetMatrixTransposed();

		/// <summary>
		/// Combine two rotation.<para/>
		/// Experiemental. Not Tested.
		/// </summary>
		/// <param name="_Rotation1">First rotation to combine.</param>
		/// <param name="_Rotation2">Second rotation to combine.</param>
		/// <returns>Rotation representing the combination of _Rotation1 and _Rotation2.</returns>
		static Rotator Combine( Rotator _Rotation1, Rotator _Rotation2 );

    private:
        /// <summary>Update Look, right and up axis.</summary>
        void UpdateAxis() const;

	protected:
		/// <summary>Angles on each axis ( X = Pitch, Y = Yaw, Z = Roll ).</summary>
		Vector3 m_Angles;

		/// <summary>The look axis of the rotation ( also called Forward ).</summary>
		mutable Vector3 m_Look;

		/// <summary>The right axis of the rotation.</summary>
		mutable Vector3 m_Right;

		/// <summary>The up axis of the rotation.</summary>
		mutable Vector3 m_Up;

        /// <summary>Set to true to update Look, right and up when retrieving them.</summary>
        mutable Bool m_UpdateAxis;
	};

} // ae
