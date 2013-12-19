/*--------------------------------------------------------------------
* OAD - TP 3 sur le probleme des tournees de vehicules
* ISIMA                            
* 
* Auteur : Adrien Calime (G31) & Alexandre Denis (G21)
* Filiere F2
* 
* Date de création : 08/11/13 
* 
* Fichier : 			  
* 		client.hpp
* 		Gestion des clients
* 		EN-TETE         						  
*--------------------------------------------------------------------*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
using namespace std;

class Client
{
	private:
		int				id_;				//identifiant du client
		int				x_;					//position du client -> x
		int				y_;					//position du client -> y
		int				horaireOuverture_;	//Heure d'ouverture du client
		int				horaireFermeture_;	//Heure de fermeture du client
		int				dureeService_;		//Duree service/livraison
		int				demande_;			//quantite demandee par le client
		static int 		nb_clients;			//nombre de clients
		
		//liste des arcs sortants voisins du depot par identifiant
		vector<int>		arcsSortants_;
		
	public:
		//constructeur d un client
		Client(int,int,int,int,int,int,int);
		//affichage du client
		void			affiche();
		//client sous forme d une chaine de caracteres
        string			to_std();
		//recupere la coordonne X
		int				getX();
		//recupere la coordonne Y
		int				getY();
		//recupere l id du client
		int				getId();
		//recupere la demande d un client
		int				getDemande();
		//recupere l'horaire de fermeture d un client
		int				getHoraireFermeture();
		//recupere l'horaire de l'ouverture d un client
		int				getHoraireOuverture();
		//recupere la duree du service d un client
		int				getDureeService();
		//recupere le nombre total de clients
		static int 		getNbClients();
		//destruction d'un client
		~Client();
	
};

#endif
