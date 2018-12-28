#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include "Record.h"
#include <string>

using namespace sf;

class Menu
{
public:;

	   Game play; //поле класса гейм

	   Texture t; //поле класса текстур

	   void loadfromfile() { //конструктор создания текстуры
		   t.loadFromFile("images/tetris.jpg");
	   }

	   Record record; //поле класса рекорд

	   int menu() {

		   RenderWindow window(VideoMode(500, 750), "Menu"); //Создаем окно игровое

		   loadfromfile();

		   Sprite s(t); //Редактируем загруженное изображение если необходимо

		   int maxscore = 0;
		   int scores = 0;
		   while (window.isOpen())
		   {
			   maxscore = record.read();
			   Event e;
			   while (window.pollEvent(e))// Устанавливаем действия которые буду происходить при нажатии клавиш
			   {
				   if (e.type == Event::Closed)
					   window.close();
				   if (e.type == Event::KeyPressed)
					   if (e.key.code == Keyboard::Enter) play.game();
					   else if (e.key.code == Keyboard::Escape) return 0;
			   }
			   window.clear(Color::Green);
			   window.draw(s);

			   Font font;//шрифт 
			   font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
			   Text menutext("", font, 25);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			   menutext.setFillColor(Color::Cyan);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			   menutext.setString("Нажмите Enter чтобы начать игру \n \n или Esc чтобы выйти");
			   menutext.setPosition(55, 200);
			   window.draw(menutext);//рисую этот текст

			   Text recordtext("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			   recordtext.setFillColor(Color::Cyan);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			   std::ostringstream record; // объявили переменную
			   record « maxscore; //занесли в нее число очков, то есть формируем строку
			   recordtext.setString("Игровой рекорд: " + record.str() + " очков.");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			   recordtext.setPosition(210, 630);
			   window.draw(recordtext);//рисую этот текст

			   window.display();
		   }
	   }
};

	
