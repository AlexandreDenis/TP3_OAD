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
* 		client.cpp
* 		Gestion des clients
* 		CODE         						  
*--------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "client.hpp"

int Client::nb_clients = 0;
/*
 * constructeur d un client
*/ 
Client::Client(	int id, 
				int x, 
				int y, 
				int horaireOuverture,
				int horaireFermeture, 
				int dureeService, 
				int demande)
		:id_(id), x_(x), y_(y), horaireOuverture_(horaireOuverture)
		,horaireFermeture_(horaireFermeture),dureeService_(dureeService)
		,demande_(demande)
{
	nb_clients++;
}


//affichage du client
void Client::affiche()
{
	cout << id_ << " " << x_ << " " << y_ << " " << demande_ << " " << horaireOuverture_ << " " << horaireFermeture_ << " " << dureeService_ << endl;
}

/*
 * client sous forme d une chaine de caracteres
 * 
 * sortie : 
 * 		la chaine de caracteres representant le client
 */ 
string	Client::to_std()
{
	stringstream 			ss;
	ss 	<< "id = " << id_ << endl 
		<< "x = " << x_ << endl 
		<< "y = " << y_ << endl
		<< "demande = " << demande_ << endl 
		<< "horaire ouverture = " << horaireOuverture_ << endl
		<< "horaire fermeture = " << horaireFermeture_ << endl
		<< "duree service = " << dureeService_ << endl;
	return ss.str();
}
/*
 * recupere la coordonne X
 * 
 * sortie :
 * 		la coordonne x du client
 */ 
int	Client::getX()
{
	return x_;
}

/*
 * recupere la coordonne Y
 * 
 * sortie :
 * 		la coordonne y du client
 */
int	Client::getY()
{
	return y_;
}

/*
 * recupere l id du client
 * 
 * sortie :
 * 		l id du client
 */ 
int	Client::getId()
{
	return id_;
}

/*
 * recupere la demande d un client
 * 
 * sortie :
 * 		retourne la quantite demandee d un client
 */ 
int Client::getDemande()
{
	return demande_;
}


/*
 * recupere l'horaire de fermeture d un client
 * 
 * sortie :
 * 		retourne l'horaire de fermeture du client
 */
int	Client::getHoraireFermeture()
{
	return horaireFermeture_;
}


/*
 * recupere l'horaire d'ouverture d un client
 * 
 * sortie :
 * 		retourne l'horaire d'ouverture du client
 */
int	Client::getHoraireOuverture()
{
	return horaireOuverture_;
}


/*
 * recupere la duree du service d un client
 * 
 * sortie:
 * 		retourne la duree du service du client
 */
int Client::getDureeService()
{
	return dureeService_;
}


/*
 * recupere le nombre total de clients
 * 
 * sortie:
 * 		retourne le nombre total de clients
 */
int Client::getNbClients()
{
	return nb_clients;
}


//destruction d'un client
Client::~Client()
{
	nb_clients--;
}
