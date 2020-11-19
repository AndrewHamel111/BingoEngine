#include "button.h"

bool ImageButtonSpriteSwap(Rectangle bounds, Texture2D atlas, Rectangle source, Rectangle altSource)
{
	Vector2 m = GetMousePosition();
	Color c = WHITE;
	bool q = false;

	Rectangle src = source;

	if (m < bounds)
	{
		// change atlas source for button
		src = altSource;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			c = GRAY;
			q = true;
		}
	}

	// draw the button
	DrawTextureRec(atlas, src, Vector2{bounds.x,bounds.y}, c);

	return q;
}

bool ImageButtonEx(Rectangle bounds, Texture2D atlas, Rectangle source)
{
	Vector2 m = GetMousePosition();
	Color c = WHITE;
	bool q = false;

	if (m < bounds)
	{
		// change render color of button
		c = LIGHTGRAY;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			c = GRAY;
			q = true;
		}
	}

	// draw the button
	DrawTextureRec(atlas, source, Vector2{bounds.x,bounds.y}, c);

	return q;
}

bool ImageButtonSink(Rectangle bounds, Texture2D atlas, Rectangle source)
{
	Vector2 m = GetMousePosition();
	Color c = WHITE;
	bool q = false;

	if (m < bounds)
	{
		c = LIGHTGRAY;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			source.y -= 9;
			q = true;
		}

	}

	// draw the button
	DrawTextureRec(atlas, source, Vector2{bounds.x,bounds.y}, c);

	return q;
}

bool TextButton(Rectangle bounds, std::string text, Color buttonColor, Color textColor)
{
	Vector2 m = GetMousePosition();
	Color c = buttonColor;
	Color o = buttonColor;
	bool q = false;
	float fontSize = 20;

	if (m < bounds)
	{
		// change render color of button
		unsigned char cOff = 40;
		unsigned char mid = 128;
		unsigned char maxx = 255;

		c = Color{	(o.r > mid) ? (unsigned char)(o.r - cOff) : (unsigned char)(o.r + cOff),
								(o.g > mid) ? (unsigned char)(o.g - cOff) : (unsigned char)(o.g + cOff),
								(o.b > mid) ? (unsigned char)(o.b - cOff) : (unsigned char)(o.b + cOff),
								o.a};

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			q = true;
	}

	// draw the button
	DrawRectangleRec(bounds, c);

	/// todo fix the alignment on this text
	DrawTextRec(GetFontDefault(), text.c_str(), bounds, fontSize, 1.0, true, textColor);

	return q;
}

