#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;

const double NU = 0.3;

class Neural_network
{
private:
	vector <pair<double, double>> input; //input.first = w; input.second = x
	double net, sigma;
	double y, E = 0;
public:
	Neural_network(int value) //value - количество переменных
	{
		pair<double, double> temp;
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

	void set_linear_y() { y = net; }

	void set_sigma(double x) //x - истинное знач-е функции
	{
		sigma = x - y;
	}

	void set_new_w()
	{
		for (int i = 1; i < input.size(); i++)
		{
			input[i].first += NU * sigma * input[i].second;
		}
	}

	void set_new_x(vector<double> xi)
	{
		for (int i = 1; i < input.size(); i++)
			input[i].second = xi[i - 1];
	}

	void set_w_to_zero() 
	{
		for (auto &el : input)
			el.first = 0;
	}

	double get_y() { return y; }
	vector<double> get_w()
	{
		vector<double> w;
		for (auto el : input)
			w.push_back(el.first);
		return w;
	}
	double get_sigma() { return sigma; }
};
