#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void gamestart();
int gameover(int result);

void printmap(int(*data)[4]);

int randomnum();
void creatnewnum(int(*data)[4]);
//控制函数
void up(int(*data)[4], int test);
void down(int(*data)[4]);
void left(int(*data)[4], int test);
void right(int(*data)[4]);
//移动函数
void moveup(int(*data)[4]);
void movedown(int(*data)[4]);
void moveright(int(*data)[4]);
void moveleft(int(*data)[4]);

int cheakmap(int(*data)[4]);
int judgecontinue(int(*data)[4]);


int grade = 0;

int main()
{
	int result = 1;
	int again = 1;
	gamestart();
	for (; again;)
	{
		//初始化棋盘
		int data[4][4] = { 0 };
		int line, row;
		system("cls");
		srand((unsigned int)time(NULL));
		for (int times = 0; times < 3; times++) {
			line = rand() % 4;
			row = rand() % 4;
			data[line][row] = ((rand() % 2) + 1) * 2;
		}

		//主体
		for (;;)
		{
			//绘制棋盘
			printmap(data);

			//游戏控制
			for (int correct = 0; correct == 0;)
			{
				char control = _getch();
				switch (control)
				{
				case 'w':up(data, 1);
					correct = 1;
					break;
				case 's':down(data);
					correct = 1;
					break;
				case 'a':left(data, 1);
					correct = 1;
					break;
				case 'd':right(data);
					correct = 1;
					break;
				default:
					correct = 0;
					break;
				}
				fflush(stdin);
			}

			system("cls");

			//检查棋盘是否填满
			result = cheakmap(data);// 0未满  -1胜 1满(负)
			int judge;
			if (result == 0)
			{
				judge = 1;
				creatnewnum(data);//空位置中产生随机数
			}
			else if (result == -1)
			{
				//绘制棋盘并退出
				printmap(data);
				break;
			}
			else if (result == 1)
			{
				judge = judgecontinue(data);
			}

			if (judge == 0)
			{
				printmap(data);
				break;
			}
			

		}
		//判断是否重来
		again = gameover(result);
	}

	return 0;
}

void gamestart()
{
	printf_s("Weclome to \"2048\" \n"
		"			by 飞火流星\n");
	_getch();
}

int gameover(int result)
{
	//判断输赢
	if (result == -1)
	{
		printf_s("66666\n");
	}
	else if (result == 1)
	{
		printf_s("挂了吧~~渣渣 23333333333\n");
	}

	//是否重来	
	for (;;)
	{
		printf_s("再来一遍？ (Y/N):");
		char YN;
		scanf_s("%c", &YN);
		fflush(stdin);
		if (YN == 'N' || YN == 'n')
		{
			printf_s("一路走好\n");
			system("pause");
			return 0;
		}
		else if (YN == 'Y' || YN == 'y')
		{
			return 1;
		}
	}
}

int randomnum()
{
	int num;
	srand((unsigned int)time(NULL));
	num = ((rand() % 2) + 1) * 2;
	return num;
}

//90%
void creatnewnum(int(*data)[4]) {
	//记录空位置
	int emptylocalline[16] = { 0 };
	int emptylocalrow[16] = { 0 };
	int count = 0;
	int line, row;

	for (line = 0, row = 0; line < 4; line++)
	{
		for (row = 0; row < 4; row++)
		{
			if (data[line][row] == 0)
			{
				emptylocalline[count] = line;
				emptylocalrow[count] = row;
				count++;
			}
		}
	}

	//空位置中产生随机数
	int creattimes = rand() % 3 + 1;//产生个数

	for (int cnt = 0; cnt < creattimes; cnt++)
	{
		int creatlocal = rand() % count;
		line = emptylocalline[creatlocal];
		row = emptylocalrow[creatlocal];
		data[line][row] = randomnum();
	}
}

