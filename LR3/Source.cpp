#include "Neuron.h"
#include <iostream>
#include <math.h>

using namespace std;

bool check(Neuron neuron, bool is_logistic) //Проверка, обучена ли НС
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

bool help(bool is_logistic)
{
	vector<vector<int>> args = { {0, 0, 0, 0}, {0, 1, 1, 0} };
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
			neu.set_new_w(is_logistic);
		}
		if (neu.get_E() == 0) break;
		else neu.set_E_to_zero();
	}
	return check(neu, is_logistic);
}

void print_era(Neuron& neuron, int E)
{
	cout << "W = (";
	for (auto el : neuron.get_w())
		cout << el << ", ";
	cout << ")" << "\t";

	cout << "E = " << E << endl;
}

void print_x(vector<int> x)
{
	cout << "X = (";
	for (auto el : x)
		cout << el << " ";
	cout << ")" << endl;
}

void print_era(Neuron& neuron)
{
	cout << "	W = (";
	for (auto el : neuron.get_w())
		cout << el << ",";
	cout << "); E = " << neuron.get_E() << endl;
}

void run(Neuron& neuron, bool is_logistic)
{
	//vector<vector<int>> min_X = { {0,0,0,0},{0,0,0,1},{1,0,0,0},{1,1,1,1} };
	//vector<vector<int>> min_X = { {0,0,0,0},{0,1,1,0},{1,0,0,1} };
	int n, r, i = 0;
	vector<int>combination;
	vector<int> args(COUNT_OF_ARGS, 0);
	vector<vector<int>> truth_table;
	vector<vector<int>> cache;

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
			neuron.set_new_w(is_logistic);
		}

		if (neuron.get_E() == 0 && check(neuron, is_logistic))
		{
			neuron.set_w_to_zero();
			cache.push_back(combinations[i]);
			r--; i = 0;
		}

		else if (neuron.get_E() == 0 && !check(neuron, is_logistic))
		{
			if (i < combinations.size() - 1) { i++; neuron.set_w_to_zero(); }
			else break;
		}

		else neuron.set_E_to_zero();
		/*for (int i = 0; i < min_X.size(); i++)
		{
			neuron.set_new_x(min_X[i]);
			neuron.set_net();
			if (is_logistic) neuron.set_logistic_y();
			else neuron.set_step_y();
			neuron.set_sigma(f(min_X[i]));
			neuron.set_new_w(is_logistic);
		}

		print_era(neuron, check(neuron, is_logistic));
		if (check(neuron, is_logistic) == 0) break;*/
	}
	neuron.set_w_to_zero();
	while (true)
	{
		for (auto pos : cache.back())
		{
			neuron.set_new_x(truth_table[pos]);
			neuron.set_net();
			if (is_logistic) neuron.set_logistic_y();
			else neuron.set_step_y();
			neuron.set_sigma(f(truth_table[pos]));
			neuron.set_new_w(is_logistic);

			print_x(truth_table[pos]);
		}

		print_era(neuron);
		if (neuron.get_E() == 0) break;
		neuron.set_E_to_zero();
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Минимальный набор и веса для пороговой ФА: " << endl;
	Neuron neuron(COUNT_OF_ARGS);
	run(neuron, false);

	cout << endl;

	cout << "Минимальный набор и веса для логистической ФА: " << endl;
	Neuron neuron2(COUNT_OF_ARGS);
	run(neuron2, true);

	cout << endl;

	cout << "Проверка минимальных наборов на обучаемость: " << endl;
	cout << help(false) << endl;
	cout << help(true) << endl;
}
