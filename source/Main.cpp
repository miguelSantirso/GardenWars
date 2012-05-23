// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

#include "EffectManager.h"
#include "SimpleResourceManager.h"
#include "ExplosionFragment.h"

#include "Simulation.h"

int main()
{
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();

	g_EffectsManager = new EffectManager();
	g_Resources = new SimpleResourceManager();

    // Set the default background clear colour
    IwGxSetColClear(0x40, 0x40, 0x40, 0);

	Simulation simulation;
	simulation.start();

	char starsCollectedText[40];
	char fpsText[40];

	uint64 lastFrameMs = s3eTimerGetMs();
    
    // Main Game Loop
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update keyboard system
        s3eKeyboardUpdate();
        if (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)    // Back key is used to exit on some platforms
            break;

        // Update pointer system
        s3ePointerUpdate();

        // Clear the screen
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		simulation.update();

		g_EffectsManager->update(s3eTimerGetMs() - lastFrameMs);

		simulation.draw();

		sprintf(starsCollectedText, "FPS: %f", 1000.0/(s3eTimerGetMs() - lastFrameMs));
		IwGxPrintString(10, 10, starsCollectedText);
		sprintf(starsCollectedText, "Stars: %d", simulation.getStarsCollected());
		IwGxPrintString(10, 20, starsCollectedText);
		
		lastFrameMs = s3eTimerGetMs();

        // Show the surface
        Iw2DSurfaceShow();

        // Yield to the opearting system
        s3eDeviceYield(0);
    }

	delete g_Resources;
	delete g_EffectsManager;

    // Shut down Marmalade graphics system and the Iw2D module
    Iw2DTerminate();
    IwGxTerminate();

    return 0;
}
