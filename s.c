#include <windows.h>

typedef struct string {
	char str[10];
} string;

string binToLine(int in);
void drawNum(int x, int y, int elements);
int numToElements(int in);
void renderNum(int equals);

int main() {
	for (int i = 0; i < 1000; i++) {
		renderNum(i);
		Sleep(1000);
	}
	while (1);
}

void drawNum(int x, int y, int elements) {
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetWindowDC(hWnd);
	int positions[7][4] = {
		{ 60 , 50 , 200, 50  }, 
		{ 10 , 100, 50 , 200 },
		{ 260, 100, 50 , 200 },
		{ 60 , 300, 200, 50  },
		{ 10 , 350, 50 , 200 },
		{ 260, 350, 50 , 200 },
		{ 60 , 550, 200, 50  },
	};
	for (int i = 0; i < 7; ++i) {
		int targetColor = RGB(0, 0, 255);
		if (binToLine(elements).str[i] == '0') {
			targetColor = RGB(0, 0, 0);
		}
		HBRUSH hBrush = CreateSolidBrush(targetColor);
		HPEN hPen = CreatePen(PS_SOLID, 1, targetColor);
		SelectObject(hDC, hBrush);
		SelectObject(hDC, hPen);
		Ellipse(hDC, positions[i][0] / 1 + x, positions[i][1] / 1 + y, positions[i][0] / 1 + x + positions[i][2] / 1, positions[i][1] / 1 + y + positions[i][3] / 1);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
	ReleaseDC(hWnd, hDC);
}

string binToLine(int in) {
	string line = { "0000000000"};
	if (in == 0) {
		return line;
	}
	int iters = 0;
	for (int i = 512; i > 0; i /= 2) {
		if (in >= i) {
			in %= i;
			line.str[iters] = '1';
		}
		++iters;
	}
	return line;
}

int numToElements(int in) {
	switch (in) {
	case 0:
		return 0b1110111000; break;
	case 1:
		return 0b0010010000; break;
	case 2:
		return 0b1011101000; break;
	case 3:
		return 0b1011011000; break;
	case 4:
		return 0b0111010000; break;
	case 5:
		return 0b1101011000; break;
	case 6:
		return 0b1101111000; break;
	case 7:
		return 0b1010010000; break;
	case 8:
		return 0b1111111000; break;
	case 9:
		return 0b1111011000; break;

	}
	return 0;
}

void renderNum(int equals) {
	int f1 = numToElements((equals - 0) / 100);
	drawNum(50, 100, f1);
	int f2 = numToElements((equals - (equals / 100 * 100)) / 10);
	drawNum(400, 100, f2);
	int f3 = numToElements(equals - (equals / 10 * 10));
	drawNum(750, 100, f3);
}

// 5:43 