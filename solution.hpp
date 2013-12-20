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
* 		solution.hpp
* 		Gestion du probleme et de sa solution
* 		EN-TETE         						  
*--------------------------------------------------------------------*/

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include "client.hpp"

using namespace std;

class Solution
{
	private:
	
		int 				capacite;		//capacite des vehicules
		
		//tableaux indexes sur les sommets
		vector<double>		dates_arrive;	//dates arrivees chez les clients
		vector<double>		dates_depart;	//dates departs chez les clients
		vector<int>			prec_tournee;	//sommet precedent dans la tournee
		vector<int>			suiv_tournee;	//sommet suivant dans la tournee
		vector<int>			num_tournee;	//numero de tournee pour un sommet
		vector<int>			charge_partielle;	//charges partielles par client
		
		//tableaux indexes sur les tournees
		vector<int>			charge_tournee;	//charge totale d une tournee
		vector<int>			premier_client;	//premier client d une tournee
		vector<int>			dernier_client;	//dernier client d une tournee
		
		int 				nb_tournee; 	//nombre de tournee		 
		
        vector<Client>      liste_clients;	//liste des clients
		double				distance_totale;//distance totale des tournees

		double 				**dist;         //matrice des distances
	public:
	
		// creer les clients a partir d un fichier
		void 				creer_clients(const char * filename);
		//initialisation de la matrice des distances
		void				init_distance();
		//affichage des clients
		void				affiche();
		//recuperation de la liste des clients
		vector<Client>& 	get_client();
		//retourne le client a une position donnee
		Client&				get_client_by_num(int pos);
		//test la capacite d une tournee
        bool 				test_capacite(int,int);
		//test la capacite d une tournee avec un client
        bool 				test_capaciteClt(int,int);
		//test la validite d'une fenetre de temps d'une tournee
		bool 				test_TW(int id_tournee,int id_client);
		//recupere la liste des suivants des sommets
		vector<int>&		get_suiv_tournee();
		//mise a jour d'une tournee par fusion
		void				update(int,int,double);
		//initialise les tournees
		void				init_tournees();
		//creer les tournees selon une heuristique de savings
		void				cst_savings();		
		//creer les tournees selon une heuristique d'insertion
		void				cst_insertion(vector<Client>, bool);	
		//recupere la distance totale de la solution
		double				getDistTot();
		//ameliore la solution avec l'algorithme du 2-opt*
		void				deux_opt_etoile();
		//verifie si le 2opt* est un mouvement ameliorant
		double				verif2opt(int i,int j,int k,int l);
		//mise a jour des tournees pour le 2opt*
		void				update2opt(int i, int j, int k, int l);
		//optimisation locale par tournee
		void                shift();
		//mise à jour des dates d'arrive apres shift
		void                update_date_shift(int tournee);
		//ameliore l'algorithme selon la methode du multistart
		void				multistart(int);
                //retourne le nombre de tournee donc le nombre de vehicule
                int                             get_nb_tournee();
		//Destructeur
		~Solution();

};


class SGain
{
public :
        int					i;
        int					j;
        double 				gain;
};

class Gain_fonc
{
	public:
		bool operator()(const SGain & s1,const SGain & s2) { return (s1.gain > s2.gain); }
};

#endif
