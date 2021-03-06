/*--------------------------------------------------------------------
* OAD - TP 3 sur le probleme des tournees de vehicules
* ISIMA                            
* 
* Auteur : Adrien Calime (G31) & Alexandre Denis (G21)
* Filiere F2
* 
* Date de cr�ation : 08/11/13 
* 
* Fichier : 			  
* 		solution.cpp
* 		Gestion du probleme et de sa solution
* 		CODE         						  
*--------------------------------------------------------------------*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

#include "solution.hpp"

double max(const double &i, const double &j)
{
	return ( (i>j) ? i : j);
}

/*
 * creer les clients a partir d un fichier
 * 
 * entree :	
 * 		ficName -> le nom du fichier a charger
 * 
 */
void Solution::creer_clients(const char * filename) 
{
	fstream					file(filename);
	int						id;
	int						x;
	int						y;
	int						ouverture;
	int						fermeture;
	int						service;
        int						demande;

	file >> capacite;		/*capacite maximale des vehicules*/
	
        liste_clients.clear();

	/*tant qu'on est pas a la fin du fichier*/
	while(!file.eof())
	{
		/*lecture d'une ligne du fichier = un client*/
		file >> id;
		file >> x;
		file >> y;
		file >> demande;
		file >> ouverture;
		file >> fermeture;
		file >> service;
		
		/*gestion de la fin du fichier*/
		if ( file.eof() )
		{
			 break;   
		}   
		
		/*ajout d'un client a la liste*/
		liste_clients.push_back( Client(id, x, y, ouverture, fermeture, service, demande) );
	}

        file.close();

        //init des parametres
        dist=NULL;
        init_tournees();
}


/*
 * initialisation de la matrice des distances
 *
 */
void Solution::init_distance()
{
        const int				nb	=	liste_clients.size();
        distance_totale				= 0;
		
        if(!dist)
        {
            //allocation de la matrice de distances
            dist 						= new double* [nb];
            for ( int i = 0 ; i < nb ; i++)
                    dist[i] = new double [nb];

            //remplissage de la matrice de distance
            for(vector<Client>::iterator it1 = liste_clients.begin() ; it1 != liste_clients.end() ; ++it1)
            {
                for(vector<Client>::iterator it2 = liste_clients.begin() ; it2 != liste_clients.end() ; ++it2)
                {
                    dist[it1->getId()][it2->getId()]	= sqrt(
                                                             pow((liste_clients[it1->getId()].getX() - liste_clients[it2->getId()].getX()),2)
                                                              +
                                                             pow((liste_clients[it1->getId()].getY() - liste_clients[it2->getId()].getY()),2)
                                                          );
                }
            }
        }

}


/*
 * affichage des clients
 */ 
void Solution::affiche()
{		
	for(vector<Client>::iterator it = liste_clients.begin(); it != liste_clients.end(); ++it)
		it->affiche();
}

/*
 * recuperation de la liste des clients
 * 
 * sortie :
 * 		la liste des clients
 */ 
vector<Client> & Solution::get_client()
{
	return liste_clients;
}

/*
 * retourne le client a une position donnee
 *
 * entre :
 * 		la position dans le tableau
 *
 * sortie :
 * 		le client demande
 */
Client&	Solution::get_client_by_num(int pos)
{
        return liste_clients[pos];
}

/*
 * retourne la tournee via un numero de tournee
 *
 * entre :
 * 		le numero de la tournee
 *
 * sortie :
 * 		la tournee sous forme de chaine de caracteres
 */
string	Solution::get_tournee_by_num(int pos)
{
    int cour;
    stringstream ss;

    ss << "tournee " << pos << endl;
    ss << "charge = " << charge_tournee[pos] << endl;
    ss << "suivant le chemin :" << endl;

    cour = premier_client[pos];

    while(cour)
    {
        ss << cour << " ";

        cour = suiv_tournee[cour];
    }

    return ss.str();
}

