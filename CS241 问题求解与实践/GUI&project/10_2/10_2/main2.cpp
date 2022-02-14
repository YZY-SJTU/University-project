
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "AnalogClock.h"



//------------------------------------------------------------------------------

	int main()
	{

		
			
		using namespace Graph_lib;   // our graphics facilities are in Graph_lib

		Point tl(100, 100);           // to become top left  corner of window

		Simple_window win(tl, 600, 400, "AnalogClock");    // make a simple window

		while (true)
		{
			setBase();
			time_t current = time(&current);/*获取当前时间*/
			char buff[26];
			ctime_s(buff, sizeof buff, &current);
			AnalogClock a(buff);
			a.display();
			Sleep(1000);
			Fl::redraw();
		}
		win.wait_for_button();       // give control to the display engine

		return 0;
	}


//------------------------------------------------------------------------------
