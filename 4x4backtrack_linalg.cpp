//Find 4x4 Magic Squares with 1 in the upper left using BackTracking and linear algebra.
//Swap partitions of 34 into place according to a fast ordering.
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//Order of checks
int do_row1(int v[]);
int do_col1(int v[]);
int do_row2(int v[]);
int do_rest(int v[]);

/*Ordering of  magic square by array indices
0  1  2  3
4  7  8  9
5  10 11 12
6  13 14 15
*/

//Ouput a magic square
ostream& operator<<(ostream& out, int v[])
{
	out << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3]  << endl
		<< v[4]<< ' ' << v[7] << ' ' << v[8] << ' ' << v[9] << endl
		<< v[5]<< ' ' << v[10] << ' ' << v[11] << ' ' << v[12] << endl
		<< v[6]<< ' ' << v[13] << ' ' << v[14]<< ' ' << v[15]  << endl << endl;
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
	//Generate triples of indices from {1..15}
	for(int i = 1; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
		if(v[i] + v[j] + v[k] == 33) //Check if the corresponding triple of values sums correctly.
		{
			//Swap the values into v[0..3]
			swap(v[1], v[i]); swap(v[2], v[j]); swap(v[3], v[k]);   
			do count += do_col1(v);							//Finish the square
			while(next_permutation(v + 1, v + 4));					//Scramblings of v[0..3]
			swap(v[3], v[k]); swap(v[2], v[j]); swap(v[1], v[i]);			//Unswap
		}
	return count;
}

//The function do_col1 counts the number of ways to finish with the numbers in v[4..15].
int do_col1(int v[])  //The first column has a 1 at the top.
{
	int count = 0;
	//Generate triples of indices from {4..15}
	for(int i = 4; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
		if(v[i] + v[j] + v[k] == 33) //Check if the corresponding triple of values sums correctly.
		{
			swap(v[4], v[i]); swap(v[5], v[j]); swap(v[6], v[k]);		//Swap the values into v[4..6]
			for(int p = 1; p <= 6; p++, next_permutation(v + 4, v + 7))	//Generate all 3! orderings of v[4..6]
				count += do_row2(v);
			swap(v[6], v[k]); swap(v[5], v[j]); swap(v[4], v[i]);		//Unswap
		}
	return count;
}

//The function do_row2 counts the number of ways to finish with v[7..15]
int do_row2(int v[])	//Columns 2 already has v[1] & v[4]
{
	int count = 0;
	//Generate triples of indices from {7..15}
	for(int i = 7; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
		if(v[4] + v[i] + v[j] + v[k] == 34) //Check if the corresponding triple of values sums correctly.
		{
			swap(v[7], v[i]); swap(v[8], v[j]); swap(v[9], v[k]);		//Swap the values into v[7..9]
			for(int p = 1; p <= 6; p++, next_permutation(v + 7, v + 10))	//Generate all 3! orderings of v[7..9]
				count += do_rest(v);
			swap(v[9], v[k]); swap(v[8], v[j]); swap(v[7], v[i]);		//Unswap
		}
	return count;
}

int do_rest(int v[])
{

	bool w[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
	for (int i=0; i<10; i++) w[v[i] - 1] = true;

	int s = v[0] - v[3] + v[4] - v[8] + v[5];				//Check that value at index 10 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;
	s = 68 - 2 * v[0] - v[1] - v[2] - v[4] - v[7] - v[5];			//Check that value at index 11 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;
	s = v[7] + v[8] - v[5];							//Check that value at index 12 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;
	s = 68 - 2 * v[0] - 2 * v[1] - v[2] - v[4] - v[7] + v[8] - v[5];	//Check that value at index 13 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;
	s = -34 + 2 * v[0] + v[1] + v[4] + v[7] - v[8] + v[5];			//Check that value at index 14 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;
	s = -v[3] + v[4] + v[5];						//Check that value at index 15 is valid
	if (s < 1 || s > 16 || w[s - 1]) return 0;
	w[s - 1] = true;

	return 1;
}
