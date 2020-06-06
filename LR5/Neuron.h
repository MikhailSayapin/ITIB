#include <iostream>
#include <vector>

using namespace std;

class Neural_network
{
private:
	int m, n;
	vector<int> f_net_last_2, f_net_last_1;
	vector<int> s;
	vector<int> t;
	vector<vector<int>> W;
	vector<int> net2;
	vector<int> net1;
public:
	Neural_network(vector<vector<int>> s, vector<vector<int>> t)
	{
		m = s[0].size();
		n = t.size();

		vector<int> temp;
		temp.assign(n, 0);
		W.assign(m, temp);
		temp.assign(m, 0);

		this->t.assign(n, 0);
		this->s.assign(m, 0);
		f_net_last_2.assign(n, 0);
		f_net_last_1.assign(m, 0);

		for (int k = 0; k < t.size(); k++)
		{
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					temp[i] += s[j][i] * t[j][k];
			}

			for (int i = 0; i < m; i++)
			{
				W[i][k] = temp[i]; temp[i] = 0;
			}
		}
	}

	void init_output_first(vector<int> s) { this->s = s; }
	void init_output_second(vector<int> t) { this->t = t; }

	void set_net2()
	{
		net2.assign(n, 0);
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++)
				net2[j] += s[i] * W[i][j];
		}
	}

	void set_t()
	{
		for (int j = 0; j < n; j++)
		{
			if (net2[j] > 0)
				t[j] = 1;
			else if (net2[j] < 0)
				t[j] = -1;
			else
				t[j] = f_net_last_2[j];
			f_net_last_2[j] = t[j];
		}
	}

	void set_net1()
	{
		net1.assign(m, 0);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				net1[i] += t[j] * W[i][j];
		}
	}

	void set_s()
	{
		for (int i = 0; i < m; i++)
		{
			if (net1[i] > 0)
				s[i] = 1;
			else if (net1[i] < 0)
				s[i] = -1;
			else
				s[i] = f_net_last_1[i];
			f_net_last_1[i] = s[i];
		}
	}

	vector<vector<int>> get_W() { return W; }
	vector<int> get_t() { return t; }
	vector<int> get_s() { return s; }
};
