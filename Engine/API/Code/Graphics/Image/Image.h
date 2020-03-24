#ifndef _IMAGE_AERO_H_
#define _IMAGE_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../../Resources/Resource/Resource.h"
#include "../Color/Color.h"
#include "../Texture/TexturePixelFormat.h"

#include "../Dependencies/OpenGL.h"

#include <string>
#include <vector>

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Store an array of pixels loaded from an RGBA image file.
	/// </summary>
	/// <seealso cref="Color"/>
	class AERO_CORE_EXPORT Image : public Resource
	{
	public:
		/// <summary>Color format of the picture.</summary>
		enum class Format : Uint8
		{
			/// <summary>Only one channel representing gray intensity.</summary>
			GeyScale = 1,
			/// <summary>Two channel representing gray intensity and alpha (transparency).</summary>
			GreyScale_Alpha = 2,
			/// <summary>Three channel representing red, blue and green intensity.</summary>
			RGB = 3,
			/// <summary>Four channel representing red, blue and green intensity and alpha (transparency).</summary>
			RGB_Alpha = 4
		};
		
		/// <summary>Algorithm used when resizing the image.</summary>
		enum class Filter : Uint8
		{
			/// <summary>Default algorithm (Catmull Rom or Mitchell depending if we upscaling or downscaling).</summary>
			Default = 0,

			/// <summary>"Box filter" : takes the same color as the neighbors.</summary>
			NearestNeighbour = 1,
			
			/// <summary>Billinear interpolation.</summary>
			Bilinear = 2,
			
			/// <summary>Cubic B-Spline interpolation. ("aka Mitchell-Netrevalli with B=1,C=0")</summary>
			CubicSpline = 3,
			
			/// <summary>Cubic B-Spline interpolation. ("aka Mitchell-Netrevalli with B=1,C=0")</summary>
			CatmullRom = 4,
			
			/// <summary>Mitchell interpolation. ("Mitchell-Netrevalli filter with B=1/3, C=1/3")</summary>
			Mitchell = 5
		};

	public:
		/// <summary>
		/// Create an empty (invalid) image.
		/// </summary>
		Image();


		/// <summary>
		/// Create a black image.
		/// </summary>
		/// <param name="_Width">The width of the image.</param>
		/// <param name="_Height">The height of the image.</param>
		/// <param name="_Format">The format of the image.</param>
		explicit Image( const Uint32 _Width, const Uint32 _Height, const Format _Format );

		/// <summary>Load an image file and store the pixels.</summary>
		/// <param name="_FileName">Name of the image file.</param>
		explicit Image( const std::string& _FileName );

		/// <summary>Copy constructor.</summary>
		/// <param name="_Copy">The image to copy.</param>
		Image( const Image& _Copy );

		/// <summary>If there is an image loaded, free the pixels.</summary>
		virtual ~Image();
		
		/// <summary>Copy operator</summary>
		/// <param name="_Copy">The image to copy.</param>
		/// <returns>The calling image with the data of <paramref name="_Copy">.</returns>
		Image& operator=( const Image& _Copy );

		/// <summary>Load an image file and store the pixels.</summary>
		/// <param name="_FileName">Name of the image file.</param>
		/// <returns>True if the loaded is completed, False if a problem happened.</returns>
		virtual Bool LoadFromFile( const std::string& _FileName );

		/// <summary>Copy pixels from memory.</summary>
		/// <param name="_Data">The data containing the pixels to copy.</param>
		/// <param name="_Width">The width of the image.</param>
		/// <param name="_Height">The height of the image.</param>
		/// <param name="_Format">The format f the image.</param>
		/// <returns>True if successfully loaded, False otherwise.</returns>
		Bool LoadFromMemory( const Uint8* _Data, const Uint32 _Width, const Uint32 _Height, const Format _Format );

		/// <summary>Gets the a particular pixel from the image loaded.</summary>
		/// <param name="_X">The index x of the pixel.</param>
		/// <param name="_Y">The index y of the pixel.</param>
		/// <returns>Color of the pixel at [<paramref name="_X"/>,<paramref name="_Y"/>] coordinates.</returns>
		Color GetPixel( const Uint32 _X, const Uint32 _Y ) const;

		/// <summary>Gets the a particular pixel from the image loaded.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <returns>Color of the pixel at <paramref name="_Index"/>.</returns>
		Color GetPixel( const Uint32 _Index ) const;

		/// <summary>Set the color of a pixel.</summary>
		/// <param name="_X">The index x of the pixel.</param>
		/// <param name="_Y">The index y of the pixel.</param>
		/// <param name="_Color">The new color of the pixel.</param>
		void SetPixel( const Uint32 _X, const Uint32 _Y, const Color& _Color );

		/// <summary>Set the color of a pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <param name="_Color">The new color of the pixel.</param>
		void SetPixel( const Uint32 _Index, const Color& _Color );

		/// <summary>Get the raw pixels array.</summary>
		/// <returns>Pixels as an raw array.</returns>
		const Uint8* GetData() const;


		/// <summary>Get the width of the image.</summary>
		/// <returns>Width of the image.</returns>
		Uint32 GetWidth() const;
		/// <summary>Get the height of the image.</summary>
		/// <returns>Height of the image.</returns>
		Uint32 GetHeight() const;

		/// <summary>Get the format of the image ( Greyscale, Greyscale + Alpha, RGB, RGBA )</summary>
		/// <returns>Format of the image</returns>
		Format GetFormat() const;

		/// <summary>Get the pixel format for setting the textures.</summary>
		/// <returns>Pixel format of the image</returns>
		virtual TexturePixelFormat GetTexturePixelFormat() const;

		/// <summary>Get the format of the image for OpenGL ( Greyscale, Greyscale + Alpha, RGB, RGBA )</summary>
		/// <returns>Format of the image for OpenGL.</returns>
		GLenum GetFormatOpenGL() const;

		/// <summary>
		/// Get the image channel count.
		/// 1 for greyscale, 2 for greyscale + alpha,
		/// 3 for RGB and 4 for RGBA.
		/// </summary>
		/// <returns>Image channel count.</returns>
		Uint32 GetChannelsCount() const;

		/// <summary>Saves the image to a file.</summary>
		/// <param name="_FileName">Name of the file.</param>
		/// <returns>True if sucessfully saved, False otherwise.</returns>
		virtual Bool SaveToFile( const std::string& _FileName ) const;

		/// <summary>Resize the image to a new size.</summary>
		/// <param name="_NewWidth">The new width.</param>
		/// <param name="_NewHeight">The new height.</param>
		/// <returns>True if successfully resized, False otherwise.</returns>
		virtual Bool Resize( const Uint32 _NewWidth, const Uint32 _NewHeight );

		/// <summary>
		/// Path to the loaded image.<para/>
		/// Can be empty if image created from memory.
		/// </summary>
		/// <returns></returns>
		const std::string& GetFilePath() const;


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor();
		
	protected : 
		/// <summary>Reserve an array of pixel.</summary>
		/// <param name="_Width">The width of the array to reserve.</param>
		/// <param name="_Height">The height of the array to reserve.</param>
		/// <param name="_ChannelsCount">The number of channels per pixel.</param>
		virtual void AllocatePixelsArray( const Uint32 _Width, const Uint32 _Height, const Uint32 _ChannelsCount );

		/// <summary>If the array is allocated, free it.</summary>
		virtual void DestroyPixelsArray();

		/// <summary>Copies from memory to the image buffer.</summary>
		/// <param name="_Pixels">The pixels to copy.</param>
		virtual void CopyPixels( const Uint8* _Pixels );

		/// <summary>Get the pixel converted from image format (Greyscale, RGB, ... ) to RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <returns>The pixel as RGBA.</returns>
		virtual Color GetPixelConverted( const Uint32 _Index ) const;

		/// <summary>Set the pixel of the image format (Greyscale, RGB, ... ) from a RGBA pixel.</summary>
		/// <param name="_Index">The index of the pixel.</param>
		/// <param name="_Color">The color of the pixel to apply as RGBA.</param>
		virtual void SetPixelConverted( const Uint32 _Index, const Color& _Color );

	protected:
		/// <summary>The width of the image.</summary>
		Uint32 m_Width;
		/// <summary>The height of the image.</summary>
		Uint32 m_Height;
		/// <summary>Array of pixels of the image.</summary>
		std::vector<Uint8> m_Pixels;

		/// <summary>
		/// Image channels count.
		/// 1 for greyscale, 2 for greyscale + alpha,
		/// 3 for RGB and 4 for RGBA.
		/// </summary>
		Int32 m_ChannelsCount;

		/// <summary>
		/// Path to the loaded file.<para/>
		/// Empty if image created from memory.
		/// </summary>
		std::string m_FilePath;
	};

}; // ae

#endif