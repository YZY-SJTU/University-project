//
#include "righttriangle.h"

righttriangle::righttriangle(double a, double b, Point c)
{
	foot.x = c.x;
	foot.y = c.y;
	if (a > b)
	{
		length_longer = a;
		length_shorter = b;
	}
	else
	{
		length_longer = b;
		length_shorter = a;
	}
}

void righttriangle::addPosition(Point p, char s)//加点为长边顶点,s表示最后一边方向
{
	other1.x = p.x;
	other1.y = p.y;
	if (s == 'l')
	{
		other2.x = int(foot.x - (other1.y - foot.y) / length_longer * length_shorter);
		other2.y = int(foot.y - (foot.x - other1.x) / length_longer * length_shorter);
	}
	if (s == 'r')
	{
		other2.x = int(foot.x + (other1.y - foot.y) / length_longer * length_shorter);
		other2.y = int(foot.y + (foot.x - other1.x) / length_longer * length_shorter);
	}
}

void righttriangle::display(int i)//表示选第i种颜色
{
	base.add(foot);
	base.add(other1);
	base.add(other2);
	if (i == 1)
		base.set_color(Graph_lib::Color::black);
	if (i == 2)
		base.set_color(Graph_lib::Color::blue);
	if (i == 3)
		base.set_color(Graph_lib::Color::cyan);
	if (i == 4)
		base.set_color(Graph_lib::Color::dark_cyan);
	if (i == 5)
		base.set_color(Graph_lib::Color::dark_yellow);
	if (i == 6)
		base.set_color(Graph_lib::Color::green);
	if (i == 7)
		base.set_color(Graph_lib::Color::magenta);
	if (i == 8)
		base.set_color(Graph_lib::Color::red);
	base.draw();
}