#include"rect.h"
#include"uniform.h"
using namespace std; 

const float WIN_SIZE = 12.0;
const int   MAX_SIZE = 3;

SimpleWindow W("KaleidoWindow", WIN_SIZE, WIN_SIZE);  //����һ������

//�����������ɫ
//color��ezWinͼ�ο��ж���ı�ʾ��ɫ��ö������
color RandomColor()
{
	return (color) Uniform(0, MaxColors - 1);
}

//������������������ĵľ���
float RandomOffSet(int Range, float TrinketSize)  
{
	float OffSet = Uniform(0,Range * 10) / 10.0f;

	//�����������ĵľ�����������߳���һ��
	if (OffSet < TrinketSize / 2.0f)              
	{
		OffSet = TrinketSize / 2.0f;
	}
	return OffSet;
}

//������������εı߳�
float RandomTrinketetSize(int MaxSize)           
{
	return Uniform(10, MaxSize * 10)/10.0f;
}

int Kaleidoscope()
{
	const float Center = WIN_SIZE / 2;                   //��������
	const float Size   = RandomTrinketetSize(MAX_SIZE);  //���������α߳�
	const color Color1 = RandomColor();	                 //����һ�������ɫ
	const color Color2 = RandomColor();                  //������һ�������ɫ
	float OffSet = RandomOffSet(MAX_SIZE, Size);         //���������������ĵľ���

	//�����ĸ�����
	RectangleShape Trinket1(W, Center, Center + OffSet, Color1, Size, Size);
	RectangleShape Trinket2(W, Center - OffSet, Center, Color1, Size, Size);
	RectangleShape Trinket3(W, Center, Center - OffSet, Color1, Size, Size);
	RectangleShape Trinket4(W, Center + OffSet, Center, Color1, Size, Size);

	//�����ĸ�����
	//Trinket1.Draw();
	//Trinket2.Draw();
	//Trinket3.Draw();
	//Trinket4.Draw();

	//�ٻ����ĸ�����
	Trinket1.SetColor(Color2);
	Trinket2.SetColor(Color1);
	Trinket3.SetColor(Color2);
	Trinket4.SetColor(Color1);

	OffSet = RandomOffSet(MAX_SIZE, Size);
	
	//������������ε�λ��
	float RandomSet = Uniform(0, 10) / 10.0f;
	if (RandomSet == 0)
	{
		//�������Ľǵ�������
		Trinket1.SetPosition(Center + OffSet, Center + OffSet);
		Trinket2.SetPosition(Center - OffSet, Center + OffSet);
		Trinket3.SetPosition(Center - OffSet, Center - OffSet);
		Trinket4.SetPosition(Center + OffSet, Center - OffSet);

		Trinket1.Draw();
		Trinket2.Draw();
		Trinket3.Draw();
	    Trinket4.Draw();
	}
	
	else if (RandomSet == 1)
	{
		//�����������ϵ�������
		Trinket1.SetPosition(Center, Center + OffSet);
		Trinket2.SetPosition(Center - OffSet, Center);
		Trinket3.SetPosition(Center, Center - OffSet);
		Trinket4.SetPosition(Center + OffSet, Center);

		Trinket1.Draw();
		Trinket2.Draw();
		Trinket3.Draw();
		Trinket4.Draw();
	}
	return 0;
}

int ApiMain()
{	
	W.Open();
	W.SetTimerCallback(Kaleidoscope);
	W.StartTimer(5);
	return 0;
}
