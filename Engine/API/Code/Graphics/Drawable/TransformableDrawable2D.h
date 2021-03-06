#pragma once

#include "../../Toolbox/Toolbox.h"

#include "Drawable.h"
#include "../../Maths/Transform/Transform2D.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Basic class to draw 2D transformable elements with OpenGL.
	/// </summary>
	class AERO_CORE_EXPORT TransformableDrawable2D : public Transform2D, public Drawable
	{
	public:
		/// <summary>
		/// Send the transform (3x3 matrix for TransformableDrawable2D, 4x4 matrix for TransformableDrawable3D) to the shader.
		/// The shader must be bound before calling this function.
		/// </summary>
		/// <param name="_Shader">Shader to send the parameters to.</param>
		void SendTransformToShader( const Shader& _Shader ) const override;
	};

} // ae
