// Find 6x6 MSQ using backtracking
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

//Order of checks
int do_diag(int v[], int s);
int do_row3(int v[]);
int do_col2(int v[]);
int do_col5(int v[]);
int do_row1(int v[]);
int do_row6(int v[]);
int do_col3(int v[]);
int do_col4(int v[]);
int do_rows245(int v[]);

int cross;

/*Ordering of magic square by array indices
0  .  .  .  .  6	-  16 22 23 19 -	-  -  -  -  -  -
.  1  .  .  7  .	.  -  .  .  -  .	30 -  26 28 -  31
.  .  2  8  .  .	12 13 -  -  14 15	-  -  -  -  -  -
.  .  9  3  .  .	.  17 -  -  20 .	32 -  -  -  -  33
.  10 .  .  4  .	.  -  .  .  -  .	34 -  27 29 -  35
11 .  .  .  .  5	-  18 24 25 21 -	-  -  -  -  -  -
*/

ostream& operator<<(ostream& out, int v[])
{
	int ord[6][6] = {{0, 16, 22, 23, 19, 6}, {30, 1, 26, 28, 7, 31}, {12, 13, 2, 8, 14, 15},
			{32, 17, 9, 3, 20, 33}, {34, 10, 27, 29, 4, 35}, {11, 18, 24, 25, 21, 5}};
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
			out << setw(3) << v[ord[i][j]] + 1;
		out << endl;
	}
	out << endl;
	return out;
}

int main()
{
	int v[36];
	for (int i = 0; i < 36; i++) v[i] = i;

	cout << "Starting value: ";
	cin >> cross;

	time_t begin_time = clock(), end_time;
	int count = do_diag(v, 0);
	end_time = clock();

	cout << count << " squares\n";
	cout << "Time: " << int(end_time - begin_time) << endl;

	return 0;
}

int do_diag(int v[], int s)
{
	int count = 0;
	for (int i = s; i < 31; i++)
	for (int j = i + 1; j < 32; j++)
	for (int k = j + 1; k < 33; k++)
	for (int m = k + 1; m < 34; m++)
	for (int n = m + 1; n < 35; n++)
	for (int p = n + 1; p < 36; p++)
	if (v[i] + v[j] + v[k] + v[m] + v[n] + v[p] == 105)
	{
		swap(v[s], v[i]); swap(v[s + 1], v[j]); swap(v[s + 2], v[k]); swap(v[s + 3], v[m]); swap(v[s + 4], v[n]); swap(v[s + 5], v[p]);
		if (s)
		{
			if (cross == 0) return do_row3(v);
			cross--;
		}
		else return do_diag(v, 6);
		if (s == 0) cout << count << endl;
		swap(v[s + 5], v[p]); swap(v[s + 4], v[n]); swap(v[s + 3], v[m]); swap(v[s + 2], v[k]); swap(v[s + 1], v[j]); swap(v[s], v[i]);
	}
	return count;
}

int do_row3(int v[])
{
	int count = 0;
	for (int i = 12; i < 33; i++)
	for (int j = i + 1; j < 34; j++)
	for (int k = j + 1; k < 35; k++)
	for (int m = k + 1; m < 36; m++)
	if (v[i] + v[j] + v[2] + v[8] + v[k] + v[m] == 105)
	{
		swap(v[12], v[i]); swap(v[13], v[j]); swap(v[14], v[k]); swap(v[15], v[m]);
		for (int perm = 0; perm < 24; perm++)
		{
			count += do_col2(v);
			next_permutation(v + 12, v + 16);
		}
		swap(v[15], v[m]); swap(v[14], v[k]); swap(v[13], v[j]); swap(v[12], v[i]);
	}
	return count;
}

int do_col2(int v[])
{
	int count = 0;
	for (int i = 16; i < 34; i++)
	for (int j = i + 1; j < 35; j++)
	for (int k = j + 1; k < 36; k++)
	if (v[i] + v[1] + v[13] + v[j] + v[10] + v[k] == 105)
	{
		swap(v[16], v[i]); swap(v[17], v[j]); swap(v[18], v[k]);
		count += do_col5(v);	// permutations of 16-18 handled in do_col5
		swap(v[18], v[k]); swap(v[17], v[j]); swap(v[16], v[i]);
	}
	return count;
}

