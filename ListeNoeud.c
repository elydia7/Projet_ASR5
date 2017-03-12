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
void initialialiserListe(Noeud *n, int port, char* add){
  n->nb_voisin=0;
  n->port=port;
  n->add=add;

}

int taille_rapport(char* buffer,int index)
{
  int t=1;
  while(buffer[t+index]!='#'){
    t++;
		
  }
  return t-1;	
}

char * extraire_sous_chaine(char* chaine, int taille, int index )
{
  int i;
  char * sous_chaine=(char*)malloc(sizeof(char*)*taille+1);
  /*recuperation taille*/
  for(i=0;i<taille;i++)
    {
      sous_chaine[i]=chaine[i+index];
		     
    }
  sous_chaine[i]='\0';
  return sous_chaine;

}

void viderbuffer(char buff[], int taille)
{
	int i;
	for(i=0; i<taille;i++)
	{
		buff[i]=0;
	}
		
}

