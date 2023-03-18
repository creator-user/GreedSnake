#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
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
	void setPosition(short x,short y)
	{
		position = {x,y};
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
//蛇标题动画小块
class SnakeTitle
{
	enum derec
	{
		LEFT,
		RIGHT
	};
	char* ch;
	derec derection; // 正在前进的方向

public:
	COORD p;
	SnakeTitle()
	{
		derection = RIGHT;
		ch = (char*)"●";
		p = { 0, 0 };
	}
	//赋值坐标
	void setXY(short x, short y)
	{
		p = { x, y };
	}
	//打印该字符
	void printCh()
	{
		// 获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 9);  // 字体颜色
		SetConsoleCursorPosition(ConsoleHandle, p); // 移动光标
		cout << ch;
	}
	//清除该字符
	void Clear()
	{
		// 获取句柄
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 9);  // 字体颜色
		SetConsoleCursorPosition(ConsoleHandle, p); // 移动光标
		cout << " ";
		if (p.X == 50)
			derection = RIGHT;
		else if (p.X == 58)
			derection = LEFT;
		if (derection == RIGHT)
			p.X += 2;
		else if (derection == LEFT)
			p.X -= 2;
	}
};
/***************函数定义****************/
//指定位置打印指定字符串
void print_title_block(short x, short y, char* ch)
{
	// 获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p = { x, y };
	SetConsoleTextAttribute(ConsoleHandle, 9);  // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, p); // 移动光标
	cout << ch;
}
//开篇动画
void cartoon() {
	//蛇
	SnakeTitle MoveSnake[15];
	//赋值初始坐标
	MoveSnake[0].setXY(50, 15);
	MoveSnake[1].setXY(52, 16);
	MoveSnake[2].setXY(54, 17);
	MoveSnake[3].setXY(56, 18);
	MoveSnake[4].setXY(58, 19);

	MoveSnake[5].setXY(50, 23);
	MoveSnake[6].setXY(52, 22);
	MoveSnake[7].setXY(54, 21);
	MoveSnake[8].setXY(56, 20);

	MoveSnake[9].setXY(52, 24);
	MoveSnake[10].setXY(54, 25);
	MoveSnake[11].setXY(56, 26);
	MoveSnake[12].setXY(58, 27);
	for (int i = 0; i < 16; i++)
	{//打印
		for (int j = 0; j < 13; j++)
		{
			MoveSnake[j].printCh();
		}
		Sleep(80);
		//清除
		for (int j = 0; j < 13; j++)
		{
			MoveSnake[j].Clear();
			MoveSnake[j].setXY(MoveSnake[j].p.X, (MoveSnake[j].p.Y) -= 1);
		}
	}
	// title title_block[100];
	for (int i = 25; i > 0; i--)
	{

		// 绘制贪吃蛇标题
		for (int x = 30; x <= 90; x += 2)
			if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 60 || x == 62 || x == 72 || x == 78 || (x >= 84 && x <= 90))
				print_title_block(x, i, (char*)"■");

		for (int x = 30; x <= 90; x += 2)
			if (x == 30 || x == 42 || x == 44 || x == 50 || x == 72 || x == 76 || x == 84)
				print_title_block(x, i + 1, (char*)"■");

		for (int x = 30; x <= 90; x += 2)
			if ((x >= 30 && x <= 36) || (x >= 58 && x <= 64) || x == 42 || x == 46 || x == 50 || x == 72 || x == 74 || (x >= 84 && x <= 90))
				print_title_block(x, i + 2, (char*)"■");

		for (int x = 30; x <= 90; x += 2)
			if (x == 36 || x == 42 || x == 48 || x == 50 || x == 72 || x == 76 || x == 72 || x == 84)
				print_title_block(x, i + 3, (char*)"■");

		for (int x = 30; x <= 90; x += 2)
			if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 56 || x == 66 || x == 72 || x == 78 || (x >= 84 && x <= 90))
				print_title_block(x, i + 4, (char*)"■");

		Sleep(60); // 显示

		// 删除此次标题，为下一次移动准备
		if (i != 1)
		{

			for (int x = 30; x <= 90; x += 2)
				if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 60 || x == 62 || x == 72 || x == 78 || (x >= 84 && x <= 90))
					print_title_block(x, i, (char*)" ");

			for (int x = 30; x <= 90; x += 2)
				if (x == 30 || x == 42 || x == 44 || x == 50 || x == 72 || x == 76 || x == 84)
					print_title_block(x, i + 1, (char*)" ");

			for (int x = 30; x <= 90; x += 2)
				if ((x >= 30 && x <= 36) || (x >= 58 && x <= 64) || x == 42 || x == 46 || x == 50 || x == 72 || x == 74 || (x >= 84 && x <= 90))
					print_title_block(x, i + 2, (char*)" ");

			for (int x = 30; x <= 90; x += 2)
				if (x == 36 || x == 42 || x == 48 || x == 50 || x == 72 || x == 76 || x == 72 || x == 84)
					print_title_block(x, i + 3, (char*)" ");

			for (int x = 30; x <= 90; x += 2)
				if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 56 || x == 66 || x == 72 || x == 78 || (x >= 84 && x <= 90))
					print_title_block(x, i + 4, (char*)" ");
		}
	}
	cout << "\n\n\t\t\tPress any key to start...\n\t\t\t";
	system("pause");
}
//设置食物
void setfood(Food food, Snake snake, COORD& foodPosition, wall wall[100]) {//设置食物
	srand(time(0));
	//找到符合条件的坐标位置
	int m = 1;
	while (1){
		foodPosition.X = rand() % 55;
		foodPosition.Y = rand() % 28;
		if (foodPosition.X >= 3 && foodPosition.X <= 54 && foodPosition.Y >= 2 && foodPosition.Y <= 27 && foodPosition.X % 2 == 1) {//在界限内
			for (int i = 0; i < snake.len; i++) {
				if (snake.body[i].X == foodPosition.X && snake.body[i].Y == foodPosition.Y) {//不为蛇身
					m = 0;
					break;
				}
			}
			if (m == 0) {
				continue;
			}
			for (int i = 0; i < 100; i++) {
				if (wall[i].block.X == foodPosition.X && wall[i].block.Y == foodPosition.Y) {//不为墙
					m = 0;
					break;
				}
			}
			if (m == 1) {
				break;
			}
			else
				continue;
		}
		else
			continue;
	}
	food.setPosition(foodPosition.X, foodPosition.Y);
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
int judgeFail(int judge,int time) {
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
		return 0;
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
		return 0;
	}
}

