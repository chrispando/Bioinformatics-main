#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

typedef vector<vector<int>> table;
typedef vector<vector<char>> path;

//To change weights for matches, gaps, and mismatches, edit the variables in class LCS
class LCS
{
private:
	string v, w;
	int m, n;
	table t;
	path p;
	vector<int>num;
	vector<char>c;
	vector<char>lcs;
	int match = 2;
	int gap = -1;
	int mismatch = -3;

	template<class T>
	void printVector(vector<vector<T>>);
public:
	LCS(string v, string w)
	{
		this->v = v;
		this->w = w;
		m = w.length();
		n = v.length();
	}

	void generateTable();
	void longestCommonSubsequence();
	void printLCS(path, string, int, int);

};

template<class T>
void LCS::printVector(vector<vector<T>>a)
{
	for (int index = 0; index < a.size(); index++)
	{
		for (int i = 0; i < a[index].size(); i++)
			cout << setw(3) << a[index][i];
		cout << endl;
	}
}
void LCS::generateTable()
{
	for (int index = 0; index < n + 1; index++)
	{
		for (int i = 0; i < m + 1; i++)
		{
			num.push_back(0);
			c.push_back('.');
		}
		t.push_back(num);
		p.push_back(c);
		num.clear();
		c.clear();
	}

	int s;
	for (int index = 0; index < m + 1; index++)
		t[0][index] += index * gap;
	for (int index = 0; index < n + 1; index++)
		t[index][0] += index * gap;

	for (int index = 1; index < n + 1; index++)
	{
		for (int i = 1; i < m + 1; i++)
		{
			int a, b, c, d;
			if (v[index - 1] == w[i - 1])//match
			{
				a = t[index - 1][i] + gap;
				b = t[index][i - 1] + gap;
				c = t[index - 1][i - 1] + match;
				s = max(max(a,b ), c);
			}
			else//mismatch
			{
				a = t[index - 1][i] + gap;
				b = t[index][i - 1] + gap;
				d = t[index - 1][i - 1] + mismatch;
				s = max(max(a, b), d);
			}
			t[index][i] = s;
			if (s == a)
			{
				p[index][i] = '|';
			}
			else if (s == b)
			{
				p[index][i] = '-';
			}
			else if (s == c)
			{
				p[index][i] = '\\';
			}
			else
			{
				p[index][i] = '0';
			}
			
		}
	}
	printVector(t);
}
void LCS::longestCommonSubsequence()
{
	printVector(p);
	printLCS(p, v, n, m);
}
void LCS::printLCS(path b, string v, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == '\\')
	{
		
		printLCS(b, v, i - 1, j - 1);
		cout << v[i-1];
	}
	else
	{
		if (b[i][j] == '|')
		{
			printLCS(b, v, i - 1, j);
		}
		else
			printLCS(b, v, i, j - 1);
	}

	
}

int main()
{
	string v = "TCCCAGTTATGTCAGGGGACACGAGCATGCAGAGAC";
	string w = "AATTGCCGCCGTCGTTTTCAGCAGTTATGTCAGATC";

	LCS longest(v, w);

	longest.generateTable();
	longest.longestCommonSubsequence();

	std::cin.get();
	return 0;
}
