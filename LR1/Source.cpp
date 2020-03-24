#include "Neuron.h"
#include <iostream>
#include <math.h>
#include <array>
#include <iostream>

using namespace std;

const int COUNT_OF_ARGS = 4;

void print_y(Neuron& neuron);
void print_era(Neuron& neuron);

int f(vector<int> &x)
{
	return !((x[0] || x[1] || x[2]) && (x[1] || x[2] || x[3]));
}

void increment(vector<int> &x)
{
	int i = x.size() - 1;
	while (i >= 0 && x[i] == 1)
	{
		x[i] = 0; i--;
	}
	if (i >= 0)
		x[i] = 1;
}

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
	Neuron neuron(COUNT_OF_ARGS);
	calculation(neuron, false);

	cout << endl << endl;

	Neuron neuron2(COUNT_OF_ARGS);
	calculation(neuron2, true);
}