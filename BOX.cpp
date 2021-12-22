/*---------------------
地板：0
墙：1
箱子目的地：2
小可爱：3
箱子：4
小可爱站在了目的地：3+2
箱子在目的地：4+2
2021.1.22
----------------------*/
# include <graphics.h> 
# include <stdio.h> 
# include <stdlib.h> 
# include <string.h>
# include <conio.h> 
# include <mmsystem.h>
# pragma comment(lib,"winmm.lib")


#define RATIO 61 

#define SCREEN_WIDTH 960 
#define SCREEN_HEIGHT 768 

#define LINE 9 
#define COLUMN 12 

#define START_X 100 
#define START_Y 150 

#define KEY_UP 'w'  
#define KEY_LEFT 'a' 
#define KEY_RIGHT 'd' 
#define KEY_DOWN 's' 

void draw();
void move();
void win();


IMAGE start;
IMAGE last;
IMAGE bg_img;
IMAGE images[7];

int map[LINE][COLUMN] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,0,0,0,1,1},
	{1,0,4,0,1,2,0,1,2,0,1,1},
	{1,0,1,0,1,0,1,1,0,0,0,1},
	{1,0,1,2,1,0,0,4,0,0,0,1},
	{1,0,0,0,1,3,0,0,0,4,0,1},
	{1,0,2,0,0,4,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,0,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};


struct kaku {
	int x;
	int y;
}ka;


int main() {
	initgraph(1202, 697);
	mciSendString(L"open ./1.mp3", 0, 0, 0);
	mciSendString(L"play ./1.mp3", 0, 0, 0);
	win();
	loadimage(&start, L"start.jpg", 1202, 697, true);
	putimage(0, 0, &start);
	setlinestyle(PS_SOLID, 0);
	settextcolor(BROWN);
	settextstyle(70, 50, _T("幼圆"), 0, 0, 1000, false, false, false);
	setbkmode(TRANSPARENT);
	roundrect(301, 248, 901, 448, 50, 50);
	setbkmode(TRANSPARENT);
	RECT r = { 301,248,901,448 };
	drawtext(_T("开始游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	while (1) {
		if (MouseHit()) {
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.mkLButton) {
				if (m.x > 301 && m.y > 248 && m.x < 901 && m.y < 448) {
					HWND hWnd0 = GetHWnd();
					MessageBox(hWnd0, L"*****即将开始游戏*****", L"提示", MB_OK);
					mciSendString(L"stop ./1.mp3", 0, 0, 0);
					mciSendString(L"close ./1.mp3", 0, 0, 0);
					closegraph();
					goto oo;
				}
			}
		}
	}


oo:
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	win();
	mciSendString(L"open ./2.mp3", 0, 0, 0);
	mciSendString(L"play ./2.mp3", 0, 0, 0);
	loadimage(&bg_img, L"background.jpg", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img); //加载道具图标 
	loadimage(&images[0], L"floor.jpg", RATIO, RATIO, true);
	loadimage(&images[1], L"wall.jpg", RATIO, RATIO, true);
	loadimage(&images[2], L"des.jpg", RATIO, RATIO, true);
	loadimage(&images[3], L"kaku.jpg", RATIO, RATIO, true);
	loadimage(&images[4], L"box1.jpg", RATIO, RATIO, true);
	loadimage(&images[5], L"kaku0.jpg", RATIO, RATIO, true);
	loadimage(&images[6], L"box2.jpg", RATIO, RATIO, true);


	while (1) {
		draw();
		move();
		int counter = 0;
		for (int i = 0; i < LINE; i++) {
			for (int j = 0; j < COLUMN; j++) {
				if (map[i][j] == 6)
					counter++;
			}
		}
		if (counter == 4)
			break;
	}

	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	win();
	loadimage(&last, L"last.gif", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &last);
	system("pause");
	system("pause");
	return 0;

}


void draw() {
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[map[i][j]]);
		}
	}
}


void move() {
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (map[i][j] == 3 || map[i][j] == 5) {
				ka.x = j;
				ka.y = i;
				goto xx;
			}
		}
	}
xx:
	char ch = _getch();
	if (ch) {
		mciSendString(L"close ./move.mp3", 0, 0, 0);
		mciSendString(L"open ./move.mp3", 0, 0, 0);
		mciSendString(L"play ./move.mp3", 0, 0, 0);
	}
	switch (ch) {
	case 'w':
	case 'W':
		if (map[ka.y - 1][ka.x] == 0 || map[ka.y - 1][ka.x] == 2) {
			map[ka.y - 1][ka.x] += 3;
			map[ka.y][ka.x] -= 3;
		} else if (map[ka.y - 1][ka.x] == 4 || map[ka.y - 1][ka.x] == 6) {
			if (map[ka.y - 2][ka.x] != 1) {
				map[ka.y - 2][ka.x] += 4;
				map[ka.y - 1][ka.x] -= 4;
				map[ka.y - 1][ka.x] += 3;
				map[ka.y][ka.x] -= 3;
			}
		}
		break;


	case 'a':
	case 'A':
		if (map[ka.y][ka.x - 1] == 0 || map[ka.y][ka.x - 1] == 2) {
			map[ka.y][ka.x - 1] += 3;
			map[ka.y][ka.x] -= 3;
		} else if (map[ka.y][ka.x - 1] == 4 || map[ka.y][ka.x - 1] == 6) {
			if (map[ka.y][ka.x - 2] != 1) {
				map[ka.y][ka.x - 2] += 4;
				map[ka.y][ka.x - 1] -= 4;
				map[ka.y][ka.x - 1] += 3;
				map[ka.y][ka.x] -= 3;
			}
		}
		break;


	case 's':
	case 'S':
		if (map[ka.y + 1][ka.x] == 0 || map[ka.y + 1][ka.x] == 2) {
			map[ka.y + 1][ka.x] += 3;
			map[ka.y][ka.x] -= 3;
		} else if (map[ka.y + 1][ka.x] == 4 || map[ka.y + 1][ka.x] == 6) {
			if (map[ka.y + 2][ka.x] != 1) {
				map[ka.y + 2][ka.x] += 4;
				map[ka.y + 1][ka.x] -= 4;
				map[ka.y + 1][ka.x] += 3;
				map[ka.y][ka.x] -= 3;
			}
		}
		break;


	case 'd':
	case 'D':
		if (map[ka.y][ka.x + 1] == 0 || map[ka.y][ka.x + 1] == 2) {
			map[ka.y][ka.x + 1] += 3;
			map[ka.y][ka.x] -= 3;
		} else if (map[ka.y][ka.x + 1] == 4 || map[ka.y][ka.x + 1] == 6) {
			if (map[ka.y][ka.x + 2] != 1) {
				map[ka.y][ka.x + 2] += 4;
				map[ka.y][ka.x + 1] -= 4;
				map[ka.y][ka.x + 1] += 3;
				map[ka.y][ka.x] -= 3;
			}
		}
		break;
	}
}


void win() {
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, L"HAPPY CODING");
}


//嘿嘿 终于完美了！
