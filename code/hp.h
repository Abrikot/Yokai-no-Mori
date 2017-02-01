/*****************************************************************************************
Icone blanche représentant un haut-parleur, passant en orange au survol d'une souris
Emet les signaux :
    -clicked() : émis lorsqu'elle est cliquée
    -hovered()/nonHovered() : émis lorsque la souris survole/quitte l'image
    -volume() : utilisé lorsque le bouton a été cliqué, émet la nouvelle valeur du volume
Utilisée dans :
    -la classe Title
    -la classe Partie
*****************************************************************************************/


#ifndef HP_H
#define HP_H

#include <QLabel>
#include <QMediaPlayer>

class Hp : public QLabel
{
    Q_OBJECT
private:
    int son;    //Valeur du volume
public:
    //Mutateur
    int getSon() const;

    //Constructeur
    Hp(QWidget*, int = 3);  //Prend 2 paramètres : le widget parent et le volume actuel (par défaut à 3)

    //Signaux, slots & fonctions annexes
signals:
    void clicked();     //Emis lorsque l'image est cliquée
    void hovered();     //Emis au survol de l'image
    void nonHovered();  //Emis lorsque la souris quitte le survol de l'image
    void volume(int);   //Emis lorsque le volume est changé, après un clic sur l'image
public slots:
    void hoverMouse();          //Appelé lors d'un survol par la souris, change la couleur de l'image et crée un son
    void leaveHoverMouse();     //Appelé lorsque la souris ne survole plus l'image, restaure la couleur de l'image
    void volumeChanged();       //Appelé lors d'un clic sur l'image, change le volume
protected:
    void enterEvent(QEvent*);               //Fonction permettant de gérer le survol par la souris
    void leaveEvent(QEvent*);               //Fonction permettant de gérer la sortie du survol par la souris
    void mousePressEvent(QMouseEvent*);     //Fonction permettant de gérer le clic
    void soundHover();                      //Fonction permettant de jouer un son lors d'un survol
};

#endif // HP_H
