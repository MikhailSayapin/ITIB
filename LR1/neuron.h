#pragma once
#include <vector>

using namespace std;

const double NU = 0.5;

class Neuron
{
private:
	vector <pair<double, int>> input; //input.first = w; input.second = x
	double net, y, sigma;
	int E = 0;
public:
	Neuron(int value) //value - количество переменных
	{
		pair<double, int> temp;
		temp.first = 0; temp.second = 1; input.push_back(temp); //единичный вход
		for (int i = 0; i < value; i++)
		{
			temp.first = temp.second = 0;
			input.push_back(temp);
		}
	}

	void set_net()
	{
		double counter = 0;
		for (auto el : input)
			counter += el.first * el.second;
		net = counter;
	}

	void set_y()
	{
		if (net >= 0) y = 1;
		else y = 0;
	}

	void set_sigma(int t) //t - истинное знач-е функции
	{
		sigma = t - y;
	}

	void set_new_w(vector<int> xi)
	{
		if (sigma == 0) return;
		else
		{
			E++;
			input[0].first += NU * sigma;
			for (int i = 1; i < xi.size(); i++)
				input[i].first += NU * sigma * xi[i];
		}
	}

	void set_new_x(vector<int> xi)
	{
		for (int i = 1; i < input.size(); i++)
			input[i].second = xi[i - 1];
	}

	void set_E_to_zero() { E = 0; }

	int get_E() { return E; }
	int get_y() { return y; }
	vector<double> get_w()
	{
		vector<double> w;
		for (auto el : input)
			w.push_back(el.first);
		return w;
	}
};