int do_col5(int v[])
{
	int count = 0;
	for (int i = 19; i < 34; i++)
	for (int j = i + 1; j < 35; j++)
	for (int k = j + 1; k < 36; k++)
	if (v[i] + v[7] + v[14] + v[j] + v[4] + v[k] == 105)
	{
		swap(v[19], v[i]); swap(v[20], v[j]); swap(v[21], v[k]);
		for (int perm = 0; perm < 6; perm++)
		{
			for (int perm2 = 0; perm2 < 6; perm2++)
			{
				count += do_row1(v);
				next_permutation(v + 19, v + 22);
			}
			next_permutation(v + 16, v + 19);
		}
		swap(v[21], v[k]); swap(v[20], v[j]); swap(v[19], v[i]);
	}
	return count;
}

int do_row1(int v[])
{
	int count = 0;
	for (int i = 22; i < 35; i++)
	for (int j = i + 1; j < 36; j++)
	if (v[0] + v[16] + v[i] + v[j] + v[19] + v[6] == 105)
	{
		swap(v[22], v[i]); swap(v[23], v[j]);
		count += do_row6(v);	// permutations of 22, 23 handled in do_row6
		swap(v[23], v[j]); swap(v[22], v[i]);
	}
	return count;
}

int do_row6(int v[])
{
	int count = 0;
	for (int i = 24; i < 35; i++)
	for (int j = i + 1; j < 36; j++)
	if (v[11] + v[18] + v[i] + v[j] + v[21] + v[5] == 105)
	{
		swap(v[24], v[i]); swap(v[25], v[j]);
		count += do_col3(v);
		swap(v[22], v[23]);
		count += do_col3(v);
		swap(v[24], v[25]);
		count += do_col3(v);
		swap(v[22], v[23]);
		count += do_col3(v);
		swap(v[24], v[25]);
		swap(v[25], v[j]); swap(v[24], v[i]);
	}
	return count;
}

int do_col3(int v[])
{
	int count = 0;
	for (int i = 26; i < 35; i++)
	for (int j = i + 1; j < 36; j++)
	if (v[22] + v[i] + v[2] + v[9] + v[j] + v[24] == 105)
	{
		swap(v[26], v[i]); swap(v[27], v[j]);
		count += do_col4(v);	// permutations of 26, 27 handled in do_col5
		swap(v[27], v[j]); swap(v[26], v[i]);
	}
	return count;
}

int do_col4(int v[])
{
	int count = 0;
	for (int i = 28; i < 35; i++)
	for (int j = i + 1; j < 36; j++)
	if (v[23] + v[i] + v[8] + v[3] + v[j] + v[25] == 105)
	{
		swap(v[28], v[i]); swap(v[29], v[j]);
		count += do_rows245(v);
		swap(v[26], v[27]);
		count += do_rows245(v);
		swap(v[28], v[29]);
		count += do_rows245(v);
		swap(v[26], v[27]);
		count += do_rows245(v);
		swap(v[28], v[29]);
		swap(v[29], v[j]); swap(v[28], v[i]);
	}
	return count;
}

int do_rows245(int v[])
{
	int count = 0;
	for (int i = 30; i < 35; i++)
	for (int j = i + 1; j < 36; j++)
	if (v[i] + v[1] + v[26] + v[28] + v[7] + v[j] == 105)
	{
		swap(v[30], v[i]); swap(v[31], v[j]);
		for (int k = 32; k < 35; k++)
		for (int m = k + 1; m < 36; m++)
		if (v[k] + v[17] + v[9] + v[3] + v[20] + v[m] == 105)
		{
			swap(v[32], v[k]); swap(v[33], v[m]);
			for (int perm = 0; perm < 2; perm++)
			{
				for (int perm2 = 0; perm2 < 2; perm2++)
				{
					for (int perm3 = 0; perm3 < 2; perm3++)
					{
						if (v[0] + v[30] + v[12] + v[32] + v[34] + v[11] == 105)
						if (v[6] + v[31] + v[15] + v[33] + v[35] + v[5] == 105)
						{
							count++;
							cout << v;
						}
						swap(v[34], v[35]);
					}
					swap(v[32], v[33]);
				}
				swap(v[30], v[31]);
			}
			swap(v[33], v[m]); swap(v[32], v[k]);
		}
		swap(v[31], v[j]); swap(v[30], v[i]);
	}
	return count;
}
