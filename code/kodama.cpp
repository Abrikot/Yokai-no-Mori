/******************************************
Classe permettant de gérer la pièce Kodama
Hérite de la classe Piece
*******************************************/


#include "kodama.h"

//Mutateurs
void Kodama::setTransforme(const bool t)
{
    transforme = t;
    if (!t)
        setImage("data/kodama.png");
    else
        setImage("data/kodamasamurai.png");
}
void Kodama::setImage(const QString s)
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
bool Kodama::getTransforme() const
{
    return transforme;
}

//Constructeurs
Kodama::Kodama(int j, int t, int a) : Piece(j,t,a)
{
    setTransforme(0);
    this->setScaledContents(true);
}

//Méthodes
bool Kodama::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    double tmp = sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee));
    if (transforme == 0)
        if (tmp == 1 && (joueur == 1 && xDepart < xArrivee || joueur == 2 && xDepart > xArrivee))
            return true;
    if (transforme == 1)
        if (tmp == 1 || (tmp == sqrt(2) && ((joueur == 1 && xDepart < xArrivee) || (joueur == 2 && xDepart > xArrivee))))
            return true;
    return false;
}
QString Kodama::getNom()
{
    return "Kodama";
}

void Kodama::pieceSelect(const bool select)
{
    if (transforme == 0)
    {
        if (select)
            setImage("data/kodamablanc.png");
        else
            setImage("data/kodama.png");
        setTailleImage();
    }
    else
    {
        if (select)
            setImage("data/kodamasamuraiblanc.png");
        else
            setImage("data/kodamasamurai.png");
        setTailleImage();
    }
}

int Kodama::getValeur()
{
    if (!transforme)
        return 1;
    else
        return 5;
}

void Kodama::testTransforme()
{
    transforme = !transforme;
}