void printmap(int(*data)[4])
{
	//字符型版
	char board[4][4][5] = {0};
	//整型转字符型
	for(int line = 0, row = 0; row < 4; row++)
	{
		for (line = 0; line < 4; line++)
		{
			itoa(data[line][row],board[line][row],10);
		}
	}
	//'0'\0 转 \0
	for(int line = 0, row = 0; row < 4; row++)
	{
		for (line = 0; line < 4; line++)
		{
			if(board[line][row][0] == '0')
			{
				board[line][row][0] = 0;
			}
		}
	}
	//输出棋盘
	printf(	"┌─────┬─────┬─────┬─────┐\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"│%5s     │%5s     │%5s     │%5s     │\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"├─────┼─────┼─────┼─────┤\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"│%5s     │%5s     │%5s     │%5s     │\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"├─────┼─────┼─────┼─────┤\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"│%5s     │%5s     │%5s     │%5s     │\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"├─────┼─────┼─────┼─────┤\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"│%5s     │%5s     │%5s     │%5s     │\n"
			"│          │          │          │          │\n"
			"│          │          │          │          │\n"
			"└─────┴─────┴─────┴─────┘\n",
		board[0][0], board[0][1], board[0][2], board[0][3],
		board[1][0], board[1][1], board[1][2], board[1][3],
		board[2][0], board[2][1], board[2][2], board[2][3],
		board[3][0], board[3][1], board[3][2], board[3][3]);


	printf("Score:%d\n", grade);
}

void up(int(*data)[4], int test)
{
	moveup(data);

	int line = 0, row = 0;
	//比较与合并 line < 4 && 
	for (row = 0; row < 4; row++)//第一列扫起
	{
		for (line = 0; line < 3; line++)//首行扫起
		{
			if (data[line][row] == data[line + 1][row])//当前行与下一行相等
			{
				data[line][row] = data[line][row] * 2;//当前行值*2
				if (test)
				{
					grade += data[line][row];
				}
				data[line + 1][row] = 0;//当前行取0
			}
		}
	}

	moveup(data);
}

void down(int(*data)[4])
{
	movedown(data);
	//比较与合并 line != 0 &&
	int line = 3, row = 0;
	for (row = 0; row < 4; row++)//首列扫起
	{
		for (line = 3; line > 0; line--)//末行扫起
		{
			if (data[line][row] == data[line - 1][row])//当前行与上一行相等
			{
				data[line][row] = data[line][row] * 2;//当前行值*2
				grade += data[line][row];
				data[line - 1][row] = 0;//当前行取0
			}
		}

	}
	movedown(data);
}

void left(int(*data)[4], int test)//左
{
	moveleft(data);

	//比较与合并 && row != 3
	int line = 0, row = 0;
	for (line = 0; line < 4; line++)//首行扫起
	{
		for (row = 0; row < 3; row++)//首列扫起
		{
			if (data[line][row] == data[line][row + 1])//当前列与下一列相等
			{
				data[line][row] = data[line][row] * 2;//当前列值*2
				if (test)
				{
					grade += data[line][row];
				}
				data[line][row + 1] = 0;//当前列取0
			}
		}
	}

	moveleft(data);
}

void right(int(*data)[4])
{
	moveright(data);

	//合并
	int line = 0, row = 3;
	for (line = 0; line < 4; line++)
	{
		for (row = 3; row > 0; row--)
		{
			if (data[line][row] == data[line][row - 1])
			{
				data[line][row] = data[line][row] * 2;
				grade += data[line][row];
				data[line][row - 1] = 0;
			}
		}
	}

	moveright(data);
}

void moveup(int(*data)[4]) {
	int line = 0, row = 0;
	int cnt = 0;//计数君

				//先行后列  line < 4 && 
	for (line = 0, row = 0; row < 4; row++)//扫列
	{
		int temp[4] = { 0 };//临时存放
							//扫行
							//存放
		for (line = 0, cnt = 0; line < 4; line++)
		{
			if (data[line][row] != 0)
			{
				temp[cnt] = data[line][row];
				cnt++;
				data[line][row] = 0;
			}
		}
		//取出
		for (line = 0, cnt = 0; line < 4; line++)
		{
			data[line][row] = temp[cnt];
			cnt++;
		}
		//重置
		//line = 0;
	}

}

