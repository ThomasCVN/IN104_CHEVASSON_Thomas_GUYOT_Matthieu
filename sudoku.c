#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//bonjour

#define n (9)

int m = sqrt(n);

	

void remplir_diago (int **grille)
{
	for (int i = 1; i<m; i+=m+1)
	{
		int j = 1;
		while (j<=9)
		{
			srand(time(NULL));
			int k = rand()%m+1;
			printf("%d",grille[i][k]);
			if (grille[i][k]==0)
			{
				grille[i][k] = j;
				j = j+1;
			}
		}
	}
}


void print_grille (int **grille)
{
	int m = sqrt(n);
	for (int i=1; i<m; i++)
	{
		for (int j=1; j<m; j++)
		{
			printf("%d ",grille[i][j]);
		}
		printf("\n");
	}
}
	
			


int main()
{
	int grille[n][n] = calloc(sizeof(int)*n);
	remplir_diago(grille);
	print_grille(grille,n);
}