/*
 * creer les tournees selon une heuristique de savings
 */
void Solution::cst_savings()
{
    vector<SGain>                   arcs_clients;
	SGain				gain_tmp;
	int 				id_cour;
	int 				tournee_cour 	= 0;
	vector<int>    liste_tournee_sup;
	
	init_tournees();
	
    nb_tournee 	= liste_clients.size()-1;

        /* creation d une tournee par client */
	for(vector<Client>::iterator it = liste_clients.begin()+1 ; it != liste_clients.end() ; ++it)
        {
                id_cour				= it->getId();

                dates_arrive[id_cour]		=  	dist[0][id_cour];

                dates_depart[id_cour]		=	dates_arrive[id_cour]+liste_clients[id_cour].getDureeService();

                prec_tournee[id_cour]		=	0;

                suiv_tournee[id_cour]		=	0;

                num_tournee[id_cour]		=	tournee_cour;

                charge_tournee[tournee_cour]    =	liste_clients[id_cour].getDemande();

                charge_partielle[id_cour] 	=	charge_tournee[tournee_cour];

                premier_client[tournee_cour]    =	id_cour;

                dernier_client[tournee_cour]    =	id_cour;

                tournee_cour++;

                distance_totale				+=	2 * dist[0][id_cour];

		
	}	
        nb_tournee = tournee_cour;
        /*
        1. Starting solution: each of the n vehicles serves one customer.
        2. For all pairs of nodes i,j, i...j, calculate the savings for joining the cycles using egde [i,j]:
                sij = c0i + c0j - cij.
        3. Sort the savings in decreasing order.
        4. Take edge [i,j] from the top of the savings list. Join two separate cycles with edge [i,j], if
                (i) the nodes belong to separate cycles
                (ii) the maximum capacity of the vehicle is not exceeded
                (iii) i and j are first or last customer on their cycles. i dernier et j premier
        5. Repeat 4 until the savings list is handled or the capacities don't allow more merging.
                The cycles if i and j are NOT united in sep 4, if the nodes belong to the same cycle OR the
                capacity is exceeded OR either node is an interior node of the cycle.
        */	
        
	int u = 0;
	int max = liste_clients.size();
	while(u < max)
	{
        liste_tournee_sup.clear();
		arcs_clients.clear();
		
        for(vector<Client>::iterator it1 = liste_clients.begin()+1 ; it1 != liste_clients.end() ; ++it1)
         {
                 for(vector<Client>::iterator it2 = liste_clients.begin()+1 ; it2 != liste_clients.end() ; ++it2)
                 {
                        //pour chaque arc (i,j) du graphe avec i != j
                        if(it1->getId() != it2->getId())
                        {
                                double 		cout_ij, cout_i0 , cout_0j , gain;
                                cout_ij 					= 	dist[it1->getId()][it2->getId()];
                                cout_i0 					= 	dist[it1->getId()][0];
                                cout_0j 					= 	dist[0][it2->getId()];
                                gain 						=	cout_i0 + cout_0j - cout_ij;

                                if(gain > 0)
                                {
                                        gain_tmp.i					= 	it1->getId();
                                        gain_tmp.j					= 	it2->getId();
                                        gain_tmp.gain				=	gain;

                                        arcs_clients.push_back(gain_tmp);
                                }
                         }
                 }
         }
         sort(arcs_clients.begin(),arcs_clients.end(),Gain_fonc());

         //Parcours des arcs dans l'ordre decroissant du gain
         for(vector<SGain>::iterator it = arcs_clients.begin(); it != arcs_clients.end(); ++it)
         {
                 //Les noeuds appartiennent a des tournees diff�rentes
                 if(num_tournee[it->i] != num_tournee[it->j])
                 {
                         //si la capacite max n'est pas excedee
                         if(test_capacite(num_tournee[it->i], num_tournee[it->j]))
                         {
                                 //si i est dernier et j est premier
                                 if(suiv_tournee[it->i] == 0 && prec_tournee[it->j] == 0)
                                 {
                                         //si la fusion respecte les fenetres de temps
                                         if(test_TW(num_tournee[it->i], it->j))
                                         {
                                             liste_tournee_sup.push_back(num_tournee[it->j]);
                                             update(it->i,it->j,it->gain);
                                             break;
                                         }
                                 }
                         }
                 }
         }
         sort(liste_tournee_sup.begin(),liste_tournee_sup.end());
         reverse(liste_tournee_sup.begin(),liste_tournee_sup.end());

         for(vector<int>::iterator it = liste_tournee_sup.begin() ; it != liste_tournee_sup.end() ; ++it)
         {
             premier_client.erase(premier_client.begin() + *it);
             dernier_client.erase(dernier_client.begin() + *it);
             charge_tournee.erase(charge_tournee.begin() + *it);
         }
         for(int i = 0 ; i < nb_tournee ; ++i)
         {
             for(int clt = premier_client[i] ; clt != 0 ; clt=suiv_tournee[clt])
             {
                 num_tournee[clt] = i;
             }
         }
         ++u;
	 }
}


