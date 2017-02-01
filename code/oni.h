/******************************************
Classe permettant de gérer la pièce Oni
Hérite de la classe Piece
*******************************************/


#ifndef ONI_H
#define ONI_H

#include "piece.h"
#include <QTransform>

class Oni : public Piece
{
private:
    bool transforme; //Indique si cet Oni est transformé
public:
    // Mutateur
    void setTransforme(const bool t);
    void setImage(const QString s);

    // Accesseur
    bool getTransforme() const;

    // Constructeurs
    Oni(int,int,int);

    // Méthodes
    bool deplacement(int, int, int, int);   //Indique si une pièce peut effectuer ou non un déplacement
    QString getNom();                       //Renvoie le nom de la pièce
    void pieceSelect(const bool);           //Change la couleur de la pièce lorsqu'elle est sélectionnée
    int getValeur();                        //Renvoie la valeur attribuée à la pièce
    void testTransforme();                  //Change l'attribut "transforme" afin de tester différents situations (IA)
};

#endif // ONI_H
