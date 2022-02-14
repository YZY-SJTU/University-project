//
#include "Binary_tree.h"

Binary_tree::Binary_tree(int l, Point r, double x, double y)
{
	level = l;
	root.x = r.x;
	root.y = r.y;
	init_distance_x = x;
	distance_y = y;

	int sum = 1;
	for (int i = 0; i < level; ++i)
		sum *= 2;
	sum--;
	int tmp = 1;
	allNode = new Point[sum];
	allNode[0].x = r.x;
	allNode[0].y = r.y;
	for (int i = 1; i < level; ++i)
	{
		double each_distance = x / tmp * i;
		allNode[tmp].x = int(r.x - x * i / 2);
		allNode[tmp].y = int(r.y + i * y);
		for (int j = tmp + 1; j < 2 * tmp + 1; ++j)
		{
			allNode[j].x = int(allNode[j - 1].x + each_distance);
			allNode[j].y = int(r.y + i * y);
		}
		tmp = 2 * tmp + 1;
	}
}

void Binary_tree::setNode(Point p)
{
	Graph_lib::Circle node(p, 4);
	node.set_color(Graph_lib::Color::black);
	node.draw();
}

void Binary_tree::display()
{
	int sum = 1;
	for (int i = 0; i < level; ++i)
		sum *= 2;
	sum--;
	int i;
	for (i = 0; i < sum / 2; ++i)
	{
		setNode(allNode[i]);
		Graph_lib::Lines tmp1, tmp2;
		tmp1.add(allNode[i], allNode[2 * i + 1]);
		tmp2.add(allNode[i], allNode[2 * i + 2]);
		tmp1.set_color(Graph_lib::Color::red);
		tmp2.set_color(Graph_lib::Color::red);
		tmp1.draw();
		tmp2.draw();
	}
	for (i; i < sum; ++i)
	{
		setNode(allNode[i]);
	}
}