/*
 * mise a jour d'une tournee par fusion
 *
 * entrees :
 * 		i -> id du client i
 * 		j -> id du client j
 * 		gain -> le gain d'une tournees
 */
void Solution::update(int i, int j,double gain)
{
        int 							cour;
        int 							prec;

        //mise a jour des suivants et precedents dans la tournee de i
        suiv_tournee[i]					=	j;
        prec_tournee[j]					=	i;

        //mise a jour de la charge de la tournee de i
        charge_tournee[num_tournee[i]] 	+=	charge_tournee[num_tournee[j]];

        //mise a jour du dernier client de la tournee i
        dernier_client[num_tournee[i]]	=	dernier_client[num_tournee[j]];

        prec 							=	i;
        cour							=	j;

        //pour chaque client de la tournee j
        while(cour)
        {
                charge_partielle[cour]                  =	charge_partielle[prec] + liste_clients[cour].getDemande();
                dates_arrive[cour]			= 	dates_depart[prec] + dist[prec][cour];
                dates_depart[cour]			= 	dates_arrive[cour] + liste_clients[cour].getDureeService();
                num_tournee[cour]			= 	num_tournee[prec];
                prec                        =   cour;
                cour                        =   suiv_tournee[cour];
        }
        
        nb_tournee--;
        distance_totale						-=	gain;

}


/*
 * test la capacite d une tournee
 *
 * entree :
 * 		id_tournee1 -> identifiant de la premiere tournee a tester
 * 		id_tournee2 -> identifiant de la deuxieme tournee a tester

 *
 * sortie : - true si capacite respectee, false sinon
 */
bool Solution::test_capacite(int id_tournee1,int id_tournee2)
{
        return ( ( charge_tournee[id_tournee1] + charge_tournee[id_tournee2] ) <= capacite );
}

/*
 * test la capacite d une tournee avec un client
 *
 * entree :
 * 		id_tournee -> identifiant de la tournee a tester
 * 		id_client -> identifiant du client a rajouter a la tournee

 *
 * sortie : - true si capacite respectee, false sinon
 */
bool Solution::test_capaciteClt(int id_tournee, int id_client)
{
	return ( (charge_tournee[id_tournee] + liste_clients[id_client].getDemande()) <= capacite);
}

/*
 * test la validite d'une fenetre de temps d'une tournee
 * 
 * entree :
 *		id_client_i -> identifiant du client depart
 * 		id_client_j -> identifiant du client arrive
 * 
 * sortie : - true si fenetre de temps respectee, false sinon
 */ 
