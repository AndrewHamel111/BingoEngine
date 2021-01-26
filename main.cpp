#include "raylib.h"
#define NEARBLACK CLITERAL(Color){ 20, 20, 20, 255}
#define MUSTARD CLITERAL(Color){ 203, 182, 51, 255}

#define DEV_SHOW_MOUSE_POS
#define WINDOW_MIN_WIDTH 500
#define WINDOW_MIN_HEIGHT 500
#define INFO_PANEL_WIDTH 400
#define INFO_PANEL_PADDING 15

#include "constants.h"
#include "button.h"
#include "bingo.h"
#include "tile.h"
#include "utilities.h"

#include "files.h"

// DEV SHIT
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

void FixTileGrid(std::vector<tile>&, int, int);

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 750;
	int screenHeight = 750;

	int TILE_WIDTH = screenWidth/5;
	int TILE_HEIGHT = screenHeight/5;

	InitWindow(screenWidth, screenHeight, "Basic Bingo Engine");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
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

	/// Prepare Game Objects

	// load tasks from file
	std::vector<bingo_task> tasks = GetTasksFromJSON("json/sm64.json");
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(0));
	std::shuffle(tasks.begin(), tasks.end(), g);

	// now create the tiles
	std::vector<tile> tiles;
	for(int i = 0; i < 25; i++)
	{
		tile t(tasks[i]); // choose a task
		t.bounds.x = (i%5)*TILE_WIDTH; // move the tile into place
		t.bounds.y = (i/5)*TILE_HEIGHT;
		tiles.push_back(t); // add to vector
	}

	// flags and vars
	bool showPanel = false;

	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update variables / Implement example logic at this point
		//----------------------------------------------------------------------------------

		if(IsWindowResized())
		{
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
			TILE_WIDTH = screenWidth/5;
			TILE_HEIGHT = screenHeight/5;

			FixTileGrid(tiles, TILE_WIDTH, TILE_HEIGHT);
		}

		// reset window size to 750 x 750 (and disable panel)
		if (IsKeyPressed(KEY_R))
		{
			showPanel = false;

			screenWidth = 750;
			screenHeight = 750;
			TILE_WIDTH = screenWidth/5;
			TILE_HEIGHT = screenHeight/5;

			SetWindowSize(screenWidth, screenHeight);
			FixTileGrid(tiles, TILE_WIDTH, TILE_HEIGHT);
		}

		// toggle panel
		/*
		if (IsKeyPressed(KEY_I))
		{
			showPanel = !showPanel;
			if (showPanel)
			{
				SetWindowSize(screenWidth, screenHeight);
				SetWindowMinSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
			}
			else
			{
				SetWindowSize(screenWidth, screenHeight);
				SetWindowMinSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
			}
		}
		*/

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing(); /// DRAW START

		ClearBackground(NEARBLACK);
		Vector2 m = GetMousePosition();

		auto iEnd = tiles.end();
		for(auto i = tiles.begin(); i != iEnd; i++)
		{
			i->update(m);
		}

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

void FixTileGrid(std::vector<tile> &t , int w, int h)
{
	for(int i = 0; i < 25; i++)
	{
		t[i].bounds.x = (i%5)*w; // move the tile into place
		t[i].bounds.y = (i/5)*h;
		t[i].bounds.width = w;
		t[i].bounds.height = h;

		t[i].fixFontSize();
	}
}
