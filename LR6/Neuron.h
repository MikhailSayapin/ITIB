#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class Neural_network
{
private:
	vector<pair<double, double>> X;
	vector<int> Y;
	vector<pair<double, double>> centers;
	vector<double> dist;
	vector<vector<pair<double, double>>> rezult;

	int count_of_neurons, count_of_outputs, count_of_inputs;
public:
	Neural_network(vector<pair<double, double>> X, vector<pair<double, double>> centers)
	{
		this->X = X; this->centers = centers;
		count_of_outputs = count_of_neurons = centers.size();
		count_of_inputs = X.size();

		dist.assign(count_of_neurons, 0);
		vector<pair<double, double>> temp; temp.push_back({ 0, 0 });
		rezult.assign(count_of_outputs, temp);
	}
private:
	void set_dist_y(int number_of_X)
	{
		int min_pos;
		for (int j = 0; j < count_of_neurons; j++)
		{
			dist[j] = sqrt(pow(X[number_of_X].first - centers[j].first, 2) + 
				pow(X[number_of_X].second - centers[j].second, 2));
		}
		min_pos = distance(dist.begin(), min_element(dist.begin(), dist.end()));
		Y.assign(count_of_outputs, 0);
		Y[min_pos] = 1;
	}
public:
	void set_rezult()
	{
		int min_pos;
		pair<double, double> curr_X;
		for (int i = 0; i < count_of_inputs; i++)
		{
			set_dist_y(i);
			min_pos = distance(Y.begin(), find(Y.begin(), Y.end(), 1));
			curr_X = { X[i].first, X[i].second };
			rezult[min_pos].push_back(curr_X);
		}

		for (auto &el : rezult)
			el.erase(el.begin());
	}

	vector<vector<pair<double, double>>> get_rezult() { return rezult; }
};