bool Solution::test_TW(int id_client_i,int id_client_j)
{
    bool 					res		= true;
    bool					stop 	= false;

    //recuperation de la date d'arrivee sur client
    double 					tj = dates_depart[id_client_i] + dist[id_client_i][id_client_j];
    int						id_cour, id_prec;
    vector<double>				arrivees(dates_arrive);
    vector<double>				departs(dates_depart);

        if(tj <= dates_arrive[id_client_j] || id_client_j == 0)
	{
		res							= true;
	}
	else
	{
		id_cour 				= id_client_j;
		id_prec					= id_client_i;
		
		do
		{
                        tj						= dates_depart[id_prec] + dist[id_prec][id_cour];
			
			
			//apres la fermeture du client
			if((tj + liste_clients[id_cour].getDureeService()) > liste_clients[id_cour].getHoraireFermeture())
			{
				res 					= false;
				stop					= true;
			}
			else 		//avant la fermeture du client
			{				
				arrivees[id_cour] = max(tj, liste_clients[id_cour].getHoraireOuverture());
				departs[id_cour] = arrivees[id_cour] + liste_clients[id_cour].getDureeService();
				
				/*on avance dans la tournee*/
				id_prec = id_cour;
				id_cour = suiv_tournee[id_cour];
				
			}
		}while(id_cour != 0 && !stop);
		
		if(!stop)
                {
                        tj						= dates_depart[id_prec] + dist[id_prec][id_cour];
			
			if(tj > liste_clients[0].getHoraireFermeture())
				res 				= false;
		}
	}
	
	return res;
}


/*
 *  recupere la liste des suivants des sommets
 *
 *  sortie :
 *      la liste des suivants des sommets
 */
vector<int>& Solution::get_suiv_tournee()
{
    return suiv_tournee;
}


/*
 * 
 * creer les tournees selon une heuristique d'insertion
 * 
 * entree :
 * 		- copyClient : vecteur de clients dans un ordre bien pr�cis pour
 * 		la r�alisation de l'heuristique d'insertion
 */
void Solution::cst_insertion(vector<Client> copyClient)
{
    vector<Client>::iterator                it;
    vector<Client>::iterator                it_erase;
    int                                     index 		= 	0;
    int                                     bestClt		=	-1;
    double                                  gain_tmp		= 	numeric_limits<double>::max();
    double                                  gain_cour 		= 	0;
    bool                                    bestCltTrouve       = 	false;
    bool                                    tourneeVide		=	true;
    unsigned int                            i;

    for(i = 0; i < copyClient.size(); ++i)
    {
            if(!copyClient[i].getId())
                    break;
    }

    if(i < copyClient.size())
            copyClient.erase(copyClient.begin() + i);

    //initialise les tournees
    init_tournees();

    while((unsigned int)index < liste_clients.size() && !copyClient.empty())
    {
        if(!bestCltTrouve)
        {
                //creation d'une tournee vide
                index = nb_tournee;
                nb_tournee++;
                charge_tournee[index] 	= 	0;
                tourneeVide		=	true;
                gain_tmp		= 	numeric_limits<double>::max();
        }

        //initialisation du meilleur client
        bestCltTrouve				= 	false;

        //Choix du "meilleur" client
        for(it = copyClient.begin(); it != copyClient.end(); ++it)
        {
                //test du respect des contraintes
                if((unsigned int)index < liste_clients.size())
                {
                        if( tourneeVide || (!tourneeVide && test_capaciteClt(index,it->getId()) && test_TW(dernier_client[index],it->getId()) ) )
                        {
                                bestCltTrouve 	= 	true;

                                if(tourneeVide)
                                {
                                        gain_cour 	= 2. * dist[0][it->getId()];
                                }
                                else
                                {
                                        gain_cour 	= dist[dernier_client[index]][it->getId()]
                                                                + dist[0][it->getId()]
                                                                - dist[0][dernier_client[index]];
                                }

                                if(	gain_cour < gain_tmp )
                                {
                                        it_erase        =       it;
                                        bestClt		=	it->getId();
                                        gain_tmp	=	gain_cour;
                                }
                        }
                }
        }
		
        //insertion du meilleur client en fin de tournee
        if(bestCltTrouve)
        {
            copyClient.erase(it_erase);

            if(tourneeVide)
            {
                    tourneeVide			=	false;
                    premier_client[index]       =	bestClt;
                    dates_arrive[bestClt]	=	dist[bestClt][0];
                    prec_tournee[bestClt]	=	0;
                    charge_partielle[bestClt]	=	liste_clients[bestClt].getDemande();
            }
            else
            {
                    charge_partielle[bestClt]	=	charge_partielle[prec_tournee[bestClt]] + liste_clients[bestClt].getDemande();
                    dates_arrive[bestClt]	=	dates_depart[dernier_client[index]]
                                                +	dist[bestClt][dernier_client[index]];
                    prec_tournee[bestClt]	=	dernier_client[index];

                    suiv_tournee[dernier_client[index]] =   bestClt;
            }

            dates_depart[bestClt]		=	dates_arrive[bestClt]
                                                +	liste_clients[bestClt].getDureeService();

            suiv_tournee[bestClt]		=	0;
            num_tournee[bestClt]		=	index;
            charge_tournee[index]		+=	liste_clients[bestClt].getDemande();
            dernier_client[index]		=	bestClt;
            distance_totale			+=	gain_tmp;
            gain_tmp                            = 	numeric_limits<double>::max();
        }
    }
}


