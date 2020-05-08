#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[11];

public:
	Xwindow(int width, int height);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	Xwindow(const Xwindow&) = delete;
	Xwindow &operator=(const Xwindow&) = delete;

	enum {White=0, Yellow, Black, Red, Green, Blue, Cyan, Magenta, Orange, Brown, Lime}; // Available colours.

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	void clearRectangle(int x, int y, int width, int height);

	// Draws a string
	void drawString(int x, int y, std::string msg);

};

#endif
