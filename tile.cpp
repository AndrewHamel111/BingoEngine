#include "tile.h"

tile::tile()
{
	// setting up the tile button (all tiles have these properties)
	this->bounds = TILE_R;
	this->margin = Rectangle{5, 5, 5, 5};
	this->setLabel("Example Tile");
	this->setColorsAuto(RAYWHITE, Color{240, 130, 40, 255});
}

tile::tile(bingo_task task): tile()
{
	this->setTask(task);
}

void tile::setTask(bingo_task task)
{
	this->task = task;
	this->setLabel(task.name);
}

void tile::draw()
{
	// recall that margin is {top ,right, bottom, left} so top = x, right = y, bottom = width, height = left
	Rectangle _bounds = this->bounds;
	if (!p1 && !p2)
	{
		_bounds.y += margin.x;
		_bounds.x += margin.height;
		_bounds.height -= margin.x + margin.width;
		_bounds.width -= margin.y + margin.height;
	}

	if (p1 && p2)
	{
		Vector2 v1, v2, v3;
		v1.x = _bounds.x + _bounds.width;
		v1.y = _bounds.y;
		v2.x = _bounds.x;
		v2.y = _bounds.y;
		v3.x = _bounds.x;
		v3.y = _bounds.y + _bounds.height;
		DrawTriangle(v1, v2, v3, COL_P1);

		v1.x = _bounds.x + _bounds.width;
		v1.y = _bounds.y;
		v2.x = _bounds.x;
		v2.y = _bounds.y + _bounds.height;
		v3.x = _bounds.x + _bounds.width;
		v3.y = _bounds.y + _bounds.height;
		DrawTriangle(v1, v2, v3, COL_P2);
	}
	else if (p1)
	{
		DrawRectangleRec(_bounds, COL_P1);
	}
	else if (p2)
	{
		DrawRectangleRec(_bounds, COL_P2);
	}
	else
	{
		Color col = col_button;
		if (v_pressed)
			col = col_pressed;
		else if (v_focus)
			col = col_focus;

		DrawRectangleRec(_bounds, col);
	}

	if (!label.empty())
	{
		int posX = _bounds.x + _bounds.width/2 - labelLength/2;
		int posY = _bounds.y + (_bounds.height - labelHeight)/2;

		DrawText(label.c_str(), posX, posY, labelSize, col_text);
	}
}

void tile::check(Vector2 m)
{
	// clear button state
	v_pressed = v_focus = false;

	// recall that margin is {top ,right, bottom, left} so top = x, right = y, bottom = width, height = left
	Rectangle _bounds = this->bounds;
	if (!p1 && !p2)
	{
		_bounds.y += margin.x;
		_bounds.x += margin.height;
		_bounds.height -= margin.x + margin.width;
		_bounds.width -= margin.y + margin.height;
	}

	if (m < _bounds)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			p1 = !p1;
			v_pressed = true;
		}
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			p2 = !p2;
			v_pressed = true;
		}
		else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			v_pressed = true;
		}
		else
		{
			v_focus = true;
		}
	}
}

void tile::update(Vector2 m)
{
	if (enabled)
		this->check(m);

	if (!noDraw)
		this->draw();
}

bool tile::isFocused() const
{
	return v_focus;
}
