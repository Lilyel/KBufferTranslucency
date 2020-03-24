#pragma once

#include "../../Graphics/Camera/Camera.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void CameraToEditor( Camera& _Camera )
            {
                // Projection

                std::string ProjectionTypes[2] = { "Perspective", "Orthographic" };
                Uint8 ProjectionType = Math::Clamp( Cast( Uint8, 0 ), Cast( Uint8, 2 ), Cast( Uint8, _Camera.GetProjectionType() ) );

                if( ImGui::BeginCombo( "Projection", ProjectionTypes[ProjectionType].c_str() ) )
                {
                    Bool IsSelected = False;
                    for( Uint8 p = 0; p < 2; p++ )
                    {
                        IsSelected = p == ProjectionType;
                        if( ImGui::Selectable( ProjectionTypes[p].c_str(), &IsSelected ) )
                            ProjectionType = p;

                        if( IsSelected )
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                _Camera.SetProjectionType( Cast( Camera::ProjectionType, ProjectionType ) );

                // Control

                std::string ControlTypes[3] = { "Free", "FPS", "Orbit" };
                Uint8 ControlType = Math::Clamp( Cast( Uint8, 0 ), Cast( Uint8, 3 ), Cast( Uint8, _Camera.GetControlType() ) );

                if( ImGui::BeginCombo( "Control", ControlTypes[ControlType].c_str() ) )
                {
                    Bool IsSelected = False;
                    for( Uint8 c = 0; c < 3; c++ )
                    {
                        IsSelected = c == ControlType;
                        if( ImGui::Selectable( ControlTypes[c].c_str(), &IsSelected ) )
                            ControlType = c;

                        if( IsSelected )
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                if( ControlType != Cast( Uint8, _Camera.GetControlType() ) )
                {
                    switch( ControlType )
                    {
                    case 0: _Camera.SetControlToFree(); break;
                    case 1: _Camera.SetControlToFPS(); break;
                    case 2:  _Camera.SetControlToOrbit( Vector3::Zero ); break;
                    default: _Camera.SetControlToFree(); break;
                    }
                }


                // Projection Settings
                float FOV = _Camera.GetFieldOfView();
                ImGui::SliderAngle( "Field Of View", &FOV, Math::Epsilon(), 179.0f );
                _Camera.SetFieldOfView( FOV );

                float Near = _Camera.GetNear();
                ImGui::DragFloat( "Near", &Near, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                _Camera.SetNear( Near );

                float Far = _Camera.GetFar();
                ImGui::DragFloat( "Far", &Far, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                _Camera.SetFar( Far );


                // Orbit Settings.
                float OrbitDistance = _Camera.GetOrbitDistance();
                ImGui::DragFloat( "Orbit Distance", &OrbitDistance, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                _Camera.SetOrbitDistance( OrbitDistance );

            }
        }

    } // priv

} // ae