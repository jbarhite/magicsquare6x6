// Find 5x5 MSQ using backtracking
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//Order of checks
int do_diag(int v[]);
int do_X(int v[]);
int start_buckle1(int v[]);
int finish_buckle1(int v[]);
int do_buckle2(int v[]);
int do_rest(int v[]);

/*Ordering of magic square by array indices
1  9  11 10 5		B . . . .	B . . . F	. J L K .	. . . . .	B J L K F
21 2  19 7  23		. C . . .	. C . H .	. . . . .	V . T . X	V C T H X
17 13 0  15 18		. . A . .	. . A . .	. N . P .	R . . . S	R N A P S
22 8  20 3  24		. . . D .	. I . D .	. . . . .	W . U . Y	W I U D Y
6  12 16 14 4		. . . . E	G . . . E	. M Q O .	. . . . .	G M Q O E
			(diagonal)	   (X)		(buckle 1)	(buckle 2)	  (all)
*/

// Ouput a magic square
/*ostream& operator<<(ostream& out, int v[])
{
	out << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3]  << endl
		<< v[12]<< ' ' << v[4] << ' ' << v[9] << ' ' << v[13] << endl
		<< v[14]<< ' ' << v[7] << ' ' << v[5] << ' ' << v[15] << endl
		<< v[11]<< ' ' << v[8] << ' ' << v[10]<< ' ' << v[6]  << endl << endl;
	return out;
}*/

