#include "button.h"

// constructors

button::button(): label{""}, labelLength{0}, labelHeight{0}, labelSize{FONT_SIZE}, v_focus{false}, v_pressed{false}, bounds{ZERO_R}, margin{ZERO_R}, col_button{RAYWHITE}, col_focus{COL_FOCUS}, col_pressed{COL_PRESSED}, col_text{NEARBLACK}, spr_Source{ZERO_R}, spr_focusSource{ZERO_R}, spr_pressedSource{ZERO_R}, atlasName{""}, noDraw{false}, enabled{true}, pressed{false}
{}

button::button(Rectangle r, Color c1, std::string str, Color c2): button()
{
	this->bounds = r;
	this->setLabel(str);

	//this->col_button = c1;
	this->setColorsAuto(c1);
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
	if (style == OUTSET || style == INSET || style == BORDER || style == DEFAULT)
	{
		// set the margin
		Rectangle _bounds = this->bounds;
		_bounds.y += margin.x;
		_bounds.x += margin.height;
		_bounds.height -= margin.x + margin.width;
		_bounds.width -= margin.y + margin.height;

		// account for border (border typed buttons only)
		Rectangle inner_bounds = _bounds;
		inner_bounds.x += BORDER_SIZE;
		inner_bounds.y += BORDER_SIZE;
		inner_bounds.width -= 2*BORDER_SIZE;
		inner_bounds.height -= 2*BORDER_SIZE;

		// shift color depending on state
		Color col = col_button;
		if (v_pressed)
			col = col_pressed;
		else if (v_focus)
			col = col_focus;

		// draw center of button
		if(style != DEFAULT)
			DrawRectangleRec(inner_bounds, col);
		else
			DrawRectangleRec(_bounds, col);

		Color col_border1; // upper variant
		Color col_border2; // lower variant

		if (style == OUTSET)
		{
			col_border1 = brightenColorBy(col, BORDER_DIFF); // lighter variant
			col_border2 = darkenColorBy(col, BORDER_DIFF); // darker variant
		}
		else
		{
			col_border1 = darkenColorBy(col, BORDER_DIFF); // darker variant
			col_border2 = brightenColorBy(col, BORDER_DIFF); // lighter variant
		}

		// draw border
		if (style == OUTSET || style == INSET)
		{
			DrawRectangleRec(Rectangle{_bounds.x, _bounds.y,
												 _bounds.width - BORDER_SIZE, BORDER_SIZE},
												 col_border1);
			DrawRectangleRec(Rectangle{_bounds.x, _bounds.y + BORDER_SIZE,
												 BORDER_SIZE, _bounds.height - 2*BORDER_SIZE},
												 col_border1);
			DrawTriangle(Vector2{_bounds.x + _bounds.width, _bounds.y},
										Vector2{_bounds.x + _bounds.width - BORDER_SIZE, _bounds.y},
										Vector2{_bounds.x + _bounds.width - BORDER_SIZE, _bounds.y + BORDER_SIZE},
										col_border1);
			DrawTriangle(Vector2{_bounds.x + BORDER_SIZE, _bounds.y + _bounds.height - BORDER_SIZE},
										Vector2{_bounds.x, _bounds.y + _bounds.height - BORDER_SIZE},
										Vector2{_bounds.x, _bounds.y + bounds.height},
										col_border1);

			DrawRectangleRec(Rectangle{_bounds.x + _bounds.width - BORDER_SIZE, _bounds.y + BORDER_SIZE,
												 BORDER_SIZE, _bounds.height - 2*BORDER_SIZE},
												 col_border2);
			DrawRectangleRec(Rectangle{_bounds.x + BORDER_SIZE, _bounds.y + _bounds.height - BORDER_SIZE,
												_bounds.width - BORDER_SIZE, BORDER_SIZE},
												col_border2);
			DrawTriangle(Vector2{_bounds.x + _bounds.width, _bounds.y},
										Vector2{_bounds.x + _bounds.width - BORDER_SIZE, _bounds.y + BORDER_SIZE},
										Vector2{_bounds.x + _bounds.width, _bounds.y + BORDER_SIZE},
										col_border2);
			DrawTriangle(Vector2{_bounds.x + BORDER_SIZE, _bounds.y + _bounds.height - BORDER_SIZE},
										Vector2{_bounds.x, _bounds.y + bounds.height},
										Vector2{_bounds.x + BORDER_SIZE, _bounds.y + bounds.height},
										col_border2);
		}
		else if (style == BORDER)
		{
			DrawRectangleRec(Rectangle{_bounds.x, _bounds.y,
												 _bounds.width, BORDER_SIZE},
												 col_border1);
			DrawRectangleRec(Rectangle{_bounds.x, _bounds.y + BORDER_SIZE,
												 BORDER_SIZE, _bounds.height - 2*BORDER_SIZE},
												 col_border1);
			DrawRectangleRec(Rectangle{_bounds.x, _bounds.y + _bounds.height - BORDER_SIZE,
												 _bounds.width, BORDER_SIZE},
												 col_border1);
			DrawRectangleRec(Rectangle{_bounds.x + _bounds.width - BORDER_SIZE, _bounds.y + BORDER_SIZE,
												BORDER_SIZE, _bounds.height - 2*BORDER_SIZE},
												col_border1);
		}
			// end border

		// draw the label
		if (!label.empty())
		{
			int posX = _bounds.x + _bounds.width/2 - labelLength/2;
			int posY = _bounds.y + (_bounds.height - labelHeight)/2;

			DrawText(label.c_str(), posX, posY, labelSize, col_text);
		}
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

		f = brightenColorBy(base, BUTTON_COLOR_DIFF/2);
		p = brightenColorBy(base, BUTTON_COLOR_DIFF);
	}
	else // light button case
	{
		t.r = t.g = t.b = 15;

		f = darkenColorBy(base, BUTTON_COLOR_DIFF/2);
		p = darkenColorBy(base, BUTTON_COLOR_DIFF);
	}

	col_focus = f;
	col_pressed = p;
	col_text = t;
}

void button::setColorsAuto(Color base, Color press)
{
	col_button = base;
	col_pressed = press;
	col_focus = getColorAverage(base, press);

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
