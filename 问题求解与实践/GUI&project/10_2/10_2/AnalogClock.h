//
#ifndef ANALOGCLOCK_GUARD
#define ANALOGCLOCK_GUARD

#include "std_lib_facilities.h"
#include <iostream>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"
#include <time.h>
#include <windows.h>
#include <cmath>

void setBase();

class AnalogClock
{
public:
	AnalogClock(char str[]);
	~AnalogClock(){}
	void display();

private:
	string Month;
	int Day = 0;
	int Year= 0;
	int Hour = 0;
	int Minute = 0;
	int Second = 0;
	string Time;
};

#endif // !ANALOGCLOCK_GUARD