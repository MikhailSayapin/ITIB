#include "Neuron.h"
#include <math.h>
#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

const int COUNT_OF_ARGS = 4;
vector<vector<int>> truth_table;

void print_y(Neuron& neuron);
void print_era(Neuron& neuron);

int f(vector<int> &x)
{
	return !((x[0] || x[1] || x[2]) && (x[1] || x[2] || x[3]));
}

//Функция обучения нейрона
void calculation(Neuron &neuron, bool is_logistic)
{
	while (true)
	{
		cout << "Y = (";
		vector<int> args(COUNT_OF_ARGS, 0);
		for (int i = 0; i < pow(2, COUNT_OF_ARGS); i++) //Цикл внутри эпохи
		{
			neuron.set_new_x(args);
			neuron.set_net();
			if (is_logistic) neuron.set_logistic_y();
			else neuron.set_step_y();
			neuron.set_sigma(f(args));
			neuron.set_new_w(args, is_logistic);

			increment(args);
			print_y(neuron);
		}

		print_era(neuron);

		if (neuron.get_E() == 0) break;
		neuron.set_E_to_zero();
	}
}

bool is_checked(Neuron neuron, bool is_logistic)
{
	vector<int> args(COUNT_OF_ARGS, 0);
	for (int i = 0; i < pow(2, COUNT_OF_ARGS); i++) //Цикл внутри эпохи
	{
		neuron.set_new_x(args);
		neuron.set_net();
		if (is_logistic) neuron.set_logistic_y();
		else neuron.set_step_y();
		neuron.set_sigma(f(args));
		if (neuron.get_sigma() != 0) return false;
		increment(args);
	}
	return true;
}

////////////////////////////////////////////
bool help(bool is_logistic)
{
	vector<vector<int>> args;
	if (is_logistic)
		args = { {0, 0, 0, 0}, {0, 1, 1, 0} , {1, 0, 0, 1} };
	else
		args = { {0, 0, 0, 1}, {0, 0, 1, 0} , {0, 1, 0, 0}, {1, 0, 0, 0} , {1, 0, 0, 1} };
	Neuron neu(COUNT_OF_ARGS);
	while (true)
	{
		for (int i = 0; i < args.size(); i++)
		{
			neu.set_new_x(args[i]);
			neu.set_net();
			if (is_logistic) neu.set_logistic_y();
			else neu.set_step_y();
			neu.set_sigma(f(args[i]));
			neu.set_new_w(args[i], is_logistic);
		}
		if (neu.get_E() == 0) break;
		else neu.set_E_to_zero();
	}
	return is_checked(neu, is_logistic);
}
///////////////////////////////////////////

void optimization(Neuron &neuron, bool is_logistic)
{
	int counter = 1000000, n, r, i = 0;
	vector<int>combination;
	vector<int> args(COUNT_OF_ARGS, 0);
	vector<vector<int>> cache_x;
	vector<vector<double>> cache_w;

	for (int k = 0; k < pow(2, COUNT_OF_ARGS); k++)
	{
		combination.push_back(k);
		truth_table.push_back(args);
		increment(args);
	}
	n = r = truth_table.size();
	args.assign(COUNT_OF_ARGS, 0);
	while (true)
	{
		vector<vector<int>> combinations = printCombination(combination, n, r);

		for (int j = 0; j < combinations[i].size(); j++)
		{
			args = truth_table[combinations[i][j]];
			neuron.set_new_x(args);
			neuron.set_net();
			if (is_logistic) neuron.set_logistic_y();
			else neuron.set_step_y();
			neuron.set_sigma(f(args));
			neuron.set_new_w(args, is_logistic);
		}

		if (neuron.get_E() == 0 && is_checked(neuron, is_logistic))
		{
			cache_x.push_back(combinations[i]);
			cache_w.push_back(neuron.get_w());
			neuron.set_w_to_zero();
			r--; i = 0;
		}

		else if (neuron.get_E() == 0 && !is_checked(neuron, is_logistic))
		{
			if (i < combinations.size() - 1) { i++; neuron.set_w_to_zero(); }
			else break;
		}

		else neuron.set_E_to_zero();
	}

	
	for (auto pos : cache_x.back())
	{
		cout << "X = (";
		for (auto el : truth_table[pos])
		{
			cout << el << ",";
		}
		cout << ")" << endl;
	}

	cout << endl << "W = (";

	for (auto el : cache_w.back())
		cout << el << ",";
	cout << ")" << endl;

	truth_table.clear();
}

void print_y(Neuron &neuron)
{
	cout << neuron.get_y() << ",";
}

void print_era(Neuron& neuron)
{
	cout << ");	W = (";
	for (auto el : neuron.get_w())
		cout << el << ",";
	cout << "); E = " << neuron.get_E() << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Для пороговой ФА на всех комбинациях:" << endl;
	Neuron neuron(COUNT_OF_ARGS);
	calculation(neuron, false); //используя пороговую ФА

	cout << endl;

	cout << "Для логистической ФА на всех комбинациях:" << endl;
	Neuron neuron2(COUNT_OF_ARGS);
	calculation(neuron2, true); //используя логистическую ФА

	cout << endl;

	cout << "Для пороговой ФА на части комбинаций:" << endl;
	Neuron neuron3(COUNT_OF_ARGS);
	optimization(neuron3, false);

	cout << endl;

	cout << "Для логистической ФА на части комбинаций:" << endl;
	Neuron neuron4(COUNT_OF_ARGS);
	optimization(neuron4, true); 

	cout << endl;

	cout << "Проверка на возможность обучения:" << endl;
	cout << help(false) << endl;
	cout << help(true) << endl;
}
