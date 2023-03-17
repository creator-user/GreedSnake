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
		head.X = 45;
		head.Y = 5;
		tail.X = head.X + len;
		tail.Y = head.Y;
		for (int i = 0; i < len; i++) {
			body[i].X = head.X - (2 * i);//ͷ���ң���������
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
			//��ӡ�˴���
			SetConsoleCursorPosition(ConsoleHandle, body[i]);//�ƶ����
			cout << ch0;
		}
	}
};

/***************��������****************/
//����ʳ��
void setfood(Food food, Snake snake, COORD& foodPosition, wall wall[]) {//����ʳ��
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
			for (int i = 0; i < 50;i++) {
				if (wall[i].block.X == foodPosition.X && wall[i].block.Y == foodPosition.Y) {//��Ϊǽ
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
int move(Snake &snake, COORD foodPosition, wall wall[])
{
	//�ж�ʳ��
	if (snake.head.X == foodPosition.X && snake.head.Y == foodPosition.Y) {
		return 1;
	}
	else {//�ж�ǽ
		for (int i = 0; i < 100; i++) {
			if (snake.head.X == wall[i].block.X && snake.head.Y == wall[i].block.Y)
				return 2;
		}
		for (int i = 1; i < snake.len; i++) {
			if (snake.head.X == snake.body[i].X && snake.head.Y == snake.body[i].Y)
				return 3;
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
void InitGraph(boundary boundary[4][27],int flag)
{
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(ConsoleHandle, 0);//������ɫ
	system("cls");
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
	COORD ps;
	ps.X = 70;
	ps.Y = 1;
	SetConsoleTextAttribute(ConsoleHandle, 15);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
	cout << "Greedy Snake" << endl;
	cout << "\t\t\t\t\t\t\t\t\t̰����" << endl;
	cout << "\t\t\t\t\t\t\t\t�ؿ���" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t��"<<flag<<"��"<< endl;
	cout << "\t\t\t\t\t\t\t\t��ʱ��" << endl;
	ps.X = 65;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 12);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
	cout << "�밴������ƶ�" << endl;
}
//��ӡǽ
void setWall(wall wall[50],int flag) {
	int index = 0;
	//��ǽ
	if (flag == 1) {//��һ��
		for (int i = 3; i < 56; i += 2) {
			wall[index].setXY(i, 15);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 2) {//�ڶ���
		for (int i = 2; i <= 14; i++) {//����
			wall[index].setXY(19, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 29; i <= 55; i += 2) {//����
			wall[index].setXY(i, 10);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 29; i += 2) {//����
			wall[index].setXY(i, 18);
			wall[index].printWall();
			index++;
		}
		for (int i = 14; i <= 27; i++) {//����
			wall[index].setXY(37, i);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 3) {//������
		for (int i = 2; i <= 27; i++) {//����
			wall[index].setXY(29, i);
			wall[index].printWall();
			index++;
		}
		for (int i = 3; i <= 55; i+=2) {//����
			wall[index].setXY(i, 14);
			wall[index].printWall();
			index++;
		}
	}
	else if (flag == 4) {//���Ĺ�
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

//ʧ�ܲ˵�
void judgeFail(int judge,int time) {
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	ps.X = 24;
	ps.Y = 10;
	SetConsoleTextAttribute(ConsoleHandle, 15);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, ps);//�ƶ����
	if (judge == 2) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              Game Over!!!             |" << endl;
		cout << "\t\t\t|         ���ź���ײ��ǽʧ���ˣ�        |" << endl;
		cout << "\t\t\t|                ������                  |" << endl;
		cout << "\t\t\t|   �Ÿոչ�ȥ�� " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                       |" << endl;
		cout << "\t\t\t ----------------------------------------" << endl;
	}
	else if (judge == 3) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              Game Over!!!             |" << endl;
		cout << "\t\t\t|         ���ź���ײ���Լ�ʧ���ˣ�      |" << endl;
		cout << "\t\t\t|                ������                  |" << endl;
		cout << "\t\t\t|   �Ÿոչ�ȥ�� " << time << "s\t\t        |" << endl;
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

//ʤ���˵�
int judgeSuccess(int time, int a)
{
	//��ȡ���
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int key = 1;//��ǰѡ����
	COORD b1 = { 24,10 };
	SetConsoleTextAttribute(ConsoleHandle, 13);//������ɫ
	SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
	if (a != 4) {
		cout << " ----------------------------------------" << endl;
		cout << "\t\t\t|              you win!!!                |" << endl;
		cout << "\t\t\t|           ��ϲ��ͨ�����أ�             |" << endl;
		cout << "\t\t\t|������ʱΪ��                            |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << "\t\t\t|��ѡ�������һ��������                  |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << " \t\t\t ----------------------------------------" << endl;
		b1 = { 47,17 };
		SetConsoleTextAttribute(ConsoleHandle, 253);//������ɫ
		SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
		cout << "�˳�";
		b1 = { 53,17 };
		SetConsoleTextAttribute(ConsoleHandle, 13);//������ɫ
		SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
		cout << "��һ��";
		while (1) {
			char ch = _getch();
			//ch = _getch();
			switch (ch) {
			case 75://left
				switch (key) {
				case 2:b1 = { 47,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 253);//������ɫ
					  SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
					  cout << "�˳�";
					  b1 = { 53,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 13);//������ɫ
					  SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
					  cout << "��һ��";
					  key--; break;
				}break;
			case 77://right
				switch (key) {
				case 1:b1 = { 47,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 13);//������ɫ
					  SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
					  cout << "�˳�";
					  b1 = { 53,17 };
					  SetConsoleTextAttribute(ConsoleHandle, 253);//������ɫ
					  SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
					  cout << "��һ��";
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
		cout << "\t\t\t|           ��ϲ��ȫ��ͨ�أ�             |" << endl;
		cout << "\t\t\t|�㱾����ʱΪ��                          |" << endl;
		cout << "\t\t\t|              " << time << "s\t\t         |" << endl;
		cout << "\t\t\t|                                        |" << endl;
		cout << " \t\t\t ----------------------------------------" << endl;
		b1.X = 28;
		b1.Y = 15;
		SetConsoleCursorPosition(ConsoleHandle, b1);//�ƶ����
		system("pause");
		exit(0);
	}
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
	cout << time << "s";
}

//��Ϸ������
void game(int &time, int flag) {
	clock_t start, end;
	//����߽����
	boundary boundary[4][27];
	wall wall[100];
	Food food;
	Snake snake;
	char ch = 77;//��ȡ����ֵ����ʼΪ��
	COORD foodPosition;//ʳ������
	foodPosition.X = 0; foodPosition.Y = 0;//��ʼ��

	//���߽�
	InitGraph(boundary,flag);
	//��ǽ
	setWall(wall, flag);
	//����ʳ��
	setfood(food, snake, foodPosition, wall);
	int judge = 0;
	start = clock();//��ʱ��ʼ
	while (1) {
		//��ӡ��
		snake.printSnake();
		Sleep(100);//�ٶȿ���
		//��ȡ��������
		input(snake, ch);
		//���ƶ�  �жϽ���
		judge = move(snake, foodPosition, wall);
		if (judge == 1)//�Ե�ʳ��
			return;
		//��ʱ
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;
		printTime(time);
		//�����˵�
		judgeFail(judge, time);
	}
}
int main()
{
	//���ع��
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	int time = 0;//��ʱ��
	int flag;
	int a = 1;//�ؿ�
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