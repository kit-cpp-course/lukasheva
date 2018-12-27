#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Record {
public:;
	int read()
	{
		std::string line;
		std::string B;

		std::ifstream in("C:/Users/Руз/source/repos/Project1/Project1/record.txt"); // окрываем файл для чтения
		if (in.is_open())//Пока файл in открыт в потоке для чтения
		{
			while (getline(in, line))//считываем файл построчно
			{
				B = line;//B присваиваем строчке line из текста
			}
		}
		in.close();     // закрываем файл

		std::stringstream A;//Переменная преобразовыватель из типа стр в тип инт.
		int C;
		A << B;
		A >> C;

		return C;
	}
	int write(int score)
	{
		std::ofstream out;          // поток для записи
		out.open("C:/Users/Руз/source/repos/Project1/Project1/record.txt"); // окрываем файл для записи
		if (out.is_open())
		{
			out << score << std::endl;
		}
		return 0;
	}

};
