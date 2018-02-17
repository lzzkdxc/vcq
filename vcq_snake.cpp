#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include<windows.h>
#include <conio.h>
void gotoxy(int x, int y) //清屏 
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};//第二个值为零表示光标隐藏
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
}
///////////////////////////////////////////////////////////////////////////////////////follow
typedef struct{
	int x;
	int y;
}ty;
ty sk,food;
int a[45][45]={0},death=1;
int turn=100,cx=0,cy=-1;
char input;
int l=3; 
void start()
{
	srand(time(NULL));
	hidecursor();
	printf("sleeptime（50-500）："); 
	scanf("%d",&turn); 
	sk.x=sk.y=8;
	a[sk.y][sk.x]=l;
	food.x=food.y=11;
	a[food.y][food.x]=-1;
	for(int i=1;i<=20;i++)
	{
		a[1][i]=-2;
		a[40][i]=-2;		
	}
	for(int i=1;i<=40;i++)
	{
		a[i][1]=-2;
		a[i][20]=-2;
	}		
}
void in()
{
	if(kbhit())
	{
		input=getch();
		if(input=='w'&&cy!=1)
		{
			cx=0;
			cy=-1;
		}
		if(input=='a'&&cx!=1)
		{
			cx=-1;
			cy=0;
		}
		if(input=='s'&&cy!=-1)
		{
			cx=0;
			cy=1;
		}
		if(input=='d'&&cx!=-1)
		{
			cx=1;
			cy=0;
		}
	}
}
void out()
{
	gotoxy(0,0);
	Sleep(turn);//蛇每15帧向既定方向位移一次 
	sk.x+=cx;
	sk.y+=cy;
	if(a[sk.x][sk.y]==-1)//吃到了
	{
		l++;
		food.x=rand()%38+2;
		food.y=rand()%18+2;
		while(a[food.x][food.y]>0)
		{
			food.x=rand()%38+2;
			food.y=rand()%18+2;
		}
		a[food.x][food.y]=-1;
	}
	else if(a[sk.x][sk.y]>0||a[sk.x][sk.y]==-2)//撞死了 
	{
		death=0;
	}
	for(int i=1;i<=20;i++)//利用延迟消除形成蛇身 
	{
		for(int j=1;j<=40;j++)
		{
			if(a[j][i]>0)a[j][i]--;
		}
	}
	a[sk.x][sk.y]=l;
	
	for(int i=1;i<=21;i++)
	{
		for(int j=1;j<=41;j++)
		{
			if(a[j][i]==0)
				printf(" ");
			else if(a[j][i]==-1)
				printf("*");
			else if(a[j][i]==-2)
				printf("+");
			else 
				printf("0");
		}
		printf("\n");
	}
	printf("longth:%d",l);
}
void finish()
{
	
}
int main()
{
	start();
	while(death)
	{
		in();
		out();
	}
	finish();
} 
