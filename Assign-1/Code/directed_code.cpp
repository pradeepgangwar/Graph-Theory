#include <bits/stdc++.h>
using namespace std;

int n, c_time=0;

vector <unsigned long long> encode(int a[1000][1000], int n)
{
    vector <unsigned long long> condensed;
    for (int i=0; i<n; i++)
    {
        int power = 0;
        unsigned long long number = 0;
        for (int j=0; j<n; j++)
        {
            c_time += 4;
            number = number + a[i][j]*pow(2, power);
            if (power == 64)
            {
                c_time += 1;
                condensed.push_back(number);
                number = 0;
                power = 0;
            }
            c_time += 1;
            power++;
        }
        c_time += 1;
        condensed.push_back(number);
    }
    return condensed;
}

void decode(vector <unsigned long long> encoded, int decoded[1000][1000], int numbers_per_row, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int k=0; k<numbers_per_row; k++)
        {
            unsigned long long number = encoded[i*numbers_per_row + k];
            for(int j=0; j<n; j++)    
            {
                decoded[i][j]=number%2;
                number = number/2;
            }
        }
    }
}

int main()
{
    FILE *direc_test, *direc_output, *direc_encode, *direc_data;
	direc_test = fopen("directed_test.txt", "r");
    direc_output = fopen("directed_output.txt", "w");
    direc_encode = fopen("directed_encoded.txt", "w");
	direc_data = fopen("direc_data.txt", "w");

    fprintf(direc_data,"# X Y\n");

    // testigng for directed graph
    for (int n=3; n<=80; n++)
    {
        vector <unsigned long long> encoded;
        encoded.clear();
        int a[1000][1000];
        for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				fscanf(direc_test, "%d", &a[i][j]);
			}
		}

        encoded = encode(a,n);
        fprintf(direc_encode, "%d\n",n);
        for (int i=0; i<encoded.size(); i++)
        {
            fprintf(direc_encode, "%llu ",encoded[i]);
        }
        fprintf(direc_encode, "\n");

        int numbers_per_row;
        if (n%64 == 0)  
            numbers_per_row = n/64;
        else
            numbers_per_row = n/64 + 1;

        int decoded[1000][1000];

        decode(encoded, decoded, numbers_per_row, n);

        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                fprintf(direc_output, "%d ",decoded[i][j]);
            }
            fprintf(direc_output, "\n");
        }
        fprintf(direc_data, "%d %d\n",n,c_time);
    }
}