//主菜单一
int main_menu1() {
	// 绘制贪吃蛇标题
	for (int x = 30; x <= 90; x += 2)
		if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 60 || x == 62 || x == 72 || x == 78 || (x >= 84 && x <= 90))
			print_title_block(x, 1, (char*)"■");

	for (int x = 30; x <= 90; x += 2)
		if (x == 30 || x == 42 || x == 44 || x == 50 || x == 72 || x == 76 || x == 84)
			print_title_block(x, 2, (char*)"■");

	for (int x = 30; x <= 90; x += 2)
		if ((x >= 30 && x <= 36) || (x >= 58 && x <= 64) || x == 42 || x == 46 || x == 50 || x == 72 || x == 74 || (x >= 84 && x <= 90))
			print_title_block(x, 3, (char*)"■");

	for (int x = 30; x <= 90; x += 2)
		if (x == 36 || x == 42 || x == 48 || x == 50 || x == 72 || x == 76 || x == 72 || x == 84)
			print_title_block(x, 4, (char*)"■");

	for (int x = 30; x <= 90; x += 2)
		if ((x >= 30 && x <= 36) || x == 42 || x == 50 || x == 56 || x == 66 || x == 72 || x == 78 || (x >= 84 && x <= 90))
			print_title_block(x, 5, (char*)"■");
	// 获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	int key = 1; // 当前选关
	ps.X = 82;
	ps.Y = 8;
	SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "闯关模式" << endl;
	ps.X = 82;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "选关模式" << endl;
	ps.X = 82;
	ps.Y = 12;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "退出游戏" << endl;
	char ch;
	while (1)
	{
		ch = _getch();
		switch (ch)
		{
		case 72://up键
			if (key != 1)//不为最上方
			{
				switch (key)
				{
				case 2:
					ps.X = 82;
					ps.Y = 8;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "闯关模式" << endl;
					ps.X = 82;
					ps.Y = 10;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "选关模式" << endl;
					key--;
					break;
				case 3:
					ps.X = 82;
					ps.Y = 10;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "选关模式" << endl;
					ps.X = 82;
					ps.Y = 12;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "退出游戏" << endl;
					key--;
					break;
				}
			}
			break;
		case 80://down键
			if (key != 3)//不为最下方
			{
				switch (key)
				{
				case 1:
					ps.X = 82;
					ps.Y = 8;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "闯关模式" << endl;
					ps.X = 82;
					ps.Y = 10;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "选关模式" << endl;
					key++;
					break;
				case 2:
					ps.X = 82;
					ps.Y = 10;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "选关模式" << endl;
					ps.X = 82;
					ps.Y = 12;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "退出游戏" << endl;
					key++;
					break;
				}
			}
			break;
		case 13:
			return key;
			break;
		default:
			break;
		}
	}
}

