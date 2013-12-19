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
* 		main.cpp
* 		Programme principal
* 		CODE         						  
*--------------------------------------------------------------------*/

#include <QApplication>
#include "vue.hpp"


/**********POINT D'ENTREE DU PROGRAMME**********/
int main(int argc, char ** argv)
{
    QApplication app(argc,argv);
    Vue v; // creation du client
    v.show(); // on affiche la fenetre
    return app.exec(); // on execute le programme
}


/*
 * point d entree du programme
 */ 
//~ int main(int, char**)
//~ {
	//~ Solution 		s;
	//~ 
	//~ s.creer_clients("don1.txt");
	//~ s.affiche();
	//~ 
	//~ return 0;
//~ }
