//
#include "hyperelliptic.h"

hyperelliptic::hyperelliptic(double aa, double bb, double mm, double nn, int NN, Point c)
{
	a = aa;
	b = bb;
	m = mm;
	n = nn;
	N = NN;
	center.x = c.x;
	center.y = c.y;
	p = new Point[2 * N - 2];
	double current_x = -a;
	double dis = 2 * a / (N - 1);
	for (int i = 0; i < N; ++i)
	{
		if (i == 0)
		{
			p[0].x = int(current_x + center.x);
			p[0].y = 0 + center.y;
			current_x += dis;
			continue;
		}
		if (i == N - 1)
		{
			p[2 * N - 3].x = int(current_x + center.x);
			p[2 * N - 3].y = 0 + center.y;
			current_x += dis;
			continue;
		}
		p[2 * i - 1].x = int(current_x + center.x);
		p[2 * i - 1].y = int(b * pow(1 - pow(abs(current_x / a), m), 1.0 / n) + center.y);
		p[2 * i].x = int(current_x + center.x);
		p[2 * i].y = int(-b * pow(1 - pow(abs(current_x / a), m), 1.0 / n) + center.y);
		current_x += dis;
	}
}

void hyperelliptic::display()
{
	using namespace Graph_lib;
	for (int i = 0; i < 2 * N - 2; ++i)
	{
		for (int j = i + 1; j < 2 * N - 2; ++j)
		{
			Graph_lib::Line a(p[i], p[j]);
			a.set_color(Color::red);
			a.draw();
		}
	}
}