#include "raylib.h"
#define NEARBLACK CLITERAL(Color){ 20, 20, 20, 255}
#define MUSTARD CLITERAL(Color){ 203, 182, 51, 255}

#define DEV_SHOW_MOUSE_POS

#include "constants.h"

#include "files.h"

// DEV SHIT
#include <iostream>

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, window_label.c_str());
	InitAudioDevice();
	SetMasterVolume(0.5f);

	/////////////////////////////////////////////////////////////
	// TODO: Load resources / Initialize variables at this point
	/////////////////////////////////////////////////////////////

	/// set fps of window
	SetTargetFPS(TARGET_FPS);

	/// remove exit key functionality (alt-f4 will always work)
	SetExitKey(-1);

	/// Load textures


	/// Load sounds

	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update variables / Implement example logic at this point
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing(); /// DRAW START

		ClearBackground(RAYWHITE);

		EndDrawing();	/// DRAW END
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------

	// TODO: Unload all loaded resources at this point

	CloseAudioDevice();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
