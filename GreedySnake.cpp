#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

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
int main()
{
	
	boundary boundary[4][27];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 27; j++) {
			switch (i) {
			case 0: boundary[i][j].setXY(j*2+3, 1); break;
			case 1: boundary[i][j].setXY(j*2+2, 28); break;
			case 2: boundary[i][j].setXY(2, j+2); break;
			case 3: boundary[i][j].setXY(56, j+2); break;
			}
			boundary[i][j].printBoundary();
		}
	}
	printf("\n\n\n");
	return 0;
}