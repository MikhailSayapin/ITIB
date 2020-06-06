#pragma once
#include <vector>

using namespace std;

const int COUNT_OF_ARGS = 4;

int f(vector<int>& x)
{
	return !((x[0] || x[1] || x[2]) && (x[1] || x[2] || x[3]));
}

void increment(vector<int>& x) //инкрементирует переменные
{
	int i = x.size() - 1;
	while (i >= 0 && x[i] == 1)
	{
		x[i] = 0; i--;
	}
	if (i >= 0)
		x[i] = 1;
}

vector<vector<int>> calculate_C() //Возвращает вектор C
{
	vector<int> args(COUNT_OF_ARGS, 0);
	vector<vector<int>> args_0;
	vector<vector<int>> args_1;

	for (int i = 0; i < pow(2, COUNT_OF_ARGS); i++)
	{
		if (f(args) == 0) args_0.push_back(args);
		else args_1.push_back(args);
		increment(args);
	}

	if (args_0.size() >= args_1.size()) return args_1;
	else return args_0;
}

vector<double> calculate_phi(vector<int>& min_X) //Возвращает вектор фи
{
	vector<vector<int>> C = calculate_C();
	vector<double> temp; temp.push_back(1);
	for (int j = 0; j < C.size(); j++)
	{
		double sum = 0;
		for (int i = 1; i <= COUNT_OF_ARGS; i++)
		{
			sum += pow((min_X[i] - C[j][i - 1]), 2);
		}
		temp.push_back(exp(-sum));
	}
	return temp;
}

void combinationUtil(vector<int>&, vector<int>&, vector<vector<int>>&, int, int, int, int);

//Возвращает число различных сочетаний из n по r массива arr
vector<vector<int>> printCombination(vector<int>& arr, int n, int r)
{
	vector<int>temp(r, 0);
	vector<vector<int>> data;
	combinationUtil(arr, temp, data, 0, n, 0, r);
	return data;
}

//производит комбинирование для ф-ции printCombination
void combinationUtil(vector<int>& arr, vector<int>& temp, vector<vector<int>>& data,
	int start, int end,
	int index, int r)
{
	if (index == r)
	{
		data.push_back(temp);
		return;
	}

	for (int i = start; i < end && end - i + 1 >= r - index; i++)
	{
		temp[index] = arr[i];
		combinationUtil(arr, temp, data, i + 1,
			end, index + 1, r);
	}
}
