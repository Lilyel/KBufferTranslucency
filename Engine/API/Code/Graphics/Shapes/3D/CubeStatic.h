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
		/// Simple 3D colored cube.
		/// </summary>
		/// <seealso cref="MeshStatic" />
		/// <seealso cref="Drawable" />
		class AERO_CORE_EXPORT CubeStatic : public MeshStatic
		{
		public:
			/// <summary>Create a colored cube with a side size.</summary>
			/// <param name="_Size">The size of cube side size.</param>
			CubeStatic( const float _Size = 1.0f );


			/// <summary>Set the side size of the cube.</summary>
			/// <param name="_Size">The new size to apply.</param>
			void SetSize( const float _Size );

            /// <summary>Retrieve the size of the cube.</summary>
            /// <returns>The size of the cube.</returns>
            float GetSize() const;
			
		private:
			/// <summary>Setup the normales of the cubes.</summary>
			void SetupNormales();

			/// <summary>Setup the normales of the cubes.</summary>
			void SetupUVs();

            /// <summary>Size of the cube.</summary>
            float m_Size;
		};

	} // Shape
} // ae
