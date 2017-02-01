/******************************************
Classe permettant de gérer la pièce Tanuki
Hérite de la classe Piece
*******************************************/


#include "tanuki.h"

//Mutateur
void Tanuki::setImage(const QString s)
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
Tanuki::Tanuki(int j, int t, int a) : Piece(j,t,a)
{
    setImage("data/tanuki.png");
    this->setScaledContents(true);
}

//Méthodes
bool Tanuki::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    if (sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee)) == 1)
        return true;
    return false;
}
QString Tanuki::getNom()
{
    return "Tanuki";
}
void Tanuki::pieceSelect(const bool select)
{
    if (select)
        setImage("data/tanukiblanc.png");
    else
        setImage("data/tanuki.png");
}
int Tanuki::getValeur()
{
    return 4;
}
