#include "raylib.h"
#define NEARBLACK CLITERAL(Color){ 20, 20, 20, 255}
#define MUSTARD CLITERAL(Color){ 203, 182, 51, 255}

#define DEV_SHOW_MOUSE_POS

#include "constants.h"
#include "button.h"
#include "bingo.h"
#include "tile.h"

#include "files.h"

// DEV SHIT
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 750;
	const int screenHeight = 750;

	const int TILE_WIDTH = screenWidth/5;
	const int TILE_HEIGHT = screenHeight/5;

	InitWindow(screenWidth, screenHeight, "Basic Bingo Engine");
	//SetWindowState(FLAG_WINDOW_RESIZABLE);
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
	Rectangle r{0,0,200,100};
	button b1(r, RAYWHITE, "Hello", NEARBLACK);
	r.y += 100;
	button b2(r, RAYWHITE, "Goodbye", NEARBLACK);

	bingo_task task;
	task.name = "Example Task";
	task.desc = "You gotta do the thing and do it right!";
	task.weight = 1;

	// create a numbered list of tasks and shuffle them
	/*
	std::vector<bingo_task> tasks;
	for(int i = 0; i < 25; i++)
	{
		task.name = std::string(FormatText("Task #%d", i + 1));
		tasks.push_back(task);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(0));
	std::shuffle(tasks.begin(), tasks.end(), g);
	*/

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

		ClearBackground(WHITE);
		Vector2 m = GetMousePosition();

		auto iEnd = tiles.end();
		for(auto i = tiles.begin(); i != iEnd; i++)
		{
			i->update(m);
		}

		/* color demo
		b1.update(m);
		b2.update(m);

		if (b1.pressed)
		{
			b1.pressed = false;
			// randomize the colors
			Color col{GetRandomValue(15,240),GetRandomValue(15,240),GetRandomValue(15,240),255};
			b2.setColorsAuto(col);
		}
		else if (b2.pressed)
		{
			b2.pressed = false;
			break;
		}
		*/

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
