//
#ifndef RIGHTTRIANGLE_GUARD
#define RIGHTTRIANGLE_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

class righttriangle
{
public:
	righttriangle(double a, double b, Point c);
	~righttriangle(){}
	void addPosition(Point p, char s);
	void display(int i);
private:
	Graph_lib::Polygon base;
	double length_longer, length_shorter;
	Point foot;
	Point other1, other2;
};



#endif // !RIGHTTRIANGLE_GUARD