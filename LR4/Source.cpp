#include <iostream>
#include <math.h>
#include "Neuron.h"

using namespace std;

void print(Neural_network& neu, double E);

void first(Neural_network& neu, vector<int> &x)
{
	neu.set_new_x1(x);
	neu.set_net1();
	neu.set_new_x2();
	neu.set_net2();
	neu.set_y();
}

void second(Neural_network& neu, vector<double>& t)
{
	neu.set_sigma2(t);
	neu.set_sigma1();
}

void third(Neural_network& neu)
{
	neu.set_new_w_ij();
	neu.set_new_w_jm();
}

void run(Neural_network& neu, vector<int>& x, vector<double>& t)
{
	while (true)
	{
		first(neu, x); second(neu, t), third(neu);
		
		double sum = 0;
		for (int j = 1; j <= neu.get_M(); j++)
			sum += pow((t[j - 1] - neu.get_y(j - 1)), 2);
		double E = sqrt(sum);

		print(neu, E);

		if (E <= eps) break;
	}
}

void print(Neural_network& neu, double E)
{		
	cout << "Y = (";
	for (auto el : neu.get_y())
		cout << el << ",";
	cout << ")" << "E = " << E << endl;
}


int main()
{
	Neural_network neu(2, 1, 2);
	vector<int>x = { 1, 2, 1 };
	vector<double>t = { -0.1, -0.1 };
	run(neu, x, t);
}
