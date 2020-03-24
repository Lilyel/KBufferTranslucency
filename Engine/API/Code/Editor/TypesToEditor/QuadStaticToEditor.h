#pragma once

#include "../../Graphics/Shapes/2D/QuadStatic.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "ColorToEditor.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void QuadStaticToEditor( QuadStatic& _QuadStatic )
            {
                ImGui::Text( "Quad Static" );

                Vector2 Size = _QuadStatic.GetSize();
                if( ImGui::DragFloat2( "Size", &Size.X, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() ) )
                    _QuadStatic.SetSize( Size.X, Size.Y );
                

                Color Color = _QuadStatic.GetColor();
                if( ColorNoAlphaToEditor( "Color", Color ) )               
                    _QuadStatic.SetColor( Color );

                ImGui::Separator();
            }
        }

    } // priv

} // ae
