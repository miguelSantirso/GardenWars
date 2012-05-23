#ifndef _EffectManager_h_
#define _EffectManager_h_

#include "Effect.h"

#include "IwArray.h"

/**
 * Manager for graphical effects.
 *
 * All new instances of Effect should be added to a manager, which is then 
 * resposible for updating/rendering/deleting them.
 */
struct EffectManager
{
    CIwArray<Effect*> effects;

    ~EffectManager();
    void add(Effect* e) { effects.append(e); }
    void clear();
    void update(int elapsed);
    void render(const CIwVec2& camPos);
};

extern EffectManager * g_EffectsManager;

#endif
