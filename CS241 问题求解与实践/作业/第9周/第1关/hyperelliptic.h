
#ifndef HYPERELLIPTIC_GUARD
#define HYPERELLIPTIC_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

class hyperelliptic
{
public:
	hyperelliptic(double aa, double bb, double mm, double nn, int NN, Point c);
	~hyperelliptic() { delete[]p;}
	void display();

private:
	Point center;
	double a, b, m, n;
	int N;
	Point* p;

};



#endif // !HYPERELLIPTIC_GUARD
