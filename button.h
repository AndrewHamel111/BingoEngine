#ifndef BUTTON_H_
#define BUTTON_H_

#include "raylib.h"
#include "operators.h"
#include <string>
#include <cstring>

#define SLIDER_HANDLE_HEIGHT 30
#define SLIDER_HEIGHT 20

/**
* @brief Draws described button and returns true when clicked.
* @param bounds The bounds of the button {x,y,width,height} where x,y denote the top left corner
* @param atlas The Texture2D sprite atlas the button image will come from.
* @param source The Rectangle describing the portion of the atlas containing the sprite.
* @param altSource Same as above, but for the alternate sprite that the button will switch to when hovered.
* @returns True iff the button is clicked on this frame.
* specializes ImageButtonEx by offering the chance to include two source rects: one for what should ordinarily be shown
* and an alternate for what should be shown when hovering.
*/
bool ImageButtonSpriteSwap(Rectangle bounds, Texture2D atlas, Rectangle source, Rectangle altSource);

/**
* @brief Draws described button and returns true when clicked.
* @param bounds The bounds of the button {x,y,width,height} where x,y denote the top left corner
* @param atlas The Texture2D sprite atlas the button image will come from.
* @param source The Rectangle describing the portion of the atlas containing the sprite.
* @returns True iff the button is clicked on this frame.
* A replacement for raygui::GuiImageButtonEx (which was not very good at all).
*/
bool ImageButtonEx(Rectangle bounds, Texture2D atlas, Rectangle source);

/**
* @brief Draws described button which sinks when moused over and returns true when clicked.
* @param bounds The bounds of the button {x,y,width,height} where x,y denote the top left corner
* @param atlas The Texture2D sprite atlas the button image will come from.
* @param source The Rectangle describing the portion of the atlas containing the sprite.
* @returns True iff the button is clicked on this frame.
* A replacement for raygui::GuiImageButtonEx (which was not very good at all).
*/
bool ImageButtonSink(Rectangle bounds, Texture2D atlas, Rectangle source);

/**
* @brief Draws a button at the bounds, displaying the specified text and returns true when clicked.
* @param bounds The bounds of the button {x,y,width,height} where x,y denote the top left corner
* @param text Label to print on the button
* @param buttonColor Color of the button itself (defaults to RAYWHITE)
* @param textColor Color of the text (defaults to NEARBLACK)
*/
bool TextButton(Rectangle bounds, std::string text, Color buttonColor = RAYWHITE, Color textColor = Color{20,20,20,255});

/**
* @brief Creates an invisible button that returns true when clicked.
* @param bounds Defines the area of the hidden button.
* @returns True iff the button is pressed this frame.
*/
bool HiddenButton(Rectangle bounds);

/**
* @brief Draws described slider bar, which is impacted by the user's mouse interaction and on change updates the value pointed to by percent.
* @param start Left side of slider bar
* @param end Right side of slider bar
* @param percent A pointer to where the "result" of the bar should be stored.
* @param scale multiplier applied to the regular percentage
* @returns the value of percent times the optional parameter scale = 1.0
* The function changes the value pointed to by percent, but also returns a scaled version of the percentage
* (which by default will be the same as the value stored at the pointer).
*/
float SliderBar(Vector2 start, float length, float* percent, Color handleColor = RAYWHITE, float scale = 1.0, bool horizontal = true);

/**
* @brief Specialization of SliderBar that takes the center of the bar instead, to take some of the weight off UI design.
* @param start Left side of slider bar
* @param end Right side of slider bar
* @param percent A pointer to where the "result" of the bar should be stored.
* @param scale multiplier applied to the regular percentage
* @returns the percentage of the bar that is full times the optional parameter scale = 1.0
*/
float SliderBarCenter(Vector2 center, float length, float* percent, Color handleColor = RAYWHITE, float scale = 1.0, bool horizontal = true);

/**
 * @brief Called in the update portion of the gameloop, updates the char* value based on user input.
 * @param r Bounds of the text field.
 * @param c Pointer to the string being changed.
 * @param max_field_length Maximum length of the string.
 * @param focus Pointer to a bool stored somewhere in main.
 * @returns True when enter is pressed, signifying the changes to the string have ended.
 * @details Keys pressed will only update the string if the field has focus. This is indicated by the bool pointer parameter, and the field is given a blue outline when it is selected so the user knows which box is selected. This field will lose focus when enter is pressed or the mouse is clicked outside the bounds of the field.
 */
bool SimpleTextBoxUpdate(Rectangle r, char* c, int max_field_length, bool* focus);

/**
 * @brief Specializes SimpleTextBoxUpdate by restricting the values populating char* c to numeric values. This does not verify that the initial value of c is a valid numeric form.
 * @param r Bounds of the text field.
 * @param c Pointer to the string being changed.
 * @param max_field_length Maximum length of the string.
 * @param focus Pointer to a bool stored somewhere in main.
 * @returns True when enter is pressed, signifying the changes to the string have ended.
 * @details Keys pressed will only update the string if the field has focus. This is indicated by the bool pointer parameter, and the field is given a blue outline when it is selected so the user knows which box is selected. This field will lose focus when enter is pressed or the mouse is clicked outside the bounds of the field.
 */
bool NumberBoxUpdate(Rectangle r, char* c, int max_field_length, bool* focus);

/**
 * @brief Called in the update portion of the gameloop, updates the char* value based on user input.
 * @param r Bounds of the text field.
 * @param c Pointer to the string being changed.
 * @param max_field_length Maximum length of the string.
 * @param focus Pointer to a bool stored somewhere in main.
 * @returns True when enter is pressed, signifying the changes to the string have ended.
 * @details Keys pressed will only update the string if the field has focus. This is indicated by the bool pointer parameter, and the field is given a blue outline when it is selected so the user knows which box is selected. This field will lose focus when enter is pressed or the mouse is clicked outside the bounds of the field.
 */
bool SimpleTextBoxDraw(Rectangle r, char* c, int max_field_length, bool* focus);
#endif
