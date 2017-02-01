/***************************************************************************************************************
Classe gérant une partie
Emet les signaux
    - clicked() : émis lorsqu'un clic est effectué sur la fenêtre
    - closed() : émis lors de la fermeture de la fenêtre
    - replayed() : émis lorsque le joueur clique sur "Rejouer"
    - iaFailed() : émis lorsque l'IA a perdu (Easter egg ;) )
    - finIaFailed() : émis lorsque le joueur clique sur "Rejouer" ou "Quitter" pour supprimer l'Easter egg ;)
    - konaPressed(QKeyEvent*) : émis lorsqu'une touche est enfoncée - gère l'Easter egg
Utilisée dans :
    -la classe Title
****************************************************************************************************************/


#ifndef PARTIE_H
#define PARTIE_H

#include "kirin.h"
#include "kitsune.h"
#include "kodama.h"
#include "koropokkuru.h"
#include "oni.h"
#include "tanuki.h"
#include "side.h"
#include "hp.h"
#include "hoverbutton.h"

#include <QCloseEvent>
#include <QMediaPlayer>
#include <QTimer>
#include <QMultiMap>

const char bg[] = "data\\Plateau YNM.jpg";

class Partie: public QLabel
{
    Q_OBJECT

protected:
    //Fonds
    QPixmap* fond = new QPixmap(bg);
    QLabel* darkback;

    //Eléments de jeu
    int lastJ = 1;              //Dernier joueur à avoir joué
    int taille;                 //Taille du plateau
    Piece*** plateau;           //Tableau accueillant les pièces
    int select[3] = {0,0,0};    //Indique si une case est déjà sélectionnée et donne ses coordonnées le cas échéant

    //Noms des joueurs
    QString j1;     //Nom du joueur 1
    QString j2;     //Nom du joueur 2
    QLabel* lj1;    //Zone de texte pour le nom du joueur 1
    QLabel* lj2;    //Zone de texte pour le nom du joueur 2

    //Réserves
    QVector <Piece*> r1;                    //Réserve du joueur 1
    QVector <Piece*> r2;                    //Réserve du joueur 2
    Side* fr1;                              //Fenêtre accueillant la réserve du joueur 1
    Side* fr2;                              //Fenêtre accueillant la réserve du joueur 2
    QVector <Piece*>* reserveParachute;     //Pointeur indiquant la réserve à utiliser pour un parachutage
    int indiceParachute;                    //Indice dans la réserve de la pièce à parachuter

    //Promotion
    QLabel* questionPromotion;  //Accueille le texte "Souhaitez-vous promouvoir votre pièce ?" en 5x6
    HoverButton* yes;           //Accueille le bouton "Oui"
    HoverButton* no;            //Accueille le bouton "Non"

    //Sons
    Hp* hp;                 //Boutons "Haut-parleur" permettant de régler le son
    int volume;             //Volume actuel
    int nbKona = 0;         //Easter egg... ;)
    bool kona = false;      //Easter egg... ;)

    //Timer
    QTimer* timer;          //Timer permettant de gérer les animations

    //Mise en échec
    QLabel* echec;          //Label recevant le texte "Attention !" lors d'une mise en échec

    //Fin de partie
    QLabel* endText;        //Label recevant les messages "a gagné !" ou "Match nul !" à la fin de la partie
    QLabel* gagne;          //Label recevant le nom du gagnant
    Piece* lastMoves[6];    //Tableau permettant de gérer le match nul lors d'une succession de 3 va-et-vient
    int nbLastMoves = 0;    //Nombre de coups sans mise en échec, parachutage ou prise de pièce
    HoverButton* replay;    //Bouton "Rejouer" à la fin de la partie
    HoverButton* exit;      //Bouton "Quitter" à la fin de la partie

    //Gestion de l'IA
    int ia;                                                         //Numéro du joueur contrôlé par l'IA
    QVector<pair<pair<int,int>,pair<int,int>>> choixPossibles;      //Liste des choix que l'IA pourrait faire
    pair<pair<int,int>,pair<int,int>> choisie;                      //Mouvement choisi parmi ceux possibles
    bool danger;                                                    //Booléen permettant de gérer le temps d'attente entre deux clics de l'IA lors d'une mise en échec

public:
    // Mutateurs
    void setVolume(const int);

    // Accesseurs
    Hp* getHp() const;
    HoverButton* getReplay() const;
    HoverButton* getExit() const;
    HoverButton* getYes() const;
    HoverButton* getNo() const;

