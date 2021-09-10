//
#ifndef BINARY_TREE_GUARD
#define BINARY_TREE_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

class Binary_tree:public Graph_lib::Shape
{
public:
	Binary_tree(int l, Point r, double x, double y);
	~Binary_tree() { delete[]allNode; }
	void display();

private:
	int level;
	double distance_y;
	double init_distance_x;
	Point root;
	Point* allNode;

protected:
	virtual void setNode(Point p);
};

#endif // !BINARY_TREE_GUARD