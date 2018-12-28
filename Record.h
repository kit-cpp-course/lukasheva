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

class Record { //Класс отвечающий за запись в текстовый файл и чтение из него
public:;

	   std::string path = "C:/Users/Руз/source/repos/Project1/Project1/record.txt";// поле для пути до текстового файла где хранятся рекорды

	   int read()
	   {
		   std::string line;
		   std::string B;

		   std::ifstream in(path); // окрываем файл для чтения
		   if (in.is_open())
		   {
			   while (getline(in, line))
			   {
				   B = line;// Считываем файл построчно 
			   }
		   }
		   in.close(); // закрываем файл

		   std::stringstream A;
		   int C;
		   A « B;
		   A » C;

		   return C;
	   }
	   int write(int score)
	   {
		   std::ofstream out; // поток для записи
		   out.open(path); // окрываем файл для записи
		   if (out.is_open())
		   {
			   out « score « std::endl; //Записываем в файл с удалением старых данных
		   }
		   return 0;
	   }

};
