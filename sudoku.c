#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include <stdbool.h>


#define n (9)
int n_sqrt=sqrt(n);

void vider_grille(int** grille)
{
	srand(time(NULL));
	int k=0;
	while (k<2)
	{
		int l = rand()%n;
		int c = rand()%n;
		if (grille[l][c] != 0)
		{
			grille[l][c] = 0;
			k=k+1;
		}
	}
}

bool verifier_chiffre(int** grille, int nombre,int i,int j,int ligne_depart, int colonne_depart)
{
	//fonction qui vérifie si on a le droit de mettre un nombre dans la case (i*n_sqrt+l,n-i*sqrt-c)
	for (int k=0;k<n;k+=1)
	{
		if (grille[i][k]==nombre && k!=j) 
		{
			return false;
		}
		if (grille[k][j]==nombre && k!=i)
		{
			return false;
		}
	}
	for (int k1=0;k1<n_sqrt;k1+=1)
	{
		for (int k2=0;k2<n_sqrt;k2+=1)
		{
			if (ligne_depart+k1 != i && colonne_depart+k2 != colonne_depart && grille[ligne_depart+k1][colonne_depart+k2]==nombre)
			{
				return false;
			}
		}
	}
	return true;
}

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

bool fillRemaining(int ** grille,int i, int j)
{
    //  System.out.println(i+" "+j);
    if (j>=n && i<n-1)
    {
        i = i + 1;
        j = 0;
    }
    if (i>=n && j>=n)
        {
        	return true;
        }
 
    if (i < n_sqrt)
    {
        if (j < n_sqrt)
            {
            	j = n_sqrt;
    		}
    }
    else if (i < n-n_sqrt)
    {
        if (j==(int)(i/n_sqrt)*n_sqrt)
            {
            	j =  j + n_sqrt;
    		}
    }
    else
    {
        if (j == n-n_sqrt)
        {
            i = i + 1;
            j = 0;
            if (i>=n)
                {
                	return true;
        		}
        }
    }

    for (int num = 1; num<=n; num++)
    {
        if (verifier_chiffre(grille,num,i, j,i-i%n_sqrt,j-j%n_sqrt))
        {
            grille[i][j] = num;
            if (fillRemaining(grille,i,j+1))
                {
                return true;
                }
            grille[i][j] = 0;
        }
    }
    return false;
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





int remplie(int** grille)
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (grille[i][j]==0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int comparer_grille (int** grille_a_remplir,int** grille_vraie)
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (grille_a_remplir[i][j]!=grille_vraie[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

void reussi(int** grille_a_remplir, int** grille_vraie)
{
	int l;
	int c;
	int nb;
	
	if (comparer_grille(grille_a_remplir,grille_vraie)==1)
	{
		printf("Bravo. Sudoku réussi \n");
		print_grille(grille_a_remplir);
	}
	
	else
	{
		printf("Sudoku faux. Donnez la ligne, la colonne et le nombre du chiffre à changer \n");
		scanf(" %d",&l);
		scanf(" %d",&c);
		scanf(" %d",&nb);
		grille_a_remplir[l-1][c-1] = nb;
		reussi(grille_a_remplir,grille_vraie);
	}
}


int main ()
{
	int **grille_vraie=calloc(n,n*sizeof(int*));
	for (int i=0;i<n;i+=1)
	{
		grille_vraie[i]=calloc(n,n*sizeof(int));
	}
	remplir_diagonales(grille_vraie);
	fillRemaining(grille_vraie,0,3);
	int** grille_a_remplir = calloc(n,n*sizeof(int*));
	for (int i=0;i<n;i++)
	{
		grille_a_remplir[i]=calloc(n,n*sizeof(int));
	}
	for(int l=0;l<n;l++)
	{
		for (int c=0;c<n;c++)
		{
			grille_a_remplir[l][c] = grille_vraie[l][c];
		}
	}
	vider_grille(grille_a_remplir);


	int l;
	int c;
	int nb;
	
	while (remplie(grille_a_remplir)==0)
	{
		printf("\n");
		print_grille(grille_a_remplir);
		printf("\n");
		printf("Donnez la ligne, la colonne et le nombre à ajouter \n");
		scanf(" %d",&l);
		scanf(" %d",&c);
		scanf(" %d",&nb);
		if (grille_a_remplir[l-1][c-1] !=0)
		{
			printf("Impossible de changer cette case.\n");
		}
		else
		{
			grille_a_remplir[l-1][c-1] = nb;
		}
	}
	reussi(grille_a_remplir,grille_vraie);
	
	

}





