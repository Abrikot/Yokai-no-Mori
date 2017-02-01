/***************************************************************************************************************
Classe abstraite héritée par toutes les autres pièces
Emet les signaux
    - hovered() : émis lorsque la pièce est survolée
    - nonHovered() : émis lorsque la pièce n'est plus survolée
Utilisée dans :
    - la classe Partie
    - la classe Side
Héritée par :
    - la classe Kirin
    - la classe Kitsune
    - la classe Kodama
    - la classe Koropokkuru
    - la classe Oni
    - la classe Tanuki
****************************************************************************************************************/


#include "piece.h"

// Mutateurs
void Piece::setJoueur(const int j)
{
    if (j == 1 || j == 2)
        joueur = j;
}
void Piece::setTailleImage()
{
    this->setFixedSize(100 + 40 * (taille*(-1) + 2),100 + 40 * (taille*(-1) + 2));
}
void Piece::setSelectionnee(const bool s)
{
    selectionnee = s;
    this->pieceSelect(s);
}
void Piece::setNewPlace(const int x, const int y)
{
    nbT = 0;
    oldX = newX;
    oldY = newY;
    largeur = this->width();
    hauteur = this->height();
    if (taille == 1)
    {
        newX = 68 + x*160;
        newY = 140 + y*160;
    }
    else
    {
        newX = 30 + x*110;
        newY = 110 + y*115;
    }
    timer->blockSignals(false);
    this->setGeometry(oldX - ((oldX - newX)/20), oldY - ((oldY - newY)/20), largeur,hauteur);
    this->setVisible(true);
    this->raise();
    QObject::disconnect(this,SIGNAL(hovered()),this,SLOT(hoverMouse()));
    QObject::disconnect(this,SIGNAL(nonHovered()),this,SLOT(leaveHoverMouse()));
    timer->start(25);
}
void Piece::setNewX(const int x)
{
    newX = x;
}
void Piece::setNewY(const int y)
{
    newY = y;
}
void Piece::setTransforme(const bool)
{
}

// Accesseurs
int Piece::getJoueur() const
{
    return joueur;
}
int Piece::getType() const
{
    return type;
}
bool Piece::getSelectionnee() const
{
    return selectionnee;
}
bool Piece::getTransforme() const
{
    return false;
}

// Constructeur
Piece::Piece(int j, int t, int a) : joueur(j), type(t), taille(a), newX(0), newY(0)
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updatePos()));
    QObject::connect(this,SIGNAL(hovered()),this,SLOT(hoverMouse()));
    QObject::connect(this,SIGNAL(nonHovered()),this,SLOT(leaveHoverMouse()));
}

// Destructeur
Piece::~Piece()
{
    if (timer != NULL)
        delete timer;
}

//Autre méthode
void Piece::testTransforme()
{
}

//Slots & méthodes associées
void Piece::updatePos()
{
    nbT++;
    int tmp = 0.5*nbT*nbT - 10*nbT;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        this->setGeometry(newX, newY, this->width(),this->height());
        this->setFixedSize(100 + 40 * (taille*(-1) + 2),100 + 40 * (taille*(-1) + 2));
        QObject::connect(this,SIGNAL(hovered()),this,SLOT(hoverMouse()));
        QObject::connect(this,SIGNAL(nonHovered()),this,SLOT(leaveHoverMouse()));
    }
    else
    {
        timer->start(25);
        this->setGeometry(oldX - (oldX - newX)/20.0 * nbT, oldY - (oldY - newY)/20.0 * nbT,
                                      largeur - (tmp),hauteur - (tmp));
        this->setFixedSize(100 + 40 * (taille*(-1) + 2) - (tmp),100 + 40 * (taille*(-1) + 2) - (tmp));
    }
}
void Piece::enterEvent(QEvent*)
{
    emit hovered();
}
void Piece::leaveEvent(QEvent*)
{
    emit nonHovered();
}
void Piece::hoverMouse()
{
    this->pieceSelect(true);
}
void Piece::leaveHoverMouse()
{
    if (!selectionnee)
        this->pieceSelect(false);
}
