#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;

void increment(vector<int>& x);
vector<vector<int>> printCombination(vector<int> &arr, int n, int r);

const double NU = 0.3;
const double eps = 0.00001;

class Neuron
{
private:
	vector <pair<double, int>> input; //input.first = w; input.second = x
	double net, sigma;
	int y, E;
public:
	Neuron(int value) //value - количество переменных
	{
		E = 0;
		pair<double, int> temp;
		temp.first = 0; temp.second = 1; input.push_back(temp); //единичный вход
		for (int i = 0; i < value; i++)
		{
			temp.first = temp.second = 0;
			input.push_back(temp);
		}
	}

	//Вычисление net
	void set_net()
	{
		double counter = 0;
		for (auto el : input)
			counter += el.first * el.second;
		net = counter;
	}

	//Вычисление ступенчатой ФА
	void set_step_y()
	{
		if (net >= 0) y = 1;
		else y = 0;
	}

	//Вычисление логистической ФА
	double f_logistic() //eps - параметр приращения функции
	{
		return 0.5 * (1 + (net / (1 + abs(net))));
	}

	//Вычисление производной от ФА
	double df_logistic()
	{
		return 0.5 / (pow(1 + abs(net), 2));
	}

	//Вычисление y
	void set_logistic_y()
	{
		if (f_logistic() >= 0.5) y = 1;
		else y = 0;
	}

	//Вычисление сигмы
	void set_sigma(int t) //t - истинное знач-е функции
	{
		sigma = t - y;
	}

	//Вычисление приращения весов
	void set_new_w(vector<int> xi, bool is_logistic)
	{
		if (sigma == 0) return;
		else
		{
			E++;
			if (is_logistic) input[0].first += NU * sigma * df_logistic();
			else input[0].first += NU * sigma;
			for (int i = 1; i <= xi.size(); i++)
			{
				if (is_logistic) input[i].first += NU * sigma * input[i].second * df_logistic();
				else input[i].first += NU * sigma * input[i].second;
			}

		}
	}

	//Установка вектора X извне
	void set_new_x(vector<int> xi)
	{
		for (int i = 1; i < input.size(); i++)
			input[i].second = xi[i - 1];
	}

	void set_E_to_zero() { E = 0; }
	void set_w_to_zero() 
	{
		for (auto &el : input)
			el.first = 0;
	}

	int get_E() { return E; }
	int get_y() { return y; }
	vector<double> get_w()
	{
		vector<double> w;
		for (auto el : input)
			w.push_back(el.first);
		return w;
	}
	double get_sigma() { return sigma; }
};
