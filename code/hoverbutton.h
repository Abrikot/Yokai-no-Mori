/***********************************************************************************
Texte blanc passant au orange lors d'un survol par la souris
Emet les signaux :
    -hovered()/nonHovered() : émis lorsque la souris passe sur le texte/quitte le texte
    -clicked() : émis lorsqu'il est cliqué
Utilisé dans :
    -la classe Title (choix)
    -la classe Partie (promotion en 5x6, rejouer, quitter)
***********************************************************************************/


#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QMediaPlayer>

class HoverButton : public QLabel
{
    Q_OBJECT
private:
    int taille;     //Taille du texte, par défaut à 50px
    int volume;     //Volume des sons lors d'un survol ou d'un clic
public:
    //Mutateur
    void setVolume(const int);

    //Constructeur
    HoverButton(QString, QWidget*, int = 50, int = 3); //Prend 4 valeurs : le texte à afficher, le widget parent, la taille du texte et le volume du son lors d'un survol/clic

    //Signaux, slots & fonctions annexes
signals:
    void hovered();     //Emis lors d'un survol par la souris
    void nonHovered();  //Emis lorsque la souris ne survole plus le texte
    void clicked();     //Emis lors d'un clic
public slots:
    void hoverMouse();      //Slot appelé lors d'un survol par la souris
    void leaveHoverMouse(); //Slot appelé lorsque la souris ne survole plus le texte
protected:
    void enterEvent(QEvent*);               //Fonction permettant de gérer l'émission du signal hovered()
    void leaveEvent(QEvent*);               //Fonction permettant de gérer l'émission du signal nonHovered()
    void mousePressEvent(QMouseEvent*);     //Fonction permettant de gérer le clic
    void soundHover();                      //Gère le son lors d'un survol
};

#endif // HOVERBUTTON_H
