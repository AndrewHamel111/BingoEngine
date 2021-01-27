#ifndef BUTTON_H_
#define BUTTON_H_

#include "raylib.h"
#include "operators.h"
#include "utilities.h"
#include <string>
#include <cstring>

#define SLIDER_HANDLE_HEIGHT 30
#define SLIDER_HEIGHT 20
#define FONT_SIZE 30
#define BORDER_SIZE 10
#define BORDER_DIFF 25
#define BUTTON_COLOR_DIFF 30

#define COL_FOCUS CLITERAL(Color){ 213, 239, 247, 255}
#define COL_PRESSED CLITERAL(Color){ 123, 191, 212, 255}
#define NEARBLACK CLITERAL(Color){ 20, 20, 20, 255}

#define ZERO_R CLITERAL(Rectangle){ 0, 0, 0, 0}

enum button_style {
	DEFAULT, OUTSET, INSET, BORDER
};

class button
{
protected:
	/// fields
	// descriptors
	std::string label; /**< Accessed through setLabel to maintain text offset for button. */
	int labelLength; /**< Controlled by setLabel and used in draw. */
	int labelHeight; /**< Controlled by setLabel and used in draw. */
	int labelSize; /**< Controlled by setLabel and used in draw. */

	// states
	bool v_focus; /**< Visual state controllers. Private to avoid confusion. Maintained by check and used in draw. */
	bool v_pressed; /**< Visual state controllers. Private to avoid confusion. Maintained by check and used in draw. */

public:
	/// fields

	// descriptors
	Rectangle bounds; /**< The active area of the button and where the button will be drawn. */
	Rectangle margin; /**< top, right, bottom left values for margin. */
	Color col_button;
	Color col_focus;
	Color col_pressed;
	Color col_text;
	Rectangle spr_Source; /**< Source rectangle for button sprite. */
	Rectangle spr_focusSource; /**< Source rectangle when button is focused. */
	Rectangle spr_pressedSource; /**< Source rectangle when button is pressed. */
	std::string atlasName; /**< Name of the appropriate atlas to draw button from. */
	bool noDraw; /**< When true the button will not be displayed but still functions. */
	bool enabled; /**< When false the button will not have any function. */
	// style
	button_style style; /**< Enum descriptor of button styles, used by button::draw. */

	// states
	bool pressed; /**< True when button has been pressed. Any calling methods checking the state of pressed and using it to trigger an event are responsible for unsetting the pressed value. */

	/// methods
	// constructors
	button();
	button(Rectangle, Color, std::string, Color);

	// update methods
	void check(Vector2);
	void draw();
	void update(Vector2);

	// access methods
	void setLabel(std::string);
	void setLabel(const char*);
	void fixFontSize();

	void setColorsAuto(Color base); /**< Provide a base color and the focus/pressed colors will be automatically generated. */
	void setColorsAuto(Color base, Color press); /**< Provide a base and pressed color and a focus color is automatically generated. */
};

#endif
