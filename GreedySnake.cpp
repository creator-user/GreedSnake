#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

//枚举类型方位
enum Direction
{
	UP, DOWN, LEFT, RIGHT
};
/**************类的定义****************/
//边界方块
class boundary
{
	char* ch;
public:
	COORD coord;//存储坐标
	boundary(){
		ch = (char*)"■";
		coord.X = 0;
		coord.Y = 0;
	}
	//设置坐标
	void setXY(int x,int y) {
		coord.X = x;
		coord.Y = y;
	}
	//打印方块
	void printBoundary() {
		//获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 9);//字体颜色
		SetConsoleCursorPosition(ConsoleHandle, coord);//移动光标
		cout << ch;
	}
};
//墙块
class wall {
	char* ch;
public:
	COORD block;
	wall() {
		ch = (char*)"■";
		block.X = 0;
		block.Y = 0;
	}
	//设置坐标
	void setXY(int x,int y) {
		block.X = x;
		block.Y = y;
	}
	//打印方块
	void printWall() {
		//获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 10);//字体颜色
		SetConsoleCursorPosition(ConsoleHandle, block);//移动光标
		cout << ch;
	}
};
//食物
class Food {
	char* ch;
	COORD position;
public:
	Food() {
		ch = (char*)"★";
		position.X = 10;
		position.Y = 10;
	}
	//设置坐标
	void setPosition(COORD p)
	{
		position = p;
	}
	void printCh() {
		//获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 14);//字体颜色
		SetConsoleCursorPosition(ConsoleHandle, position);//移动光标
		cout << ch;
	}
};
//蛇
class Snake {

public:
	COORD head;//蛇头位置
	COORD tail; //上一次蛇尾位置
	COORD body[100];//蛇身位置
	int len;     //蛇长
	char* ch0;
	Direction direc;//实时方位
	//赋初值
	Snake() {
		ch0 = (char*)"●";
		len = 5;
		head.X = 45;
		head.Y = 5;
		tail.X = head.X + len;
		tail.Y = head.Y;
		for (int i = 0; i < len; i++) {
			body[i].X = head.X - (2 * i);//头在右，身体在左
			body[i].Y = head.Y;
		}
		direc = RIGHT;
	}
	void change_dir(char ch) {
		//改变方向（不能是同一直线上改方向）
		switch (ch) {
		case 72:if (direc != UP && direc != DOWN)direc = UP; break;
		case 75:if (direc != LEFT && direc != RIGHT)direc = LEFT; break;
		case 77:if (direc != LEFT && direc != RIGHT)direc = RIGHT; break;
		case 80:if (direc != UP && direc != DOWN)direc = DOWN; break;
		}
	}
	//打印实时蛇位置
	void printSnake() {
		//获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(ConsoleHandle, 12);//字体颜色
		//删除上一次的蛇尾
		SetConsoleCursorPosition(ConsoleHandle, tail);
		cout << " ";
		tail = body[len - 1];//更新蛇尾位置
		for (int i = 0; i < len; i++) {
			//打印此次蛇
			SetConsoleCursorPosition(ConsoleHandle, body[i]);//移动光标
			cout << ch0;
		}
	}
};