    // Constructeur
    Partie(const QString, const QString, const int, const int);     //Prends 4 paramètres : les noms des jouers, la taille du plateau et le volume

    // Destructeur
    ~Partie();

    //Autres méthodes
    void addReserve(int, int, int);                     //Ajoute une pièce à la réserve
    void changerPlace(int,int,int,int);                 //Place la pièce présente en (xD,yD) sur la case (xA,yA)
    void promotion(int,int);                            //Promeut une pièce
    bool verifColKodama(int, int);                      //Vérifie qu'une colonne est libre pour un parachutage de Kodama (en 5x6)
    void movePlayed();                                  //Son lorsqu'un coup est joué
    void soundPromotion();                              //Son joué lors d'une promotion
    void endedGame(int);                                //Affiche la fin de la partie (fond noir + textes + boutons "Rejouer"/"Quitter)
    bool addLastMove(Piece*);                           //Ajoute le dernier coup à la liste des coups (en 3x4)
    pair <int,int> chess(int, int, int, bool = true);   //Renvoie la position de la première pièce mettant le Koropokkuru en échec, renvoie <-1,-1> s'il n'est pas en échec
    int chessAndMat();                                  //Vérifie si la position actuelle contient un mat
    bool posPossible(int,int,int);                      //Renvoie si un Koropokkuru en (x,y) appartenant au joueur joueur a une position possible autour de lui
    void verifSuivantPromo();                           //Effectue les vérifications de fin de tour (mat, pat, mise en échec)
    pair <int,int> rechercheKoro(int);                  //Renvoie la position du Koropokkuru appartenant au joueur joueur
    void miseEchec();                                   //Affiche le fond noir et le texte "Attention !"
    bool parachutageAutorise(int,int,int,int);          //Indique si un parachutage est autorisé
    void changerTailleLabelJ(int);                      //Change la taille d'écriture du nom du joueur j

    //Signaux, slots & méthodes associées
signals:
    void clicked();                 //Emis lorsq'un clic est effectué sur la partie
    void closed();                  //Emis lorsque la fenêtre est fermée
    void replayed();                //Emis lorsque le joueur clique sur "Rejouer"
    void iaFailed();                //Emis lorsque l'IA a perdu (Easter Egg ;))
    void finIaFailed();             //Emis lorsque l'IA a perdu et que le joueur clique sur "Rejouer" ou "Quitter" (Easter Egg ;))
    void konaPressed(QKeyEvent*);   //Emis lors de l'appui sur une touche (Easter Egg ;))

public slots:
    void slotClicked();                         //Méthode appelée lors du clic sur la fenêtre
    void parachutage(int, QVector<Piece*>*);    //Méthode appelée lors d'un parachutage, prenant en paramètre la position de la pièce dans la réserve ainsi qu'un pointeur sur cette réserve
    void promotionAcceptee();                   //Méthode appelée lorsqu'une promotion est acceptée
    void promotionRefusee();                    //Méthode appelée lorsqu'une promotion est refusée
    void finMiseEchec();                        //Méthode appelée pour faire disparaître le fond noir et le texte "Attention !"
    void replayEvent();                         //Méthode appelée lors du clic sur "Rejouer"

protected:
    void mousePressEvent(QMouseEvent*);     //Méthode émettant le signal clicked()
    void keyPressEvent(QKeyEvent*);         //Méthode émettant le signal konaPressed() (Easter egg ;))
    void closeEvent(QCloseEvent* event);    //Méthode émettant le signal close() permettant de fermer la fenêtre


    /*****************/
    /*Gestion de l'IA*/
    /*****************/
private:
    QVector <pair<int,int>> recherchePieces(int);                                                       //Recherche toutes les pièces appartenant au joueur joueur
    QVector<pair<pair<int,int>,pair<int,int>>> recherchePossibilites(QVector<pair<int,int>>, int);      //Recherche toutes les possibilités de déplacement des pièces listées précédemment et appartenant au joueur joueur
    void choix();                                                                                       //Effectue le choix du déplacement en fonction de divers critères
private slots:
    void choixPart1();  //Méthode appelée après le choix permettant de sélectionner la pièce à déplacer
    void choixPart2();  //Méthode appelée après choixPart1() permettant de sélectionner la case où la pièce doit être déplacée
};

#endif // PARTIE_H
