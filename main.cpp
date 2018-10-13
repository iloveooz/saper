// main.cpp - основной программный модуль

	#include <iostream>
	#include <ctime>
	
	#include <SFML/Graphics.hpp>
	
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
		
		sf::RenderWindow window(sf::VideoMode((XF * 100) + (XF * 10), (YF * 100) + (YF * 10)), "SAPER!");

		sf::RectangleShape rectangle[XF][YF];
		
		for (int m = 0; m < XF; m++)
			for (int n = 0; n < YF; n++) {		
				rectangle[m][n].setSize(sf::Vector2f(100, 100));
				if (field[m][n] == 0) rectangle[m][n].setFillColor(sf::Color::White);
				if (field[m][n] == 1) rectangle[m][n].setFillColor(sf::Color::Green);
				if (field[m][n] == 2) rectangle[m][n].setFillColor(sf::Color::Blue);
				if (field[m][n] == 3) rectangle[m][n].setFillColor(sf::Color(255, 192, 203, 255));
				if (field[m][n] == 4) rectangle[m][n].setFillColor(sf::Color::Yellow);
				if (field[m][n] == 5) rectangle[m][n].setFillColor(sf::Color(255, 165, 0, 255));
				if (field[m][n] == 6) rectangle[m][n].setFillColor(sf::Color(165, 42, 42, 255));
				if (field[m][n] == 7) rectangle[m][n].setFillColor(sf::Color::Magenta);
				if (field[m][n] == 8) rectangle[m][n].setFillColor(sf::Color::Black);
				if (field[m][n] == BOMB) rectangle[m][n].setFillColor(sf::Color::Red);

				rectangle[m][n].setPosition((m * 105) + 10, (n * 105) + 10);
			}

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			for (int m = 0; m < XF; m++)
				for (int n = 0; n < YF; n++)
					window.draw(rectangle[m][n]);
			window.display();
		}		
		
		return 0;
	}
