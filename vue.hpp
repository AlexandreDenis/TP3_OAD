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
* 		vue.hpp
* 		Gestion de l'affichage graphique du programme
* 		EN-TETE
*--------------------------------------------------------------------*/

#ifndef VUE_HPP
#define VUE_HPP

#include <QWidget>
#include <QObject>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItem>
#include <boost/shared_ptr.hpp>

#include "solution.hpp"
#include "ui_interface_graphique.h"

using namespace std;

/*Classe de la vue*/
class Vue : public QWidget,private Ui::interface_graphique_2
{
    Q_OBJECT

private:    
    //scene pour l'affichage
    QGraphicsScene scene;
    //boost::shared_ptr<Solution> s;
    Solution * s;
    bool afficher;
    bool saving;
    bool insert;
    QList<QGraphicsItem*> lignes;

public:
    Vue(QWidget *parent=0);
    ~Vue();
    void afficherGraphe();
    void afficherLigne();

public slots:
    void init();
    void afficherClt();
    void sav();
    void ins();
    void deux_opt_vue();
    void sht();
    void multi();
};

#endif // VUE_HPP
