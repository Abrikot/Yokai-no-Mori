/***********************************************
Classe permettant de gérer la pièce Koropokkuru
Hérite de la classe Piece
************************************************/


#include "koropokkuru.h"

//Mutateur
void Koropokkuru::setImage(const QString s)
{
    QPixmap tmp = (QPixmap)s;
    this->setPixmap(tmp);
    if (joueur == 1)
    {
        QTransform tr;
        this->setPixmap(this->pixmap()->transformed(tr.rotate(180)));
    }
}

//Constructeur
Koropokkuru::Koropokkuru(int j, int t, int a) : Piece(j,t,a)
{
    setImage("data/koropokkuru.png");
    this->setScaledContents(true);
}

//Méthodes
bool Koropokkuru::deplacement(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    double tmp = sqrt((xDepart - xArrivee) * (xDepart - xArrivee) + (yDepart - yArrivee) * (yDepart - yArrivee));
    if (tmp == 1 || tmp == sqrt(2))
        return true;
    return false;
}
QString Koropokkuru::getNom()
{
    return "Koropokkuru";
}
void Koropokkuru::pieceSelect(const bool select)
{
    if (select)
        setImage("data/koropokkurublanc.png");
    else
        setImage("data/koropokkuru.png");
    setTailleImage();
}
int Koropokkuru::getValeur()
{
    return 0;
}
