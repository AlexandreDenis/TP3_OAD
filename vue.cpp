/*--------------------------------------------------------------------
* OAD - TP n°3
* ISIMA                            
* 
* Auteur : Adrien Calime (G31) & Alexandre Denis (G21)
* Filiere F2
* 
* Date de création : 12/11/13    
* 
* Fichier : 			  
* 		vue.cpp
* 		Gestion de l'affichage graphique du programme
* 		CODE        						  
*--------------------------------------------------------------------*/

#include "vue.hpp"

#include <sstream>
#include <iostream>
#include <QMessageBox>

const int rapport_image=20;

/**************METHODES DE LA CLASSE Vue*****************/

/* CONSTRUCTEUR	
 * 
 * En entree :  
 * 			* parent : pointeur sur le widget parent
 */
Vue::Vue(QWidget *parent)
    :QWidget(parent)
{
    afficher=false;
    saving=false;
    insert=false;
    multi_go=false;
    setupUi(this);
    interface_graphique->setScene(&scene);
    connect(afficher_graphe,SIGNAL( clicked() ),this,SLOT( init() ));
    connect(client,SIGNAL( clicked() ),this,SLOT( afficherClt() ));
    connect(infosTournees,SIGNAL( clicked() ),this,SLOT( afficherTrn() ));
    connect(savings,SIGNAL( clicked() ),this,SLOT( sav() ));
    connect(insertion,SIGNAL( clicked() ),this,SLOT( ins() ));
    connect(deux_opt,SIGNAL( clicked() ),this,SLOT( deux_opt_vue() ));
    connect(shift,SIGNAL( clicked() ),this,SLOT( sht() ));
    connect(mult,SIGNAL( clicked() ),this,SLOT( multi() ));
    QString qs("don1.txt");
    chemin_fichier->setText(qs);
    s=new Solution();
}

/* Destructeur	: rend la memoire allouee
 */
Vue::~Vue()
{
    delete s;
}

/*
 * Initialise le probleme
 */
void Vue::init()
{
    saving=false;
    insert=false;
    multi_go=false;

    s->creer_clients( ( (chemin_fichier->text()).toStdString() ).data() );

    afficherGraphe();
}

/**********************************************************/
/**********************************************************/

/* afficherGraphe		
 * 		Affichage graphique du graphe
 */
void Vue::afficherGraphe()
{
    QRectF 			rec(0,0,rapport_image,rapport_image);
    stringstream 		ss;
    vector<Client>		clients;
    
    afficher=true;

    clients = s->get_client();

    spinBox->setMaximum(clients.size()-1);
    
    //remise a zero de l affichage
    //~ scene.clear();
    if(lignes.size() > 0)
        {
            for(QList<QGraphicsItem*>::iterator it = lignes.begin() ; it != lignes.end() ; ++it)
                scene.removeItem(*it);
                
            lignes.clear();
        }
    
    //pour chaque client
    for(vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
		// recuperation des coordonnees du client
                int 			x_cour				= it->getX()*rapport_image;
                int 			y_cour				= it->getY()*rapport_image;
		
		//on differencie le depot des clients graphiquement
                if(it == clients.begin() )
		{
			scene.addRect(rec)->setPos(x_cour,y_cour);
		}
		else
		{
			scene.addEllipse(rec)->setPos(x_cour,y_cour);
		}
		
		//affichage des identifiants
        ss.str("");
		ss << it->getId();
		scene.addText(ss.str().data())->setPos(x_cour,y_cour);
	}
	
	dist_tot->setText("");
}

/*
 * affiche un client
 */ 
void Vue::afficherClt()
{
	if(afficher)
	{
		QMessageBox 		win;
                win.setText(s->get_client_by_num(spinBox->value()).to_std().data());
		win.show();
		win.exec();
	}
}

/*
 * affiche une tournee
 */
void Vue::afficherTrn()
{
    if(afficher && (insert || saving || multi_go))
    {
        QMessageBox 		win;
        win.setText(s->get_tournee_by_num(spinBox_2->value()).data());
        win.show();
        win.exec();
    }
}

/*
 * applique l'algo de savings
 */
void Vue::sav()
{
    if(afficher)
    {
        s->cst_savings();
        afficherLigne();
        saving = true;
    }
}

/*
 * applique l'algo d'insertion
 */
void Vue::ins()
{
    if(afficher)
    {
        s->cst_insertion(s->get_client());
        afficherLigne();
        insert = true;
    }
}

/*
 * applique l'algo du 2-opt*
 * 
 */ 
void Vue::deux_opt_vue()
{
        if(afficher && (insert || saving))
        {
            s->deux_opt_etoile();
            afficherLigne();
        }
}

/*
  affiche l'algo shift
 */
void Vue::sht()
{
    if(afficher && (insert || saving))
    {
        s->shift();
        afficherLigne();
    }
}


/*
  affiche le resultat de l'algo multistart
  * -> base sur l'heuristique d'insertion
 */
void Vue::multi()
{
    if(afficher)
    {
        multi_go = true;
        s->multistart(1);
        afficherLigne();
    }
}

/*
  affiche les lignes du graphes representants les déplacements faits
  */
void Vue::afficherLigne()
{
    stringstream                ss;
    vector<Client>              clients;
    vector<int>                 clients_suiv;

    if(lignes.size() > 0)
    {
        for(QList<QGraphicsItem*>::iterator it = lignes.begin() ; it != lignes.end() ; ++it)
                                    scene.removeItem(*it);

        lignes.clear();
    }

    clients                                         = s->get_client();
    clients_suiv                                    = s->get_suiv_tournee();

    //affichage des liaisons
    for(vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        // recuperation des coordonnees du client
        int 			x_cour		= it->getX()*rapport_image+rapport_image/2;
        int 			y_cour		= it->getY()*rapport_image+rapport_image/2;
        int 			x_cour2		= clients[clients_suiv[it->getId()]].getX()*rapport_image+rapport_image/2;
        int 			y_cour2		= clients[clients_suiv[it->getId()]].getY()*rapport_image+rapport_image/2;

        lignes.push_back(scene.addLine(x_cour,y_cour,x_cour2,y_cour2));
    }

    ss << "distance totale = " << s->getDistTot() << endl << "nombre de vehicules = " << s->get_nb_tournee();
    dist_tot->setText(ss.str().data());
}
