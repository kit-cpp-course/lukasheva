#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include "Record.h"
#include "Tetromino.h"

using namespace sf;

const int M = 20;
const int N = 10;
int score = 0;

int field[M][N] = { 0 };//Игровое поле очистили

struct Point
{
	int x, y;
} a[4], b[4];
int figures[7][4] =
{
	1,3,5,7,//I
	2,4,5,7,//Z
	3,5,4,6,//S
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//O

};//Создаем все фигурки по координатам

bool check()//Проверка координат создаваемой фигуры
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
}
class Game {
public : 
	int game()
	{

		RenderWindow window(VideoMode(500, 750), "The game!");

		Record record;

		Texture t;
		t.loadFromFile("images/tetris.jpg");

		Sprite s(t);
		s.setTextureRect(IntRect(0, 0, 26, 26));

		int dx = 0; bool rotate = 0; int colorNum = 1;
		float timer = 0, delay = 0.3;

		Clock clock;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
					window.close();
				if (e.type == Event::KeyPressed)
					if (e.key.code == Keyboard::Up) rotate = true;
					else if (e.key.code == Keyboard::Left) dx = -1;
					else if (e.key.code == Keyboard::Right) dx = 1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

			Move(dx);

			Rotate(rotate);

			///////Tick////////
			if (timer > delay)
			{
				for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

				if (!check())
				{
					for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

					colorNum = 1 + rand() % 7;
					int n = rand() % 7;
					for (int i = 0; i < 4; i++)
					{
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				}
				timer = 0;
			}

			////////check lines/////////
			int k = M - 1;
			int count = 0;
			for (int i = M - 1; i > 0; i--)
			{
				count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[i][j]) count++;
					field[k][j] = field[i][j];
				}
				if (count < N) k--;
				else if (count == N) score++;
			}

			k = 1;
			count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[k][j]) count++;
			}
			if (count > 0)
			{
				t.loadFromFile("images/lose.jpg");
				Sprite s(t);
				window.draw(s);
				window.display();
				Sleep(2000);
				int rec = record.read();
				if (score > rec) record.write(score);
				for (int i = M - 1; i > 0; i--)
				{
					for (int j = 0; j < N; j++)
					{
						field[i][j] = 0;
					}
				}
				score = 0;
				return 0;
			}

			int n = 3;
			if (a[0].x == 100)
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}

			dx = 0; rotate = 0; delay = 0.3;

			///////draw/////////
			window.clear(Color::White);

			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (field[i][j] == 0) continue;
					s.setTextureRect(IntRect(field[i][j] * 26, 0, 26, 26));
					s.setPosition(j * 26, i * 26);
					window.draw(s);
				}
			}
			for (int i = 0; i < 4; i++) {
				s.setTextureRect(IntRect(colorNum * 26, 0, 26, 26));
				s.setPosition(a[i].x * 26, a[i].y * 26);
				window.draw(s);
			}
			window.draw(s);


			//////////Scores////////////

			Font font;//шрифт 
			font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
			Text scoretext("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			scoretext.setFillColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			scoretext.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

			std::ostringstream playerScoreString;    // объявили переменную
			playerScoreString << score;		//занесли в нее число очков, то есть формируем строку
			scoretext.setString("Очки:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			scoretext.setPosition(400, 0);
			window.draw(scoretext);

			window.display();
		}
		return 0;
	}

	int Move(int dx) {
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		return 0;
	}

	int Rotate(bool rotate) {
		if (rotate)
		{
			Point p = a[1];//центр вращения
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		}
		return 0;
	}
};
