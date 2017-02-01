/***********************************************
Classe permettant de gérer la pièce Koropokkuru
Hérite de la classe Piece
************************************************/


#ifndef KOROPOKURRU_H
#define KOROPOKKURU_H

#include "piece.h"
#include <QTransform>

class Koropokkuru : public Piece
{
public:
    //Mutateur
    void setImage(const QString s);

    // Constructeur
    Koropokkuru(int,int,int);

    // Méthodes
    bool deplacement(int, int, int, int);   //Indique si une pièce peut effectuer ou non un déplacement
    QString getNom();                       //Renvoie le nom de la pièce
    void pieceSelect(const bool);           //Change la couleur de la pièce lorsqu'elle est sélectionnée
    int getValeur();                        //Renvoie la valeur attribuée à la pièce
};



#endif // Koropokkuru_H
