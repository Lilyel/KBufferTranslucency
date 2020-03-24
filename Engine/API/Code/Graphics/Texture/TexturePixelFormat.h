#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Dependencies/OpenGL.h"

#include <string>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Format of the pixel in texture.<para/>
	/// Depth will be automatically set to GL_DEPTH_COMPONENT.
	/// DepthStencil will be automatically set to GL_DEPTH24_STENCIL8 (24 for depth and 8 for stencil).
	/// </summary>
	enum class TexturePixelFormat : Uint32
	{
		/// <summary>One channel, unsigned byte.</summary>
		Red_U8,
		/// <summary>One channel, unsigned short.</summary>
		Red_U16,
		/// <summary>One channel, unsigned int.</summary>
		Red_U32,
		/// <summary>One channel, half float.</summary>
		Red_F16,
		/// <summary>One channel, float.</summary>
		Red_F32,

		/// <summary>One channel, unsigned byte, not normalized.</summary>
		Red_U8_NOTNORM,
		/// <summary>One channel, unsigned short, not normalized.</summary>
		Red_U16_NOTNORM,
		/// <summary>One channel, unsigned int, not normalized.</summary>
		Red_U32_NOTNORM,

		/// <summary>Two channel : Red and green, unsigned byte.</summary>
		RedGreen_U8,
		/// <summary>Two channel : Red and green, unsigned short.</summary>
		RedGreen_U16,
		/// <summary>Two channel : Red and green, unsigned short.</summary>
		RedGreen_U32,
		/// <summary>Two channel : Red and green, half float.</summary>
		RedGreen_F16,
		/// <summary>Two channel : Red and green, float.</summary>
		RedGreen_F32,

		/// <summary>RGB channels, unsigned byte.</summary>
		RGB_U8,
		/// <summary>RGB channels, unsigned short.</summary>
		RGB_U16,
		/// <summary>RGB channels, unsigned int.</summary>
		RGB_U32,
		/// <summary>RGB channels, half float.</summary>
		RGB_F16,
		/// <summary>RGB channels, float.</summary>
		RGB_F32,

		/// <summary>RGB channels, unsigned byte, rgb8 format for image binding.</summary>
		RGB_U8_FLOATIMAGE,

		/// <summary>RGBA channels, unsigned byte.</summary>
		RGBA_U8,
		/// <summary>RGBA channels, unsigned short.</summary>
		RGBA_U16,
		/// <summary>RGBA channels, unsigned int.</summary>
		RGBA_U32,
		/// <summary>RGBA channels, half float.</summary>
		RGBA_F16,
		/// <summary>RGBA channels, float.</summary>
		RGBA_F32,

		/// <summary>RGBA channels, unsigned byte, rgba8 format for image binding.</summary>
		RGBA_U8_FLOATIMAGE,

		/// <summary>Gamma corrected RGB channels, unsigned byte.</summary>
		sRGB_U8,
		/// <summary>Gamma corrected RGBA channels, unsigned byte.</summary>
		sRGBA_U8,

		/// <summary>One depth channel, float.</summary>
		Depth_F32,

		/// <summary>Combination of depth and stencil into one channel, unsigned int splitted with 24 bits for the depth and 8 bits for the stencil.</summary>
		DepthStencil_U24_U8,

		/// <summary>Number of available pixel format.</summary>
		Count,

		/// <summary>Default format when creation a texture.</summary>
		DefaultTexture = RGBA_U8,

		/// <summary>Invalid format.</summary>
		Unknown
	};

	/// <summary>Convert a TexturePixelFormat to a value for "internal format" parameter in OpenGL calls.</summary>
	/// <param name="_Format">The value to convert.</param>
	/// <returns>The OpenGL internal format value that correspond to the format.</returns>
	AERO_CORE_EXPORT GLint ToGLInternalFormat( TexturePixelFormat _Format );

	/// <summary>Convert a TexturePixelFormat to a value for "internal format" parameter in OpenGL glBindImageTexture calls.</summary>
	AERO_CORE_EXPORT GLint ToGLImageFormat( TexturePixelFormat _Format );

	/// <summary>Convert a TexturePixelFormat to a value for "format" parameter in OpenGL calls.</summary>
	/// <param name="_Format">The value to convert.</param>
	/// <returns>The OpenGL format value that correspond to the format.</returns>
	AERO_CORE_EXPORT GLint ToGLFormat( TexturePixelFormat _Format );

	/// <summary>Convert a TexturePixelFormat to a value for "type" parameter in OpenGL calls.</summary>
	/// <param name="_Format">The value to convert.</param>
	/// <returns>The OpenGL type value that correspond to the format.</returns>
	AERO_CORE_EXPORT GLint ToGLType( TexturePixelFormat _Format );


	/// <summary>Find the number of channel that correspond the TexturePixelFormat.</summary>
	/// <param name="_Format">The value to process.</param>
	/// <returns>The number of channel that correspond to the format.</returns>
	AERO_CORE_EXPORT Uint8 GetChannelsCount( TexturePixelFormat _Format );


	/// <summary>Convert a TexturePixelFormat to a string value.</summary>
	/// <param name="_Format">The value to convert.</param>
	/// <returns>The string conversion of the value.</returns>
	AERO_CORE_EXPORT std::string ToString( TexturePixelFormat _Format );
}
