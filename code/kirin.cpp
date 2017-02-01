/******************************************
Classe permettant de gérer la pièce Kirin
Hérite de la classe Piece
*******************************************/

#include "kirin.h"

//Mutateur
void Kirin::setImage(const QString s)
{
    QPixmap tmp = (QPixmap)s;
    this->setPixmap(tmp);
    if (joueur == 1)
    {
        QTransform tr;
        this->setPixmap(this->pixmap()->transformed(tr.rotate(180)));
    }
}

//Constructeurs
Kirin::Kirin(int j, int t, int a) : Piece(j,t,a)
{
    setImage("data/kirin.png");
    this->setScaledContents(true);
}

//Méthodes
bool Kirin::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    double tmp = sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee));
    if (tmp == 1 || (tmp == sqrt(2) && (joueur == 1 && xDepart < xArrivee || joueur == 2 && xDepart > xArrivee)))
        return true;
    return false;
}
QString Kirin::getNom()
{
    return "Kirin";
}
void Kirin::pieceSelect(const bool select)
{
    if (select)
        setImage("data/kirinblanc.png");
    else
        setImage("data/kirin.png");
}
int Kirin::getValeur()
{
    return 5;
}
