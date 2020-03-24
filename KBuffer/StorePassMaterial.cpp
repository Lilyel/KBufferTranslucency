#include "StorePassMaterial.h"

#include "KBuffer.h"

#include <API/Code/Graphics/Color/Color.h>

Int32 StorePassMaterial::MAT_INDEX = 0;

StorePassMaterial::StorePassMaterial() :
	m_MaterialIndex( nullptr ),
	m_BaseColor( nullptr ),
	m_IsTranslucent( nullptr ),
	m_TranslucentColor( nullptr ),
	m_MaxTranslucentThickness( nullptr )
{
	m_MaterialIndex = AddIntParameterToMaterial( "Material Index", "MaterialIndex", MAT_INDEX, MAT_INDEX, MAT_INDEX );
	MAT_INDEX++;

	m_BaseColor = AddColorParameterToMaterial( "Base Color", "BaseColor", ae::Color::White );

	m_IsTranslucent = AddBoolParameterToMaterial( "Is Translucent", "IsTranslucent", False );

	m_TranslucentColor = AddColorParameterToMaterial( "Translucent Color", "TranslucentColor", ae::Color::White );

	m_MaxTranslucentThickness = AddFloatParameterToMaterial( "Max Translucent Thickness", "MaxTranslucentThickness", 0.0f, 0.0f );
}

const ae::ShaderParameterInt& StorePassMaterial::GetMaterialIndex() const
{
	return *m_MaterialIndex;
}

ae::ShaderParameterColor& StorePassMaterial::GetBaseColor()
{
	return *m_BaseColor;
}

const ae::ShaderParameterColor& StorePassMaterial::GetBaseColor() const
{
	return *m_BaseColor;
}

ae::ShaderParameterBool& StorePassMaterial::GetIsTranslucent()
{
	return *m_IsTranslucent;
}

const ae::ShaderParameterBool& StorePassMaterial::GetIsTranslucent() const
{
	return *m_IsTranslucent;
}

ae::ShaderParameterColor& StorePassMaterial::GetTranslucentColor()
{
	return *m_TranslucentColor;
}

const ae::ShaderParameterColor& StorePassMaterial::GetTranslucentColor() const
{
	return *m_TranslucentColor;
}

ae::ShaderParameterFloat& StorePassMaterial::GetMaxTranslucentThickness()
{
	return *m_MaxTranslucentThickness;
}

const ae::ShaderParameterFloat& StorePassMaterial::GetMaxTranslucentThickness() const
{
	return *m_MaxTranslucentThickness;
}

Int32 StorePassMaterial::GetStorePassMaterialCount()
{
	return MAT_INDEX;
}
