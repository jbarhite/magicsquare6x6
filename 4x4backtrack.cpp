//Find 4x4 Magic Squares using BackTracking.
//Swap partitions of 34 into place according to a fast ordering.
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//Order of checks
int do_row1(int v[]);
int do_diag1(int v[]);
int do_col2(int v[]);
int do_col3(int v[]);
int do_diag2(int v[]);	//Also handles last row
int do_row2(int v[]);
int do_col1(int v[]);

/*Ordering of  magic square by array indices
0  1  2  3
12 4  9  13
14 7  5  15
11 8  10 6
*/

//Ouput a magic square
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
	//Generate pairs of indices from {7..15}
	for(int i = 7; i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(v[1] + v[4] + v[i] + v[j] == 34)		//Check if column 2 sums correctly
		{
			//Swap values into v[7] & v[8] and try both ways
			swap(v[7], v[i]);					swap(v[8], v[j]);
			if (v[1] + v[8] > v[5]) count += do_col3(v);		swap(v[7],v[8]);	
			if (v[1] + v[8] > v[5]) count += do_col3(v);		swap(v[7], v[8]);	//Back to beginning of cycle?
			swap(v[8], v[j]);					swap(v[7], v[i]);	//Unswap
		}
	return count;
}
//The function do_col3 counts the number of ways to finish with v[9..15]
int do_col3(int v[])	//Column 3 already has v[2] & v[5]
{
	int count = 0;
	//Generate pairs of indices from {9..15}
	for(int i = 9; i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(v[2] + v[5] + v[i] + v[j] == 34)
		{
			//Swap values into v[9] & v[10] and try both ways
			swap(v[9], v[i]);		swap(v[10], v[j]);
			count += do_diag2(v);	swap(v[9],v[10]);	
			count += do_diag2(v);	swap(v[9],v[10]);	//Back to beginning of cycle?
			swap(v[10], v[j]);		swap(v[9], v[i]);	//Unswap
		}
	return count;
}
//The function do_diag2 counts the number of ways to finish with v[11..15].
//We tackle the last row while we are at it.
int do_diag2(int v[])		//The up diagonal already has v[3], v[9], & v[7]
{
	int s = v[3] + v[9] + v[7];				//Sum of 3 on diagonal
	if(s > 33 || s < 18) return 0;			//Too high already or too low
	if(s != v[8] + v[10] + v[6]) return 0;	//Sum of 3 on last row
	
	s = 34 - s;		//Re-using s as the number to be put in lower right
	for(int i = 11; i <= 15; i++)	//Looking for s among v[11..15]
		if(s == v[i])
		{
			swap(v[11], v[i]);
			int count = do_row2(v);
			swap(v[11], v[i]);
			return count;
		}
	return 0;
}
//The function do_row2 counts the number of ways to finish with v[12..15]
int do_row2(int v[])	//Row 2 already has v[4] and v[9]
{
	int count = 0;
	//Generate pairs of indices from {12..14}
	for(int i = 12; i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(v[4] + v[9] + v[i] + v[j] == 34) 
		{
			swap(v[12], v[i]);		swap(v[13],v[j]);
			count += do_col1(v);	swap(v[12],v[13]);	
			count += do_col1(v);	swap(v[12],v[13]);	//Back to beginning of cycle
			swap(v[13], v[j]);		swap(v[12], v[i]);	//Unswap
		}
	return count;
}
//The function do_col1 decides if possible to complete a magic square with the last 2 numbers
int do_col1(int v[])
{
	//Try both v[14] and v[15] in the first column
	if(v[0] + v[12] + v[14] + v[11] == 34 || v[0] + v[12] + v[15] + v[11] == 34)
		return 1;
	return 0;
}



