#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Neuron.h"

using namespace std;

void make_libraries(vector<pair<double, double>>& X)
{
	ifstream fin;
	fin.open("data_of_libraries.txt");
	if (!fin.is_open()) 
		cout << "Ошибка открытия файла data_of_libraries.txt" << endl;
	string coordinates, str_x1, str_x2;
	pair<double, double> curr_X;
	while (!fin.eof())
	{
		getline(fin, coordinates);
		str_x1 = coordinates.substr(0, coordinates.find('\t'));
		str_x2 = coordinates.substr(coordinates.find('\t') + 1);

		curr_X = { stod(str_x1), stod(str_x2) };
		X.push_back(curr_X);
	}
	fin.close();
}

void make_centers(vector<pair<double, double>>& centers)
{
	ifstream fin;
	fin.open("data_of_centers.txt");
	if (!fin.is_open())
		cout << "Ошибка открытия файла data_of_centers.txt" << endl;
	string coordinates, str_x1, str_x2;
	pair<double, double> curr_center;
	while (!fin.eof())
	{
		getline(fin, coordinates);
		str_x1 = coordinates.substr(0, coordinates.find(' '));
		str_x2 = coordinates.substr(coordinates.find(' ') + 1);

		curr_center = { stod(str_x1), stod(str_x2) };
		centers.push_back(curr_center);
	}
	fin.close();
}

void print(Neural_network& neu)
{
	cout.precision(8);
	setlocale(LC_ALL, "ru");
	vector<vector<pair<double, double>>> rezult = neu.get_rezult();
	int counter = 1;
	for (auto center : rezult)
	{
		switch (counter)
		{
		case 1:
			cout << "Координаты библиотек, попавшие в округ ЦАО: " << endl;
			break;
		case 2:
			cout << "\nКоординаты библиотек, попавшие в округ CАО: " << endl;
			break;
		case 3:
			cout << "\nКоординаты библиотек, попавшие в округ CВАО: " << endl;
			break;
		case 4:
			cout << "\nКоординаты библиотек, попавшие в округ ВАО: " << endl;
			break;
		case 5:
			cout << "\nКоординаты библиотек, попавшие в округ ЮВАО: " << endl;
			break;
		case 6:
			cout << "\nКоординаты библиотек, попавшие в округ ЮАО: " << endl;
			break;
		case 7:
			cout << "\nКоординаты библиотек, попавшие в округ ЮЗАО: " << endl;
			break;
		case 8:
			cout << "\nКоординаты библиотек, попавшие в округ ЗАО: " << endl;
			break;
		case 9:
			cout << "\nКоординаты библиотек, попавшие в округ CЗАО: " << endl;
			break;
		case 10:
			cout << "\nКоординаты библиотек, попавшие в округ ЗелАО: " << endl;
			break;
		case 11:
			cout << "\nКоординаты библиотек, попавшие в округ ТАО: " << endl;
			break;
		case 12:
			cout << "\nКоординаты библиотек, попавшие в округ НАО: " << endl;
			break;
		}
		for (auto el : center)
			cout << "(" << el.first << "," << el.second << ")" << endl;
		counter++;
	}
}

int main()
{
	vector<pair<double, double>> X;
	vector<pair<double, double>> centers;
	make_libraries(X);
	make_centers(centers);

	Neural_network neu(X, centers);
	neu.set_rezult();

	print(neu);
}
