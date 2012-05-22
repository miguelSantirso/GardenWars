#include "FloatText.h"

#include "Iw2D.h"
#include "RenderManager.h"

FloatText::FloatText(CIwVec2 const & startPos, const char * string)
{
    timer = 0;
    pos = startPos;
    text = string;
}

bool FloatText::update(int elapsed)
{
    // Slide upwards
    timer += elapsed;
    pos.y -= elapsed * 15;

    // The text disappears after 2 seconds
    return timer<2000;
}

void FloatText::render()
{
    // Convert position to pixels
    // Set the rectangle for font rendering to 400 pixels square (arbitrary) centered on our position
    Iw2DDrawString(text.c_str(),
        CIwSVec2((int16)IW_FIXED_MUL(pos.x, g_TileSize)-200,(int16)IW_FIXED_MUL(pos.y, g_TileSize)-200),
        CIwSVec2(400,400),
        IW_2D_FONT_ALIGN_CENTRE, IW_2D_FONT_ALIGN_CENTRE);
}
