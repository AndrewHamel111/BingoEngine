#include "utilities.h"


void ShowMessage(const char* msg, int fontSize, int posX, int posY, BoxAnchor anchor)
{
	// fontSize
	Vector2 measure = MeasureTextEx(GetFontDefault(), msg, fontSize, 1.15);

	// pos
	Rectangle rec;
	if (anchor == TOP_LEFT)
	{
		rec.x = posX;
		rec.y = posY;
		rec.width = measure.x + fontSize;
		rec.height = measure.y + fontSize;
	}
	else if (anchor == TOP_CENTER)
	{
		rec.y = posY;
		rec.width = measure.x + fontSize;
		rec.height = measure.y + fontSize;
		rec.x = posX - rec.width/2;
	}
	else if (anchor == BOTTOM_CENTER)
	{
		rec.width = measure.x + fontSize;
		rec.height = measure.y + fontSize;
		rec.x = posX - rec.width/2;
		rec.y = posY - rec.height;
	}
	else
	{
		rec.width = measure.x + fontSize;
		rec.height = measure.y + fontSize;
		rec.x = posX - rec.width/2;
		rec.y = posY - rec.height/2;
	}

	// tPos
	int tPosX, tPosY;

	tPosX = rec.x + (rec.width - measure.x)/2;
	tPosY = rec.y + (rec.height - measure.y)/2;

	// draw
	DrawRectangleRec(rec, MSG_BOX_COLOR);
	DrawText(msg ,tPosX, tPosY, fontSize, BLACK);
}

/** Overloaded method that will also accept std::string as opposed to const char*. Simply calls the original ShowMessag def'n.
*/
void ShowMessage(std::string msg, int fontSize, int posX, int posY, BoxAnchor anchor)
{
	ShowMessage(msg.c_str(), fontSize, posX, posY);
}

Color brightenColorBy(Color c, int a)
{
	return Color{(unsigned char)std::min(255, (int)c.r + a),
	(unsigned char)std::min(255, (int)c.g + a),
	(unsigned char)std::min(255, (int)c.b + a),c.a
	};
}

Color darkenColorBy(Color c, int a)
{
	return Color{(unsigned char)std::max(0, (int)c.r - a),
	(unsigned char)std::max(0, (int)c.g - a),
	(unsigned char)std::max(0, (int)c.b - a), c.a
	};
}

Color getColorAverage(Color c1, Color c2)
{
	return Color{(unsigned char)(((int)c1.r + (int)c2.r)/2), (unsigned char)(((int)c1.g + (int)c2.g)/2),
	(unsigned char)(((int)c1.b + (int)c2.b)/2), (unsigned char)(((int)c1.a + (int)c2.a)/2)};
}