/***************函数定义****************/
//设置食物
void setfood(Food food, Snake snake, COORD& foodPosition, wall wall[]) {//设置食物
	srand((int)time(0));
	//找到符合条件的坐标位置
	int m = 1;
	do {
		foodPosition.X = rand() % 55;
		foodPosition.Y = rand() % 28;
		if (foodPosition.X >= 3 && foodPosition.X <= 54 && foodPosition.Y >= 2 && foodPosition.Y <= 27 && foodPosition.Y % 2 == 0 && foodPosition.X % 2 == 1) {//在界限内
			for (int i = 0; i < snake.len; i++) {
				if (snake.body[i].X == foodPosition.X && snake.body[i].Y == foodPosition.Y) {//不为蛇身
					m = 0;
					break;
				}
			}
			for (int i = 0; i < 50;i++) {
				if (wall[i].block.X == foodPosition.X && wall[i].block.Y == foodPosition.Y) {//不为墙
					m = 0;
					break;
				}
			}
			if (m == 1) {
				break;
			}
		}
	} while (1);
	food.setPosition(foodPosition);
	food.printCh();
}
//蛇的移动
int move(Snake &snake, COORD foodPosition, wall wall[])
{
	//判断食物
	if (snake.head.X == foodPosition.X && snake.head.Y == foodPosition.Y) {
		return 1;
	}
	else {//判断墙
		for (int i = 0; i < 100; i++) {
			if (snake.head.X == wall[i].block.X && snake.head.Y == wall[i].block.Y)
				return 2;
		}
		for (int i = 1; i < snake.len; i++) {
			if (snake.head.X == snake.body[i].X && snake.head.Y == snake.body[i].Y)
				return 3;
		}
	}
	//删除尾巴，整体后移
	for (int i = snake.len - 1; i > 0; i--) {
		snake.body[i] = snake.body[i - 1];
	}
	//判断方向
	switch (snake.direc) {
	case UP:snake.head.Y--; break;
	case DOWN:snake.head.Y++; break;
	case LEFT:snake.head.X -= 2; break;
	case RIGHT:snake.head.X += 2; break;
	}
	//穿越边界
	if (snake.head.X > 55)
		snake.head.X = 3;
	else if (snake.head.X < 2)
		snake.head.X = 55;
	else if (snake.head.Y < 2)
		snake.head.Y = 27;
	else if (snake.head.Y > 27)
		snake.head.Y = 2;

	snake.body[0] = snake.head;//插入新头
	return 0;
}
//检测输入，改变蛇方向
void input(Snake& snake, char& ch)
{
	if (_kbhit()){//判断有键盘输入
		_getch();//清除无关字符
		ch = _getch();//读取键盘输入值
	}
	//改变方向（不能是同一直线上改方向）
	snake.change_dir(ch);
}
//初始化界面
void InitGraph(boundary boundary[4][27],int flag)
{
	//获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(ConsoleHandle, 0);//字体颜色
	system("cls");
	//画边界
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 27; j++) {
			switch (i) {
			case 0: boundary[i][j].setXY(j * 2 + 3, 1); break;
			case 1: boundary[i][j].setXY(j * 2 + 2, 28); break;
			case 2: boundary[i][j].setXY(2, j + 2); break;
			case 3: boundary[i][j].setXY(56, j + 2); break;
			}
			boundary[i][j].printBoundary();
		}
	}
	COORD ps;
	ps.X = 70;
	ps.Y = 1;
	SetConsoleTextAttribute(ConsoleHandle, 15);//字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps);//移动光标
	cout << "Greedy Snake" << endl;
	cout << "\t\t\t\t\t\t\t\t\t贪吃蛇" << endl;
	cout << "\t\t\t\t\t\t\t\t关卡：" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t第"<<flag<<"关"<< endl;
	cout << "\t\t\t\t\t\t\t\t用时：" << endl;
	ps.X = 65;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 12);//字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps);//移动光标
	cout << "请按方向键移动" << endl;
}
//打印墙
void setWall(wall wall[50],int flag) {
	int index = 0;
	//画墙
	if (flag == 1) {//第一关
		for (int i = 3; i < 56; i += 2) {
			wall[index].setXY(i, 15);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 2) {//第二关
		for (int i = 2; i <= 14; i++) {//左上
			wall[index].setXY(19, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 29; i <= 55; i += 2) {//右上
			wall[index].setXY(i, 10);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 29; i += 2) {//左上
			wall[index].setXY(i, 18);
			wall[index].printWall();
			index++;
		}
		for (int i = 14; i <= 27; i++) {//右下
			wall[index].setXY(37, i);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 3) {//第三关
		for (int i = 2; i <= 27; i++) {//竖线
			wall[index].setXY(29, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 55; i+=2) {//横线
			wall[index].setXY(i, 14);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 4) {//第四关
		for (int i = 3; i <= 9; i+=2) {
			wall[index].setXY(i, 2);
			wall[index].printWall();
			index++;
		}
		for (int i = 17; i <= 49; i+=2) {
			wall[index].setXY(i, 2);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 4; i++) {
			wall[index].setXY(3, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i < 10; i++) {
			wall[index].setXY(27, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 55; i+=2) {
			if (i != 29 && i != 33 && i != 31) {
				wall[index].setXY(i, 10);
				wall[index].printWall();
				index++;
			}
		}
		for (int i = 3; i <= 55; i+=2) {
			wall[index].setXY(i, 20);
			wall[index].printWall();
			index++;
		}
		for (int i = 20; i <= 27; i++) {
			wall[index].setXY(27, i);
			wall[index].printWall();
			index++;
		}
	}
}

//失败菜单
void judgeFail(int judge,int time) {
	//获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	ps.X = 24;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 15);//字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps);//移动光标
	if (judge == 2) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              Game Over!!!             |" << endl;
		cout << "\t\t\t|         很遗憾你撞上墙失败了！        |" << endl;
		cout << "\t\t\t|                〒▽〒                  |" << endl;
		cout << "\t\t\t|   才刚刚过去了 " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                       |" << endl;
		cout << "\t\t\t ----------------------------------------" << endl;
	}
	else if (judge == 3) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              Game Over!!!             |" << endl;
		cout << "\t\t\t|         很遗憾你撞上自己失败了！      |" << endl;
		cout << "\t\t\t|                〒▽〒                  |" << endl;
		cout << "\t\t\t|   才刚刚过去了 " << time << "s\t\t        |" << endl;
		cout << "\t\t\t|                                       |" << endl;
		cout << "\t\t\t ----------------------------------------" << endl;
	}
	if (judge != 0) {
		ps.X = 28;
		ps.Y = 15;
		SetConsoleCursorPosition(ConsoleHandle, ps);//移动光标
		system("pause");
		exit(0);
	}
}

//胜利菜单
int judgeSuccess(int time, int a)
{
	//获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int key = 1;//当前选中项
	COORD b1 = { 24,10 };
	SetConsoleTextAttribute(ConsoleHandle, 13);//字体颜色
	SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
	if (a != 4) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              you win!!!                |" << endl;
		cout << "\t\t\t|           恭喜你通过本关！             |" << endl;
		cout << "\t\t\t|你所用时为：                            |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << "\t\t\t|请选择你的下一步操作：                  |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << " \t\t\t ----------------------------------------" << endl;
		b1 = { 47,17 };
		SetConsoleTextAttribute(ConsoleHandle, 253);//字体颜色
		SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
		cout << "退出";
		b1 = { 53,17 };
		SetConsoleTextAttribute(ConsoleHandle, 13);//字体颜色
		SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
		cout << "下一关";
		while (1) {
			char ch = _getch();
			//ch = _getch();
			switch (ch) {
			case 75://left
				switch (key) {
				case 2:b1 = { 47,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 253);//字体颜色
					  SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
					  cout << "退出";
					  b1 = { 53,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 13);//字体颜色
					  SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
					  cout << "下一关";
					  key--; break;
				}break;
			case 77://right
				switch (key) {
				case 1:b1 = { 47,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 13);//字体颜色
					  SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
					  cout << "退出";
					  b1 = { 53,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 253);//字体颜色
					  SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
					  cout << "下一关";
					  key++; break;
				}break;
			case 13://enter
				return key;
			default:break;
			}
		}
	}
	else
	{
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              you win!!!                |" << endl;
		cout << "\t\t\t|           恭喜你全部通关！             |" << endl;
		cout << "\t\t\t|你本关用时为：                          |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << " \t\t\t ----------------------------------------" << endl;
		b1.X = 28;
		b1.Y = 15;
		SetConsoleCursorPosition(ConsoleHandle, b1);//移动光标
		system("pause");
		exit(0);
	}
}

//打印时间
void printTime(int time) {
	//获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pt;
	pt.X = 80;
	pt.Y = 6;
	SetConsoleTextAttribute(ConsoleHandle, 15);//字体颜色
	SetConsoleCursorPosition(ConsoleHandle, pt);//移动光标
	cout << time << "s";
}

//游戏主程序
void game(int &time, int flag) {
	clock_t start, end;
	//定义边界对象
	boundary boundary[4][27];
	wall wall[100];
	Food food;
	Snake snake;
	char ch = 77;//获取键盘值，初始为右
	COORD foodPosition;//食物坐标
	foodPosition.X = 0; foodPosition.Y = 0;//初始化

	//画边界
	InitGraph(boundary,flag);
	//画墙
	setWall(wall, flag);
	//设置食物
	setfood(food, snake, foodPosition, wall);
	int judge = 0;
	start = clock();//计时开始
	while (1) {
		//打印蛇
		snake.printSnake();
		Sleep(100);//速度控制
		//获取键盘输入
		input(snake, ch);
		//蛇移动  判断结束
		judge = move(snake, foodPosition, wall);
		if (judge == 1)//吃到食物
			return;
		//计时
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
		printTime(time);
		//结束菜单
		judgeFail(judge, time);
	}
}
int main()
{
	//隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	int time = 0;//总时间
	int flag;
	int a = 1;//关卡
	while (1) {
		flag = 0;
		game(time,a);
		flag = judgeSuccess(time,a);
		if (flag == 1)
			break;
		else if (flag == 2) {
			a++;
		}
	}
	return 0;
}