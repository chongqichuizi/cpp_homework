#include "circle.h"  //ezWinLibrary中的圆形类
#include "label.h"   //ezWinLibrary中的标签类
#include "Time.h"    //自定义的时间类

const float WIN_SIZE = 10.0f;
SimpleWindow W("Clock", WIN_SIZE, WIN_SIZE);

int Clock(){
	static Time tm;
	static Date dt;
	++tm;
	if (tm.same() > 0)++dt;
	CircleShape clock(W, Position(WIN_SIZE / 2, WIN_SIZE / 2),
		Yellow, WIN_SIZE - 0.3f);
	Label time(W, Position(WIN_SIZE / 2, WIN_SIZE / 2),
		tm.GetTime(), Black, Green);
	Label date(W, Position(WIN_SIZE / 2, WIN_SIZE / 6), dt.GetDate(), Black, Green);
	time.SetFont("Arial", 120);
	date.SetFont("Arial", 120);
	clock.Draw();
	time.Draw();
	date.Draw();
	return 0;
}

int ApiMain()
{
	W.Open();
	W.SetTimerCallback(Clock);
	W.StartTimer(1000);
	return 0;
}
