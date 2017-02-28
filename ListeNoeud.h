#ifndef _LIST_NOEUD
#define _LIST_NOEUD

typedef int Elem;
typedef struct _Noeud
{
  char* addIp;
  struct _Noeud *voisin;
} Noeud;

typedef struct _Liste
{
  Noeud *ad;
  int nb_noeud;
} Liste;

void initialialiserListe(Liste *l);
void insertionDansliste(Liste *l, Noeud n);
void rechercherDansListe(Liste *l, char * nameFile);
void testamentListe(Liste *l);




#endif
