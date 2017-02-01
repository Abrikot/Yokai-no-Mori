/***************************************************************************************************************
Classe gérant l'écran titre et le lancement d'une partie
Emet les signaux
    - endedMusic() : émis lorsque la musique est terminée
    - clicked() : émis lorsqu'un clic est effectué sur la fenêtre
    - keyPressed(QKeyEvent*) : émis lorsqu'une touche est enfoncée
    - konaPressed(QKeyEvent*) : émis lorsqu'une touche est enfoncée - gère l'Easter egg
****************************************************************************************************************/


#ifndef TITLE_H
#define TITLE_H

#include <QGraphicsOpacityEffect>

#include "partie.h"

class Title : public QLabel
{
    Q_OBJECT
private:
    HoverButton* b1;        //Lancer une partie 3x4
    HoverButton* b2;        //Lancer une partie 5x6
    QLabel* titre1;         //"Yokai"
    QLabel* titre2;         //"No"
    QLabel* titre3;         //"Mori"
    Hp* hp;                 //Icone servant à régler le son
    Partie* p;              //Pointeur sur la partie
    int taille;             //Taille de la partie qui sera lancée
    QMediaPlayer* player;   //Ambiance musicale
    int volume;             //Volume de la musique et des bruitages
    QTimer* timer;          //Timer pour les animations
    int nbT = 0;            //Nombre d'occurences pour les animations
    int nbKona = 0;         //Easter egg... ;)
    bool kona = false;      //Easter egg... ;)

    //Noms
    QLabel* question;       //Accueille la question "Quel le nom du Xème joueur ?"
    QLabel* lj;             //Accueille le nom des joueurs
    QString j1;             //Nom du joueur 1
    QString j2;             //Nom du joueur 2

    //Sélection du mode de jeu
    HoverButton* iaYes;     //Bouton "Jouer contre l'ordinateur"
    HoverButton* iaNo;      //Bouton "Joueur contre un autre joueur"

    //Transparence
    /*
     * Tous ces membres servent à gérer les animations -
     * notamment les apparitions et les disparitions des différents textes
     */
    QGraphicsOpacityEffect* go1;
    QGraphicsOpacityEffect* go2;
    QGraphicsOpacityEffect* goTitle1;
    QGraphicsOpacityEffect* goTitle2;
    QGraphicsOpacityEffect* goTitle3;
    QGraphicsOpacityEffect* goQuestion;
    QGraphicsOpacityEffect* goLj;
    QGraphicsOpacityEffect* goIaYes;
    QGraphicsOpacityEffect* goIaNo;

public:
    //Constructeur
    Title();

    //Destructeur
    ~Title();

    //Autres méthodes
    void dismiss();
    void agree();

    //Signaux, slots & autres méthodes
signals:
    void endedMusic();              //Emis lors de la fin de la musique
    void clicked();                 //Emis lors d'un clic dans la fenêtre
    void keyPressed(QKeyEvent*);    //Emis lorsqu'une touche est enfoncée
    void konaPressed(QKeyEvent*);   //Emis lorsqu'une touche est enfoncée
public slots:
    void firstButtonClicked();              //Méthode appelée lorsque le bouton "Jouer en 3x4" est cliqué
    void secondButtonClicked();             //Méthode appelée lorsque le bouton "Jouer en 5x6" est cliqué
    void iaYesClicked();                    //Méthode appelée lorsque le bouton "Jouer contre l'ordinateur" est cliqué
    void iaNoClicked();                     //Méthode appelée lorsque le bouton "Jouer contre un autre joueur" est cliqué
    void gameClosed();                      //Méthode gérant la fermeture de la fenêtre de jeu
    void replayGame();                      //Méthode gérant la relance d'une partie directement après la précédente
    void endMusic(QMediaPlayer::State);     //Méthode relançant la musique une fois celle-ci terminée
    void volumeChanged(int);                //Méthode appelée lorsque le volume des sons est changé

    /*************************************************************/
    /* Les méthodes suivantes permettent de créer des animations */
    /*************************************************************/
    void animatedTitle();
    void fadeOut();
    void fadeOutIaYes();
    void fadeOutIaNo();
    void fadeOutName();
    void fadeOutName2();
    void fadeInIa();
    void fadeIn();
    void fadeInName();

    void changedNameJ1(QKeyEvent*); //Méthode appelée lorsque le joueur entre le nom du premier joueur
    void changedNameJ2(QKeyEvent*); //Méthode appelée lorsque le joueur entre le nom du deuxième joueur
    void konaVerif(QKeyEvent*);     //Easter egg ;)
    void iaFailed();                //Easter egg ;)
    void finIaFailed();             //Easter egg ;)
protected:
    void mousePressEvent (QMouseEvent*);    //Méthode gérant les clics de souris
    void keyPressEvent(QKeyEvent*);         //Méthode gérant l'appui sur une touche
};

#endif // TITLE_H
