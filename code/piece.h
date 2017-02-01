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


#ifndef PIECE_H
#define PIECE_H

#include <QtWidgets>
#include <QTimer>

class Piece : public QLabel
{
    Q_OBJECT
protected:
    int joueur;                     //Numéro du joueur possédant la pièce
    int type;                       /*
                                    Type de la pièce :
                                    1 : Koropokkuru
                                    2 : Kitsune
                                    3 : Tanuki
                                    4 : Kodama
                                    5 : Kirin
                                    6 : Oni
                                    */
    int taille;                     //Taille du plateau
    bool selectionnee = false;      //Indique si la pièce est sélectionnée (fond blanc)

    //Timer & variables pour l'animation du déplacement d'une pièce
    QTimer* timer;  //Timer
    int nbT = 0;    //Numéro de l'occurence de l'animation
    int oldX = 0;   //Ancienne position en abscisse
    int oldY = 0;   //Ancienne position en ordonnée
    int newX = 0;   //Nouvelle position en abscisse
    int newY = 0;   //Nouvelle position en ordonnée
    int largeur;    //Largeur de l'image pièce
    int hauteur;    //Hauteur de l'image pièce

public:
    // Mutateurs
    void setJoueur(const int);
    void setTailleImage();
    void setSelectionnee(const bool=false);
    void setNewPlace(const int, const int);
    void setNewX(const int);
    void setNewY(const int);
    virtual void setTransforme(const bool);
    virtual void setImage(const QString) = 0;

    // Accesseurs
    int getJoueur() const;
    int getType() const;
    bool getSelectionnee() const;
    virtual bool getTransforme() const;

    // Constructeurs
    Piece(int, int, int); // Prends 3 paramètres : le numéro du joueur, le type de la pièce et la taille du plateau

    // Destructeur
    virtual ~Piece();

    // Méthodes virtuelles pures
    virtual bool deplacement(int, int, int, int) = 0;   //Indique si une pièce peut effectuer ou non un déplacement
    virtual QString getNom() = 0;                       //Renvoie le nom de la pièce
    virtual void pieceSelect(const bool) = 0;           //Change la couleur du fond de la pièce si elle est sélectionnée
    virtual int getValeur() = 0;                        //Renvoie la valeur de la pièce pour l'IA

    //Autre méthode
    virtual void testTransforme();  //Teste une transformation de pièce pour l'IA

    //Signaux, slots & méthodes associées
signals:
    void hovered();     //Emis lorsque la pièce est survolée
    void nonHovered();  //Emis lorsque la pièce n'est plus survolée
public slots:
    void updatePos();           //Animation du déplacement d'une pièce
    void hoverMouse();          //Méthode appelée lors du survol de la pièce par la souris
    void leaveHoverMouse();     //Méthode appelée lorsque la pièce n'est plus survolée par la souris
protected:
    void enterEvent(QEvent*);   //Méthode permettant de gérer le survol par la souris
    void leaveEvent(QEvent*);   //Méthode permettant de gérer la sortie du survol
};


#endif // PIECE_H
