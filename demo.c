/*Sow Mamadou  */
#include "socklib.h"
#include "ListeNoeud.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#define ORDER_RECH 1
#define ORDER_TRANSF 2
#define ORDER_QUIT 0
#define ORDER_SUPP 3
int main(int argc, char *argv[]) {
  int server = 0;
  Noeud n;
  int s;
  // int fin=0;
  int finS= 0;
  int status;
  int sock_attente;
  char received_data[1024];
  char send_data[1024];
  char add_client[4][23]={{0}};
  char nouv_client[4][23]={{0}};
  // char prt_serveur[4][10]={{0}};
  n.nb_voisin=0;
  socklen_t len;
  struct sockaddr_storage addr;
  char ipstr[INET6_ADDRSTRLEN];
 
  
   
  
  //char h_name[NI_MAXHOST], s_name[NI_MAXSERV];
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

	getpeername(s, (struct sockaddr*)&addr, &len);
	int fils= fork();
	
	if(fils==-1)
	  exit(1);
	else if(fils==0)
	  {
	    int port; 
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

	    // printf("Peer IP address: %s\n", ipstr);
	    //printf("Peer port      : %d\n", port);
	     
	      
	      
	    if(n.nb_voisin < 4)
	      {
		strcat( add_client[n.nb_voisin],ipstr);
		strcat( add_client[n.nb_voisin],"\0");
		//printf("addresse %s\n", add_client[n.nb_voisin]);
		(n.nb_voisin<4) ? n.nb_voisin++: n.nb_voisin ;
		int nn = n.nb_voisin;
		char buf[10] = "";
		sprintf( buf , "%d" , nn );
		send(s , buf , sizeof( buf ), 0 );	  
		for(int i=0; i<n.nb_voisin;i++){
		  if(send(s,(char*)&add_client[i],sizeof(add_client[i]),0)==SOCKET_ERROR)
		    {
		      printf("echec transmission messages\n");
		    }
		    
		}
		int fin2=0;
		int menu;
		int r = recv(s,received_data, 1024, MSG_WAITALL);
		if (r == -1) {
		  perror("recv");
		}
		char *taille  = extraire_sous_chaine(received_data, 0, 1 );
		menu=atoi(taille);
		while(!fin2)
		  {    
		    switch(menu)
		      {
		      case ORDER_QUIT:
			viderbuffer(add_client[n.nb_voisin], 23);
			printf("un client deconnecté \n");
			     
			close(s);
			fin2=1;
			break;
		      case ORDER_RECH:
			break;
		      case ORDER_TRANSF:
			break;
		      case ORDER_SUPP:
			break;
		      default:
			break;
		      }
		  }
		  
	      }
	    else
	      {
		/*******************si on a pas reussi à se connecter aus reseau*******************/ 
		/*for(int i=0; i<n.nb_voisin;i++){
		//printf("add_p %d =  %s\n",i,add_client[i]);	    
		if(send(s,(char*)&add_client[i],sizeof(add_client[i]),0)==SOCKET_ERROR)
		{
		printf("echec transmission messages\n");
		}
		else
		printf("messages transmis!\n");
		fprintf(stdout, "Le client à recu '%s' voisin = %d\n",add_client[i] , i);
		   
		}
		close(s);
		}*/
	      }
	  }
	else//Dans le père
	  {
	 
	      
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
	      } //fin ok 
	  }//fin dans le père
	
      } //fin serveur
  } else {// dans le client
    // insertion dans le reseau  
    char buf[10] = "";
    recv(s , buf , sizeof buf , 0 );
    sscanf( buf , "%d" , &n.nb_voisin );
    printf("nn=%d\n",n.nb_voisin);
    for(int i=0;i<n.nb_voisin;i++){
      int r = recv(s, (char*)&nouv_client[i], sizeof(nouv_client[i]), MSG_WAITALL);
      if (r == -1) {
	perror("recv");
      }
      fprintf(stdout, "Le client à recu '%s' voisin = %d\n",nouv_client[i] , i);
    }
    if(n.nb_voisin<4)
      {
	printf("%d\n", n.nb_voisin);
	printf("vous est connecté au reseau\n et voila la liste de vos voisin\n");
	strcpy(add_client[0],argv[1]);
	printf("voisin 0 '%s' \n",add_client[0]);	
	for(int i=1;i<n.nb_voisin;++i){
	  strcpy(add_client[i],nouv_client[i]);
	  printf("voisin %d '%s' \n",i,add_client[i]);	  
	}
	int fin2=0;
	while(!fin2)
	  {
	      
	    switch(menuClient())
	      {
	      case ORDER_QUIT:
		viderbuffer(add_client[n.nb_voisin], 23);
		if( send(s,"0\0",2, 0)<0)
		  {
		    perror("send");
		    exit(1);
		  }
		printf("vous êtes deconnecté\n");
		close(s);
		fin2=1;
		break;
	      case ORDER_RECH:
		break;
	      case ORDER_TRANSF:
		break;
	      case ORDER_SUPP:
		   
	      default:
		break;
	      }
	  }
	  
      }
    else//nb voisin >4
      {
	close(s);
	for(int i=0; i<4; ++i)
	  {
	    int fils= fork();
	    
	    if(fils==-1)
	      exit(1);
	    else if(fils==0)
	      {
		//dans le fils
		s = CreeSocketClient(argv[i], argv[2]);
		  
	      }
	    else
	      {
		//dans le père
	      }
	  
	  }//fin for
      }//end >4
      
  }//fin dans le client
  return 0;
}//fin main
