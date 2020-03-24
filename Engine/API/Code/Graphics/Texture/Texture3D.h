#pragma once

#include "../../Toolbox/Toolbox.h"
#include "Texture.h"

namespace ae
{
	class FramebufferAttachement;

	/// \ingroup graphics
	/// <summary>
	/// 3D samplable data that can be link to a shader to be rendered.
	/// </summary>
	class AERO_CORE_EXPORT Texture3D : public Texture
	{
	public:
		/// <summary>Create an empty texture 3D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		Texture3D( Uint32 _Width, Uint32 _Height, Uint32 _Depth, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings..</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		Texture3D( Uint32 _Width, Uint32 _Height, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement );


		/// <summary>Create an empty texture 3D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_Format">Format of the texture : channels, type.</param>
		void Set( Uint32 _Width, Uint32 _Height, Uint32 _Depth, TexturePixelFormat _Format = TexturePixelFormat::DefaultTexture );

		/// <summary>Create an empty texture with framebuffer attachement settings..</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		/// <param name="_FramebufferAttachement">Settings to apply.</param>
		void Set( Uint32 _Width, Uint32 _Height, Uint32 _Depth, const FramebufferAttachement& _FramebufferAttachement );


		/// <summary>Resize the texture 1D.</summary>
		/// <param name="_Width">The width of the texture.</param>
		/// <param name="_Height">The height of the texture.</param>
		/// <param name="_Depth">The depth of the texture.</param>
		void Resize( Uint32 _Width, Uint32 _Height, Uint32 _Depth );

		/// <summary>Get the width of the texture.</summary>
		/// <returns>Width of the texture.</returns>
		Uint32 GetWidth() const;

		/// <summary>Get the height of the texture.</summary>
		/// <returns>Height of the texture.</returns>
		Uint32 GetHeight() const;

		/// <summary>Get the depth of the texture.</summary>
		/// <returns>Depth of the texture.</returns>
		Uint32 GetDepth() const;

		/// <summary>Called by the framebuffer to attach the texture to it.</summary>
		void AttachToFramebuffer( const FramebufferAttachement& _Attachement ) const override;

		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		void ToEditor() override;

	private:
		/// <summary>Create an empty texture.</summary>
		virtual void SetupEmpty();
		
	protected:
		/// <summary>Width of the texture.</summary>
		Uint32 m_Width;

		/// <summary>Width of the texture.</summary>
		Uint32 m_Height;

		/// <summary>Depth of the texture (for 3D texture).</summary>
		Uint32 m_Depth;
	};

} // ae