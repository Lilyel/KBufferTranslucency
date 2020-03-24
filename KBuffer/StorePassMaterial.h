#pragma once

#include <API/Code/Graphics/Material/Material.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterColor.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterBool.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterFloat.h>
#include <API/Code/Graphics/Shader/ShaderParameter/ShaderParameterInt.h>

class KBuffer;

/// <summary>
/// Material used for the store pass of the K-Buffer.<para/>
/// It is a simple material that allow a simple color and transparency or translucency effet.
/// </summary>
class StorePassMaterial : public ae::Material
{
public:
	/// <summary>Create material with the default values for the parameters.</summary>
	StorePassMaterial();

	/// <summary>Get the material index parameter used to store this material data in the K-Buffer.</summary>
	/// <returns>The material index parameter to represents where the material is stored in the K-Buffer.</returns>
	const ae::ShaderParameterInt& GetMaterialIndex() const;

	/// <summary>Color parameter for the surface color of the object.</summary>
	/// <returns>The surface color.</returns>
	ae::ShaderParameterColor& GetBaseColor();

	/// <summary>Color parameter for the surface color of the object.</summary>
	/// <returns>The surface color.</returns>
	const ae::ShaderParameterColor& GetBaseColor() const;

	/// <summary>Boolean parameter to determine if the the object is translucent or transparent.</summary>
	/// <returns>True if the object is translucent, False if the object is transparent.</returns>
	ae::ShaderParameterBool& GetIsTranslucent();

	/// <summary>Boolean parameter to determine if the the object is translucent or transparent.</summary>
	/// <returns>True if the object is translucent, False if the object is transparent.</returns>
	const ae::ShaderParameterBool& GetIsTranslucent() const;


	/// <summary>
	/// Color parameter to set the color at the max thickness<para/>
	/// used only for translucent objects.
	/// </summary>
	/// <returns>The color parameter of the translucent color at the max thickness.</returns>
	ae::ShaderParameterColor& GetTranslucentColor();

	/// <summary>
	/// Color parameter to set the color at the max thickness<para/>
	/// used only for translucent objects.
	/// </summary>
	/// <returns>The color parameter of the translucent color at the max thickness.</returns>
	const ae::ShaderParameterColor& GetTranslucentColor() const;


	/// <summary>
	/// Float parameter to process the physical extinction.<para/>
	/// The color of the object at this thickness will be the translucent color.<para/>
	/// used only for translucent objects.
	/// </summary>
	/// <returns>The maximum thickness of the object.</returns>
	ae::ShaderParameterFloat& GetMaxTranslucentThickness();

	/// <summary>
	/// Float parameter to process the physical extinction.<para/>
	/// The color of the object at this thickness will be the translucent color.<para/>
	/// used only for translucent objects.
	/// </summary>
	/// <returns>The maximum thickness of the object.</returns>
	const ae::ShaderParameterFloat& GetMaxTranslucentThickness() const;
	

	/// <summary>Retrieve the number of this material created.</summary>
	/// <returns>The number of this material created.</returns>
	static Int32 GetStorePassMaterialCount();

private:
	/// <summary>Index of the this store pass material.</summary>
	ae::ShaderParameterInt* m_MaterialIndex;

	/// <summary>Surface color of the object.</summary>
	ae::ShaderParameterColor* m_BaseColor;

	/// <summary>Is the object is translucent or just transparent ?</summary>
	ae::ShaderParameterBool* m_IsTranslucent;

	/// <summary>Color of the interior of the object in case of translucent objects.</summary>
	ae::ShaderParameterColor* m_TranslucentColor;

	/// <summary>
	/// Max thickness of translucent objects. <para/>
	/// The color of the interior of the object will be interpolated between the translucent color and the base color,
	/// the color will be the translucent color if the thickness is bigger than this parameter.
	/// </summary>
	ae::ShaderParameterFloat* m_MaxTranslucentThickness;


	/// <summary>Count of store pass materials.</summary>
	static Int32 MAT_INDEX;
};
