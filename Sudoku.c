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

void vider_carreau( int** grille, int i,int j)
{
	for (int l=0;l<n_sqrt;l+=1)
	{
		for (int c=0;c<n_sqrt;c+=1)
		{
			grille[i+l][j+c]=0;
		}
	}
}

int verifier_chiffre(int** grille, int nombre,int i,int j)
{
	//fonction qui vérifie si on a le droit de mettre un nombre dans la case (i*n_sqrt+l,n-i*sqrt-c)
	int test=1;
	for (int k=0;k<n;k+=1)
	{
		if (grille[i][k]==nombre || grille[k][j]==nombre)
		{
			test=0;
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
				int l=rand()%n_sqrt;
				int c=rand()%n_sqrt;
				if (grille[i*n_sqrt+l][c+i*n_sqrt]==0)
				{
					grille[i*n_sqrt+l][c+i*n_sqrt]=j;
					j+=1;
				}
			}
		}
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
			int j=1;
			int compteur=0;
			while(j<=n)
			{
				int l=rand()%n_sqrt+1;
				int c=rand()%n_sqrt+1;
				int verification=verifier_chiffre(grille,j,i*n_sqrt+l-1,n-(c+i*n_sqrt));
				if (grille[i*n_sqrt+l-1][n-(c+i*n_sqrt)]==0 && verification==1)
				{
					grille[i*n_sqrt+l-1][n-(c+i*n_sqrt)]=j;
					j+=1;
				}
				compteur+=1;
				if (compteur==100)
				{
					vider_carreau(grille,i*n_sqrt,n-3-i*n_sqrt);
					print_grille(grille);
					printf("J'ai vidé le carreau antidiagonal\n");
					compteur=0;
					j=1;
				}
			}
		}
}

void finir_remplir_grille(int** grille)
{
	
	//remplir le carreau en haut au milieu
	int j=1;
	int compteur=0;
	while(j<=n)
	{
		int l=rand()%n_sqrt+1;
		int c=rand()%n_sqrt+1;
		int verification=verifier_chiffre(grille,j,l-1,2+c);
		if (grille[l-1][2+c]==0 && verification==1)
		{
			grille[l-1][2+c]=j;
			j+=1;
		}
//		printf("compteur=%d\n",compteur);
		compteur+=1;
		if (compteur==100)
		{
			print_grille(grille);
			vider_carreau(grille,0,3);
			printf("J'ai vidé le carreau\n");
			compteur=0;
			j=1;
		}
	}
	//remplir le carreau au milieu à gauche
	j=1;
	compteur=0;
	while(j<=n)
	{
		int l=rand()%n_sqrt+1;
		int c=rand()%n_sqrt+1;
		int verification=verifier_chiffre(grille,j,2+l,c-1);
		if (grille[2+l][c-1]==0 && verification==1)
		{
			grille[2+l][c-1]=j;
			j+=1;
		}
		printf("compteur2=%d\n",compteur);
		compteur+=1;
		if (compteur==100)
		{
			vider_carreau(grille,3,0);
			compteur=0;
			j=1;
		}
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
	remplir_anti_diagonale(grille_test);
	printf("%d\n",8);
	finir_remplir_grille(grille_test);
	print_grille(grille_test);
}
