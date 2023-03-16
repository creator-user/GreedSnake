#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

//ö�����ͷ�λ
enum Direction
{
	UP, DOWN, LEFT, RIGHT
};
/**************��Ķ���****************/
//�߽緽��
class boundary
{
	char* ch;
public:
	COORD coord;//�洢����
	boundary(){
		ch = (char*)"��";
		coord.X = 0;
		coord.Y = 0;
	}
	//��������
	void setXY(int x,int y) {
		coord.X = x;
		coord.Y = y;
	}
	//��ӡ����
	void printBoundary() {
		//��ȡ���
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 9);//������ɫ
		SetConsoleCursorPosition(ConsoleHandle, coord);//�ƶ����
		cout << ch;
	}
};
//ǽ��
class wall {
	char* ch;
public:
	COORD block;
	wall() {
		ch = (char*)"��";
		block.X = 0;
		block.Y = 0;
	}
	//��������
	void setXY(int x,int y) {
		block.X = x;
		block.Y = y;
	}
	//��ӡ����
	void printWall() {
		//��ȡ���
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 10);//������ɫ
		SetConsoleCursorPosition(ConsoleHandle, block);//�ƶ����
		cout << ch;
	}
};
//ʳ��
class Food {
	char* ch;
	COORD position;
public:
	Food() {
		ch = (char*)"��";
		position.X = 10;
		position.Y = 10;
	}
	//��������
	void setPosition(COORD p)
	{
		position = p;
	}
	void printCh() {
		//��ȡ���
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(ConsoleHandle, 14);//������ɫ
		SetConsoleCursorPosition(ConsoleHandle, position);//�ƶ����
		cout << ch;
	}
};
//��
class Snake {

public:
	COORD head;//��ͷλ��
	COORD tail; //��һ����βλ��
	COORD body[100];//����λ��
	int len;     //�߳�
	char* ch0;
	Direction direc;//ʵʱ��λ
	//����ֵ
	Snake() {
		ch0 = (char*)"��";
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
		//�ı䷽�򣨲�����ͬһֱ���ϸķ���
		switch (ch) {
		case 72:if (direc != UP && direc != DOWN)direc = UP; break;
		case 75:if (direc != LEFT && direc != RIGHT)direc = LEFT; break;
		case 77:if (direc != LEFT && direc != RIGHT)direc = RIGHT; break;
		case 80:if (direc != UP && direc != DOWN)direc = DOWN; break;
		}
	}
	//��ӡʵʱ��λ��
	void printSnake() {
		//��ȡ���
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(ConsoleHandle, 12);//������ɫ
		//ɾ����һ�ε���β
		SetConsoleCursorPosition(ConsoleHandle, tail);
		cout << " ";
		tail = body[len - 1];//������βλ��
		for (int i = 0; i < len; i++) {
			//��ӡ�˴���ͷ
			SetConsoleCursorPosition(ConsoleHandle, body[i]);//�ƶ����
			cout << ch0;
		}
		
	}
};

