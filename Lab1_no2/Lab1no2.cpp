/*Задано множество точек на двухмерной плоскости. Найти три разные точки, которые
составляют треугольник наибольшего периметра.
Автор: Алексей Уханов*/

#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

typedef struct
{
	double x;
	double y;
} TPoint; //структура с координатами точки

		  // возвращает расстояние между точками p1 и p2
double Distance(TPoint p1, TPoint p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

//функция ввода координат точки
TPoint EnterPoint()
{
	TPoint temp;
	cout << "Enter the coordinates of the x and y points:" << endl;
	cin >> temp.x;
	cin >> temp.y;
	return temp;
}

//проверка на то, образуют ли данные три точки треугольник
bool CheckTriangle(TPoint p1, TPoint p2, TPoint p3)
{
	double a = Distance(p2, p1);
	double b = Distance(p3, p1);
	double c = Distance(p2, p3);
	return (a > abs(b - c)) && (a < b + c);
}

//функция, возвращающая периметр треугольника образованного данными точками
double Perimetr(TPoint p1, TPoint p2, TPoint p3)
{
	return Distance(p2, p1) + Distance(p3, p1) + Distance(p2, p3);
}

int Menu()
{
	int anwser;
	cout << "Enter the sourse:\n1 - From keyboard\n2 - From file (in format x1 y1 on every string)\n0 - Exit" << endl;
	cin >> anwser;
	return anwser;
}

TPoint *FileText(int &len)
{
	char str[80];
	TPoint *mas;
	TPoint temp;
	cout << "Enter filename:" << endl;
	cin >> str;
	//открытие введенного пользователем файла
	ifstream file;
	file.open(str);
	if (!file)
		cout << "Can not open file.\n";
	else
	{
		double x, y;
		while (!file.eof())
		{
			file >> x;
			file >> y;
			++len;
		}
		file.clear();
		file.seekg(0);
		mas = new TPoint[len];
		for (int i = 0; i < len; i++)
		{
			file >> x;
			file >> y;
			temp.x = x;
			temp.y = y;
			mas[i] = temp;
		}
		file.close(); //закрываем файл
	}
	return mas;
}


int main()
{
	TPoint *points = NULL;//массив точек
	int count = 0; //количество точек
	double MaxP = 0;//максимальный периметр
	int anwser = Menu(); //выбранный пункт меню

	while (anwser != 0)
	{
		switch (anwser)
		{
		case 1:
		{
			cout << "Enter the number of points (from 3):" << endl;
			cin >> count;
			while (count < 3)
			{
				cout << "Invalid number of points entered. Enter a number greater than or equal to three:" << endl;
				cin >> count;
			}
			points = new TPoint[count]; //задаем массив в count точек
			for (int i = 0; i < count; i++)
			{
				points[i] = EnterPoint();
			}
			break;
		}
		case 2:
		{
			points = FileText(count);
			break;
		}
		}
		double MaxP = 0; //Максимальный периметр
		for (int ia = 0; ia<count - 2; ia++)
		{
			for (int ib = ia + 1; ib<count - 1; ib++)
			{
				for (int ic = ib + 1; ic<count; ic++)
				{
					if (CheckTriangle(points[ia], points[ib], points[ic])) // если верно, то найден новый максимальный периметр
					{
						if (Perimetr(points[ia], points[ib], points[ic])>MaxP)
						{
							MaxP = Perimetr(points[ia], points[ib], points[ic]);
						}
					}
				}
			}
		}
		if (MaxP>0)
			cout << "The maximum perimeter of a triangle is: " << MaxP << endl;
		else
			if (count != 0)
				cout << "In this set of points there are no points forming a triangle." << endl;
		anwser = Menu();
	}
}