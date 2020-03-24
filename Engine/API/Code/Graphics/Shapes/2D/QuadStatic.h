#pragma once


#include "../../../Toolbox/Toolbox.h"
#include "../../../Maths/Transform/Transform2D.h"
#include "../../../Maths/Primitives/TRect.h"
#include "../../Drawable/TransformableDrawable2D.h"
#include "../../Vertex/VertexArray.h"

namespace ae
{
    class Texture;

    /// \ingroup graphics
    /// <summary>
    /// 2D holder for texture. Can be drawn on a Renderer.
    /// </summary>
    /// <seealso cref="Transform2D"/>
    /// <seealso cref="Drawable"/>
    /// \par Example :
    /// \snippet SpriteSample/Code/main.cpp Sprite example
    class AERO_CORE_EXPORT QuadStatic : public TransformableDrawable2D
    {
    public:
        /// <summary>Create a colored cube with a side size.</summary>
        /// <param name="_Width">The width of the cube.</param>
        /// <param name="_Height">The height of the cube.</param>
        QuadStatic( float _Width = 1.0f, float _Height = 1.0f );


        /// <summary>Set the side size of the cube.</summary>
        /// <param name="_Width">The new width to apply.</param>
        /// <param name="_Height">The new height to apply.</param>
        void SetSize( float _Width, float _Height );

        /// <summary>Retrieve the size of the quad.</summary>
        /// <returns>The size  (width, height) of the quad.</returns>
        Vector2 GetSize() const;

        /// <summary>Set the width of the quad.</summary>
        /// <param name="_Width">The new width to apply.</param>
        void SetWidth( float _Width );

        /// <summary>Retrieve the width of the quad.</summary>
        /// <returns>The width of the quad.</returns>
        float GetWidth() const;

        /// <summary>Set the height of the quad.</summary>
        /// <param name="_Height">The new height to apply.</param>
        void SetHeight( float _Height );

        /// <summary>Retrieve the height of the quad.</summary>
        /// <returns>The height of the quad.</returns>
        float GetHeight() const;

        /// <summary>Set the color of the quad vertices.</summary>
        /// <param name="_Color">The new color to apply.</param>
        void SetColor( const Color& _Color );

        /// <summary>Retrieve the color of the quad.</summary>
        /// <returns>The color of the quad.</returns>
        const Color& GetColor() const;
        

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        void ToEditor() override;

    private:
        /// <summary>Update the quad points and UVs.</summary>
        void UpdateQuad();

    private:
        /// <summary>Vertices to render.</summary>
        Vertex2DArray m_QuadVertices;
        /// <summary>Indices of the triangles made with the vertices.</summary>
        IndexArray m_QuadIndices;

        /// <summary>Width of the quad.</summary>
        float m_Width;

        /// <summary>Height of the quad</summary>
        float m_Height;

        /// <summary>Color of the quad's vertices.</summary>
        Color m_Color;
    };

} // ae