/*
 * 
 * initialise les tournees
 * 
 */
void Solution::init_tournees()
{
        dates_arrive.clear();
        dates_arrive.resize(liste_clients.size());
        dates_depart.clear();
        dates_depart.resize(liste_clients.size());
        prec_tournee.clear();
        prec_tournee.resize(liste_clients.size());
        suiv_tournee.clear();
        suiv_tournee.resize(liste_clients.size());
        num_tournee.clear();
        num_tournee.resize(liste_clients.size());
        charge_tournee.clear();
        charge_tournee.resize(liste_clients.size());
        premier_client.clear();
        premier_client.resize(liste_clients.size());
        dernier_client.clear();
        dernier_client.resize(liste_clients.size());
        charge_partielle.clear();
        charge_partielle.resize(liste_clients.size());

        dates_arrive[0]=0;
        dates_depart[0]=0;
        nb_tournee = 0;
        init_distance();
}

	
/*
 * 
 * recupere la distance totale de la solution
 * 
 * sortie : 
 * 		la distance totale
 */ 
double Solution::getDistTot()
{
	return distance_totale;
}	


/*
 * ameliore la solution avec l'algorithme du 2-opt*
 * 
 */
void Solution::deux_opt_etoile()
{
    int         deb_arc1        =        0;
    int         deb_arc2        =        0;
    int         fin_arc1        =        0;
    int         fin_arc2        =        0;
    double      gain;
    bool        fin =        false;

    while(!fin )
    {
        fin = true;
        //pour chaque tournee
        for(int tournee_1 = 0 ; tournee_1 < nb_tournee && fin; ++tournee_1)
        {
            deb_arc1 						=  	0;
            fin_arc1 						= 	premier_client[tournee_1];
            
            //pour chaque arc de la tournee
            while((deb_arc1 || fin_arc1) && fin)
            {                        
                //pour chaque tournee
                for(int tournee_2 = tournee_1 + 1 ; tournee_2 < nb_tournee && fin; ++tournee_2)
                {
                    deb_arc2                =	0;
                    fin_arc2                =   premier_client[tournee_2];
                                                
                    //pour chaque arc de la tournee
                    while((deb_arc2 || fin_arc2) && fin)
                    {
                        //on ne teste pas les cas inutiles
                        if( !( (deb_arc1 == 0 && deb_arc2==0)
                            ||	(fin_arc1==0 && fin_arc2==0)
                             ))
                        {
                            gain =        verif2opt(deb_arc1,fin_arc2,deb_arc2,fin_arc1);
                            if(gain < -0.1)
                            {
                                update2opt(deb_arc1,fin_arc2,deb_arc2,fin_arc1);
                                distance_totale                        +=        gain;
                                fin = false;
                            }
                        }
                        deb_arc2 =        fin_arc2;
                        if(fin_arc2)
                            fin_arc2		=	suiv_tournee[fin_arc2];
                    }
                }
                deb_arc1 =        fin_arc1;
                if(fin_arc1)
                    fin_arc1		=	suiv_tournee[fin_arc1];
            }
        }
    }
}



