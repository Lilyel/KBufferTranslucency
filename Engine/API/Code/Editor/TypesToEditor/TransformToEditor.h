#pragma once

#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Maths/Transform/Transform.h"
#include "../../UI/Dependencies/IncludeImGui.h"
#include "../../UI/UI.h"
#include "../../Graphics/Camera/Camera.h"
#include "../../Aero/Aero.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void TransformToEditor( Transform& _Object )
            {
                ImGui::Text( "Transform" );

                Vector3 Position = _Object.GetPosition();
                ImGui::DragFloat3( "Position", &Position.X );
                _Object.SetPosition( Position );

                Vector3 Rotation = _Object.GetRotationAngles();
                Rotation = Vector3( Math::RadToDeg( Rotation.X ), Math::RadToDeg( Rotation.Y ), Math::RadToDeg( Rotation.Z ) );
                ImGui::DragFloat3( "Rotation", &Rotation.X );
                Rotation = Vector3( Math::DegToRad( Rotation.X ), Math::DegToRad( Rotation.Y ), Math::DegToRad( Rotation.Z ) );
                _Object.SetRotation( Rotation );

                Vector3 Scale = _Object.GetScale();
                ImGui::DragFloat3( "Scale", &Scale.X );
                _Object.SetScale( Scale );
                
                Vector3 Pivot = _Object.GetPivot();
                ImGui::DragFloat3( "Pivot", &Pivot.X );
                _Object.SetPivot( Pivot );

                ImGui::Separator();
            }
        }

    } // priv

} // ae

