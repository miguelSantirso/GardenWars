// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

#include "World.h"
#include "BallBot.h"
#include "Star.h"

#define MAX_STARS 15

int nStars = 0;
Star* stars[MAX_STARS];

void spawnStars();
void drawStars(int camX, int camY);


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

	World theWorld;
	BallBot theBot;
	
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

		// draw
		theWorld.draw((int)theBot.worldX, (int)theBot.worldY);
		drawStars((int)theBot.worldX, (int)theBot.worldY);
		theBot.draw();

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


void drawStars(int camX, int camY)
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		if (stars[i] != NULL)
			stars[i]->draw(camX, camY);
	}
}
