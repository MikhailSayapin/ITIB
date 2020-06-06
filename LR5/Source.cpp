#include <iostream>
#include <vector>
#include "Neuron.h"

using namespace std;

vector<vector<int>> I =
{
	{-1, 1, 1, 1, -1},
	{-1, -1, 1, -1, -1},
	{-1, -1, 1, -1, -1},
	{-1, -1, 1, -1, -1},
	{-1, 1, 1, 1, -1}
};

vector<vector<int>> V =
{
	{1, -1, -1, -1, 1},
	{1, -1, -1, -1, 1},
	{-1, 1, -1, 1, -1},
	{-1, 1, -1, 1, -1},
	{-1, -1, 1, -1, -1}
};

vector<vector<int>> X =
{
	{1, -1, -1, -1, 1},
	{-1, 1, -1, 1, -1},
	{-1, -1, 1, -1, -1},
	{-1, 1, -1, 1, -1},
	{1, -1, -1, -1, 1}
};

vector<int> vectorization(vector<vector<int>>& vec)
{
	vector<int>temp;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
			temp.push_back(vec[i][j]);
	}
	return temp;
}

vector<vector<int>> make_sets()
{
	vector<vector<int>>temp;
	temp.push_back(vectorization(I));
	temp.push_back(vectorization(V));
	temp.push_back(vectorization(X));
	return temp;
}

void test(Neural_network& neu, vector<int> s)
{
	neu.init_output_first(s);
	neu.set_net2();
	neu.set_t();
	neu.set_net1();
	neu.set_s();
}

void inverse_test(Neural_network& neu, vector<int> t)
{
	neu.init_output_second(t);
	neu.set_net1();
	neu.set_s();
	neu.set_net2();
	neu.set_t();
}

vector<vector<int>> distortion()
{
	vector<vector<int>>distorted_sets;
	distorted_sets = make_sets();

	//В "I" исказим 9 и 20 символы
	distorted_sets[0][8] = 1; distorted_sets[0][19] = -1;
	//В "V" исказим 4 и 23 символы
	distorted_sets[1][3] = 1; distorted_sets[1][22] = 1;
	//В "X" исказим 17 и 25 символы
	distorted_sets[2][16] = -1; distorted_sets[2][24] = -1;

	return distorted_sets;
}

vector<vector<int>> correction(Neural_network& neu, vector<vector<int>> distorted_sets, vector<vector<int>> &t)
{
	vector<vector<int>> fixed_sets = distorted_sets;
	for (int i = 0; i < distorted_sets.size(); i++)
	{
		test(neu, distorted_sets[i]);
		fixed_sets[i] = neu.get_s();
		t[i] = neu.get_t();
	}
	return fixed_sets;
}

void print_W(Neural_network& neu)
{
	cout << "Матрица весов: " << endl;
	for (auto vec : neu.get_W())
	{
		cout << "( ";
		for (auto el : vec)
			cout << el << " ";
		cout << ")" << endl;
	}
	cout << endl;
}

//is_direct = true - прямой порядок тестирования
//is_direct = false - обратный порядок тестирования
void print_t_s(Neural_network& neu, bool is_direct, int i)
{
	if (is_direct)
	{
		if (i == 0) 
			cout << "Для набора, соответствующему I вектор t равен " << "( ";
		if (i == 1) 
			cout << "Для набора, соответствующему V вектор t равен " << "( ";
		if (i == 2) 
			cout << "Для набора, соответствующему X вектор t равен " << "( ";
		for (auto el : neu.get_t())
			cout << el << " ";
		cout << ")" << endl;
	}
	else
	{
		if (i == 0) 
			cout << "Для пары-ассоциации, соответствующей I вектор s равен " << "( ";
		if (i == 1) 
			cout << "Для пары-ассоциации, соответствующей V вектор s равен " << "( ";
		if (i == 2) 
			cout << "Для пары-ассоциации, соответствующей X вектор s равен " << "( ";
		for (auto el : neu.get_s())
			cout << el << " ";
		cout << ")" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	//Явно зададим пары-ассоциации
	vector<vector<int>> t = { {-1, -1, 1}, { -1, 1, -1 }, { -1, 1, 1 } }; 
	Neural_network neu(make_sets(), t);
	print_W(neu);

	cout << "Тест эталонных паттернов в прямом направлении: " << endl;
	for (int i = 0; i < make_sets().size(); i++)
	{
		test(neu, make_sets()[i]);
		print_t_s(neu, true, i);
	}

	cout << "\nТест эталонных паттернов в обратном направлении: " << endl;
	for (int i = 0; i < t.size(); i++)
	{
		inverse_test(neu, t[i]);
		print_t_s(neu, false, i);
	}

	cout << "\nРезультат работы РНС Коско при искажённых паттернах: " << endl;
	vector<vector<int>> distort_sets = distortion();
	//Активируем функцию correction для исправления векторов,
	//которая возвращает исправленные. Перед этим очистим 
	//вектора t, чтобы нейросеть рассчитала исходные пары-ассоциации
	t.assign(t.size(), { 0, 0, 0 });
	vector<vector<int>> fixed_sets = correction(neu, distortion(), t);

	cout << "В I исказим 9 и 20 символы: (";
	for (auto el : distort_sets[0]) cout << el << " ";
		
	cout << ") \nВ V исказим 4 и 23 символы: (";
	for (auto el : distort_sets[1]) cout << el << " ";

	cout << ") \nВ X исказим 17 и 25 символы: (";
	for (auto el : distort_sets[2]) cout << el << " ";
		

	cout << ") \n\nИсправленный вектор I: (";
	for (auto el : fixed_sets[0]) cout << el << " ";
		
	cout << ") \nИсправленный вектор V: (";
	for (auto el : fixed_sets[1]) cout << el << " ";
		
	cout << ") \nИсправленный вектор X: (";
	for (auto el : fixed_sets[2]) cout << el << " ";
		

	cout << ") \n\nПолученная пара-ассоциация для I: (";
	for (auto el : t[0]) cout << el << " ";
	cout << ") \nПолученная пара-ассоциация для V: (";
	for (auto el : t[1]) cout << el << " ";
	cout << ") \nПолученная пара-ассоциация для X: (";
	for (auto el : t[2]) cout << el << " "; cout << ")";
}
