#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include<windows.h>
#include <conio.h>
void gotoxy(int x, int y) //���� 
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};//�ڶ���ֵΪ���ʾ�������
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
int l=3,s=0,mode; 
void start()
{
	srand(time(NULL));
	hidecursor();
	printf("\n���� 1 �� 0 ��ѡ��\"����ģʽ\"��\"����ģʽ\"");
	scanf("%d",&mode) ;
	printf("λ�Ƽ����50-500���룩��"); 
	scanf("%d",&turn); 
	system("cls");
	death=1;
	l=3;
	s=0;
	for(int i=1;i<=20;i++)//�����ӳ������γ����� 
		for(int j=1;j<=40;j++)
			a[j][i]=0;
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
	Sleep(turn);//��ÿ15֡��ȶ�����λ��һ�� 
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

void ML()
{
	l=1000;
	s++;
	if(a[sk.x][sk.y]==-1)//�Ե���
	{
		s+=50;
		food.x=rand()%38+2;
		food.y=rand()%18+2;
		while(a[food.x][food.y]>0)
		{
			food.x=rand()%38+2;
			food.y=rand()%18+2;
		}
		a[food.x][food.y]=-1;
	}
}
void MJ()
{
	if(a[sk.x][sk.y]==-1)//�Ե���
	{
		l+=1;
		food.x=rand()%38+2;
		food.y=rand()%18+2;
		while(a[food.x][food.y]>0)
		{
			food.x=rand()%38+2;
			food.y=rand()%18+2;
		}
		a[food.x][food.y]=-1;
	}
	for(int i=1;i<=20;i++)//�����ӳ������γ����� 
	{
		for(int j=1;j<=40;j++)
		{
			if(a[j][i]>0)a[j][i]--;
		}
	}
} 
void out()
{
	sk.x+=cx;
	sk.y+=cy;
	if(mode)
		MJ();
	else 
		ML();
	
	gotoxy(0,0);
	if(a[sk.x][sk.y]>0||a[sk.x][sk.y]==-2)//ײ���� 
	{
		death=0;
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
	printf("�÷�:%d",s);
}
int main()
{
	while(1)
	{
		start();
		while(death)
		{
			in();
			out();
		}
	}
	
} 
