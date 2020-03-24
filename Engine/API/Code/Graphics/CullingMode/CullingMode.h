#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"


namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Culling mode to apply to renderers (cull back faces, front faces, ...).
	/// </summary>
	enum class CullingMode : GLenum
	{
		/// <summary>
		/// No face culling.
		/// </summary>
		NoCulling,

		/// <summary>
		/// Default value. <para/>
		/// The faces that don't face the camera will not be drawn.
		/// </summary>
		BackFaces,

		/// <summary>
		/// The faces that face the camera will not be drawn.
		/// </summary>
		FrontFaces,

		/// <summary>
		/// The faces that face and don't face the camera will not be drawn.
		/// </summary>
		BackAndFrontFaces,


		/// <summary>Invalid culling mode. For internal use only.</summary>
		Unknown
	};
}