/*
 * verifie si le 2opt* est un mouvement ameliorant
 * 
 * entree :
 * 			- i : depart de l'arc1 a echanger
 * 			- j : arrivee de l'arc1 a echanger
 * 			- k : depart de l'arc2 a echanger
 * 			- l : arrivee de l'arc2 a echanger
 * 
 * sortie :
 * 			le gain calcule si trouve, infini sinon
 */ 
double Solution::verif2opt(int i,int j,int k,int l)
{
    double 		gain =  numeric_limits<double>::max();
    int			charge0i;
    int			charge0k;
    int			chargej0;
    int			chargel0;
    int                 tournee1,tournee2;

    if(i)
        tournee1 = num_tournee[i];
    else
        tournee1 = num_tournee[l];
    if(k)
        tournee2 = num_tournee[k];
    else
        tournee2 = num_tournee[j];

	
	//memes tournees
     if(tournee1 != tournee2)
	{
		//verification du respect des fenetres de temps
		if(test_TW(i,j) && test_TW(k,l))
		{
			//calcul des charges necessaires au calcul du gain
			if(i)
			{
				charge0i		=	charge_partielle[i];
				chargel0		=	charge_tournee[num_tournee[i]] - charge_partielle[i];
			}
			else
			{
				charge0i		=	0;
				chargel0		=	charge_tournee[num_tournee[l]];
			}
			
			if(k)
			{
				charge0k		= 	charge_partielle[k];
				chargej0		= 	charge_tournee[num_tournee[k]] - charge_partielle[k];
			}
			else
			{
				charge0k		= 	0;
				chargej0		= 	charge_tournee[num_tournee[j]];
			}
			
                        //verification de la capacite
                        if(((charge0i + chargej0) < capacite) && ((charge0k + chargel0) < capacite))
			{
				//calcul du gain
				gain		=	dist[i][j] + dist[k][l] - dist[i][l] - dist[k][j];
			}
		}
	}
	
	return gain;
}

/*
 * 
 * mise a jour des tournees pour le 2opt*
 * 
 * entrees : 
 * 			- i : depart de l'arc1 a echanger
 * 			- j : arrivee de l'arc1 a echanger
 * 			- k : depart de l'arc2 a echanger
 * 			- l : arrivee de l'arc2 a echanger
 * 
 */
