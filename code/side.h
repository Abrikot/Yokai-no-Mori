/***********************************************************************************
Classe gérant la réserve (affichage)
Emet les signaux :
    - clicked() : émis lorsqu'une pièce de la réserve est cliquée
    - parachutageSelect(int, QVector<Piece*>*) : émis lorsque la pièce est sélectionnée
Utilisée dans :
    -la classe Partie
************************************************************************************/


#ifndef SIDE_H
#define SIDE_H

#include "piece.h"

#include <iostream>
using namespace std;

class Side : public QLabel
{
    Q_OBJECT
private:
    int taille;              // Taille du plateau
    QVector <Piece*>* liste; // Pointeur sur le vecteur contenant les pièces à afficher dans la réserve
    int select[3] = {0,0,0}; // Contient les données lors de la sélection d'une pièce
public:
    //Accesseur
    int getSelect() const;

    //Mutateur
    void setSelect(int);

    // Constructeur
    Side(int,int,QString, int); // Prends 4 paramètres : la place de la fenêtre (placeX,placeY), le nom du joueur la possédant et la taille du plateau (3x4 ou 5x6)

    //Destructeur
    ~Side();

    //Autre méthode
    void displaySide(QVector <Piece*>&);    // Permet d'actualiser l'affichage de la réserve

    //Signaux, slots & méthodes associées
signals:
    void clicked();                                 // Signal émis lorsque la souris clique sur la réserve
    void parachutSelect(int, QVector<Piece*>*);     // Signal émis lors de la sélection d'une pièce pour le parachutage
public slots:
    void slotClicked();                             // Méthode appelée lorsque la souris clique sur la réserve
public:
    void mousePressEvent (QMouseEvent*);            // Méthode servant à gérer les clics
    void closeEvent(QCloseEvent* event);            // Méthode servant à empêcher la fermeture de la fenêtre accueillant la réserve
};

#endif // SIDE_H
