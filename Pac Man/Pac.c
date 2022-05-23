/*Thomas Chevasson et Matthieu Guyot*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define H (30)
#define W (60)
#define NR_GHOSTS (5)

struct coordinates
{
	int x;
	int y;
};

struct PacMan
{
	struct coordinates* coordonnees;
	int nx;
	int ny;
	int lives;
	int food;
};

struct Ghost
{
	struct coordinates* coordonnees;
	int nx;
	int ny;
};

struct Ghost** allGhosts[NR_GHOSTS];

struct coordinates depart_PacMan={1,1};
struct PacMan Pm={&depart_PacMan,0,0,3,0};

char area[H][W]={
   { "############################################################" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#        # # # # #          #             # # # # # #      #" },
   { "#        #       #         # #            #                #" },
   { "#        #       #        #   #           #                #" },
   { "#        # # # # #       #     #          #                #" },
   { "#        #              # # # # #         #                #" },
   { "#        #             #         #        #                #" },
   { "#        #            #           #       #                #" },
   { "#        #           #             #      #                #" },
   { "#        #          #               #     # # # # # #      #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#        ##        ##           #          ##        #     #" },
   { "#        # #      # #          # #         # #       #     #" },
   { "#        #  #    #  #         #   #        #  #      #     #" },
   { "#        #    # #   #        #     #       #   #     #     #" },
   { "#        #     #    #       # # # # #      #    #    #     #" },
   { "#        #          #      #         #     #     #   #     #" },
   { "#        #          #     #           #    #      #  #     #" },
   { "#        #          #    #             #   #       # #     #" },
   { "#        #          #   #               #  #        ##     #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "############################################################" }
};

void initialize (struct Ghost** allGhosts, char** area)
{
   srand(time(NULL));
   for (int i=0;i<NR_GHOSTS;i+=1)
   {
      struct Ghost* G=malloc (sizeof (struct Ghost));
      int x0=rand()%(H+1);
      int y0=rand()%(W+1);
      while(y0==1 && x0==1)
      {
         x0=rand()%(H+1);
         y0=rand()%(W+1);
      }
      struct coordinates* c=malloc(sizeof(struct Ghost));
      c->x=x0;
      c->y=y0;
      G->coordonnees=c;
      G->nx=0;
      G->ny=0;
      allGhosts[i]=G;
      area[x0][y0]='G';
   }
}

void move_Pac_Man(struct PacMan* PacMan, char** area)
{
   struct coordinates* c=PacMan->coordonnees;

   if (area[c->x+PacMan->nx][c->y+PacMan->ny]!='#')
   {
      area[c->x][c->y]=' ';
      c->x+=PacMan->nx;
      c->y+=PacMan->ny;
      if (area[c->x][c->y]=='.')
      {
         PacMan->food+=1;
      }
      area[c->x][c->y]='P';
   }
   else
   {
      PacMan->lives-=1;
      area[c->x][c->y]=' ';
      c->x=1;
      c->y=1;
      area[c->x][c->y]='P';
   }
}

void print_area(char area[H][W])
{
   for (int l=0;l<H;l+=1)
      {
         for (int c=0;c<W;c+=1)
         {
            printf("%c",area[l][c]);
         }
         printf("\n");
      }
}
void clavier(struct PacMan* P, struct Ghost** allGhosts)
{
   srand(time(NULL));
   char direction;
   scanf(" %c",&direction);
   if (direction == 'z')
   {
      P->ny = 1;
      P->nx = 0;
   }
   else if (direction == 's')
   {
      P->ny = -1;
      P->nx = 0;
   }
   else if (direction == 'q')
   {
      P->nx = -1;
      P->ny = 0;  
   }
   else if (direction == 'd')
   {
      P->nx = 1;
      P->ny = 0;
   }
   for  (int k=0;k<NR_GHOSTS;k++)
   {
      int c = rand()%2;
      if (c==1)
      {
         allGhosts[k]->nx = 0;
         int d = rand()%2;
         if (d==1)
         {
            allGhosts[k]->ny = -1;
         }
         else
         {
            allGhosts[k]->ny = 1;
         }
      }
      else
      {
         allGhosts[k]->ny = 0;
         int d = rand()%2;
         if (d==1)
         {
            allGhosts[k]->nx = -1;
         }
         else
         {
            allGhosts[k]->nx = 1;
         }
      }
   }
}

void check_life(struct PacMan* PacMan)
{
   if(PacMan->lives>=0)
   {
      print_area(area);
   }
   else
   {
      printf("La partie est terminée.\nVotre score est de %d points.\n",PacMan->food);
   }
}


int main()
{
   for (int l=0;l<H;l+=1)
      {
         for (int c=0;c<W;c+=1)
         {
            if (area[l][c]==' ')
            {
               area[l][c]='.';
            }
         }
      }
   print_area(area);
}
