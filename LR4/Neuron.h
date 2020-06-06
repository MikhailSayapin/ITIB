#pragma once
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

const double NU = 1;
const double eps = 0.001;

class Neural_network
{
private:
	int N, J, M;
	vector<vector<double>> w_ij;
	vector<vector<double>> w_jm;
	vector <int> input_x1;
	vector <double> input_x2;

	vector<double> net1;
	vector<double> net2;
	vector<double> sigma_2;
	vector<double> sigma_1;
	
	vector<double> y;
public:
	Neural_network(int N, int J, int M) 
	{
		this->N = N; this->J = J; this->M = M;
		vector<double> temp_N; vector<double> temp_J;

		for (int j = 1; j <= J; j++)
			temp_N.push_back(0);
		for (int i = 0; i <= N; i++)
			w_ij.push_back(temp_N);

		for (int m = 1; m <= M; m++)
			temp_J.push_back(0);
		for (int j = 0; j <= J; j++)
			w_jm.push_back(temp_J);

		input_x1.assign(N + 1, 0);
		input_x2.assign(J + 1, 0); input_x2[0] = 1;

		net1.assign(J, 0);
		net2.assign(M, 0);
		sigma_2.assign(M, 0);

		sigma_1.assign(J, 0);

		y.assign(M, 0);
	}

	void set_net1()
	{
		for (int j = 0; j < J; j++)
		{
			double counter = 0;
			for (int i = 0; i <= N; i++)
				counter += w_ij[i][j] * input_x1[i];
			net1[j] = counter;
		}
	}

	void set_net2()
	{
		for (int m = 0; m < M; m++)
		{
			double counter = 0;
			for (int j = 0; j <= J; j++)
				counter += w_jm[j][m] * input_x2[j];
			net2[m] = counter;
		}
	}
private:
	double fnet(double net)
	{
		return (1 - exp(-net)) / (1 + exp(-net));
	}
	
	double dfnet(double net)
	{
		return (1 - pow(fnet(net), 2)) / 2;
	}
public:
	void set_new_x1(vector<int> xi)
	{
		for (int i = 0; i <= N; i++)
			input_x1[i] = xi[i];
	}

	void set_new_x2()
	{
		for (int j = 0; j < J; j++)
			input_x2[j+1] = fnet(net1[j]);
	}

	void set_y()
	{
		for (int m = 0; m < M; m++)
			y[m] = fnet(net2[m]);
	}

	void set_sigma2(vector<double> t)
	{
		for (int m = 0; m < M; m++)
			sigma_2[m] = dfnet(net2[m]) * (t[m] - y[m]);
	}

	void set_sigma1()
	{
		for (int j = 0; j < J; j++)
		{
			double counter = 0;
			for (int m = 0; m < M; m++)
				counter += w_jm[j][m] * sigma_2[m];
			sigma_1[j] = dfnet(net1[j]) * counter;
		}
	}

	void set_new_w_ij()
	{
		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j < J; j++)
				w_ij[i][j] += NU * input_x1[i] * sigma_1[j];
		}
	}

	void set_new_w_jm()
	{
		for (int j = 0; j <= J; j++)
		{
			for (int m = 0; m < M; m++)
				w_jm[j][m] += NU * input_x2[j] * sigma_2[m];
		}
	}

	int get_M() { return M; }
	double get_y(int index) { return y[index]; }
	vector<double> get_y() { return y; }
};