//主菜单二
int main_menu2()
{
	// 获取句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	int key = 1; // 当前选关
	ps.X = 55;
	ps.Y = 3;
	SetConsoleTextAttribute(ConsoleHandle, 10); // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "选关模式" << endl;
	ps.X = 60;
	ps.Y = 5;
	SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "第一关" << endl;
	ps.X = 60;
	ps.Y = 7;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "第二关" << endl;
	ps.X = 60;
	ps.Y = 9;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "第三关" << endl;
	ps.X = 60;
	ps.Y = 11;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "第四关" << endl;
	ps.X = 60;
	ps.Y = 13;
	SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
	SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
	cout << "退回" << endl;
	char ch;
	while (1)
	{
		ch = _getch();
		switch (ch)
		{
		case 72:
			if (key != 1)
			{
				switch (key)
				{
				case 2:
					ps.X = 60;
					ps.Y = 5;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第一关" << endl;
					ps.X = 60;
					ps.Y = 7;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第二关" << endl;
					key--;
					break;
				case 3:
					ps.X = 60;
					ps.Y = 7;
					SetConsoleTextAttribute(ConsoleHandle, 249); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第二关" << endl;
					ps.X = 60;
					ps.Y = 9;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第三关" << endl;
					key--;
					break;
				case 4:
					ps.X = 60;
					ps.Y = 9;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第三关" << endl;
					ps.X = 60;
					ps.Y = 11;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第四关" << endl;
					key--;
					break;
				case 5:
					ps.X = 60;
					ps.Y = 11;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第四关" << endl;
					ps.X = 60;
					ps.Y = 13;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "退回" << endl;
					key--;
					break;
				}
			}
			break;
		case 80:
			if (key != 5)
			{
				switch (key)
				{
				case 1:
					ps.X = 60;
					ps.Y = 5;
					SetConsoleTextAttribute(ConsoleHandle, 9); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第一关" << endl;
					ps.X = 60;
					ps.Y = 7;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第二关" << endl;
					key++;
					break;
				case 2:
					ps.X = 60;
					ps.Y = 7;
					SetConsoleTextAttribute(ConsoleHandle, 9); // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第二关" << endl;
					ps.X = 60;
					ps.Y = 9;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第三关" << endl;
					key++;
					break;
				case 3:
					ps.X = 60;
					ps.Y = 9;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第三关" << endl;
					ps.X = 60;
					ps.Y = 11;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第四关" << endl;
					key++;
					break;
				case 4:
					ps.X = 60;
					ps.Y = 11;
					SetConsoleTextAttribute(ConsoleHandle, 9);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "第四关" << endl;
					ps.X = 60;
					ps.Y = 13;
					SetConsoleTextAttribute(ConsoleHandle, 249);   // 字体颜色
					SetConsoleCursorPosition(ConsoleHandle, ps); // 移动光标
					cout << "退回" << endl;
					key++;
					break;
				}
			}
			break;
		case 13:
			return key;
			break;
		default:
			break;
		}
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
int game(int &time, int flag) {
	clock_t start, end;
	//定义边界对象
	boundary boundary[4][27];
	wall wall[100];
	Food food;
	Snake snake;
	char ch = 77;//获取键盘值，初始为右
	COORD foodPosition{};//食物坐标

	//初始化
	InitGraph(boundary,flag);
	//画墙
	setWall(wall, flag);
	//设置食物
	setfood(food, snake, foodPosition, wall);
	int judge1 = 0,judge2 = 1;
	start = clock();//计时开始
	while (1) {
		//打印蛇
		snake.printSnake();
		Sleep(100);//速度控制
		//获取键盘输入
		input(snake, ch);
		//蛇移动  判断结束
		judge1 = move(snake, foodPosition, wall);
		if (judge1 == 1)//吃到食物
			return 1;
		//计时
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
		printTime(time);
		//结束菜单
		judge2 = judgeFail(judge1, time);
		if (judge2 == 0)
			return 0;
	}
}
int main()
{
	//隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	int time = 0;//总时间
	int flag,menu1,menu2;//
	int a = 1;//关卡
	//开场动画
	cartoon();
	while (1) {
		menu1 = main_menu1();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);  // 黑色清屏
		system("cls");
		if (menu1 == 1) {//闯关模式
			while (1) {
				flag = 0;
				flag = game(time, a);
				if (flag == 0)//游戏失败返回菜单
					break;
				flag = judgeSuccess(time, a);
				if (flag == 1 || flag == 0)//退回主菜单
					break;
				else if (flag == 2) {//下一关
					a++;
				}
			}
		}
		while (menu1 == 2) {//选关模式
			system("cls");
			menu2 = main_menu2();
			switch (menu2) {
			case 1:flag = game(time, 1); break;
			case 2:flag = game(time, 2); break;
			case 3:flag = game(time, 3); break;
			case 4:flag = game(time, 4); break;
			case 5:break;
			}
			if (menu2 == 5)
				break;
			if (flag == 1)
				judgeSuccess(time, 4);
		}
		if (menu1 == 3)//退出
			break;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);  // 黑色清屏
		system("cls");
	}
	return 0;
}