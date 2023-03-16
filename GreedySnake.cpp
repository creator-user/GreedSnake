#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

//枚举类型方位
enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

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
		head.X = 13;
		head.Y = 5;
		tail.X = head.X + len;
		tail.Y = head.Y;
		for (int i = 0; i < len; i++) {
			body[i].X = head.X + (i + 1);
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
			//打印此次蛇头
			SetConsoleCursorPosition(ConsoleHandle, body[i]);//移动光标
			cout << ch0;
		}
		
	}
};


int move(Snake &snake, COORD foodPosition)
{
	
	//判断食物
	if (snake.head.X == foodPosition.X && snake.head.Y == foodPosition.Y) {
		return 1;
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

void InitGraph(boundary boundary[4][27])
{
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
}

//结束菜单
void judgeSuccess(int judge) {
	if (judge == 1)//吃到食物
	{
		cout << "闯关成功！" << endl;
	}
}
int main()
{
	//定义边界对象
	boundary boundary[4][27];
	Food food;
	Snake snake;
	char ch = 77;//获取键盘值，初始为右
	//隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	//画边界
	InitGraph(boundary);
	//设置食物
	COORD foodPosition;
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
			if (m == 1) {
				break;
			}
		}
	} while (1);
	food.setPosition(foodPosition);
	food.printCh();
	int judge = 0;
	while (1) {
		snake.printSnake();
		input(snake, ch);
	    judge = move(snake, foodPosition);
		judgeSuccess(judge);
		Sleep(100);
	}
	printf("\n\n\n");
	return 0;
}