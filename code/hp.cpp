/*****************************************************************************************
Icone blanche représentant un haut-parleur, passant en orange au survol d'une souris
Emett les signaux
    -clicked() : émis lorsqu'elle est cliquée
    -hovered()/nonHovered() : émis lorsque la souris survole/quitte l'image
    -volume() : utilisé lorsque le bouton a été cliqué, émet la nouvelle valeur du volume
Utilisée dans :
    -la classe Title
    -la classe Partie
*****************************************************************************************/


#include "hp.h"

//Mutateur
int Hp::getSon() const
{
    return son;
}

//Constructeur
Hp::Hp(QWidget* parent, int v) : QLabel(parent), son(v)
{
    this->setPixmap((QPixmap)("data/hp" + QString::number(v) +"_petit.png"));

    QObject::connect(this,SIGNAL(hovered()),this,SLOT(hoverMouse()));
    QObject::connect(this,SIGNAL(nonHovered()),this,SLOT(leaveHoverMouse()));
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(volumeChanged()));
}

//Slots & fonctions annexes
void Hp::hoverMouse()
{
    this->setPixmap((QPixmap)("data/hp" + QString::number(son) +"_petit_hover.png"));
    soundHover();
}
void Hp::leaveHoverMouse()
{
    this->setPixmap((QPixmap)("data/hp" + QString::number(son) +"_petit.png"));
}
void Hp::volumeChanged()
{
    son -= 1;
    if (son == -1)
        son = 3;
    this->setPixmap((QPixmap)("data/hp" + QString::number(son) +"_petit_hover.png"));
    emit volume(son);
}
void Hp::enterEvent(QEvent*)
{
    emit hovered();
}
void Hp::leaveEvent(QEvent*)
{
    emit nonHovered();
}
void Hp::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
void Hp::soundHover()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/deplacement.mp3"));
    if (son > 0)
        player->setVolume(20 + 20* son);
    else
        player->setVolume(0);
    player->play();
}
