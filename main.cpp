// main.cpp - основной программный модуль

	#include <iostream>
	#include <ctime>
	
	#define MINES 10
	#define BOMB 9
	
	#define XF 8
	#define YF 8

	bool inField(int x, int y) {
		return x >= 0 && y >= 0 && x < XF && y < YF;
	}
	
	int main() {
		
		// рандомизация
		srand(time(0));
				
		// игровое поле
		int field[XF][YF];
		int *ptrField = &field[0][0];
		
		int xm, ym;
				
		// размер массива
		int NF = sizeof(field) / sizeof(field[0][0]);		
		
		// заполняем массив нулями
		for (int i = 0; i < NF; i++) 
			*(ptrField + i) = 0;
		
		// заполняем массив минами
		for (int i = 0; i < MINES; i++) {
			do {
				xm = rand() % XF;
				ym = rand() % YF;
			} 
			while (field[xm][ym] == BOMB);

			// Устанавливаем мину
			field[xm][ym] = BOMB;
		}    

		// считаем количество мин в квадрате 3х3 с центром в ячейке
		for (int m = 0; m < XF; m++)
			for (int n = 0; n < YF; n++)
				for (int j = -1; j <= 1; j++)
					for (int k = -1; k <= 1; k++)
						if (inField(m + j, n + k) && field[m + j][n + k] == BOMB) 
							if (field[m][n] != BOMB) field[m][n]++;

		std::cout << "size of array - " << NF << std::endl;
		std::cout << "mines count - " << MINES;
		
		// вывести игровое поле
		for (int i = 0; i < NF; i++) {
			if (!(i % XF)) std::cout << '\n' << '\n' << '\n';
			if (*(ptrField + i) == BOMB) std::cout << "\033[31m";
			std::cout << '\t' << *(ptrField + i);
			if (*(ptrField + i) == BOMB) std::cout << "\033[0m";
		}
		
		std::cout << std::endl;
		return 0;
	}
