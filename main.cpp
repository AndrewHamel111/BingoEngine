// TODO
// FIXES
// - resizing breaks info panel text placement (make a function to fix)
//	- consider making an array for the infopanel params like with screenParams
// NEXT STEPS
// - build the editor for the bingo cards (consider using lazarus?)
// CLEANUP
// - replace any manual darkening/brightening of colors with utilities functions

#include "raylib.h"
#define NEARBLACK CLITERAL(Color){ 20, 20, 20, 255}
#define MUSTARD CLITERAL(Color){ 203, 182, 51, 255}

#define DEV_SHOW_MOUSE_POS
#define WINDOW_MIN_WIDTH 500
#define WINDOW_MIN_HEIGHT 500
#define WINDOW_DEFAULT_WIDTH 750
#define WINDOW_DEFAULT_HEIGHT 750
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

enum SCREEN_PARAM {
	SCREEN_WIDTH, SCREEN_HEIGHT, GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, TILE_HEIGHT
};

void FixTileGrid(std::vector<tile>&, int, int);
void FixWindow(int*, bool, bool fromResizeEvent = false, int _ScreenWidth = 0, int _ScreenHeight = 0);

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenParams[6] = {750, 750, 750, 750, 750/5, 750/5}; /**< Array that stores references to the screen size, tile grid size and individual tile size. */

	// raylib window configuration
	InitWindow(screenParams[SCREEN_WIDTH], screenParams[SCREEN_HEIGHT], "Basic Bingo Engine");
	//SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
	InitAudioDevice();
	SetMasterVolume(0.5f);
	SetTargetFPS(TARGET_FPS);
	SetExitKey(-1);

	/////////////////////////////////////////////////////////////
	// TODO: Load resources / Initialize variables at this point
	/////////////////////////////////////////////////////////////

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
		t.bounds.x = (i%5)*screenParams[TILE_WIDTH]; // move the tile into place
		t.bounds.y = (i/5)*screenParams[TILE_HEIGHT];
		tiles.push_back(t); // add to vector
	}

	// buttontest
	/*
	std::vector<button> buttons;
	Rectangle r{0,0,270,70};
	button b(r, BLUE, "Hello", BLACK);
	b.style = OUTSET;
	buttons.push_back(b);
	r = Rectangle{0,80,270,70};
	b = button(r, GREEN, "Goodbye", BLACK);
	b.style = INSET;
	buttons.push_back(b);
	r = Rectangle{0,160,270,70};
	b = button(r, ORANGE, "CUM", BLACK);
	b.style = BORDER;
	buttons.push_back(b);
	*/

	// flags and vars
	bool showPanel = true; /* When true the description panel is displayed on the right side of the screen. */
	std::string cur_name; /* The currently highlighted Tile's name. */
	std::string cur_desc; /* The currently highlighted Tile's description. */

	/// Coords and Recs
	// info panel coords
	Vector2 panelOrigin{(float)screenParams[GRID_WIDTH], 0};
	Rectangle titleRec{panelOrigin.x + INFO_PANEL_PADDING, panelOrigin.y + INFO_PANEL_PADDING,
		INFO_PANEL_WIDTH - (2 * INFO_PANEL_PADDING), 100};
	Rectangle descRec{panelOrigin.x + 2 * INFO_PANEL_PADDING, panelOrigin.y + INFO_PANEL_PADDING + 100,
		INFO_PANEL_WIDTH - (4 * INFO_PANEL_PADDING), 300};

	//--------------------------------------------------------------------------------------
	// Post-Init
	//--------------------------------------------------------------------------------------

	// final fix window
	if (showPanel)
	{
		screenParams[SCREEN_WIDTH] = screenParams[GRID_WIDTH] + INFO_PANEL_WIDTH;

		SetWindowMinSize(WINDOW_MIN_WIDTH + INFO_PANEL_WIDTH, WINDOW_MIN_HEIGHT);
		SetWindowSize(screenParams[SCREEN_WIDTH], screenParams[SCREEN_HEIGHT]);
	}

	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//----------------------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------------------

		if(IsWindowResized())
		{
			FixWindow(screenParams, showPanel, true, GetScreenWidth(), GetScreenHeight());
			FixTileGrid(tiles, screenParams[TILE_WIDTH], screenParams[TILE_HEIGHT]);
		}

		// reset window size to 750 x 750 (and disable panel)
		if (IsKeyPressed(KEY_R))
		{
			showPanel = false;
			screenParams[SCREEN_WIDTH] = WINDOW_DEFAULT_WIDTH;
			screenParams[SCREEN_HEIGHT] = WINDOW_DEFAULT_HEIGHT;

			SetWindowSize(screenParams[SCREEN_WIDTH], screenParams[SCREEN_HEIGHT]);
			FixWindow(screenParams, showPanel);
			FixTileGrid(tiles, screenParams[TILE_WIDTH], screenParams[TILE_HEIGHT]);
		}

		// toggle info panel
		if (IsKeyPressed(KEY_I))
		{
			showPanel = !showPanel;
			if (showPanel)
			{
				screenParams[SCREEN_WIDTH] = screenParams[GRID_WIDTH] + INFO_PANEL_WIDTH;

				SetWindowMinSize(WINDOW_MIN_WIDTH + INFO_PANEL_WIDTH, WINDOW_MIN_HEIGHT);
				SetWindowSize(screenParams[SCREEN_WIDTH], screenParams[SCREEN_HEIGHT]);
			}
			else
			{
				screenParams[SCREEN_WIDTH] = screenParams[GRID_WIDTH];

				SetWindowMinSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
				SetWindowSize(screenParams[SCREEN_WIDTH], screenParams[SCREEN_HEIGHT]);
			}
		}

		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing(); /// DRAW START

		ClearBackground(NEARBLACK);
		Vector2 m = GetMousePosition();

		// display tiles
		auto iEnd = tiles.end();
		bool q = false;
		for(auto i = tiles.begin(); i != iEnd; i++)
		{
			i->update(m);

			// get highlighted name and desc. when applicable
			if (i->isFocused())
			{
				q = true;
				cur_name = i->task.name;
				cur_desc = i->task.desc;
			}
		}
		if (!q)
			cur_name = cur_desc = "";

		// display info panel
		if (showPanel)
		{
			// task name
			DrawTextRec(GetFontDefault(), cur_name.c_str(), titleRec, 40, 1.15, true, RAYWHITE);
			// task desc
			DrawTextRec(GetFontDefault(), cur_desc.c_str(), descRec, 28, 1.15, true, RAYWHITE);
			// hide prompt
			ShowMessage("Press 'i' to hide", 20, (panelOrigin.x + screenParams[SCREEN_WIDTH]) / 2, screenParams[SCREEN_HEIGHT], BOTTOM_CENTER);
		}

		// display buttons (buttontest)
		/*
		auto i = buttons.begin(), e = buttons.end();
		for(; i != e; i++)
		{
			i->update(m);
		}
		*/

		EndDrawing();	/// DRAW END
		//----------------------------------------------------------------------------------
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

void FixWindow(int* screenParams, bool showPanel, bool fromResizeEvent, int _ScreenWidth, int _ScreenHeight)
{
	if (fromResizeEvent)
	{
		screenParams[SCREEN_WIDTH] = _ScreenWidth;
		screenParams[SCREEN_HEIGHT] = _ScreenHeight;
	}
	else
	{
		screenParams[SCREEN_WIDTH] = WINDOW_DEFAULT_WIDTH;
		screenParams[SCREEN_HEIGHT] = WINDOW_DEFAULT_HEIGHT;
	}

	screenParams[GRID_WIDTH] = screenParams[SCREEN_WIDTH];
	if (showPanel)
		screenParams[GRID_WIDTH] -= INFO_PANEL_WIDTH;
	screenParams[GRID_HEIGHT] = screenParams[SCREEN_HEIGHT];

	screenParams[TILE_WIDTH] = screenParams[GRID_WIDTH]/5;
	screenParams[TILE_HEIGHT] = screenParams[GRID_HEIGHT]/5;
}
