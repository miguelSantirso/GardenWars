// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

#include "EffectManager.h"
#include "ExplosionFragment.h"

#include "World.h"
#include "Player.h"
#include "Star.h"

#define MAX_STARS 60

int nStars = 0;
Star* stars[MAX_STARS];

int starsCollected = 0;

EffectManager effects;
SimpleResourceManager* resources;

void spawnStars();
void drawStars(CIwVec2 camPos);
void checkCollisionsWithStars(CIwVec2);

int main()
{
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();

	resources = new SimpleResourceManager();

    // Set the default background clear colour
    IwGxSetColClear(0x40, 0x40, 0x40, 0);

    // Get the display surface width and height
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();

	World theWorld(resources);
	Player theBot(resources->getImage(RESOURCE_CHARACTER));

	char starsCollectedText[40];
	char fpsText[40];
	
	float cameraX = 0;
	float cameraY = 0;

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

		theBot.update();
		spawnStars();
		checkCollisionsWithStars(theBot.position);

		effects.update(s3eTimerGetMs() - lastFrameMs);

		// draw
		theWorld.draw((int)theBot.position.x, (int)theBot.position.y);
		drawStars(theBot.position);
		theBot.draw(theBot.position);

		effects.render(theBot.position);

		sprintf(starsCollectedText, "FPS: %f", 1000.0/(s3eTimerGetMs() - lastFrameMs));
		IwGxPrintString(10, 10, starsCollectedText);
		sprintf(starsCollectedText, "Stars: %d", starsCollected);
		IwGxPrintString(10, 20, starsCollectedText);
		
		lastFrameMs = s3eTimerGetMs();

        // Show the surface
        Iw2DSurfaceShow();

        // Yield to the opearting system
        s3eDeviceYield(0);
    }

	theWorld.release();
	theBot.release();

	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL)
		{
			stars[i]->release();
			delete stars[i];
		}
	}
	delete [] stars;

	resources->release();

    // Shut down Marmalade graphics system and the Iw2D module
    Iw2DTerminate();
    IwGxTerminate();

    return 0;
}


void spawnStars()
{
	if (nStars >= MAX_STARS)
		return;

	if (true || IwRand() % 100 == 0)
	{
		stars[nStars] = new Star(resources->getImage(RESOURCE_STAR));
		stars[nStars]->position.x = IwRandMinMax(0, WORLD_PIXELS_WIDTH);
		stars[nStars]->position.y = IwRandMinMax(0, WORLD_PIXELS_HEIGHT);

		nStars++;
	}

}


void checkCollisionsWithStars(CIwVec2 playerPos)
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL && (playerPos - stars[i]->position).GetLength() < 80)
		{
			ExplosionFragment* exp = new ExplosionFragment(resources->getImage(RESOURCE_STAR), stars[i]->position, CIwVec2(0, -0.0001), 0xff223355);
			effects.add(exp);

			delete stars[i];
			stars[i] = NULL;

			starsCollected++;
		}
	}
}


void drawStars(CIwVec2 camPos)
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL)
			stars[i]->draw(camPos);
	}
}
