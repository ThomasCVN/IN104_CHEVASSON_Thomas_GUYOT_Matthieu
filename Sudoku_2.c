/*Matthieu Guyot*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n (9)
int n_sqrt=sqrt(n);


void print_grille (int** grille)
{
	for (int i=0;i<n;i+=1)
	{
		for (int j=0;j<n;j+=1)
		{
			printf("%d ",grille[i][j]);
		}
		printf("\n");
	}
}

int verifier_chiffre(int** grille, int nombre,int i,int l,int c)
{
	//fonction qui vérifie si on a le droit de mettre un nombre dans la case (i*n_sqrt+l,n-i*sqrt-c)
	int test=1;
	for (int k=0;k<n;k+=1)
	{
		if (grille[i*n_sqrt+l][k]==nombre || grille[k][n-(i*n_sqrt+c)-1]==nombre)
		{
			test=0;
		}
	}
	for (int k1=0;k1<n_sqrt;k1+=1)
	{
		for (int k2=0;k2<n_sqrt;k2+=1)
		{
			if (k1!=l && k2!=c)
			{
				if (grille[i*n_sqrt+k1][n-(i*n_sqrt+k2)-1]==nombre && k1!=l)
				{
					test=0;
				}
			}
		}
	}
	return test;
}

void remplir_diagonales(int** grille)
{
	srand(time(NULL));
	for (int i=0; i<n_sqrt;i+=1)
		{
			int j=1;
			while(j<=n)
			{
				int l=rand()%n_sqrt+1;
				int c=rand()%n_sqrt+1;
				if (grille[i*n_sqrt+l-1][c+i*n_sqrt-1]==0)
				{
					grille[i*n_sqrt+l-1][c+i*n_sqrt-1]=j;
					j+=1;
				}
			}
		}
	print_grille(grille);
}





void remplir_anti_diagonale(int ** grille)
{
	srand(time(NULL));
	for (int i=0; i<n_sqrt;i+=1)
		{
			if (n_sqrt%2==1 && i==(n_sqrt+1)/2-1)
			{
				i+=1;
			}
			printf("i=%d\n",i);
			for (int l=0;l<3;l+=1)
			{
				for (int c=0;c<3;c+=1)
				{
					while(grille[i*n_sqrt+l][n-(c+i*n_sqrt)]==0)
					{
						srand(time(NULL));
						int j=rand()%9+1;
						int verification=verifier_chiffre(grille,j,i,l,c);
						printf("verif=%d, l=%d,c=%d\n",verification,l,c);
						if (grille[i*n_sqrt+l][n-(c+i*n_sqrt)-1]==0 && verification==1)
						{
							grille[i*n_sqrt+l][n-(c+i*n_sqrt)-1]=j;
						}
					}
				}
			}
				print_grille(grille);
				printf("\n");
		}
}


int main ()
{
	int **grille_test=calloc(n,n*sizeof(int*));
	for (int i=0;i<n;i+=1)
	{
		grille_test[i]=calloc(n,n*sizeof(int));
	}
	remplir_diagonales(grille_test);
	printf("%d\n",8);
	remplir_anti_diagonale(grille_test);
	print_grille(grille_test);
}
