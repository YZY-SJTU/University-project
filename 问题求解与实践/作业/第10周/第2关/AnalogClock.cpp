#include "AnalogClock.h"

void setBase()
{
	using namespace Graph_lib;

	Graph_lib::Polygon background;
	background.add(Point(0, 0));
	background.add(Point(600, 0));
	background.add(Point(600, 400));
	background.add(Point(0, 400));
	background.set_fill_color(Color::white);
	background.draw();

	Circle clock(Point(300, 200), 150);
	clock.set_color(Color::black);
	clock.draw();

	Point tmp2(300, 60);
	Point tmp1(300, 50);
	Lines h12;
	h12.add(tmp1, tmp2);
	h12.set_color(Color::black);
	h12.draw();


	tmp1.x += 75;
	tmp1.y += int(-75 * sqrt(3) + 150);
	tmp2.x += 70;
	tmp2.y += int(-70 * sqrt(3) + 140);
	Lines h1;
	h1.add(tmp1, tmp2);
	h1.set_color(Color::black);
	h1.draw();

	tmp1.x += int(75 * sqrt(3) - 75);
	tmp1.y += int(75 * sqrt(3) - 75);
	tmp2.x += int(70 * sqrt(3) - 70);
	tmp2.y += int(70 * sqrt(3) - 70);
	Lines h2;
	h2.add(tmp1, tmp2);
	h2.set_color(Color::black);
	h2.draw();

	tmp1.x += int(-75 * sqrt(3) + 150);
	tmp1.y += 75;
	tmp2.x += int(-70 * sqrt(3) + 140);
	tmp2.y += 70;
	Lines h3;
	h3.add(tmp1, tmp2);
	h3.set_color(Color::black);
	h3.draw();

	tmp1.x += int(+75 * sqrt(3) - 150);
	tmp1.y += 75;
	tmp2.x += int(+70 * sqrt(3) - 140);
	tmp2.y += 70;
	Lines h4;
	h4.add(tmp1, tmp2);
	h4.set_color(Color::black);
	h4.draw();

	tmp1.x += int(-75 * sqrt(3) + 75);
	tmp1.y += int(-75 + 75 * sqrt(3));
	tmp2.x += int(-70 * sqrt(3) + 70);
	tmp2.y += int(-70 + 70 * sqrt(3));
	Lines h5;
	h5.add(tmp1, tmp2);
	h5.set_color(Color::black);
	h5.draw();

	tmp1.x += -75;
	tmp1.y += int(-75 * sqrt(3) + 150);
	tmp2.x += -70;
	tmp2.y += int(-70 * sqrt(3) + 140);
	Lines h6;
	h6.add(tmp1, tmp2);
	h6.set_color(Color::black);
	h6.draw();

	tmp1.x += -75;
	tmp1.y += int(+75 * sqrt(3) - 150);
	tmp2.x += -70;
	tmp2.y += int(+70 * sqrt(3) - 140);
	Lines h7;
	h7.add(tmp1, tmp2);
	h7.set_color(Color::black);
	h7.draw();

	tmp1.x += int(75 - 75 * sqrt(3));
	tmp1.y += int(-75 * sqrt(3) + 75);
	tmp2.x += int(70 - 70 * sqrt(3));
	tmp2.y += int(-70 * sqrt(3) + 70);
	Lines h8;
	h8.add(tmp1, tmp2);
	h8.set_color(Color::black);
	h8.draw();

	tmp1.x += int(-150 + 75 * sqrt(3));
	tmp1.y += -75;
	tmp2.x += int(-140 + 70 * sqrt(3));
	tmp2.y += -70;
	Lines h9;
	h9.add(tmp1, tmp2);
	h9.set_color(Color::black);
	h9.draw();

	tmp1.x += int(150 - 75 * sqrt(3));
	tmp1.y += -75;
	tmp2.x += int(140 - 70 * sqrt(3));
	tmp2.y += -70;
	Lines h10;
	h10.add(tmp1, tmp2);
	h10.set_color(Color::black);
	h10.draw();

	tmp1.x += int(-75 + 75 * sqrt(3));
	tmp1.y += int(75 - 75 * sqrt(3));
	tmp2.x += int(-70 + 70 * sqrt(3));
	tmp2.y += int(70 - 70 * sqrt(3));
	Lines h11;
	h11.add(tmp1, tmp2);
	h11.set_color(Color::black);
	h11.draw();

	Point tmp3(295, 40);
	Text t12(tmp3, "12");
	t12.set_color(Color::black);
	t12.draw();

	tmp3.x += 80;
	tmp3.y += int(160 - 80 * sqrt(3));
	Text t1(tmp3, "1");
	t1.set_color(Color::black);
	t1.draw();

	tmp3.x += int(-80 + 80 * sqrt(3));
	tmp3.y += int(-80 + 80 * sqrt(3));
	Text t2(tmp3, "2");
	t2.set_color(Color::black);
	t2.draw();

	tmp3.x += int(160 - 80 * sqrt(3));
	tmp3.y += 80;
	Text t3(tmp3, "3");
	t3.set_color(Color::black);
	t3.draw();

	tmp3.x += int(-160 + 80 * sqrt(3));
	tmp3.y += 80;
	Text t4(tmp3, "4");
	t4.set_color(Color::black);
	t4.draw();

	tmp3.x += int(80 - 80 * sqrt(3));
	tmp3.y += int(-75 + 80 * sqrt(3));
	Text t5(tmp3, "5");
	t5.set_color(Color::black);
	t5.draw();

	tmp3.x += -80;
	tmp3.y += int(160 - 80 * sqrt(3));
	Text t6(tmp3, "6");
	t6.set_color(Color::black);
	t6.draw();

	tmp3.x += -80;
	tmp3.y += int(-160 + 80 * sqrt(3));
	Text t7(tmp3, "7");
	t7.set_color(Color::black);
	t7.draw();

	tmp3.x += int(80 - 80 * sqrt(3));
	tmp3.y += int(80 - 80 * sqrt(3));
	Text t8(tmp3, "8");
	t8.set_color(Color::black);
	t8.draw();

	tmp3.x += int(-160 + 80 * sqrt(3));
	tmp3.y += -80;
	Text t9(tmp3, "9");
	t9.set_color(Color::black);
	t9.draw();

	tmp3.x += int(150 - 80 * sqrt(3));
	tmp3.y += -80;
	Text t10(tmp3, "10");
	t10.set_color(Color::black);
	t10.draw();

	tmp3.x += int(-75 + 80 * sqrt(3));
	tmp3.y += int(80 - 80 * sqrt(3));
	Text t11(tmp3, "11");
	t11.set_color(Color::black);
	t11.draw();
}