void movedown(int(*data)[4]) {
	int line = 0, row = 0;
	int cnt = 0;//计数君

				//先行后列 line >= 0 &&
	for (line = 3, row = 0; row < 4; row++)//扫列
	{
		int temp[4] = { 0 };//临时存放
							//扫行
							//存放
		for (line = 3, cnt = 0; line >= 0; line--)
		{
			if (data[line][row] != 0)
			{
				temp[cnt] = data[line][row];
				cnt++;
				data[line][row] = 0;
			}
		}
		//取出
		for (line = 3, cnt = 0; line >= 0; line--)
		{
			data[line][row] = temp[cnt];
			cnt++;
		}
		//重置
		//line = 0;
	}
}

void moveleft(int(*data)[4]) {
	int line = 0, row = 0;
	int cnt = 0;//计数君

				//先列后行
	for (line = 0, row = 0; line < 4; line++)//扫行
	{
		int temp[4] = { 0 };//临时存放
							//扫列
							//存放
		for (row = 0, cnt = 0; row < 4; row++)
		{
			if (data[line][row] != 0)
			{
				temp[cnt] = data[line][row];
				cnt++;
				data[line][row] = 0;
			}
		}
		//取出
		for (row = 0, cnt = 0; row < 4; row++)
		{
			data[line][row] = temp[cnt];
			cnt++;
		}
	}
}

void moveright(int(*data)[4]) {
	int line = 0, row = 0;
	int cnt = 0;//计数君

				//先列后行
	for (line = 0, row = 0; line < 4; line++)//扫行
	{
		int temp[4] = { 0 };//临时存放
							//扫列
							//存放
		for (row = 3, cnt = 0; row >= 0; row--)
		{
			if (data[line][row] != 0)
			{
				temp[cnt] = data[line][row];
				cnt++;
				data[line][row] = 0;
			}
		}
		//取出
		for (row = 3, cnt = 0; row >= 0; row--)
		{
			data[line][row] = temp[cnt];
			cnt++;
		}

	}
}

//90%
//检查棋盘是否填充满
int cheakmap(int(*data)[4])
{
	int line = 0, row = 0;

	//设棋盘初始为满
	int full = 1;

	//判断输赢 (pass)
	for (line = 0, row = 0; line < 4; line++)//扫描行
	{
		for (row = 0; row < 4; row++)//扫描列
		{
			if (data[line][row] == 2048)
			{
				full = -1;
				break;
			}
		}

		if (full == -1)
		{
			break;
		}
	}

	//判断棋盘是否为满
	for (line = 0, row = 0; line < 4 && full != -1; line++)
	{
		for (row = 0; row < 4; row++)
		{
			//若有值为0的格子就退出循环
			if (data[line][row] == 0) {
				full = 0;
				break;
			}
		}

		if (full == 0)
		{
			break;
		}
	}


	if (full == 1)
	{
		return 1;//棋盘已满
	}
	else if (full == 0)
	{
		return 0;//棋盘未满
	}
	else if (full == -1)
	{
		return -1;//胜利
	}
}

int judgecontinue(int(*data)[4]) 
{
	int judge;

	int temp[4][4];
	for (int line = 0, row = 0; line < 4; line++) {
		for ( row = 0; row < 4; row++)
		{
			temp[line][row] = data[line][row];
		}
	}

	up(temp, 0);
	judge = cheakmap(temp);
	if (judge == 0)
	{
		return  1;//可继续
	}

	left(temp, 0);
	judge = cheakmap(temp);
	if (judge == 0)
	{
		return 1;//可继续
	}

	return 0;//不可继续
}
