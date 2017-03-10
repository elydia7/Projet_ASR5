/*Sow Mamadou  */
#include "socklib.h"
#include "ListeNoeud.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  int server = 0;
  Noeud n;
  int s;
  int fin=0;
  int finS= 0;
  int status;
  int sock_attente;
  char add_client[4][20]={{0}};
  n.nb_voisin=0;
  socklen_t len;
  struct sockaddr_storage addr;
  char ipstr[INET6_ADDRSTRLEN];
  int port;
  
   
  
  //char h_name[NI_MAXHOST], s_name[NI_MAXSERV];

  printf("Demo\n");
  if (argc == 2) {
    // je suis le serveur (l'argument est le port)
    server = 1;

    // Création de la socket d'attente
    sock_attente = CreeSocketServeur(argv[1]);
    if (sock_attente == -1) {
      exit(1);
    }

    // attente du client
    
  } else if (argc == 3){
    // Je suis le client
    server = 0;
    
    // création d'une socker et connexion
    s = CreeSocketClient(argv[1], argv[2]);
    
  } else {
    // il y a un problème car il manque d'argument
    fprintf(stderr, "Usage serveur: %s <port>\n       client: %s <server> <port>\n", argv[0], argv[0]);
    exit(1);
  }


  if (server) {
    
    while(!finS)
      {
	//
	

	s = AcceptConnexion(sock_attente);
	if(n.nb_voisin<4){
	getpeername(s, (struct sockaddr*)&addr, &len);
	  int fils= fork();
	
	  if(fils==-1)
	    exit(1);
	  else if(fils==0)
	    {

	   
	      len = sizeof addr;
	      getpeername(s, (struct sockaddr*)&addr, &len);

	      // deal with both IPv4 and IPv6:
	      if (addr.ss_family == AF_INET) {
		struct sockaddr_in *s = (struct sockaddr_in *)&addr;
		port = ntohs(s->sin_port);
		inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
	      } else { // AF_INET6
		struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
		port = ntohs(s->sin6_port);
		inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
	      }

	      printf("Peer IP address: %s\n", ipstr);
	      printf("Peer port      : %d\n", port);
	     
	      strcat( add_client[n.nb_voisin],ipstr);
	      strcat( add_client[n.nb_voisin],"\0");
	      printf("addresse %s\n", add_client[n.nb_voisin]);
	      n.nb_voisin++;
	      printf("nb voisin %d \n",n.nb_voisin);
	    
	      /*dans le fils*/
	      // un message à envoyer
	      //const char *mess = " Telle est la réponse à la question ... ";

	      // Envoie d'un premier message avec la taille de la suite
	      // e premier message fait 30 caractères
	      //EnvoieMessage(s, "TailleMessage:%16d", strlen(mess));
	      // Envoie d'un second message avec le reste
	      //EnvoieMessage(s, mess);
	 
	      /*while(!fin){
		char buff[31];
		int r2 = recv(s, buff, 30, MSG_WAITALL);
		}*/
	    
	    }
	  else{
	    /*Dans le père*/
	 
	    int ok=0;
	    while(!ok)
	      { 
		int res = waitpid(-1,&status,0);
		if(res==-1)
		  {
		    printf("erreur waitpid \n");
		    exit(1);
		  }
		else if(res!=0)
		  {
		    fprintf(stdout,"le processus vient de se terminer %d \n",res);
		    if(WIFEXITED(status))
		      {
			fprintf(stdout,"le fils a retourné %d \n ", WEXITSTATUS(status));
		      }
		  }
		else
		  {
		    ok=1;
		  }
	      }  
	  }
	}else
	  {
	    /*on renvois la liste des voisins dans les voisin*/
	   
             	    
	    for(int i=0; i<4;i++){
	      //printf("add_p %d =  %s\n",i,add_client[i]);
	      if(send(s,(char*)&add_client[i],sizeof(add_client[i]),0)==SOCKET_ERROR)
		{
		  printf("echec transmission messages\n");
		}
	      else
		printf("messages transmis!\n");
	      	fprintf(stdout, "Le client à recu '%s' voisin = %d\n",add_client[n.nb_voisin] , n.nb_voisin);
	    }
	    
	  }
      }
  } else {
    // char buff[20];
    
    while(!fin){
      //menuClient();
      // lecure des 30 premiers caractères
      if(n.nb_voisin<4){
	int r = recv(s, (char*)&add_client[n.nb_voisin], sizeof(add_client[n.nb_voisin]), MSG_WAITALL);
	if (r == -1) {
	  perror("recv");
	}
	n.nb_voisin++;
	//strcat( add_client[n.nb_voisin],buff);
	//strcat( add_client[n.nb_voisin],"\0");
	fprintf(stdout, "Le client à recu '%s' voisin = %d\n",add_client[n.nb_voisin] , n.nb_voisin);
      }
      //break;
      //sleep(10);
      
      // J'ajoute le caractère de fin de chaine à la fin du message recu
      /* buff[r] = '\0';
	 fprintf(stdout, "Le client à recu '%s'\n", buff);*/

      // lecture de la taille du second message
      /** int taille;
      sscanf(buff, "TailleMessage:%16d", &taille);
      // lecure de la suite du message
      char buff2[taille];
      r = recv(s, buff2, taille, MSG_WAITALL);
      if (r == -1) {
	perror("recv");
      }
    
      // ecriture du message (comme un ensemble d'octet et pas comme une chaine de caractère)
      write(STDOUT_FILENO, buff2, r);
      fprintf(stdout, "\n");*/
    
      }//
  }
  return 0;
}