AnalogClock::AnalogClock(char str[])
{
	int i = 0;
	while (str[i] != ' ')
		++i;
	++i;

	while (str[i] != ' ')
	{
		Month += str[i];
		++i;
	}
	++i;

	while (str[i] != ' ')
	{
		Day = Day * 10 + int(str[i] - '0');
		++i;
	}
	++i;

	while (str[i] != ':')
	{
		Hour = Hour * 10 + int(str[i] - '0');
		++i;
	}
	++i;

	while (str[i] != ':')
	{
		Minute = Minute * 10 + int(str[i] - '0');
		++i;
	}
	++i;

	while (str[i] != ' ')
	{
		Second = Second * 10 + int(str[i] - '0');
		++i;
	}
	++i;

	while (str[i] <= '9' && str[i] >= '0')
	{
		Year = Year * 10 + int(str[i] - '0');
		++i;
	}

	int tmp1 = Year;
	int cnt = 1, digit = 1;
	while (tmp1 >= 10)
	{
		++cnt;
		tmp1 /= 10;
		digit *= 10;
	}
	tmp1 = Year;
	for (int i = 0; i < cnt; ++i)
	{
		Time += char('0' + (tmp1 / digit));
		tmp1 -= (tmp1 / digit) * digit;
		digit /= 10;
	}
	Time += ' ';

	Time += Month;
	Time += ' ';

	tmp1 = Day;
	Time += char('0' + tmp1 / 10);
	Time += char('0' + tmp1 % 10);
	Time += ' ';

	tmp1 = Hour;
	Time += char('0' + tmp1 / 10);
	Time += char('0' + tmp1 % 10);
	Time += ':';

	tmp1 = Minute;
	Time += char('0' + tmp1 / 10);
	Time += char('0' + tmp1 % 10);
	Time += ':';

	tmp1 = Second;
	Time += char('0' + tmp1 / 10);
	Time += char('0' + tmp1 % 10);

	if (Hour >= 12)
		Hour -= 12;

	cout << "Time: " << Time << endl;;
}

void AnalogClock::display()
{
	using namespace Graph_lib;   // our graphics facilities are in Graph_lib

	Point center(300, 200);
	double hAngle = (Hour + double(Minute) / 60 + double(Second) / 3600) * acos(-1) / 6;
	Point hp;
	hp.x = 300 + int(70 * sin(hAngle));
	hp.y = 200 - int(70 * cos(hAngle));
	Lines hl;
	hl.add(center, hp);
	hl.set_color(Color::blue);
	hl.draw();

	double mAngle = (Minute + double(Second) / 60) * acos(-1) / 30;
	Point mp;
	mp.x = 300 + int(100 * sin(mAngle));
	mp.y = 200 - int(100 * cos(mAngle));
	Lines ml;
	ml.add(center, mp);
	ml.set_color(Color::black);
	ml.draw();

	double sAngle = Second * acos(-1) / 30;
	Point sp;
	sp.x = 300 + int(130 * sin(sAngle));
	sp.y = 200 - int(130 * cos(sAngle));
	Lines sl;
	sl.add(center, sp);
	sl.set_color(Color::red);
	sl.draw();

	Text label(Point(400, 50), Time);
	label.set_font(Font::times);
	label.set_color(Color::black);
	label.draw();

	Text hLabel(Point(475, 270), "blue->hour");
	hLabel.set_font(Font::times);
	hLabel.set_color(Color::blue);
	hLabel.draw();

	Text mLabel(Point(475, 285), "black->minute");
	mLabel.set_font(Font::times);
	mLabel.set_color(Color::black);
	mLabel.draw();

	Text rLabel(Point(475, 300), "red->second");
	rLabel.set_font(Font::times);
	rLabel.set_color(Color::red);
	rLabel.draw();
}