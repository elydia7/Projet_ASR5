#include "ListeNoeud.h"

/*Menu client*/
int menuClient()
{
  int i;
  printf("******Coté Client.****** \n \n");
  printf("Faites votre choix.\n");
  printf("1-Rechercher un fichier\n");
  printf("2-Transfer de fichier\n");
  printf("0-Deconnexion du client\n");
  printf("\n\n\nVotre choix?");
  scanf("%d",&i); getchar();
  while(i<0 || i>3)
    {
      printf("Recommencez SVP !");
      scanf("%d",&i); getchar();
    }
  return i;
}
/*Initialisation du Noeud*/
void initialialiserListe(Noeud *n, char * port, char* add){
  n->nb_voisin=0;
  n->port=port;
  n->add=add;

}
