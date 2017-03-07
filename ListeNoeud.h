#ifndef _LIST_NOEUD
#define _LIST_NOEUD
#define MAX_VOISIN 3
#define T_ADD 15
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//typedef int Elem;
typedef struct _Noeud
{
  int nb_voisin;
  int port;
  char * add;
  char voisin_direct[MAX_VOISIN][T_ADD];
} Noeud;

/*typedef struct _Liste
{
  Noeud *ad;
  int nb_noeud;
} Liste;
*/
void initialialiserListe(Noeud *n, int port, char* add );
void insertionDansliste(Noeud *n);
//void rechercherDansListe(Liste *l, char * nameFile);
//void testamentNoeud(Noeud *l);
int menuClient();




#endif
