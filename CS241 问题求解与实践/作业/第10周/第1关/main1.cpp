
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "BarChart.h"

//------------------------------------------------------------------------------

using namespace std;

int main()
{
    string str1 = "Austin.csv";
    string str2 = "NewYork.csv";
    BarChart a(str1, str2);
    a.display();
    return 0;
}

//------------------------------------------------------------------------------
