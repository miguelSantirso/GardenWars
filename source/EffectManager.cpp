#include "EffectManager.h"

#include "Iw2D.h"

EffectManager* g_EffectsManager = 0;


EffectManager::~EffectManager()
{
    clear();
}

void EffectManager::clear()
{
    for (uint32 i=0; i<effects.size(); i++)
        delete effects[i];
    effects.clear();
}

void EffectManager::update(int elapsed)
{
    for (uint32 i=0; i<effects.size(); )
    {
        Effect* e = effects[i];
        if (!effects[i]->update(elapsed))
        {
            // Note: this is quite inefficient if many objects are removed at the same time
            effects.erase(i);
            delete e;
        }
        else
            i++;
    }
}

void EffectManager::render(const CIwVec2& camPos)
{
    Iw2DSetColour(0xff808080);
    Iw2DSetAlphaMode(IW_2D_ALPHA_ADD);
    for (uint32 i=0; i<effects.size(); i++)
        effects[i]->render(camPos);
    Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
    Iw2DSetColour(0xffffffff);
}
