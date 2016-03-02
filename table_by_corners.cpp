//Find all 4x4 Magic Squares Using BackTracking
//Swap partitions of 34 into place
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <fstream>
#define STATS	//For generating statistics by partition and permutation
using namespace std;

//Order of checks
void do_corners(int a[]);
void do_diag(int a[]);
void do_row1(int a[]);
void do_col2(int a[]);
void do_col3(int a[]);	//and back diagonal and row 4
void do_row2(int a[]);
void do_col1(int a[]);

/*Ordering of  magic square by array indices
 0 6 7 1
12 4 10 13
14 8 5 15
2 9 11 3*/

//Ouput a magic square 
ostream& operator<<(ostream& out, int a[])
{
	out << setw(3) << a[0] << setw(3) << a[6] << setw(3) << a[7] << setw(3) << a[1]  << endl
		<< setw(3) << a[12]<< setw(3) << a[4] << setw(3) << a[10] << setw(3) << a[13] << endl
		<< setw(3) << a[14]<< setw(3) << a[8] << setw(3) << a[5] << setw(3) << a[15] << endl
		<< setw(3) << a[2]<< setw(3) << a[9] << setw(3) << a[11]<< setw(3) << a[3]  << endl << endl;
	return out;
}

int num_magic = 0;	//Global count of magic squares
ofstream fout("output.txt");

int main()
{
	time_t begin_time, end_time;
	int a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
   
	begin_time = clock();
	do_corners(a);
	end_time = clock();

	cout << "Num Magic: " << num_magic << "\nTime: " << int(end_time - begin_time) << "\n\n";

	system("pause");	return 0;
}
void do_corners(int a[])
{
	//Generate quads of indices from {0..15}
	for(int h = 0;     h <= 12; h++)
	for(int i = h + 1; i <= 13; i++)
	for(int j = i + 1; j <= 14; j++)
	for(int k = j + 1; k <= 15; k++)
	{
		if(a[h] + a[i] + a[j] + a[k] == 34) //Check if the corresponding quad of values sums correctly.
		{
			//Swap the values into a[0..3]
			swap(a[0], a[h]); swap(a[1], a[i]); swap(a[2], a[j]); swap(a[3], a[k]);
			#if defined(STATS) 
				fout << setw(3) << a[0] << setw(3) << a[1] << setw(3) << a[2] << setw(3) << a[3] << " | ";
				int row_sum = 0;
			#endif
			do	//Over all scramblings of a[0..3]
			{
				#if defined(STATS) 
					int before = num_magic;
				#endif
				do_diag(a);
				#if defined(STATS)
					row_sum += num_magic - before;
					fout << setw(3) << num_magic - before << ' ';
				#endif
			}while(next_permutation(a, a+4));
			#if defined(STATS)
				fout << " = " << setw(4) << row_sum << endl;
			#endif
			swap(a[3], a[k]); swap(a[2], a[j]); swap(a[1], a[i]); swap(a[0], a[h]);	//Unswap
		}
	}
}
//The function do_dia populates the main diagonal with numbers from a[4..15].
void do_diag(int a[])
{
	//Generate pairs of indices from {4..15}
	for(int i = 4;     i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(a[0] + a[i] + a[j] + a[3] == 34)
		{
			//Swap values into a[4] & a[5] and try both ways
			swap(a[4], a[i]);  swap(a[5], a[j]);
			do_row1(a);  swap(a[4], a[5]);  do_row1(a);  swap(a[4], a[5]);
			swap(a[5], a[j]);  swap(a[4], a[i]);  //Unswap
		}
}
//The function do_row1 populates row1 with numbers from a[6..15].
void do_row1(int a[])
{
	//Generate pairs of indices from {4..15}
	for(int i = 6;     i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(a[0] + a[i] + a[j] + a[1] == 34)
		{
			//Swap values into a[6] & a[7] and try both ways
			swap(a[6], a[i]);  swap(a[7], a[j]);
			do_col2(a);  swap(a[6], a[7]);  do_col2(a);  swap(a[6], a[7]);
			swap(a[7], a[j]);  swap(a[6], a[i]);  //Unswap
		}
}
	
//The function do_col2 populates column2 with numbers from a[8..15]
void do_col2(int a[])
{
	//Generate pairs of indices from {8..15}
	for(int i = 8;     i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(a[6] + a[4] + a[i] + a[j] == 34)
		{
			//Swap values into a[8] & a[9] and try both ways
			swap(a[8], a[i]);  swap(a[9], a[j]);
			do_col3(a);  swap(a[8], a[9]);  do_col3(a);  swap(a[8], a[9]);
			swap(a[9], a[j]);  swap(a[8], a[i]);  //Unswap
		}
}
//The function do_col3 populates column3 with numbers from a[10..15]
//Also do back diagonal and row 4
void do_col3(int a[])
{
	//Generate pairs of indices from {10..15}
	for(int i = 10;     i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(a[7] + a[i] + a[5] + a[j] == 34)
		{
			//Swap values into a[10] & a[11] and try both ways
			swap(a[10], a[i]);  swap(a[11], a[j]);
			if(a[1] + a[10] + a[8] + a[2] == 34 && a[2] + a[9] + a[11] + a[3] == 34) do_row2(a);
			swap(a[10],a[11]);
			if(a[1] + a[10] + a[8] + a[2] == 34 && a[2] + a[9] + a[11] + a[3] == 34) do_row2(a);
			swap(a[10],a[11]);
			swap(a[11], a[j]);  swap(a[10], a[i]);  //Unswap
		}
}

//The function do_row2 populates row2 from numbers in a[12..15]
void do_row2(int a[])
{
	//Generate pairs of indices from {12..14}
	for(int i = 12;    i <= 14; i++)
	for(int j = i + 1; j <= 15; j++)
		if(a[i] + a[4] + a[10] + a[j] == 34) 
		{
			swap(a[12], a[i]);  swap(a[13],a[j]);
			do_col1(a);  swap(a[12],a[13]);  do_col1(a);  swap(a[12],a[13]);
			swap(a[13], a[j]);  swap(a[12],a[i]);  //Unswap
		}
}
//The function do_col1 tries both a[14] and a[15] in the first column to complete
void do_col1(int a[])
{
	if(a[0] + a[12] + a[14] + a[2] == 34 || a[0] + a[12] + a[15] + a[2] == 34)
		num_magic++;
}

