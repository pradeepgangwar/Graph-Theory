#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<stddef.h>

int main()
{
   	FILE *fptr, *fptr1;
   	srand(time(NULL));
   	fptr = fopen("undirected_test.txt", "w");
    fptr1 = fopen("directed_test.txt", "w");

   	if(fptr == NULL)
   	{
      	printf("Error!");
      	exit(1);
   	}
    if(fptr1 == NULL)
   	{
      	printf("Error!");
      	exit(1);
   	}
    int n;

   	int i, j, a[1000][1000];

    // Undirected graph
    for (n=3; n<=80; n++)
    {
        for(i=0;i<n;i++)
        {
            for(j=i;j<n;j++)
            {			
                if (i == j)
                {
                    a[i][j] = 0;
                    continue;
                }
                a[i][j] = rand()%2;
                a[j][i] = a[i][j];
            }   
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {				
                fprintf(fptr,"%d ",a[i][j]);
            }
            fprintf(fptr, "\n");
        }
    }
    fclose(fptr);

    // Directed graph
    for (n=3; n<=80; n++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {	
                if (i == j)
                {
                    a[i][j] = 0;
                    continue;
                }		
                a[i][j] = rand()%2;
            }   
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {				
                fprintf(fptr1,"%d ",a[i][j]);
            }
            fprintf(fptr1, "\n");
        }
    }
    fclose(fptr1);    
    
   	return 0;
}
