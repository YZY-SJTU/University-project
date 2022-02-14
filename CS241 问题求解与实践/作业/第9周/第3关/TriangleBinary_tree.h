#ifndef TRIANGLEBINARY_TREE_GUARD
#define TRIANGLEBINARY_TREE_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"
#include "Binary_tree.h"

class TriangleBinary_tree:public Binary_tree
{
public:
	TriangleBinary_tree(int l, Point r, double x, double y):Binary_tree(l, r, x, y){}
	~TriangleBinary_tree(){}

protected:
	void setNode(Point p);
};




#endif // !TRIANGLEBINARY_TREE_GUARD