bool HiddenButton(Rectangle bounds)
{
	return GetMousePosition() < bounds && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

float SliderBar(Vector2 start, float length, float* percent, Color handleColor, float scale, bool horizontal)
{
	bool isHovering;
	if (horizontal)
	{
		isHovering = GetMousePosition() < Rectangle{start.x - SLIDER_HEIGHT, start.y - SLIDER_HANDLE_HEIGHT, length + 2* SLIDER_HEIGHT, 2*SLIDER_HANDLE_HEIGHT};
	}
	else
	{
		isHovering = GetMousePosition() < Rectangle{start.x - SLIDER_HANDLE_HEIGHT, start.y - SLIDER_HEIGHT, 2*SLIDER_HANDLE_HEIGHT, length + 2*SLIDER_HEIGHT};
	}
	Color col;

	////////////
	//// UPDATE ////
	////////////

	if (isHovering && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		col = DARKBLUE;

		// use mousepos to find the new percent
		if(horizontal)
			*percent = ((GetMouseX() - start.x) / length);
		else
			*percent = ((GetMouseY() - start.y) / length);

		// clamp percent to [0,1]
		if (*percent < 0) *percent = 0;
		else if (*percent > 1.0) *percent = 1.0;
	}
	else if (isHovering)
		col = BLUE;
	else
		col = handleColor;

	//////////
	//// DRAW ////
	//////////

	Vector2 handlePosition = start;
	// offset
	if (horizontal)
	{
		handlePosition.x -= SLIDER_HANDLE_HEIGHT/2;
		handlePosition.y -= SLIDER_HANDLE_HEIGHT/2;

		// adjust X pos to the current percentage
		handlePosition.x += (*percent) * length;

		// draw bar and handle
		DrawRectangleRec(Rectangle{start.x, start.y - SLIDER_HEIGHT/2, length, SLIDER_HEIGHT}, GRAY);
		DrawRectangleRec(Rectangle{handlePosition.x, handlePosition.y, SLIDER_HANDLE_HEIGHT, SLIDER_HANDLE_HEIGHT}, col);
	}
	else
	{
		handlePosition.x -= SLIDER_HANDLE_HEIGHT/2;
		handlePosition.y -= SLIDER_HANDLE_HEIGHT/2;

		// adjust Y pos to the current percentage
		handlePosition.y += (*percent) * length;

		// draw bar and handle
		DrawRectangleRec(Rectangle{start.x - SLIDER_HEIGHT/2, start.y, SLIDER_HEIGHT, length}, GRAY);
		DrawRectangleRec(Rectangle{handlePosition.x, handlePosition.y, SLIDER_HANDLE_HEIGHT, SLIDER_HANDLE_HEIGHT}, col);
	}

	return (*percent) * scale;
}

float SliderBarCenter(Vector2 center, float length, float* percent, Color handleColor, float scale, bool horizontal)
{
	Vector2 v = center;
	if(horizontal)
	{
		v.x -= length/2;
		v.y -= SLIDER_HEIGHT/2;
	}
	else
	{
		v.x -= SLIDER_HEIGHT/2;
		v.y -= length/2;
	}

	return SliderBar(v, length, percent, handleColor, scale, horizontal);
}

/// All characters except /\:*?"<>|.,
int validKeys[] = {KEY_SPACE, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_MINUS, KEY_APOSTROPHE, KEY_EQUAL, KEY_ZERO, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET} ;

bool SimpleTextBoxUpdate(Rectangle r, char* c, int max_field_length, bool* focus)
{
	static int hold_counter = 0;

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMousePosition() < r)
			*focus = true;
		else
			*focus = false;
	}

	if (!(*focus)) return false;

	if (IsKeyPressed(KEY_ESCAPE)) return *focus = false;

	int field_length = strlen(c);

	if (IsKeyPressed(KEY_ENTER))
	{
		*focus = false;
		if (field_length > 0)
			return true;
	}

	// update char* accordingly

	if(IsKeyDown(KEY_BACKSPACE))
	{
		if (++hold_counter >= 50)
		{
			if (hold_counter % 2 == 0 && field_length > 0)
			{
				c[field_length - 1] = '\0';
				field_length--;
			}
			return false;
		}
	}
	else
		hold_counter = 0;

	for(int key : validKeys)
	{
		if (IsKeyPressed(key) && field_length < max_field_length)
		{
			if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
			{
				switch(key)
				{
				case KEY_MINUS:
					c[field_length] = '_';
					break;
				case KEY_EQUAL:
					c[field_length] = '+';
					break;
				case KEY_LEFT_BRACKET:
					c[field_length] = '{';
					break;
				case KEY_RIGHT_BRACKET:
					c[field_length] = '}';
					break;
				case KEY_ONE:
					c[field_length] = '!';
					break;
				case KEY_TWO:
					c[field_length] = '@';
					break;
				case KEY_THREE:
					c[field_length] = '#';
					break;
				case KEY_FOUR:
					c[field_length] = '$';
					break;
				case KEY_FIVE:
					c[field_length] = '%';
					break;
				case KEY_SIX:
					c[field_length] = '^';
					break;
				case KEY_SEVEN:
					c[field_length] = '&';
					break;
				case KEY_EIGHT:
					c[field_length] = key;
					break;
				case KEY_NINE:
					c[field_length] = '(';
					break;
				case KEY_ZERO:
					c[field_length] = ')';
					break;
				/*
				case KEY_A: case KEY_B: case KEY_C: case KEY_D: case KEY_E: case KEY_F: case KEY_G: case KEY_H: case KEY_I: case KEY_J: case KEY_K: case KEY_L: case KEY_M: case KEY_N: case KEY_O: case KEY_P: case KEY_Q: case KEY_R: case KEY_S: case KEY_T: case KEY_U: case KEY_V: case KEY_W: case KEY_X: case KEY_Y: case KEY_Z:
				c[field_length] = key;
				break;*/
				default:
					c[field_length] = key;
					break;
				}
			}
			else if (KEY_A <= key && key <= KEY_Z)
				c[field_length] = key + 32;
			else
				c[field_length] = key;

			c[field_length + 1] = '\0';
			field_length++;
		}
	}

	if (IsKeyPressed(KEY_BACKSPACE) && field_length > 0)
	{
		c[field_length - 1] = '\0';
		field_length--;
	}

	return false;
}

bool NumberBoxUpdate(Rectangle r, char* c, int max_field_length, bool* focus)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMousePosition() < r)
			*focus = true;
		else
			*focus = false;
	}

	if (!(*focus)) return false;

	int field_length = strlen(c);

	if (IsKeyPressed(KEY_ENTER))
	{
		*focus = false;
		if (field_length > 0)
			return true;
	}

	// update char* accordingly
	for(int key = KEY_ZERO; key <= KEY_NINE; key++)
	{
		if (IsKeyPressed(key) && field_length < max_field_length)
		{
			c[field_length] = key;

			c[field_length + 1] = '\0';
			field_length++;
		}
	}

	if (IsKeyPressed(KEY_BACKSPACE) && field_length > 0)
	{
		c[field_length - 1] = '\0';
		field_length--;
	}

	return false;
}

bool SimpleTextBoxDraw(Rectangle r, char* c, int max_field_length, bool* focus)
{
	const int fontSize = 30;
	const float lineWidth = 4;
	const Color col{54, 193, 247,255};
	Color col1 = RAYWHITE;
	Color col2 = Color{20,20,20,255};
	Rectangle r_inner = Rectangle{r.x + lineWidth, r.y + lineWidth, r.width - 2*lineWidth, r.height - 2*lineWidth};

	// draw background
	if (*focus)
	{
		col1 = WHITE;
		col2 = BLACK;
	}
	DrawRectangleRec(r, RAYWHITE);

	// draw outline when focused
	if (*focus)
	{
		DrawLineEx(Vector2{r.x, r.y + lineWidth/2}, Vector2{r.x + r.width, r.y + lineWidth/2}, lineWidth, col);
		DrawLineEx(Vector2{r.x + r.width - lineWidth/2, r.y}, Vector2{r.x + r.width - lineWidth/2, r.y + r.height}, lineWidth, col);
		DrawLineEx(Vector2{r.x + r.width, r.y + r.height - lineWidth/2}, Vector2{r.x, r.y + r.height - lineWidth/2}, lineWidth, col);
		DrawLineEx(Vector2{r.x + lineWidth/2, r.y + r.height}, Vector2{r.x + lineWidth/2, r.y}, lineWidth, col);
	}

	// draw TEXT
	DrawTextRec(GetFontDefault(), c, r_inner, fontSize, 1.0f, true, col2);

	return false;
}