/***************��������****************/
//����ʳ��
void setfood(Food food, Snake snake, COORD& foodPosition) {//����ʳ��
	srand((int)time(0));
	//�ҵ���������������λ��
	int m = 1;
	do {
		foodPosition.X = rand() % 55;
		foodPosition.Y = rand() % 28;
		if (foodPosition.X >= 3 && foodPosition.X <= 54 && foodPosition.Y >= 2 && foodPosition.Y <= 27 && foodPosition.Y % 2 == 0 && foodPosition.X % 2 == 1) {//�ڽ�����
			for (int i = 0; i < snake.len; i++) {
				if (snake.body[i].X == foodPosition.X && snake.body[i].Y == foodPosition.Y) {//��Ϊ����
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
//�ߵ��ƶ�
int move(Snake &snake, COORD foodPosition,wall wall[])
{
	
	//�ж�ʳ��
	if (snake.head.X == foodPosition.X && snake.head.Y == foodPosition.Y) {
		return 1;
	}
	else {//�ж�ǽ
		for (int i = 0; i < 55;i++) {
			if (snake.head.X == wall[i].block.X && snake.head.Y == wall[i].block.Y)
				return 2;
		}
	}
	//ɾ��β�ͣ��������
	for (int i = snake.len - 1; i > 0; i--) {
		snake.body[i] = snake.body[i - 1];
	}
	//�жϷ���
	switch (snake.direc) {
	case UP:snake.head.Y--; break;
	case DOWN:snake.head.Y++; break;
	case LEFT:snake.head.X -= 2; break;
	case RIGHT:snake.head.X += 2; break;
	}
	//��Խ�߽�
	if (snake.head.X > 55)
		snake.head.X = 3;
	else if (snake.head.X < 2)
		snake.head.X = 55;
	else if (snake.head.Y < 2)
		snake.head.Y = 27;
	else if (snake.head.Y > 27)
		snake.head.Y = 2;

	snake.body[0] = snake.head;//������ͷ
	return 0;
}
//������룬�ı��߷���
void input(Snake& snake, char& ch)
{
	if (_kbhit()){//�ж��м�������
		_getch();//����޹��ַ�
		ch = _getch();//��ȡ��������ֵ
	}
	//�ı䷽�򣨲�����ͬһֱ���ϸķ���
	snake.change_dir(ch);
}
//��ʼ������
void InitGraph(boundary boundary[4][27], wall wall[])
{
	//���߽�
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
	//��ǽ
	for (int i = 3; i < 56; i++) {
		wall[i].setXY(i, 15);
		wall[i].printWall();
	}
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	ps.X = 70;
	ps.Y = 1;
	SetConsoleTextAttribute(ConsoleHandle, 15);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
	cout << "Greedy Snake" << endl;
	cout << "\t\t\t\t\t\t\t\t\t̰����" << endl;
	cout << "\t\t\t\t\t\t\t\t�ؿ���" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t��һ��" << endl;
	cout << "\t\t\t\t\t\t\t\t��ʱ��" << endl;
}

//��ӡʱ��
void printTime(int time) {
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pt;
	pt.X = 80;
	pt.Y = 6;
	SetConsoleTextAttribute(ConsoleHandle, 15);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, pt);//�ƶ����
	cout << time <<"s";
}
//�����˵�
void judgeSuccess(int judge,int time) {
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	ps.X = 24;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 15);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
	if (judge == 1)//�Ե�ʳ��
	{
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              you win!!!                |" << endl;
		cout << "\t\t\t|             ��ϲ��ɹ��ˣ�             |" << endl;
		cout << "\t\t\t|������ʱΪ��                            |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << " \t\t\t ----------------------------------------" << endl;
	}
	else if (judge == 2) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              Game Over!!!             |" << endl;
		cout << "\t\t\t|             ���ź���ʧ���ˣ�          |" << endl;
		cout << "\t\t\t|������ʱΪ��                           |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t        |" << endl;
		cout << "\t\t\t|                                       |" << endl;
		cout << "\t\t\t ----------------------------------------" << endl;
	}
	if (judge != 0) {
		ps.X = 28;
		ps.Y = 15;
		SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
		system("pause");
		exit(0);
	}
}
int main()
{
	clock_t start, end;
	//����߽����
	boundary boundary[4][27];
	wall wall[100];
	Food food;
	Snake snake;
	char ch = 77;//��ȡ����ֵ����ʼΪ��
	COORD foodPosition;//ʳ������
	foodPosition.X = 0; foodPosition.Y = 0;//��ʼ��

	//���ع��
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	
	//���߽�
	InitGraph(boundary, wall);
	//����ʳ��
	setfood(food,snake,foodPosition);
	int judge = 0;
	int time = 0;
	start = clock();//��ʱ��ʼ
	while (1) {
		//��ӡ��
		snake.printSnake();
		//��ȡ��������
		input(snake, ch);
		//���ƶ�  �жϽ���
	    judge = move(snake, foodPosition, wall);
		//��ʱ
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
		printTime(time);
		//�����˵�
		judgeSuccess(judge,time);
		Sleep(150);//�ٶȿ���
	}
	printf("\n\n\n");
	return 0;
}