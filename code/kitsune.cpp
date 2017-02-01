/*******************************************
Classe permettant de gérer la pièce Kitsune
Hérite de la classe Piece
********************************************/

#include "kitsune.h"

//Mutateur
void Kitsune::setImage(const QString s)
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
Kitsune::Kitsune(int j, int t, int a) : Piece(j,t,a)
{
    setImage("data/kitsune.png");
    this->setScaledContents(true);
}

//Méthodes
bool Kitsune::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    double tmp = sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee));
    if (tmp == sqrt(2))
            return true;
    return false;
}
QString Kitsune::getNom()
{
    return "Kitsune";
}
void Kitsune::pieceSelect(const bool select)
{
    if (select)
        setImage("data/kitsuneblanc.png");
    else
        setImage("data/kitsune.png");
    setTailleImage();
}
int Kitsune::getValeur()
{
    return 3;
}
