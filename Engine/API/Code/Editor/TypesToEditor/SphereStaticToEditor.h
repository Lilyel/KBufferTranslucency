#pragma once

#pragma once

#include "../../Graphics/Shapes/3D/SphereStatic.h"
#include "../../UI/Dependencies/IncludeImGui.h"

namespace ae
{
    namespace priv
    {
        namespace ui
        {
            inline void SphereStaticToEditor( ae::Shape::SphereStatic& _SphereStatic )
            {
                ImGui::Text( "Sphere Static Mesh" );

                float Radius = _SphereStatic.GetRadius();
                ImGui::DragFloat( "Radius", &Radius, 1.0f, Math::Epsilon(), std::numeric_limits<float>::max() );
                if( !Math::IsEqualByEpsilon( Radius, _SphereStatic.GetRadius() ) )
                    _SphereStatic.SetRadius( Radius );

				int RingCount = static_cast<int>( _SphereStatic.GetRingCount() );
				ImGui::DragInt( "Ring Count", &RingCount, 1.0f, 3, std::numeric_limits<int>::max() );
				if( RingCount != static_cast<int>( _SphereStatic.GetRingCount() ) )
					_SphereStatic.SetRingCount( static_cast<Uint32>( RingCount ) );

				int SegmentCount = static_cast<int>( _SphereStatic.GetSegmentCount() );
				ImGui::DragInt( "Segment Count", &SegmentCount, 1.0f, 3, std::numeric_limits<int>::max() );
				if( SegmentCount != static_cast<int>( _SphereStatic.GetSegmentCount() ) )
					_SphereStatic.SetSegmentCount( static_cast<Uint32>( SegmentCount ) );

                ImGui::Separator();
            }
        }

    } // priv

} // ae