int main()
{
	int v[25] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
   
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
					count += start_buckle1(v);
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

int start_buckle1(int v[])
{
	int count = 0;
	for (int i = 9; i < 25; i++) // sequence through Js
	{
		swap(v[9], v[i]);
		for (int j = 10; j < 25; j++)		// sequence through K,L pairs
		for (int k = j + 1; k < 25; k++)
		if (v[j] + v[k] == 60 - v[1] - v[5] - v[9])	// K + L = 60 - B - F - J
		{
			swap(v[10], v[j]); swap(v[11], v[k]);
			for (int m = 12; m < 25; m++)		// sequence through M,N pairs
			for (int n = m + 1; n < 25; n++)
			if (v[m] + v[n] == 60 - v[2] - v[8] - v[9])	// M + N = 60 - C - I - J
			{
				swap(v[12], v[m]); swap(v[13], v[n]);
				count += finish_buckle1(v);		// try all four arrangments of K,L and M,N
				swap(v[12], v[13]);
				count += finish_buckle1(v);
				swap(v[10], v[11]);
				count += finish_buckle1(v);
				swap(v[12], v[13]);
				count += finish_buckle1(v);
				swap(v[10], v[11]);
				swap(v[13], v[n]); swap(v[12], v[m]);
			}
			swap(v[11], v[k]); swap(v[10], v[j]);
		}
		swap(v[9], v[i]);
	}
	return count;
}

int finish_buckle1(int v[])
{
	int count = 0;
	for (int i = 14; i < 24; i++)	// sequence through Os
	for (int j = i + 1; j < 25; j++) // sequence through Ps
	if (v[i] + v[j] == 60 - v[10] - v[7] - v[3])	// O + P = 60 - K - H - D
	{
		swap(v[14], v[i]); swap(v[15], v[j]);
		for (int perm = 0; perm < 2; perm++)
		{
			for (int k = 16; k < 25; k++)	// sequence through Qs
			if (v[14] + v[k] == 60 - v[12] - v[4] - v[6])	// O + Q = 60 - M - E - G
			{
				swap(v[16], v[k]);
				count += do_buckle2(v);
				swap(v[16], v[k]);
			}
			swap(v[14], v[15]);
		}
		swap(v[15], v[j]); swap(v[14], v[i]);
	}
	return count;
}

int do_buckle2(int v[])
{
	int count = 0;
	for (int i = 17; i < 25; i++)	// sequence through Rs
	for (int j = i + 1; j < 25; j++)	// sequence through Ss
	if (v[i] + v[j] == 60 - v[0] - v[13] - v[15])	// R + S = 60 - A - N - P
	{
		swap(v[17], v[i]); swap(v[18], v[j]);
		for (int k = 19; k < 25; k++)	// sequence through Ts
		for (int m = k + 1; m < 25; m++)	// sequence through Us
		if (v[k] + v[m] == 60 - v[0] - v[11] - v[16])	// T + U = 60 - A - L - Q
		{
			swap(v[19], v[k]); swap(v[20], v[m]);
			count += do_rest(v);
			swap(v[19], v[20]);
			count += do_rest(v);
			swap(v[17], v[18]);
			count += do_rest(v);
			swap(v[19], v[20]);
			count += do_rest(v);
			swap(v[17], v[18]);
			swap(v[20], v[m]); swap(v[19], v[k]);
		}
		swap(v[18], v[j]); swap(v[17], v[i]);
	}
	return count;
}

int do_rest(int v[])
{
	int count = 0;
	for (int i = 21; i < 24; i++)	// sequence through Vs
		for (int j = i + 1; j < 25; j++)	// sequence through Ws
		if (v[i] + v[j] + v[1] + v[6] + v[17] == 60 && i != j)	// check that first column sums correctly
		{
			swap(v[21], v[i]); swap(v[22], v[j]);
			for (int perm = 0; perm < 2; perm++)
			{
				if (v[23] + v[24] + v[5] + v[18] + v[4] == 60)	// check that last column sums correctly
				if (	v[23] + v[21] + v[2] + v[19] + v[7] == 60 ||
					v[24] + v[21] + v[2] + v[19] + v[7] == 60) count++;
				swap(v[21], v[22]);
			}
			swap(v[22], v[j]); swap(v[21], v[i]);
		}	
	return count;
}

// attempting to implement the last stages of Schroeppel's algorithm
// see Beeler's report for explanation
/*
int check_X(int v[])
{
	int X = 60 - v[2] - v[7] - v[19] - v[21]; // X = 60 - C - H - T - V
	if (v[23] == X || v[24] == X) return 1;
	return 0;
}

int check_Y(int v[])
{
	int Y = 60 - v[3] - v[8] - v[20] - v[22]; // X = 60 - D - I - U - W
	if (v[23] == Y || v[24] == Y) return 1;
	return 0;
}

int check_V(int v[])
{
	int Y = 60 - v[3] - v[8] - v[20] - v[22]; // X = 60 - D - I - U - W
	if (v[23] == Y || v[24] == Y) return 1;
	return 0;
}

int do_buckle2(int v[])
{
	int count = 0;
	for (int i = 17; i < 25; i++)	// sequence through Rs
	for (int j = i + 1; j < 25; j++)	// sequence through Ss
	if (v[i] + v[j] == 60 - v[0] - v[13] - v[16])	// R + S = 60 - A - N - P
	{
		swap(v[17], v[i]); swap(v[18], v[j]);
		for (int k = 19; k < 25; k++)	// sequence through Ts
		for (int m = k + 1; m < 25; m++)	// sequence through Us
		if (v[k] + v[m] == 60 - v[0] - v[11] - v[16])	// T + U = 60 - A - L - Q
		{
			swap(v[19], v[k]); swap(v[20], v[m]);
			for (int n = 21; n < 25; n++)	// sequence through Vs
			for (int p = n + 1; p < 25; p++)	// sequence through Ws
			if (v[n] + v[p] == 60 - v[1] - v[6] - v[17])	// V + W = 60 - B - G - R
			{
				swap(v[21], v[n]); swap(v[22], v[p]);
				// put min of R,S first, etc.
				bool swapRS = v[18] < v[17], swapTU = v[20] < v[19], swapVW = v[22] < v[21];
				//if (swapRS) swap(v[17], v[18]); if (swapTU) swap(v[19], v[20]); if (swapVW) swap(v[21], v[22]);

				count += check_X(v);
				swap(v[19], v[20]); swap(v[21], v[22]);
				count += check_Y(v);
				swap(v[19], v[20]);
				count += check_X(v);
				swap(v[19], v[20]); swap(v[21], v[22]);
				count += check_Y(v);
				swap(v[17], v[18]); swap(v[19], v[20]);
				//count += check_V(v);
				swap(v[19], v[20]); swap(v[21], v[22]);
				//count += check_W(v);
				swap(v[19], v[20]);
				//count += check_V(v);
				swap(v[19], v[20]); swap(v[21], v[22]);
				//count += check_W(v);
				swap(v[17], v[18]); swap(v[19], v[20]);

				//if (swapRS) swap(v[17], v[18]); if (swapTU) swap(v[19], v[20]); if (swapVW) swap(v[21], v[22]);
				swap(v[22], v[p]); swap(v[21], v[n]);
			}
			swap(v[20], v[m]); swap(v[19], v[k]);
		}
		swap(v[18], v[j]); swap(v[17], v[i]);
	}
	return count;
}
*/
