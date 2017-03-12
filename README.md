									###########################################
									#***************README********************#
									###########################################
Nom: Sow
Prenom: Mamadou
numero_etu: 11414531

PROJET: ASR5

1-> /******Decommpresser l'archive******/

3-> /*******Pour Compiler ? **********/
	- j'ai utiliser le makefile que le professeur a	 fourni

4-> /*******Pour Executer**********/
	- dans deux terminals different du repertoire courant tapez les commandes
		./demo.ex port ->>>pour lancer le serveur
		./demo.ex add_ip port  ->>>pour lancer le lient

5-> le client se connecte directement sur le serveur qui a chaque fois fait un fork lorsqu'il qu'il ya un nouveau
    client et lui renvoi la liste de ses voisin directe. et si jamais il a atteint le nombre maximun de voisin 
    il refuse la connextion en fermant la socket.


5-> /*******Ensuite suivez les messages afficher **********/

	-Pour recherchez nn fichier:
		tapez 1 j'ai eu le temps de faire cette partie mais mon idée etais de faire lancer une commande find dans un procesus fils
		après retourné le resultat a l'aide des pipes pour pouvoir ensuite poursuivre l'opération. 
		

	-Pour tranferer un fichier:
		tapez 2

	-Pour suprimer un voisin:
		tapez 3 

	-Pour quitter:
		tapez 0 le client envoie un message au serveur qui ensuite ferme la socket du cote serveur 
		et le client lui même ferme sa socket et se deconecte.


6-> Dans ce projet vous avez la possiblité de connecter plusieur clients avec des  @ip diferrentes.
	j'ai pas gerer la partie si il n'y plus de places pour les voisns.

Projet Realiser: par SOW MAMADOU
