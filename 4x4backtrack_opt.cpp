//Find 4x4 Magic Squares using BackTracking.
//Swap partitions of 34 into place according to a fast ordering.
//We use the fact that the corners sum to 34 to fill in the bottom left corner.
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//Order of checks
int do_row1(int v[]);
int do_diag1(int v[]);
int do_col2(int v[]);
int do_col3(int v[]);
int do_row2(int v[]);
int do_col1(int v[]);

/*Ordering of  magic square by array indices
0  1  2  3
12 4  10 13
14 8  5  15
7  9  11 6
*/

//Ouput a magic square
ostream& operator<<(ostream& out, int v[])
{
	out << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3]  << endl
		<< v[12]<< ' ' << v[4] << ' ' << v[10] << ' ' << v[13] << endl
		<< v[14]<< ' ' << v[8] << ' ' << v[5] << ' ' << v[15] << endl
		<< v[7]<< ' ' << v[9] << ' ' << v[11]<< ' ' << v[6]  << endl << endl;
	return out;
}

int main()
{
	int v[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
   
	time_t begin_time = clock(), end_time;
	int count = do_row1(v);
	end_time = clock();

	cout << count << " squares\n";
	cout << "Time: " << int(end_time - begin_time) << endl;

	// system("pause");
	return 0;
}

int do_row1(int v[])
{
	int count = 0;
	//Generate quadruples of indices from {0..15}
	for(int h = 0; h <= 12; h++)
	for(int i = h + 1; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
		if(v[h] + v[i] + v[j] + v[k] == 34) //Check if the corresponding triple of values sums correctly.
		{
			//Swap the values into v[0..3]
			swap(v[0], v[h]); swap(v[1], v[i]); swap(v[2], v[j]); swap(v[3], v[k]);   
			do count += do_diag1(v);							//Finish the square
			while(next_permutation(v, v + 4));						//Scramblings of v[0..3]
			swap(v[3], v[k]); swap(v[2], v[j]); swap(v[1], v[i]); swap(v[0], v[h]);		//Unswap
		}
	return count;
}

//The function do_diag1 counts the number of ways to finish with the numbers in v[4..15].
int do_diag1(int v[])  //The main diagonal has a 1 in the upper left.
{
	int count = 0;
	//Generate triples of indices from {4..15}
	for(int i = 4; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
		if(v[0] + v[i] + v[j] + v[k] == 34) //Check if the corresponding triple of values sums correctly.
		{
			swap(v[4], v[i]); swap(v[5], v[j]); swap(v[6], v[k]);		//Swap the values into v[4..6]
			for(int p = 1; p <= 6; p++, next_permutation(v + 4, v + 7))	//Generate all 3! orderings of v[4..6]
				if (v[1] + v[2] > v[6])
					count += do_col2(v);
			swap(v[6], v[k]); swap(v[5], v[j]); swap(v[4], v[i]);		//Unswap
		}
	return count;
}

//The function do_col2 counts the number of ways to finish with v[7..15]
int do_col2(int v[])	//Columns 2 already has v[1] & v[4]
{
	int count = 0;
	int s = 34 - v[0] - v[3] - v[6];
	if(s > 16 || s < 1) return 0;			//Too high already or too low
	for(int h = 7; h <= 15; h++)			//Look for the element we need in the bottom left corner
		if(v[h] == s)
		{
			swap(v[7], v[h]);		//Swap into bottom left corner
			for(int i = 8; i <= 14; i++)
			for(int j = i + 1; j <= 15; j++)
				if(v[1] + v[4] + v[i] + v[j] == 34)			//Check if column 2 sums correctly
				{
					//Swap values into v[8] & v[9] and try both ways
					swap(v[8], v[i]);					swap(v[9], v[j]);
					count += do_col3(v);					swap(v[8], v[9]);
					count += do_col3(v);					swap(v[8], v[9]);
					swap(v[9], v[j]);					swap(v[8], v[i]);	//Unswap
				}
			swap(v[7], v[h]);		//Unswap
			break;
		}
	return count;
}

//The function do_col3 counts the number of ways to finish with v[10..15]
int do_col3(int v[])	//Column 3 already has v[2] & v[5]
{
	int count = 0;
	int s = 34 - v[3] - v[8] - v[7];			//Number needed for v[10] so diagonal 2 sums correctly
	for(int i = 10; i <= 15; i++)
	{
		if(v[i] != s) continue;

		s = 34 - v[7] - v[9] - v[6];			//Number needed for v[11] so row 4 sums correctly
		if(s > 16 || s < 1) return 0;
		if(s != 34 - v[2] - v[i] - v[5]) break;		//Check if column 3 will sum correctly (maybe not necessary?)
		swap(v[10], v[i]);				//Swap into place
		for(int j = 11; j <= 15; j++)
			if(v[j] == s)
			{
				swap(v[11], v[j]);		//Swap into place
				count += do_row2(v);
				swap(v[11], v[j]);		//Unswap
			}

		swap(v[10], v[i]);				//Unswap
	}
	return count;
}

//The function do_row2 counts the number of ways to finish with v[12..15]
int do_row2(int v[])	//Row 2 already has v[4] and v[10]
{
	int count = 0;
	//Generate pairs of indices from {12..14}
	for(int i = 12; i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(v[4] + v[10] + v[i] + v[j] == 34)
		{
			swap(v[12], v[i]);		swap(v[13],v[j]);
			count += do_col1(v);		swap(v[12],v[13]);	
			count += do_col1(v);		swap(v[12],v[13]);	//Back to beginning of cycle
			swap(v[13], v[j]);		swap(v[12], v[i]);	//Unswap
		}
	return count;
}

//The function do_col1 decides if possible to complete a magic square with the last 2 numbers
int do_col1(int v[])
{
	//Try both v[14] and v[15] in the first column
	if(v[0] + v[12] + v[14] + v[7] == 34 || v[0] + v[12] + v[15] + v[7] == 34)
		return 1;
	return 0;
}
