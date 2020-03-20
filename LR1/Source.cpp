#include "Neuron.h"
#include <iostream>
#include <math.h>
#include <array>
#include <iostream>

using namespace std;

const int COUNT_OF_ARGS = 3;

int f(vector<int> &x)
{
	return !((x[0] || x[1] || x[2]) && (x[1] || x[2] || x[3]));
}

int test_f(vector<int>& x)
{
	return !(((!(x[1]) || x[3]) && x[0]) || (x[0] && x[2]));
}

int test2_f(vector<int>& x)
{
	return x[0] && x[1] && x[2];
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

void calculation(Neuron &neuron)
{
	while (true)
	{
		vector<int> args(COUNT_OF_ARGS, 0);
		for (int i = 0; i < pow(2, COUNT_OF_ARGS); i++) //Цикл внутри эпохи
		{
			neuron.set_net();
			neuron.set_y();
			neuron.set_sigma(test2_f(args));
			neuron.set_new_w(args);

			increment(args);
		}

		if (neuron.get_E() == 0) break;
		neuron.set_E_to_zero();
	}
}

int main()
{
	Neuron neuron(COUNT_OF_ARGS);
	calculation(neuron);
}
