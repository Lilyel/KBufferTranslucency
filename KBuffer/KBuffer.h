#pragma once

#include <API/Code/Graphics/Texture/Texture2D.h>
#include <API/Code/Graphics/Texture/Texture2DArray.h>
#include <API/Code/Graphics/Texture/Texture1DArray.h>
#include <API/Code/Graphics/Framebuffer/Framebuffer.h>
#include <API/Code/Graphics/Framebuffer/FramebufferSprite.h>
#include <API/Code/Graphics/Shader/Shader.h>

/// <summary>
/// Render target that store up to K fragment.<para/>
/// During the store pass, objects can be drawn and the K nearest fragments are saved.<para/>
/// During the resolve pass, the K fragments are sorted and blended to get the final color.
/// </summary>
class KBuffer : public ae::Framebuffer, public ae::Resource
{
public:
	/// <summary>Build a K-Buffer to store, sort and blend <paramref name="_K"/> fragments.</summary>
	/// <param name="_Width">The width of the K-Buffer</param>
	/// <param name="_Height">The height of the K-Buffer.</param>
	/// <param name="_K">The maximum number of fragment to store.</param>
	KBuffer( Uint32 _Width, Uint32 _Height, Uint32 _K );

	/// <summary>Retrieve the maximum number of fragment that the K-Buffer can store.</summary>
	/// <returns>The maximum number of fragment to store.</returns>
	Uint32 GetK() const;

	/// <summary>Set the maximum number of fragment that the K-Buffer can store [1-16].</summary>
	/// <param name="_K">The new maximum number of fragment to store.</param>
	void SetK( Uint32 _K );


	/// <summary>Is the final color of the resolve pass must be tone mapped ?</summary>
	/// <returns>True if the K-Buffer apply the tone mapping, False otherwise.</returns>
	Bool IsToneMapped() const;

	/// <summary>Must the K-Buffer apply a tone map to the color of the resolve pass ?</summary>
	/// <param name="_IsGammaCorrected">True to apply tone mapping, False to not apply it.</param>
	void SetIsToneMapped( Bool _IsToneMapped );


	/// <summary>Retrieve the exposure of the tone mapping.</summary>
	/// <returns>The current exposure used for the tone mapping.</returns>
	float GetExposure() const;

	/// <summary>Set the exposure to use for the tone mapping.</summary>
	/// <param name="_Exposure">The new expose value to use for tone mapping.</param>
	void SetExposure( float _Exposure );


	/// <summary>Is the final color of the resolve pass must be corrected ?</summary>
	/// <returns>True if the K-Buffer apply the gamma correction, False otherwise.</returns>
	Bool IsGammaCorrected() const;

	/// <summary>Must the K-Buffer apply a gamma correction to the color of the resolve pass ?</summary>
	/// <param name="_IsGammaCorrected">True to apply gamma correction, False to not apply it.</param>
	void SetIsGammaCorrected( Bool _IsGammaCorrected );

	/// <summary>Retrieve the gamma for the gamma correcton.</summary>
	/// <returns>The current gamma used.</returns>
	float GetGamma() const;

	/// <summary>Set the gamma used for the gamma correction.</summary>
	/// <param name="_Gamma">The new gamma to use.</param>
	void SetGamma( float _Gamma );


	/// <summary>Set the number of materials to save in the store pass.</summary>
	/// <param name="_Count">Maximum number of materials storable.</param>
	void SetStorePassMaterialCount( Int32 _Count );

	/// <summary>Resize the K-Buffer and all its images.</summary>
	/// <param name="_Width">The new width of the K-Buffer.</param>
	/// <param name="_Height">The new Height of the K-Buffer.</param>
	void Resize( Uint32 _Width, Uint32 _Height ) override;

	/// <summary>Remove the stored data from the K-Buffer and reset semaphores and fragment counts.</summary>
	void ClearPass();

	/// <summary>Draw an object to the K-Buffer during the "store pass".</summary>
	/// <param name="_Object">The object to draw.</param>
	/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
	void Draw( const ae::Drawable& _Object, ae::Camera* _Camera = nullptr ) override;

	/// <summary>
	/// Resolve pass of the K-Buffer : <para/>
	/// Sort the stored fragments and blend them.
	/// </summary>
	/// <param name="_Target">The final texture to draw on.</param>
	/// <param name="_ClearTarget">Must the <paramref name="_Target"/> be clear ? (Color and depth will be cleared)</param>
	/// <param name="_BackgroundColor">The color to apply when (and if ) clearing the <paramref name="_Target"/></param>
	/// <param name="_Camera">Optionnal camera. If null, the current active camera will be taken.</param>
	void Resolve( ae::Framebuffer& _Target, Bool _ClearTarget, const ae::Color& _BackgroundColor = ae::Color::Black, ae::Camera* _Camera = nullptr );


	/// <summary>
	/// Function called by the editor.
	/// It allows the class to expose some attributes for user editing.
	/// Think to call all inherited class function too when overloading.
	/// </summary>
	void ToEditor() override;

private:	
	/// <summary>The maximum fragments that the K-Buffer can store.</summary>
	Uint32 m_K;


	/// <summary>The shader used to store the fragment of drawn objects into the K-Buffer.</summary>
	ae::Shader m_StorePassShader;

	/// <summary>The shader used to sort and blend the stored fragments.</summary>
	ae::Shader m_ResolvePassShader;


	/// <summary>K-Buffer semaphores ( 0 or 1 ).</summary>
	ae::Texture2D m_Semaphores;
	
	/// <summary>Count of fragments stored.</summary>
	ae::Texture2D m_Counts;

	/// <summary>Index of the material for each fragment stored.</summary>
	ae::Texture2DArray m_MaterialIndices;

	/// <summary>Depth of each fragment stored.</summary>
	ae::Texture2DArray m_Depths;

	/// <summary>Position of each fragment stored.</summary>
	ae::Texture2DArray m_Positions;

	/// <summary>Material datas for each different StorePassMaterial met.</summary>
	ae::Texture1DArray m_Materials;

	/// <summary>Sprite for fullscreen passes.</summary>
	ae::FramebufferSprite m_FullscreenSprite;


	/// <summary>Must the final color of the resolve pass be tone mapped ?</summary>
	Bool m_IsToneMapped;

	/// <summary>Exposure for the tone mapping.</summary>
	float m_Exposure;

	/// <summary>Must the final color of the resolve pass be converted to sRGB ?</summary>
	Bool m_IsGammaCorrected;

	/// <summary>Gamma to apply to convert the color to sRGB.</summary>
	float m_Gamma;
};