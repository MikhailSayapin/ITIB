#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;

const int COUNT_OF_ARGS = 4;

vector<vector<int>> calculate_C();
vector<double> calculate_phi(vector<int>& min_X);
void increment(vector<int>& x);
int f(vector<int>& x);
vector<vector<int>> printCombination(vector<int>& arr, int n, int r);

const double NU = 0.3;
const double eps = 0.00001;

class Neuron
{
private:
	vector<double> input_w;
	vector <int> input_x;
	double net, sigma;
	double y;
	int E;
public:
	Neuron(int value) //value - количество переменных
	{
		vector<double> temp_w; vector<int> temp_x;
		temp_w.push_back(0); temp_x.push_back(1); //единичный вход
		for (int i = 0; i < value; i++)
			temp_x.push_back(0);
		for (int i = 0; i < calculate_C().size(); i++) //calculate_C().size() = J
			temp_w.push_back(0);
		input_w = temp_w; input_x = temp_x;
	}

	void set_net()
	{
		double counter = input_w[0];
		vector<double> phi = calculate_phi(input_x);
		for (int i = 1; i <= calculate_C().size(); i++)
			counter += input_w[i] * phi[i];
		net = counter;
	}

	void set_step_y()
	{
		if (net >= 0) y = 1;
		else y = 0;
	}

	//Вычисление логистической ФА
	double f_logistic() 
	{
		//return 1 / (2 * (net / (1 + abs(net) + 1)));
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

	void set_sigma(double t) //t - истинное знач-е функции
	{
		sigma = t - y;
		if (sigma != 0) E++;
	}

	void set_new_w(bool is_logistic)
	{
		vector<double> phi = calculate_phi(input_x);

		if (is_logistic)
		{
			for (int i = 0; i < input_w.size(); i++)
				input_w[i] += NU * sigma * phi[i] * df_logistic();
		}
		else
		{
			for (int i = 0; i < input_w.size(); i++)
				input_w[i] += NU * sigma * phi[i];
		}
		
	}

	void set_new_x(vector<int> xi)
	{
		for (int i = 1; i < input_x.size(); i++)
			input_x[i] = xi[i - 1];
	}

	void set_w_to_zero() 
	{
		for (auto &el : input_w)
			el = 0;
	}

	void set_E_to_zero() { E = 0; }

	int get_y() { return y; }
	vector<double> get_w()
	{
		vector<double> w;
		for (auto el : input_w)
			w.push_back(el);
		return w;
	}
	int get_E() { return E; }
	double get_sigma() { return sigma; }
};
