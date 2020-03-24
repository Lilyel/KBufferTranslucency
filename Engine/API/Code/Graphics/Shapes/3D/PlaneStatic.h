#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "../../Mesh/MeshStatic.h"

namespace ae
{
	class Window;

	namespace Shape
	{
		/// \ingroup graphics
		/// <summary>
		/// Simple 3D colored plane.<para/>
		/// The normal of the plane by default is the Y axis.
		/// </summary>
		/// <seealso cref="MeshStatic" />
		/// <seealso cref="Drawable" />
		class AERO_CORE_EXPORT PlaneStatic : public MeshStatic
		{
		public:
			/// <summary>Create a colored plane with a side size.</summary>
			/// <param name="_Size">The size of cube side size.</param>
			PlaneStatic( const float _Size = 1.0f );


			/// <summary>Set the side size of the plane.</summary>
			/// <param name="_Size">The new size to apply.</param>
			void SetSize( const float _Size );

			/// <summary>Retrieve the size of the plane.</summary>
			/// <returns>The size of the plane.</returns>
			float GetSize() const;

		private:
			/// <summary>Setup the normales of the plane.</summary>
			void SetupNormales();

			/// <summary>Setup the normales of the plane.</summary>
			void SetupUVs();

			/// <summary>Size of the plane.</summary>
			float m_Size;
		};

	} // Shape
} // ae
