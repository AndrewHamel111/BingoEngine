#include "button.h"

// constructors

button::button(): label{""}, labelLength{0}, labelHeight{0}, labelSize{FONT_SIZE}, v_focus{false}, v_pressed{false}, bounds{ZERO_R}, margin{ZERO_R}, col_button{RAYWHITE}, col_focus{COL_FOCUS}, col_pressed{COL_PRESSED}, col_text{NEARBLACK}, spr_Source{ZERO_R}, spr_focusSource{ZERO_R}, spr_pressedSource{ZERO_R}, atlasName{""}, noDraw{false}, enabled{true}, pressed{false}
{}

button::button(Rectangle r, Color c1, std::string str, Color c2): button()
{
	this->bounds = r;
	this->setLabel(str);

	this->col_button = c1;
	this->col_text = c2;
}


/** Update method for the button updates the values of the state fields. No button is drawn.

@param m Mouse position passed from calling function to reduce OpenGL overhead.
*/
void button::check(Vector2 m)
{
	// clear button state
	v_pressed = v_focus = false;

	// recall that margin is {top ,right, bottom, left} so top = x, right = y, bottom = width, height = left
	Rectangle _bounds = this->bounds;
	_bounds.y += margin.x;
	_bounds.x += margin.height;
	_bounds.height -= margin.x + margin.width;
	_bounds.width -= margin.y + margin.height;

	if (m < _bounds)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			pressed = true;
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

void button::draw()
{
	// recall that margin is {top ,right, bottom, left} so top = x, right = y, bottom = width, height = left
	Rectangle _bounds = this->bounds;
	_bounds.y += margin.x;
	_bounds.x += margin.height;
	_bounds.height -= margin.x + margin.width;
	_bounds.width -= margin.y + margin.height;

	Color col = col_button;
	if (v_pressed)
		col = col_pressed;
	else if (v_focus)
		col = col_focus;

	DrawRectangleRec(_bounds, col);

	if (!label.empty())
	{
		int posX = _bounds.x + _bounds.width/2 - labelLength/2;
		int posY = _bounds.y + (_bounds.height - labelHeight)/2;

		DrawText(label.c_str(), posX, posY, labelSize, col_text);
	}
}

/** Update the appropriate states of the button; first checking the mouse position and button states (when enabled), then drawing the button (when noDraw is off).

@param m Mouse position passed from calling function to reduce OpenGL overhead.
*/
void button::update(Vector2 m)
{
	if (enabled)
		this->check(m);

	if (!noDraw)
		this->draw();
}

/// //////////////// ///
///  access methods  ///
/// //////////////// ///

void button::setLabel(std::string str)
{
	// update label value
	this->label = str;
	fixFontSize();
}

void button::setLabel(const char* str)
{
	std::string _str(str);
	setLabel(_str);
}

void button::fixFontSize()
{
	int fontSize = FONT_SIZE;

	// measure the label size
	this->labelLength = MeasureText(label.c_str(), fontSize);

	// repeatedly reduce the font size until it fits in the button
	while(this->labelLength > (this->bounds.width - (2 * fontSize)) && fontSize > 5)
	{
		fontSize--;
		this->labelLength = MeasureText(label.c_str(), fontSize);
	}

	this->labelHeight = MeasureTextEx(GetFontDefault(), label.c_str(), fontSize, 1.15).y;
	this->labelSize = fontSize;
}

void button::setColorsAuto(Color base)
{
	const unsigned char DEL = 30;

	col_button = base;

	Color f; // focus color
	Color p; // pressed color
	Color t; // text color

	t.a = base.a; // text alpha value matches button alpha value
	f.a = p.a = 255; // semitransparent buttons become solid when focused/pressed

	// set text color to either white or black depending on the base color
	// everything else is "shifted" darker when the color is bright and lighter when the color is dark.
	if (base.r + base.g + base.b < 400) // dark button case
	{
		t.r = t.g = t.b = 240;

		f.r = (unsigned char)std::min(255, base.r + DEL/2);
		f.g = (unsigned char)std::min(255, base.g + DEL/2);
		f.b = (unsigned char)std::min(255, base.b + DEL/2);

		p.r = (unsigned char)std::min(255, base.r + DEL);
		p.g = (unsigned char)std::min(255, base.g + DEL);
		p.b = (unsigned char)std::min(255, base.b + DEL);
	}
	else // light button case
	{
		t.r = t.g = t.b = 15;

		f.r = (unsigned char)std::max(0, base.r - DEL/2);
		f.g = (unsigned char)std::max(0, base.g - DEL/2);
		f.b = (unsigned char)std::max(0, base.b - DEL/2);

		p.r = (unsigned char)std::max(0, base.r - DEL);
		p.g = (unsigned char)std::max(0, base.g - DEL);
		p.b = (unsigned char)std::max(0, base.b - DEL);
	}

	col_focus = f;
	col_pressed = p;
	col_text = t;
}

void button::setColorsAuto(Color base, Color press)
{
	col_button = base;
	col_pressed = press;
	col_focus = Color{(base.r + press.r)/2, (base.g + press.g)/2, (base.b + press.b)/2, (base.a + press.a)/2};

	// set text color
	if (base.r + base.g + base.b < 400) // dark button case
	{
		col_text.r = col_text.g = col_text.b = 240;
	}
	else // light button case
	{
		col_text.r = col_text.g = col_text.b = 15;
	}
}

/// /////////// ///
///  c methods  ///
/// /////////// ///

/*
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

*/
