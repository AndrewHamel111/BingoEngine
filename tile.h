#ifndef TILE_H_
#define TILE_H_

#include "button.h"
#include "bingo.h"

#define TILE_R CLITERAL(Rectangle){ 0, 0, 150, 150}
#define COL_P1 CLITERAL(Color){ 240,140,40,255 }
#define COL_P2 CLITERAL(Color){ 40,140,240,255 }

// a tile is a button that has a bingo task embedded in it and when clicked will always do the same thing (set the value of the info panel to the bingo task)
class tile : public button
{
public:
	///fields
	bingo_task task;

	// state fields
	bool p1; /**< true when p1 has completed this task */
	bool p2; /**< true when p2 has completed this task */

	///methods
	// constructors
	tile();
	tile(bingo_task);

	// update methods
	void draw();
	void check(Vector2);
	void update(Vector2);

	// access methods
	void setTask(bingo_task);
};

#endif // TILE_H_
