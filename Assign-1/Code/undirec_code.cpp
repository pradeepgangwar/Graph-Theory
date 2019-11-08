#include <bits/stdc++.h>
using namespace std;

int n,c_time=0;

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
    FILE *undirec_test, *undirec_output, *undirec_encode, *undirec_data;
	undirec_test = fopen("undirected_test.txt", "r");
    undirec_output = fopen("undirected_output.txt", "w");
    undirec_encode = fopen("undirected_encoded.txt", "w");
	undirec_data = fopen("undirec_data.txt", "w");

    fprintf(undirec_data,"# X Y\n");

    // testigng for directed graph
    for (int n=3; n<=80; n++)
    {
        vector <unsigned long long> encoded;
        int a[1000][1000];
        for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				fscanf(undirec_test, "%d", &a[i][j]);
			}
		}

        encoded = encode(a,n);
        fprintf(undirec_encode, "%d\n",n);
        for (int i=0; i<encoded.size(); i++)
        {
            fprintf(undirec_encode, "%llu ",encoded[i]);
        }
        fprintf(undirec_encode, "\n");

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
                fprintf(undirec_output, "%d ",decoded[i][j]);
            }
            fprintf(undirec_output, "\n");
        }
        fprintf(undirec_data, "%d %d\n",n,c_time);
    }

}