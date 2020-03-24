#pragma once

#include "../../Graphics/Framebuffer/Framebuffer.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
	namespace priv
	{
		namespace ui
		{
			inline void FramebufferToEditor( Framebuffer& _Framebuffer )
			{
				ImGui::Text( "Framebuffer" );

				ImGui::Spacing();

				ImGui::Text( "Draw Mode" );

				DrawMode CurrentDrawMode = _Framebuffer.GetDrawMode();

				if( ImGui::RadioButton( "Filled", CurrentDrawMode == DrawMode::Filled ) )
					CurrentDrawMode = DrawMode::Filled;

				ImGui::SameLine();

				if( ImGui::RadioButton( "Wireframe", CurrentDrawMode == DrawMode::Wireframe ) )
					CurrentDrawMode = DrawMode::Wireframe;

				ImGui::SameLine();

				if( ImGui::RadioButton( "Points", CurrentDrawMode == DrawMode::Points ) )
					CurrentDrawMode = DrawMode::Points;

				_Framebuffer.SetDrawMode( CurrentDrawMode );


				ImGui::Spacing();

				ImGui::Text( "Culling Mode" );

				CullingMode CurrentCullingMode = _Framebuffer.GetCullingMode();

				if( ImGui::RadioButton( "No Culling", CurrentCullingMode == CullingMode::NoCulling ) )
					CurrentCullingMode = CullingMode::NoCulling;

				if( ImGui::RadioButton( "Back Faces", CurrentCullingMode == CullingMode::BackFaces ) )
					CurrentCullingMode = CullingMode::BackFaces;

				if( ImGui::RadioButton( "Front Faces", CurrentCullingMode == CullingMode::FrontFaces ) )
					CurrentCullingMode = CullingMode::FrontFaces;

				if( ImGui::RadioButton( "Back and Front Faces", CurrentCullingMode == CullingMode::BackAndFrontFaces ) )
					CurrentCullingMode = CullingMode::BackAndFrontFaces;

				_Framebuffer.SetCullingMode( CurrentCullingMode );

				ImGui::Separator();
			}
		}

	} // priv

} // ae
