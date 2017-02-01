/***********************************************************************************
Texte blanc passant au orange lors d'un survol par la souris
Emette les signaux
    -hovered()/nonHovered() : émis lorsque la souris passe sur le texte/quitte le texte
    -clicked() : émis lorsqu'il est cliqué
Utilisé dans :
    -la classe Title (choix)
    -la classe Partie (promotion en 5x6, rejouer, quitter)
************************************************************************************/


#include "hoverbutton.h"

//Mutateur
void HoverButton::setVolume(const int v)
{
    if (volume < 4)
        volume = v;
}

//Constructeur
HoverButton::HoverButton(QString s, QWidget* parent, int tailleTexte, int v) : QLabel(parent), taille(tailleTexte)
{
    this->setStyleSheet("color : #FFFFFF; font-size : " + QString::number(tailleTexte) + "px; font-family : \"shanghai\";");
    this->setText(s);
    this->adjustSize();

    setVolume(v);

    QObject::connect(this,SIGNAL(hovered()),this,SLOT(hoverMouse()));
    QObject::connect(this,SIGNAL(nonHovered()),this,SLOT(leaveHoverMouse()));
}

//Slots & fonctions annexes
void HoverButton::hoverMouse()
{
    if (this->isEnabled())
        soundHover();
    this->setStyleSheet("color : #FF6600; font-size : " + QString::number(taille) + "px; font-family : \"shanghai\";");
}
void HoverButton::leaveHoverMouse()
{
    this->setStyleSheet("color : #FFFFFF; font-size : " + QString::number(taille) + "px; font-family : \"shanghai\";");
}
void HoverButton::enterEvent(QEvent*)
{
    emit hovered();
}
void HoverButton::leaveEvent(QEvent*)
{
    emit nonHovered();
}
void HoverButton::mousePressEvent(QMouseEvent*)
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/promotion.wav"));
    if (volume > 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
    emit clicked();
}
void HoverButton::soundHover()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/deplacement.mp3"));
    if (volume > 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
}
