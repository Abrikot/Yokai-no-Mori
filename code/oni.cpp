/******************************************
Classe permettant de gérer la pièce Oni
Hérite de la classe Piece
*******************************************/


#include "oni.h"

//Mutateur
void Oni::setTransforme(const bool t)
{
    transforme = t;
    if (!t)
        setImage("data/oni.png");
    else
        setImage("data/superoni.png");
}
void Oni::setImage(const QString s)
{
    QPixmap tmp = (QPixmap)s;
    this->setPixmap(tmp);
    if (joueur == 1)
    {
        QTransform tr;
        this->setPixmap(this->pixmap()->transformed(tr.rotate(180)));
    }
}

//Accesseur
bool Oni::getTransforme() const
{
    return transforme;
}

//Constructeurs
Oni::Oni(int j, int t, int a) : Piece(j,t,a)
{
    setTransforme(0);
    this->setScaledContents(true);
}

//Méthodes
bool Oni::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    double tmp = sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee));
    if (transforme == 0)
        if (tmp == sqrt(2) || (tmp == 1 && (joueur == 1 && xDepart < xArrivee || joueur == 2 && xDepart > xArrivee)))
                return true;
    if (transforme == 1)
        if (tmp == 1 || (tmp == sqrt(2) && (joueur == 1 && xDepart < xArrivee || joueur == 2 && xDepart > xArrivee)))
            return true;
    return false;
}
QString Oni::getNom()
{
    return "Oni";
}
void Oni::pieceSelect(const bool select)
{
    if (transforme == 0)
    {
        if (select)
            setImage("data/oniblanc.png");
        else
            setImage("data/oni.png");
    }
    else
    {
        if (select)
            setImage("data/superoniblanc.png");
        else
            setImage("data/superoni.png");
    }
}
int Oni::getValeur()
{
    if (!transforme)
        return 4;
    else
        return 5;
}
void Oni::testTransforme()
{
    transforme = !transforme;
}