void Solution::update2opt(int i, int j, int k, int l)
{
        int prec;
        int cour;
        int charge_tournee1=0;
        int charge_tournee2=0;
        int dernier_clt_tmp;
        int num_tour1=-1;
        int num_tour2=-1;
        int tmp_charge1=0;
        int tmp_charge2=0;

        if(i)
        {
            num_tour1 = num_tournee[i];
            tmp_charge1 = charge_partielle[i];
            charge_tournee1 =   charge_tournee[num_tournee[i]];
        }
        else
        {
            num_tour1 = num_tournee[l];
            tmp_charge1 = 0;
            charge_tournee1 =   charge_tournee[num_tournee[l]];
        }

        if(k)
        {
            num_tour2 = num_tournee[k];
            tmp_charge2 = charge_partielle[k];
            charge_tournee2 =   charge_tournee[num_tournee[k]];
        }
        else
        {
            num_tour2 = num_tournee[j];
            tmp_charge2 = 0;
            charge_tournee2 =   charge_tournee[num_tournee[j]];
        }

		//mise a jour de la tournee
		charge_tournee[num_tour1]	=	tmp_charge1 + charge_tournee2 - tmp_charge2;
		charge_tournee[num_tour2]	=	tmp_charge2 + charge_tournee1 - tmp_charge1;
		dernier_clt_tmp             =       dernier_client[num_tour1];
		dernier_client[num_tour1]	=	dernier_client[num_tour2];
		dernier_client[num_tour2]   =       dernier_clt_tmp;

		//permutation
		if(i)
			suiv_tournee[i] 			= j;
		if(j)
			prec_tournee[j] 			= i;
		if(k)
			suiv_tournee[k] 			= l;
		if(l)
			prec_tournee[l] 			= k;

		//mise a jour des clients de la tournee
		prec = i;
		cour = j;
		while(cour)
		{
				dates_arrive[cour]		= dates_depart[prec] + dist[cour][prec];
				dates_depart[cour]		= dates_arrive[cour] + liste_clients[cour].getDureeService();

				charge_partielle[cour]          = charge_partielle[prec] + liste_clients[cour].getDemande();
				num_tournee[cour]		= num_tournee[prec];

				prec                            = cour;
				cour                            = suiv_tournee[cour];
		}

		prec = k;
		cour = l;
		while(cour)
		{
				dates_arrive[cour]		= dates_depart[prec] + dist[cour][prec];
				dates_depart[cour]		= dates_arrive[cour] + liste_clients[cour].getDureeService();

				charge_partielle[cour]      = charge_partielle[prec] + liste_clients[cour].getDemande();
				num_tournee[cour]		= num_tournee[prec];

				prec                        = cour;
				cour                        = suiv_tournee[cour];
		}

		if(!i && !j)	//on supprime la tournee de i
		{
				 nb_tournee--;
				 premier_client.erase(premier_client.begin() + num_tour1);
				 dernier_client.erase(dernier_client.begin() + num_tour1);
				 charge_tournee.erase(charge_tournee.begin() + num_tour1);

				for(int u = num_tour1; u < nb_tournee; ++u)
				{
						 for(int clt = premier_client[u] ; clt != 0 ; clt=suiv_tournee[clt])
						 {
								 num_tournee[clt] = u;
						 }
				}
		}
		else if(!k && !l)	//on supprime la tournee de k
		{
				nb_tournee--;
				premier_client.erase(premier_client.begin() + num_tour2);
				dernier_client.erase(dernier_client.begin() + num_tour2);
				charge_tournee.erase(charge_tournee.begin() + num_tour2);

				for(int u = num_tour2; u < nb_tournee; ++u)
				{
						 for(int clt = premier_client[u] ; clt != 0 ; clt=suiv_tournee[clt])
						 {
								 num_tournee[clt] = u;
						 }
				}
		}
        
}


