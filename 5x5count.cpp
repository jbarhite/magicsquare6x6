// Find 5x5 MSQ using backtracking
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//Order of checks
int do_diag(int v[]);
int do_X(int v[]);

/*Ordering of  magic square by array indices
0  1  2  3
12 4  9  13
14 7  5  15
11 8  10 6
*/

// Ouput a magic square
ostream& operator<<(ostream& out, int v[])
{
	out << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3]  << endl
		<< v[12]<< ' ' << v[4] << ' ' << v[9] << ' ' << v[13] << endl
		<< v[14]<< ' ' << v[7] << ' ' << v[5] << ' ' << v[15] << endl
		<< v[11]<< ' ' << v[8] << ' ' << v[10]<< ' ' << v[6]  << endl << endl;
	return out;
}

int main()
{
	int v[25] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
	//bool a[25];
	//for (int i = 0; i < )
   
	time_t begin_time = clock(), end_time;
	int count = do_diag(v);
	end_time = clock();

	cout << count << " squares\n";
	cout << "Time: " << int(end_time - begin_time) << endl;

	// system("pause");
	return 0;
}

int do_diag(int v[])
{
	int count = 0;
	for (int i = 0; i < 13; i++)	// sequence through As
	{
		swap(v[0], v[i]);
		for (int j = 1; j < 25; j++)	// sequence through Bs
		{
			swap(v[1], v[j]);
			for (int k = 2; k < 25; k++)	// sequence through Cs
			if (v[k] > v[1])		// C > B
			{
				swap(v[2], v[k]);
				for (int m = 3; m < 25; m++)	// sequence through Ds
				if (v[m] > v[2])		// D > C
				{
					int E = 60 - v[0] - v[1] - v[2] - v[m];
					if (E <= v[1] || E > 24) continue;	// E > B
					swap(v[3], v[m]);
					for (int n = 4; n < 25; n++)
					if (v[n] == E)
					{
						swap(v[4], v[n]);
						if (v[0] == 12) count += do_X(v);
						else count += 2 * do_X(v);
						swap(v[4], v[n]);
					}
					swap(v[3], v[m]);
				}
				swap(v[2], v[k]);
			}
			swap(v[1], v[j]);
		}
		swap(v[0], v[i]);
	}
	return count;
}

int do_X(int v[])
{
	int count = 0;
	for (int i = 5; i < 25; i++)	// sequence through Fs
	if (v[i] > v[1])		// F > B
	{
		swap(v[5], v[i]);
		for (int j = 6; j < 25; j++)	// sequence through Gs
		if (v[j] > v[5])		// G > F
		{
			swap(v[6], v[j]);
			for (int k = 7; k < 25; k++)	// sequence through Hs
			if (v[k] > v[1])		// H > B
			{
				int I = 60 - v[0] - v[5] - v[6] - v[k];
				if (I <= v[1] || I > 24) continue;	// I > B
				swap(v[7], v[k]);
				for (int m = 8; m < 25; m++)
				if (v[m] == I)
				{
					swap(v[8], v[m]);
					count++;
					swap(v[8], v[m]);
				}
				swap(v[7], v[k]);
			}
			swap(v[6], v[j]);
		}
		swap(v[5], v[i]);
	}
	return count;
}
