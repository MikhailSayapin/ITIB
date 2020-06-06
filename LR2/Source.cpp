#include <iostream>
#include <math.h>
#include <vector>
#include "Neuron.h"

using namespace std;

const int M = 20;

double f(double t)
{
	return log(t) - 1;
}

vector<double> values(double a, double b)
{
	vector<double> temp;
	double dN = static_cast<double>(b - a) / M;
	
	temp.push_back(f(a));
	for (int i = 1; i < M - 1; i++)
		temp.push_back(f(a + i * dN));
	temp.push_back(f(b));

	return temp;
}

void print_era(int era_counter, Neural_network& neu, double eps)
{
	cout.precision(8);
	cout << "Количество эпох: " << era_counter << "\tСреднеквадратичная ошибка = " << eps << endl;
	cout << "Веса = ( ";
	for (auto el : neu.get_w())
		cout << el << " ";
	cout << ")" << endl;
}

void print_rezults(vector<double> predict_values, int M, int p)
{
	cout.precision(8);
	cout << "\nПри размере окна = " << p << " значения функции на интервале [a, b] = ( ";
	for (auto it = predict_values.begin(); it != predict_values.begin() + M; it++)
		cout << *it << " ";
	cout << ")" << endl;
	cout << "\nПри размере окна = " << p << " значения функции на интервале (b, 2b-a] = ( ";
	for (auto it = predict_values.begin() + M; it != predict_values.end(); it++)
		cout << *it << " ";
	cout << ")" << endl;
}

void training(Neural_network &neu, int p, int N, int nu)
{
	vector<vector<double>> v_values;
	vector<double> real_values = values(1, 5);
	double eps = 0;

	for (int i = 0; i < M - p; i++)
	{
		vector<double>temp;
		for (int j = i; j < p + i; j++)
			temp.push_back(real_values[j]);
		v_values.push_back(temp);
		temp.clear();
	}

	for (int era_counter = 0; era_counter < N; era_counter++)
	{
		eps = 0;
		for (int i = 0; i < v_values.size(); i++)
		{
			neu.set_new_x(v_values[i]);
			neu.set_net();
			neu.set_linear_y();
			neu.set_sigma(real_values[i + p]);
			neu.set_new_w();

			eps += pow(real_values[i + p] - neu.get_y(), 2);
		}
	}
	print_era(N, neu, sqrt(eps));
}

void prediction(Neural_network &neu, int p)
{
	vector<vector<double>> v_values;
	vector<double> real_values = values(1, 5);
	vector<double> predict_values = real_values;

	for (int i = 0; i < M - p + 1; i++)
	{
		vector<double>temp;
		for (int j = i; j < p + i; j++)
			temp.push_back(real_values[j]);
		v_values.push_back(temp);
		temp.clear();
	}

	for (int i = M - p; i < 2 * M - p; i++)
	{
		neu.set_new_x(v_values[i]);
		neu.set_net();
		neu.set_linear_y();
		predict_values.push_back(neu.get_y());

		vector<double> temp;
		for (int j = i + 1; j < i + p + 1; j++)
		{
			temp.push_back(predict_values[j]);
		}
		v_values.push_back(temp);
		temp.clear();
	}

	print_rezults(predict_values, M, p);
}

int main()
{
	setlocale(LC_ALL, "ru");
	double p, N, nu;
	cout << "Введите ширину окна: ";
	cin >> p;
	cout << "Введите количество эпох обучения: ";
	cin >> N;
	cout << "Введите коэффициент обучения: ";
	cin >> nu;

	Neural_network neu(p);
	training(neu, p, N, nu);
	prediction(neu, p);
}
