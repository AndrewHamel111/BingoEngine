#ifndef UTILITIES_H_
#define UTILITIES_H_

#define PADDING 20
#define MSG_BOX_COLOR CLITERAL(Color){255, 255, 255, 255}

#include "raylib.h"
#include <string>

enum BoxAnchor {
	TOP_LEFT, TOP_CENTER, CENTER
};

void ShowMessage(const char* msg, int fontSize, int posX, int posY, BoxAnchor anchor = TOP_LEFT);
void ShowMessage(std::string msg, int fontSize, int posX, int posY, BoxAnchor anchor = TOP_LEFT);

#endif // UTILITIES_H_
