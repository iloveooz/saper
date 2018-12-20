

	#include <SFML/Graphics.hpp>
	#include <time.h>
	
	int main() {
		srand(time(NULL));
		
		sf::RenderWindow app(sf::VideoMode(400, 400), "Miner!");
		
		int w = 32;
		int grid[12][12];
		
		// для отображения
		int sgrid[12][12];
		
		sf::Texture t;
		t.loadFromFile("images/tiles.jpg");
		
		sf::Sprite s(t);
		
		for (int i = 1; i <= 10; i++) 
			for (int j = 1; j <= 10; j++) {
				sgrid[i][j] = 10;
				if (rand() % 6 == 0)
					grid[i][j] = 9;
				else
					grid[i][j] = 0;				
			}
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++) {
				int n = 0;
				if (grid[i][j] == 9) continue;
				
				if (grid[i + 1][j] == 9) n++;
				if (grid[i][j + 1] == 9) n++;
				if (grid[i - 1][j] == 9) n++;
				if (grid[i][j - 1] == 9) n++;
				
				if (grid[i + 1][j + 1] == 9) n++;
				if (grid[i - 1][j - 1] == 9) n++;
				if (grid[i - 1][j + 1] == 9) n++;
				if (grid[i + 1][j - 1] == 9) n++;
				
				grid[i][j] = n;
			}
		
		
		while (app.isOpen()) {
			
			sf::Vector2i pos = sf::Mouse::getPosition(app);
			
			// чтобы была дискретизация по клеткам
			int x = pos.x / w;
			int y = pos.y / w;
			
			
			sf::Event e;
			while (app.pollEvent(e)) {
				if (e.type == sf::Event::Closed)
					app.close();
					
				if (e.type == sf::Event::MouseButtonPressed) {
					if (e.key.code == sf::Mouse::Left) sgrid[x][y] = grid[x][y];
						else if (e.key.code == sf::Mouse::Right) sgrid[x][y] = 11;
				}
			}
			
			app.clear(sf::Color::White);
			
			for (int i = 1; i <= 10; i++) 
				for (int j = 1; j <= 10; j++) {
					// проверка - наступил ли на мину
					if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
					
					s.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
					s.setPosition(i * w, j * w);
					app.draw(s);
				}
			
			app.display();
			
		}
		
		return 0;
	}
