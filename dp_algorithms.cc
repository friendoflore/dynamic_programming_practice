/*****
** Description: Generic implementations of classic dynamic programming algorithms
** Author: Tim Robinson
** Date: 10/1/2016
***********************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::max;
using std::max_element;

// Print utilities
template <typename T>
void _print_vector(vector<T> in)
{
	cout << "[";
	for (auto x : in)
		cout << x << " ";
	cout << "]" << endl;
}

// Compare functions
template <typename T>
bool size_compare(T const &lhs, T const &rhs)
{
	return lhs.size() < rhs.size();
}



// Longest Increasing Subsequence
// Time: O(n^2)
// Space: O(n^2) (returns the actual subsequence)

template <typename T>
void _lis_print_run(T to_print)
{
	for (auto x : to_print) {
		for (auto y : x)
			cout << y << " ";
		cout << endl;
	}
}

template <typename T>
T lis(T const &input)
{
	int n = input.size();
	vector<T> run(n);

	auto run_it = run.begin();
	
	// Initialize the table of running solutions
	for (auto it = input.begin(); it != input.end(); ++it) 
	{
		run_it->push_back(*it);
		++run_it;
	}

	run_it = run.begin();
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		auto in_run_it = run.begin();
		for (auto in_it = input.begin(); in_it != it; ++in_it)
		{	
			if (*it > *in_it)
			{	
				if (run_it->size() < (in_run_it->size() + 1))
				{
					*run_it = *in_run_it;
					run_it->push_back(*it);
				}
			}
			++in_run_it;
		}

		++run_it;
	}

	auto longest = max_element(run.begin(), run.end(), size_compare<T>);

	return *longest;
}



// Longest Common Subsequence
// Time: O(n*m)
// Space: O(n*m)

template <typename T>
T lcs(T const &in1, T const &in2)
{

	int m = in1.size();
	int n = in2.size();
	vector<vector<int>> LCS(m + 1, vector<int>(n + 1));

	for (int i = 0; i < m + 1; ++i)
		LCS[i][0] = 0;
	for (int i = 0; i < n + 1; ++i)
		LCS[0][i] = 0;

	for (int i = 1; i < m + 1; ++i) {
		for (int j  = 1; j < n + 1; ++j)
		{
			if (in1[i - 1] == in2[j - 1])
			{
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			} else
			{
				LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
	}

	T result;
	int i = m;
	int j = n;

	while (i && j)
	{
		if (LCS[i][j] == LCS[i][j - 1])
			--j;
		else if (LCS[i][j] == LCS[i - 1][j])
			--i;
		else if (LCS[i][j] > LCS[i - 1][j - 1])
		{
			result.insert(result.begin(), in1[i - 1]);
			--i;
			--j;
		}
	}

	return result;
}



// Longest Palindromic Subsequence
// Time: O(n^2)
// Space: O(n^3) (This returns the longest palindrome itself)

template <typename T>
void _print_lps_matrix(const vector<vector<T>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			cout << matrix[i][j].size() << " ";
		}
		cout << endl;
	}
}

template <typename T>
T lps(T const &in)
{
	int n = in.size();

	vector<vector<T>> LPS(n, vector<T>(n));

	for (int i = 0; i < n; ++i)
	{
		LPS[i][i].push_back(in[i]);
	}

	for (int sublen = 2; sublen <= n; ++sublen)
	{
		for (int i = 0; i < n - sublen + 1; ++i)
		{
			int j = i + sublen - 1;

			if ((in[i] == in[j]) && (sublen == 2))
			{
				LPS[i][j].clear();
				LPS[i][j].push_back(in[1]);
				LPS[i][j].push_back(in[2]);
			} else if (in[i] == in[j])
			{
				LPS[i][j] = LPS[i + 1][j - 1];
				LPS[i][j].insert(LPS[i][j].begin(), in[i]);
				LPS[i][j].push_back(in[j]); 
			} else
			{
				LPS[i][j] = max(LPS[i + 1][j], LPS[i][j - 1], size_compare<T>);
			}
		}
	}

	// _print_lps_matrix(LPS);

	return LPS[0][n - 1];

}




// TODO
// Knapsack Problem
// Time: O(n*W)
// Space: O(n*W)



int main(int argc, char *argv[])
{

	// Function test calls

	// LIS
		// static const int arr[] = {1, 5, 3, 4, 2, 7, 8, 2, 5, 9, 1, 2, 5, 3, 7, 4, 9, 3, 1, 5};
		// vector<int> vTest(arr, arr + sizeof(arr)/sizeof(arr[0]));
		// vector<int> vResult = lis<vector<int>>(vTest);
		// _print_vector(vResult);	

		// string result = lis<string>("thequickfoxjumpedoverthelazydog");
		// cout << result << endl;

	// LCS
		// string str1 = "LNIOGDURFGHAERUGSRBVIBEUVAUEGFVLVEURULFIBUSRFSLVBUIRFGSIU";
		// string str2 = "OACHBGVCWEIBZSHFIAUNFZSDNBCVSZHRUSFRUFIHASWERUYGQAWEYGAHR";
		// cout << lcs<string>(str1, str2) << endl;

		// static const int arr1[] = {1, 5, 3, 4, 2, 7, 8, 2, 5, 9, 1, 2, 5, 3, 7, 4, 9, 3, 1, 5};
		// static const int arr2[] = {3, 4, 5, 8, 2, 9, 0, 4, 3, 2, 1, 4, 5, 8, 2, 3, 5, 6, 9, 1};
		// vector<int> v1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		// vector<int> v2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));

		// vector<int> vResult = lcs<vector<int>>(v1, v2);
		// _print_vector(vResult);

	// LPS
		// string str = "xabacabdbcddbcabadcbx";
		// cout << lps<string>(str) << endl;

		// static const int arr1[] = {1, 5, 3, 4, 2, 7, 8, 2, 5, 9, 1, 2, 5, 3, 7, 4, 9, 3, 1, 5};	
		// vector<int> v1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));

		// _print_vector(lps<vector<int>>(v1));

	return 0;
}