/*
 * optimisation locale par tournee
*/
void Solution::shift()
{
    double  gain_max    =   -0.1;
    double  gain_cour   =   0;
    int     pos_max1    =   0;
    int     pos_max2    =   0;
    bool    fin;

    for(int i = 0 ; i < nb_tournee ; ++i)
    {
        fin     =   false;
        if(premier_client[i] != dernier_client[i]) // si il y a plus d'un �l�ment dans la tourn�e
        {
            while(!fin)
            {
                fin         =   true;
                for(int cour = premier_client[i]; cour != 0 ; cour = suiv_tournee[cour] )
                {
                    for(int cour2 = cour; cour2 != 0 ; cour2 = suiv_tournee[cour2] )
                    {
                        if(cour != cour2)
                        {
                            gain_cour   =   dist[prec_tournee[cour]][suiv_tournee[cour]]
                                        +   dist[cour2][cour]
                                        +   dist[cour][suiv_tournee[cour2]]
                                        -   dist[cour][prec_tournee[cour]]
                                        -   dist[cour][suiv_tournee[cour]]
                                        -   dist[cour2][suiv_tournee[cour2]];

                            if(gain_cour < gain_max)
                            {
                                gain_max    =   gain_cour;
                                pos_max1    =   cour;
                                pos_max2    =   cour2;
                            }
                        }
                    }
                }
                if(gain_max < -0.1)
                {
                    int tmp1 = suiv_tournee[pos_max1];
                    int tmp2 = prec_tournee[pos_max1];
                    int tmp3 = suiv_tournee[pos_max2];

                    if(tmp2)
                        suiv_tournee[tmp2]    =   tmp1;
                    if(tmp1)
                        prec_tournee[tmp1]    =   tmp2;
                    if(tmp3)
                        prec_tournee[tmp3]    =   pos_max1;

                    prec_tournee[pos_max1]                      =   pos_max2;
                    suiv_tournee[pos_max1]                      =   tmp3;
                    suiv_tournee[pos_max2]                      =   pos_max1;

                    distance_totale                             +=  gain_max;
                    gain_max                                    =   -0.1;
                    fin                                         =   false;

                    update_date_shift(i);
                }
            }
        }
    }
}

/*
    mise ? jour des dates d'arrive apres shift

    entree:
        tournee : le num�ro de tournee dont il faut changer les dates des clients
*/
void Solution::update_date_shift(int tournee)
{
    for(int clt = premier_client[tournee] ; clt != 0 ; clt = suiv_tournee[clt] )
    {
        dates_arrive[clt]   =   dist[clt][prec_tournee[clt]];
        dates_depart[clt]   =   dates_arrive[clt]+liste_clients[clt].getDureeService();
    }
}

/*
 * ameliore l'algorithme selon la methode du multistart
 * 
 * entree :
 * 		- nb_max : nombre maximale d'iterations a realiser
 */ 
void Solution::multistart(int nb_max)
{
    vector<Client>      copyClient      = liste_clients;
    vector<Client>      oldClt;
    double              oldDist         = numeric_limits<double>::max();
    double              newDist;
    double              dist_amel_old, dist_amel_new;
        
    for(int i = 0; i < nb_max; ++i)
    {
        //generation d'une sequence de clients aleatoires
        random_shuffle(copyClient.begin(), copyClient.end());

        //on applique l'heurisique d'insertion en utilisant cet ordre
        cst_insertion(copyClient);

        dist_amel_old = numeric_limits<double>::max();
        dist_amel_new = distance_totale;

        //tant qu'on peut ameliorer
        while(dist_amel_old > dist_amel_new)
        {
            dist_amel_old = distance_totale;

            //recherche_locale
            deux_opt_etoile();
            shift();

            dist_amel_new = distance_totale;
        }

        //on recupere la nouvelle distance totale
        newDist                 =       distance_totale;

        //la nouvelle solution est plus performente que l'actuelle
        if(newDist < oldDist)
        {
            oldDist             =        newDist;
            oldClt.clear();
            oldClt              =        copyClient;
        }
    }

    /*on met en place la meilleure solution trouvee*/
    cst_insertion(oldClt);
    
    dist_amel_old = numeric_limits<double>::max();
    dist_amel_new = distance_totale;

    while(dist_amel_old > dist_amel_new)
    {
        dist_amel_old = distance_totale;

        //recherche_locale
        deux_opt_etoile();
        shift();

        dist_amel_new = distance_totale;
    }
}


/*
retourne le nombre de tournee donc le nombre de vehicule

sortie : le nombre de v�hicule

*/
int Solution::get_nb_tournee()
{
    return nb_tournee;
}

//Destructeur
Solution::~Solution()
{
        const int				nb	=	liste_clients.size();

        for ( int i = 0 ; i < nb ; i++)
        {
                delete	[] 	dist[i];
        }

        delete [] dist;
}

















