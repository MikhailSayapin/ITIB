#pragma once
#include <vector>

using namespace std;

//Алгоритм инкрементирования булевых векторов, взят из Т.Кормена
void increment(vector<int>& x)  
{
	int i = x.size() - 1;
	while (i >= 0 && x[i] == 1)
	{
		x[i] = 0; i--;
	}
	if (i >= 0)
		x[i] = 1;
}

void combinationUtil(vector<int>&, vector<int>&, vector<vector<int>>&, int, int, int, int);

//Возвращает число различных сочетаний из n по r массива arr
vector<vector<int>> printCombination(vector<int> &arr, int n, int r)
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
