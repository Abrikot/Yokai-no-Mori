/******************************************
Classe permettant de gérer la pièce Kodama
Hérite de la classe Piece
*******************************************/


#ifndef KODAMA_H
#define KODAMA_H

#include "piece.h"
#include <QTransform>

class Kodama : public Piece
{
private:
    bool transforme; //Indique si ce Kodama est transformé
public:
    // Mutateurs
    void setTransforme(const bool t);
    void setImage(const QString s);

    // Accesseur
    bool getTransforme() const;

    // Constructeurs
    Kodama(int,int,int);

    // Méthodes
    bool deplacement(int, int, int, int);   //Indique si une pièce peut effectuer ou non un déplacement
    QString getNom();                       //Renvoie le nom de la pièce
    void pieceSelect(const bool);           //Change la couleur de la pièce lorsqu'elle est sélectionnée
    int getValeur();                        //Renvoie la valeur attribuée à la pièce
    void testTransforme();                  //Change l'attribut "transforme" afin de tester différents situations (IA)
};


#endif // KODAMA_H
