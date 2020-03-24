#pragma once

#include "../../Graphics/Image/Image.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void ImageToEditor( Image& )
			{
				ImGui::Text( "Image" );

				
				ImGui::Separator();
			}
		}

	} // priv

} // ae
