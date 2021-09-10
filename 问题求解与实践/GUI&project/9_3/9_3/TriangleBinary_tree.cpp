//
#include "TriangleBinary_tree.h"

void  TriangleBinary_tree::setNode(Point p)
{
	Graph_lib::Polygon s;
	Point tmp1, tmp2, tmp3;
	tmp1.x = p.x;
	tmp1.y = p.y - 4;
	tmp2.x = p.x - 3;
	tmp2.y = p.y + 2;
	tmp3.x = p.x + 3;
	tmp3.y = p.y + 2;
	s.add(tmp1);
	s.add(tmp2);
	s.add(tmp3);
	s.set_color(Graph_lib::Color::black);
	s.draw();
}