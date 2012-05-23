// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

#include "World.h"
#include "Player.h"
#include "Star.h"

#define MAX_STARS 15

int nStars = 0;
Star* stars[MAX_STARS];

int starsCollected = 0;

void spawnStars();
void drawStars(int camX, int camY);
void checkCollisionsWithStars(CIwVec2);

int main()
{
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();

    // Set the default background clear colour
    IwGxSetColClear(0x40, 0x40, 0x40, 0);

    // Get the display surface width and height
    int surface_width = Iw2DGetSurfaceWidth();
    int surface_height = Iw2DGetSurfaceHeight();

	SimpleResourceManager resources;

	World theWorld(&resources);
	Player theBot(resources.getImage(RESOURCE_CHARACTER));

	char starsCollectedText[40];
	
	float cameraX = 0;
	float cameraY = 0;
    
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

		sprintf(starsCollectedText, "Stars: %d", starsCollected);
		IwGxPrintString(10, 10, starsCollectedText);

		// draw
		theWorld.draw((int)theBot.position.x, (int)theBot.position.y);
		drawStars((int)theBot.position.x, (int)theBot.position.y);
		theBot.draw(theBot.position);

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

    // Shut down Marmalade graphics system and the Iw2D module
    Iw2DTerminate();
    IwGxTerminate();

    return 0;
}


void spawnStars()
{
	if (nStars >= MAX_STARS)
		return;

	if (IwRand() % 100 == 0)
		stars[nStars++] = new Star(IwRandMinMax(0, 2000), IwRandMinMax(0, 2000));
}


void checkCollisionsWithStars(CIwVec2 playerPos)
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL && (playerPos - stars[i]->position).GetLength() < 80)
		{
			delete stars[i];
			stars[i] = NULL;

			starsCollected++;
		}
	}
}


void drawStars(int camX, int camY)
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL)
			stars[i]->draw(camX, camY);
	}
}
