#pragma once

#include "KBuffer.h"

#include <API/Code/UI/UI.h>
#include <API/Code/UI/Dependencies/IncludeImGui.h>
#include <API/Code/Maths/Functions/MathsFunctions.h>

inline void KBufferToEditor( KBuffer& _KBuffer )
{
	ImGui::Text( "K-Buffer" );
	

	int K = Cast( int, _KBuffer.GetK() );
	if( ImGui::SliderInt( "K", &K, 1, 16 ) )
		_KBuffer.SetK( Cast( Uint32, K ) );


	Bool IsToneMapped = _KBuffer.IsToneMapped();
	if( ImGui::Checkbox( "Tone Map", &IsToneMapped ) )
		_KBuffer.SetIsToneMapped( IsToneMapped );

	float Exposure = _KBuffer.GetExposure();
	if( ImGui::DragFloat( "Exposure", &Exposure, 0.01f ) )
		_KBuffer.SetExposure( Exposure );


	Bool IsGammaCorrected = _KBuffer.IsGammaCorrected();
	if( ImGui::Checkbox( "Gamma Correction", &IsGammaCorrected ) )
		_KBuffer.SetIsGammaCorrected( IsGammaCorrected );

	float Gamma = _KBuffer.GetGamma();
	if( ImGui::DragFloat( "Gamma", &Gamma, 0.01f ) )
		_KBuffer.SetGamma( Gamma );

	ImGui::Separator();
}