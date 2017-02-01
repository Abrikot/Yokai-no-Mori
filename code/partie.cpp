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


#include "partie.h"

// Mutateurs
void Partie::setVolume(const int v)
{
    volume = v;
}

//Accesseurs
Hp* Partie::getHp() const
{
    return hp;
}
HoverButton* Partie::getReplay() const
{
    return replay;
}
HoverButton* Partie::getExit() const
{
    return exit;
}
HoverButton* Partie::getYes() const
{
    return yes;
}
HoverButton* Partie::getNo() const
{
    return no;
}

// Constructeur
Partie::Partie(const QString s1, const QString s2, const int t, const int v) : j1(s1), j2(s2), taille(t), volume(v)
{
    //Définition de la fenêtre
    if (taille == 1)
        setPixmap(fond->copy(600,0,600,900)); //Chargement de l'image du plateau si le jeu est en 3x4
    else
        setPixmap(fond->copy(0,0,600,900)); //Chargement de l'image du plateau si le jeu est en 5x6
    setFixedSize(600,900);
    setGeometry(600,50,this->width(),this->height());
    this->setWindowTitle(QString("Yokaï no Mori ") + (QString)((taille == 1)?"3x4":"5x6") + " - Au tour de " + j2);
    setWindowIcon((QIcon)"data/koropokkuru.jpg");

    //Définition des éléments de jeu
    if (taille == 1) {
        //Initialisation du plateau 3x4
        plateau = new Piece**[4];
        for (int i = 0; i < 4; ++i)
            plateau[i] = new Piece*[3];

        //Création & affichage des pièeces
        plateau[0][0] = new Tanuki(1,3,1);
        plateau[0][1] = new Koropokkuru(1,1,1);
        plateau[0][2] = new Kitsune(1,2,1);
        plateau[1][1] = new Kodama(1,4,1);

        plateau[3][0] = new Kitsune(2,2,1);
        plateau[3][1] = new Koropokkuru(2,1,1);
        plateau[3][2] = new Tanuki(2,3,1);
        plateau[2][1] = new Kodama(2,4,1);

        plateau[1][0] = NULL;
        plateau[1][2] = NULL;
        plateau[2][0] = NULL;
        plateau[2][2] = NULL;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3;j++)
                if (plateau[i][j] != NULL){
                    plateau[i][j]->setTailleImage();
                    plateau[i][j]->setParent(this);
                    plateau[i][j]->setNewPlace(j,i);
                }
    }
    else
    {
        //Initialisation du plateau 5x6
        plateau = new Piece**[6];
        for (int i = 0; i < 6; ++i)
            plateau[i] = new Piece*[5];

        //Création & affichage des pièeces
        plateau[0][0] = new Oni(1,6,2);
        plateau[0][4] = new Oni(1,6,2);
        plateau[0][1] = new Kirin(1,5,2);
        plateau[0][3] = new Kirin(1,5,2);
        plateau[0][2] = new Koropokkuru(1,1,2);
        plateau[2][1] = new Kodama(1,4,2);
        plateau[2][2] = new Kodama(1,4,2);
        plateau[2][3] = new Kodama(1,4,2);

        plateau[5][0] = new Oni(2,6,2);
        plateau[5][4] = new Oni(2,6,2);
        plateau[5][1] = new Kirin(2,5,2);
        plateau[5][3] = new Kirin(2,5,2);
        plateau[5][2] = new Koropokkuru(2,1,2);
        plateau[3][1] = new Kodama(2,4,2);
        plateau[3][2] = new Kodama(2,4,2);
        plateau[3][3] = new Kodama(2,4,2);

        plateau[1][0] = NULL;
        plateau[1][1] = NULL;
        plateau[1][2] = NULL;
        plateau[1][3] = NULL;
        plateau[1][4] = NULL;

        plateau[2][0] = NULL;
        plateau[2][4] = NULL;

        plateau[3][0] = NULL;
        plateau[3][4] = NULL;

        plateau[4][0] = NULL;
        plateau[4][1] = NULL;
        plateau[4][2] = NULL;
        plateau[4][3] = NULL;
        plateau[4][4] = NULL;

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 5;j++)
            {
                if (plateau[i][j] != NULL)
                {
                    plateau[i][j]->setTailleImage();
                    plateau[i][j]->setParent(this);
                    plateau[i][j]->setNewPlace(j,i);
                }
            }
    }

    lj1 = new QLabel(this);
    lj1->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\"; font-size : 20px;");
    lj1->setText(j1);
    lj1->adjustSize();
    lj1->setGeometry(this->width() - lj1->width() - 20,(this->height() - lj1->height())/40,lj1->width(),lj1->height());

    lj2 = new QLabel(this);
    lj2->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\";font-size : 20px;");
    lj2->setText(j2);
    lj2->adjustSize();
    lj2->setGeometry(20,(this->height() - lj2->height())/40*39,lj2->width(),lj2->height());

    hp = new Hp(this,v);
    hp->setGeometry(460,820,25,25);

    darkback = new QLabel(this);
    darkback->setGeometry(0,0,600,900);
    darkback->setPixmap((QPixmap)"data/darkback.png");
    darkback->setVisible(false);

    questionPromotion = new QLabel(this);
    questionPromotion->setText("Souhaitez-vous promouvoir votre pièce ?");
    questionPromotion->setStyleSheet("color : #FFFFFF; font-size : 50px; font-family : \"shanghai\";");
    questionPromotion->setWordWrap(true);
    questionPromotion->adjustSize();
    questionPromotion->setGeometry(100,250,questionPromotion->width(),questionPromotion->height());
    questionPromotion->setVisible(false);

    yes = new HoverButton("Oui",this);
    yes->adjustSize();
    yes->setGeometry(100,550,yes->width(),yes->height());
    yes->setVisible(false);
    yes->setVolume(volume);
    no = new HoverButton("Non",this);
    no->adjustSize();
    no->setGeometry(400,550,no->width(),yes->height());
    no->setVisible(false);
    no->setVolume(volume);

    echec = new QLabel(this);
    echec->setStyleSheet("color : #FFFFFF; font-size : 100px; font-family : \"shanghai\";");
    echec->setText("Attention !");
    echec->adjustSize();
    echec->setGeometry((600-echec->width())/2,(900-echec->height())/2,echec->width(),echec->height());
    echec->setVisible(false);

    replay = new HoverButton("Rejouer", this);
    replay->adjustSize();
    replay->setGeometry((this->width() - replay->width())/6, (this->height() - replay->height())/5*4,replay->width(),replay->height());
    replay->setVisible(false);
    replay->setVolume(volume);

    exit = new HoverButton("Quitter", this);
    exit->adjustSize();
    exit->setGeometry((this->width() - replay->width())/6*5, (this->height() - replay->height())/5*4,replay->width(),replay->height());
    exit->setVisible(false);
    exit->setVolume(volume);

    timer = new QTimer(this);

    for (int i = 0 ; i < 6; i++)
        lastMoves[i] = NULL;

    this->show();

    //Création des réserves
    fr1 = new Side(this->x()-400,this->y()+30,j1, taille);
    fr2 = new Side(this->x()-400,this->y()+498,j2, taille);

    QObject::connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::connect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::connect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));

    setMouseTracking(true);

    this->activateWindow();

    this->changerTailleLabelJ(lastJ%2+1);

    if (j2.toLower() == "ia")
    {
        ia = 2;
        choixPossibles = recherchePossibilites(recherchePieces(ia),ia);
        choix();
    }
}

// Destructeur
Partie::~Partie()
{
    if (taille == 1)
    {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if (plateau[i][j] != NULL)
                    delete plateau[i][j];
            }
            delete []plateau[i];
        }
        delete []plateau;
    }
    else
    {
        for(int i = 0; i < 6; ++i)
        {
            for(int j = 0; j < 5; ++j)
                if (plateau[i][j] != NULL)
                    delete plateau[i][j];
            delete []plateau[i];
        }
        delete []plateau;
    }


    for (int i = 0; i < r1.size();i++)
        delete r1[i];
    for (int i = 0; i < r2.size();i++)
        delete r2[i];

    if (timer != NULL)
        delete timer;
    if (darkback != NULL)
        delete darkback;
    if (questionPromotion != NULL)
        delete questionPromotion;
    if (yes != NULL)
        delete yes;
    if (no != NULL)
        delete no;
    if (hp != NULL)
        delete hp;
    if (echec != NULL)
        delete echec;
}

//Autres méthodes
void Partie::addReserve(int x, int y, int j)
{
    plateau[x][y]->setTransforme(0);
    plateau[x][y]->setJoueur(plateau[x][y]->getJoueur()%2+1);
    QTransform tr;
    plateau[x][y]->setPixmap(plateau[x][y]->pixmap()->transformed(tr.rotate(180)));
    if (j == 1)
    {
        plateau[x][y]->setNewX(600);
        plateau[x][y]->setNewY(0);
        r1.push_back(plateau[x][y]);
        plateau[x][y] = NULL;
        fr1->displaySide(r1);
    }
    else
    {
        plateau[x][y]->setNewX(0);
        plateau[x][y]->setNewY(900);
        r2.push_back(plateau[x][y]);
        plateau[x][y] = NULL;
        fr2->displaySide(r2);
    }
}
void Partie::changerPlace(int xD,int yD,int xA,int yA)
{
    plateau[xA][yA] = plateau[xD][yD];
    plateau[xA][yA]->setNewPlace(yA,xA);
    plateau[xD][yD] = NULL;
}
void Partie::promotion(int xPoint, int yPoint)
{
    if ((plateau[xPoint][yPoint]->getType() == 4 || plateau[xPoint][yPoint]->getType() == 6) && plateau[xPoint][yPoint]->getTransforme() == 0)
    {
        if (taille == 1)
        {
            if (plateau[xPoint][yPoint]->getJoueur() == 1 && xPoint == 3 ||
                    plateau[xPoint][yPoint]->getJoueur() == 2 && xPoint == 0)
            {
                plateau[xPoint][yPoint]->setTransforme(1);
                plateau[xPoint][yPoint]->setTailleImage();
                soundPromotion();
            }
            verifSuivantPromo();
        }
        else
        {
            if (plateau[xPoint][yPoint]->getJoueur() == 1 && (xPoint == 4 || xPoint == 5) ||
                    plateau[xPoint][yPoint]->getJoueur() == 2 && (xPoint == 0 || xPoint == 1))
            {
                if ((plateau[xPoint][yPoint]->getType() == 6 ||
                     (plateau[xPoint][yPoint]->getType() == 4 && (plateau[xPoint][yPoint]->getJoueur() == 1 && xPoint == 4 || plateau[xPoint][yPoint]->getJoueur() == 2 && xPoint == 1)))
                        && ((plateau[xPoint][yPoint]->getJoueur() == 1)?(j1.toLower()!="ia"):(j2.toLower()!="ia")))
                {
                    select[1] = xPoint;
                    select[2] = yPoint;

                    QObject::disconnect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
                    QObject::disconnect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
                    QObject::disconnect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));

                    darkback->raise();
                    questionPromotion->raise();
                    yes->raise();
                    no->raise();
                    darkback->setVisible(true);
                    questionPromotion->setVisible(true);
                    yes->setVisible(true);
                    no->setVisible(true);

                    QObject::connect(yes,SIGNAL(clicked()),this,SLOT(promotionAcceptee()));
                    QObject::connect(no,SIGNAL(clicked()),this,SLOT(promotionRefusee()));
                }
                else
                {
                    plateau[xPoint][yPoint]->setTransforme(1);
                    plateau[xPoint][yPoint]->setTailleImage();
                    soundPromotion();
                    verifSuivantPromo();
                }
            }
            else
                verifSuivantPromo();
        }
    }
    else
        verifSuivantPromo();
}
bool Partie::verifColKodama(int col, int joueur)
{
    for(int i = 0; i < 6; i++)
    {
        if (plateau[i][col] != NULL && plateau[i][col]->getJoueur() == joueur && plateau[i][col]->getType() == 4)
        {
            if (plateau[i][col]->getTransforme() == 0)
                return false;
        }
    }
    return true;
}
void Partie::movePlayed()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/deplacement.mp3"));
    if (volume > 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
}
void Partie::soundPromotion()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/promotion.wav"));
    if (volume > 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
}
void Partie::endedGame(int j)
{
    QString nomGagnant = (j == 1 ? j1 : j2);

    if ((j == 1 && j2 == "IA") || (j == 2 && j1 == "IA"))
        emit iaFailed();

    QObject::disconnect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::disconnect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::disconnect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));

    darkback->raise();
    darkback->setVisible(true);

    endText = new QLabel(this);
    endText->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\"; font-size : 100px; font-weight : bold;");

    gagne = new QLabel(this);
    gagne->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\"; font-size : 80px;");

    if (j == 1 || j == 2)
    {
        endText->setText(nomGagnant);
        endText->adjustSize();
        endText->setGeometry((this->width() - endText->width())/2,250,600,300);
        endText->setVisible(true);
        gagne->setText("a gagné !");
        gagne->adjustSize();
        gagne->setGeometry((this->width() - gagne->width())/2,450,600,200);
    }
    else
    {
        QString tmp = QString("Yokaï no Mori ") + (QString)((taille == 1)?"3x4":"5x6") + " - Match nul ";
        this->setWindowTitle(tmp);
        gagne->setText("Match nul !");
        gagne->adjustSize();
        gagne->setGeometry((this->width() - gagne->width())/2,350,600,200);
    }
    gagne->setVisible(true);

    replay->setVisible(true);
    exit->setVisible(true);
    replay->raise();
    exit->raise();

    QObject::connect(replay,SIGNAL(clicked()),this,SLOT(replayEvent()));
    QObject::connect(exit,SIGNAL(clicked()),this,SLOT(close()));
}
bool Partie::addLastMove(Piece* p)
{
    if (nbLastMoves < 6)
    {
        if (nbLastMoves != -1)
            lastMoves[nbLastMoves] = p;
        nbLastMoves++;
    }
    else
    {
        for (int i = 1; i < 6; i++)
            lastMoves[i-1] = lastMoves[i];
        lastMoves[5] = p;
    }

    if (nbLastMoves == 6)
    {
        if (lastMoves[0] == lastMoves[2] && lastMoves[0] == lastMoves[4] &&
                lastMoves[1] == lastMoves[3] && lastMoves[1] == lastMoves[5])
        {
            endedGame(0);
            return true;
        }
    }
    return false;
}
pair<int,int> Partie::chess(int xPoint, int yPoint, int joueur, bool koro)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (taille == 1 &&
                    (xPoint + i > -1 && xPoint + i < 4 &&
                     yPoint + j > -1 && yPoint + j < 3) ||
                    taille == 2 &&
                    (xPoint + i > -1 && xPoint + i < 6 &&
                     yPoint + j > -1 && yPoint + j < 5))
                if (plateau[xPoint + i][yPoint + j] != NULL &&
                        plateau[xPoint + i][yPoint + j]->getJoueur() != joueur &&
                        plateau[xPoint + i][yPoint + j]->deplacement(xPoint + i,yPoint + j, xPoint, yPoint))
                {
                    if (koro ||
                            !koro && plateau[xPoint + i][yPoint + j]->getType()!= 1)
                        return make_pair(xPoint+i,yPoint+j);
                }
        }
    }
    return make_pair(-1,-1);
}
int Partie::chessAndMat()
{
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;
    int x1, y1, x2, y2;

    /*  Récupération des positions des 2 Koropokkurus  */
    for (int i = 0; i < tailleX; i++)
        for (int j = 0; j < tailleY; j++)
        {
            if (plateau[i][j] != NULL && plateau[i][j]->getType() == 1)
            {
                if (plateau[i][j]->getJoueur() == 1)
                {
                    x1 = i;
                    y1 = j;
                }
                if (plateau[i][j]->getJoueur() == 2)
                {
                    x2 = i;
                    y2 = j;
                }
            }
        }


    /* Test de la mise en échec de ceux-ci  */
    int xP1, yP1, xP2, yP2;
    xP1 = (chess(x1,y1,plateau[x1][y1]->getJoueur())).first;
    yP1 = (chess(x1,y1,plateau[x1][y1]->getJoueur())).second;
    xP2 = (chess(x2,y2,plateau[x2][y2]->getJoueur())).first;
    yP2 = (chess(x2,y2,plateau[x2][y2]->getJoueur())).second;

    if ( xP1 == -1 && xP2 == -1) //Si aucun des deux Koropokkurus n'est mis en échec
    {
        return 0;
    }
    else
    {
        if (xP1 != -1)
        {
            if(!(posPossible(x1,y1,1) || (chess(xP1,yP1,2,false)).first != -1))
                return 1;
        }
        if (xP2 != -1)
        {
            if(!(posPossible(x2,y2,2) || (chess(xP2,yP2,1,false)).first != -1))
                return 2;
        }
        return 0;
    }
}
bool Partie::posPossible(int x, int y, int joueur)
{
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;
    for (int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++)
        {
            if (x + i > -1 && x + i < tailleX && y + j > -1 && y + j < tailleY)
            {
                if ((plateau[x + i][y + j] != NULL && plateau[x + i][y + j]->getJoueur() != joueur) ||
                        plateau[x + i][y + j] == NULL)
                {
                    if ((chess(x+i,y+j,joueur)).first == -1)
                        return true;
                }
            }
        }
    return false;
}
void Partie::verifSuivantPromo()
{
    int x,y, fin = false;
    int verifMat = chessAndMat();

    //Vérification de la mise en échec et mat
    if (verifMat)
    {
        verifMat = verifMat%2+1;
        endedGame(verifMat);
        QString tmp;
        tmp = QString("Yokaï no Mori ") + (QString)((taille == 1)?"3x4":"5x6") + " - " + ((verifMat == 1)?j1:j2) + " a gagné !";
        this->setWindowTitle(tmp);
        fin = true;
    }
    else
    {
        //Vérification de la situation de pat
        if (!fin)
        {
            int joueur = lastJ%2+1;

            if ((joueur == 1 && r1.size() == 0) ||
                    (joueur == 2 && r2.size() == 0))
            {
                bool seul = true;
                int xKoro = rechercheKoro(joueur).first;
                int yKoro = rechercheKoro(joueur).second;

                int tailleX = (taille == 1)?4:6;
                int tailleY = (taille == 1)?3:5;

                for (int i = 0; i < tailleX; i++)
                    for (int j = 0; j < tailleY; j++)
                        if (plateau[i][j] != NULL && plateau[i][j]->getType() != 1 && plateau[i][j]->getJoueur() == joueur)
                            seul = false;
                if (seul)
                {
                    if(!posPossible(xKoro,yKoro,joueur))
                    {
                        endedGame(lastJ);
                        fin = true;
                    }
                }
            }
        }

        if (!fin)
        {
            danger = false;
            x = rechercheKoro(1).first;
            y = rechercheKoro(1).second;
            if ((chess(x,y,1)).first != -1)
            {
                miseEchec();
                danger = true;
            }

            x = rechercheKoro(2).first;
            y = rechercheKoro(2).second;
            if ((chess(x,y,2)).first != -1)
            {
                miseEchec();
                danger = true;
            }

            if ((lastJ == 1 && j2.toLower() == "ia") || (lastJ == 2 && j1.toLower() == "ia" ))
            {
                choixPossibles.clear();
                ia = lastJ%2+1;
                choixPossibles = recherchePossibilites(recherchePieces(ia),ia);
                choix();
            }
        }
    }
}
pair <int,int> Partie::rechercheKoro(int joueur)
{
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;
    for (int i = 0; i < tailleX; i++)
        for (int j = 0 ; j < tailleY; j++)
            if (plateau[i][j] != NULL && plateau[i][j]->getType() == 1 && plateau[i][j]->getJoueur() == joueur)
                return make_pair(i,j);
    return make_pair(-1,-1);
}
void Partie::miseEchec()
{
    QObject::disconnect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::disconnect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::disconnect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(finMiseEchec()));
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(finMiseEchec()));

    darkback->setVisible(true);
    darkback->raise();
    echec->setVisible(true);
    echec->raise();
    timer->start(1000);
}
bool Partie::parachutageAutorise(int joueur, int place, int xPoint, int yPoint)
{
    if (plateau[xPoint][yPoint] != NULL)
        return false;
    if (joueur == 1)
    {
        if (r1[place]->getType() != 4 || taille == 1)
            return true;
        else
        {
            if (xPoint == 5)
                return false;
            if (!verifColKodama(yPoint,1))
            {
                return false;
            }
            plateau[xPoint][yPoint] = r1[place];
            if (chessAndMat())
            {
                plateau[xPoint][yPoint] = NULL;
                return false;
            }
            plateau[xPoint][yPoint] = NULL;
        }
    }
    else
    {
        if (r2[place]->getType() != 4 || taille == 1)
            return true;
        else
        {
            if (xPoint == 0)
                return false;
            if (!verifColKodama(yPoint,2))
            {
                return false;
            }
            plateau[xPoint][yPoint] = r2[place];
            if (chessAndMat())
            {
                plateau[xPoint][yPoint] = NULL;
                return false;
            }
            plateau[xPoint][yPoint] = NULL;
        }
    }
    return true;
}
void Partie::changerTailleLabelJ(int j)
{
    if (j == 1)
    {
        lj1->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\";font-size : 30px;");
        lj1->adjustSize();
        lj1->setGeometry(this->width() - lj1->width() - 20,(this->height() - lj1->height())/40,lj1->width(),lj1->height());

        lj2->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\";font-size : 20px;");
        lj2->adjustSize();
        lj2->setGeometry(20,(this->height() - lj2->height())/40*39,lj2->width(),lj2->height());
    }
    else
    {
        lj1->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\";font-size : 20px;");
        lj1->adjustSize();
        lj1->setGeometry(this->width() - lj1->width() - 20,(this->height() - lj1->height())/40,lj1->width(),lj1->height());

        lj2->setStyleSheet("color : #FFFFFF; font-family : \"shanghai\";font-size : 30px;");
        lj2->adjustSize();
        lj2->setGeometry(20,(this->height() - lj2->height())/40*39,lj2->width(),lj2->height());
    }
}

//Signaux, slots et méthodes associées
void Partie::slotClicked()
{
    // Récupération de la case pointée
    int xPoint, yPoint;

    if (taille == 1){
        if (cursor().pos().y() - this->pos().y() > 160 && cursor().pos().y() - this->pos().y() < 800 && // Vérifie que le curseur est bien dans une zone du plateau et non sur les côtés
                cursor().pos().x() - this->pos().x() > 68 && cursor().pos().x() - this->pos().x() < 548)
        {
            xPoint = ((cursor().pos().y() - this->pos().y())-160)/160;
            yPoint = ((cursor().pos().x() - this->pos().x())-68)/160;
        }
        else
        {
            xPoint = -1;
            yPoint = -1;
        }
    }
    else
    {
        if (cursor().pos().y() - this->pos().y() > 137 && cursor().pos().y() - this->pos().y() < 827 && // Vérifie que le curseur est bien dans une zone du plateau et non sur les côtés
                cursor().pos().x() - this->pos().x() > 30 && cursor().pos().x() - this->pos().x() < 580)
        {
            xPoint = ((cursor().pos().y() - this->pos().y())-137)/115;
            yPoint = ((cursor().pos().x() - this->pos().x())-30)/110;

        }
        else
        {
            xPoint = -1;
            yPoint = -1;

        }
    }

    // Tests de sélection et de déplacement
    if (select[0] == 2) //Tests pour les parachutages
    {
        if ((xPoint != -1 || yPoint != -1) && parachutageAutorise((*reserveParachute)[indiceParachute]->getJoueur(),indiceParachute,xPoint,yPoint))
        {
            plateau[xPoint][yPoint] = (*reserveParachute)[indiceParachute];
            plateau[xPoint][yPoint]->setParent(this);
            plateau[xPoint][yPoint]->setVisible(false);
            plateau[xPoint][yPoint]->setSelectionnee(false);
            plateau[xPoint][yPoint]->setNewPlace(yPoint,xPoint);

            QVector<Piece*>::iterator it = reserveParachute->begin() + indiceParachute;
            reserveParachute->erase(it);

            if (reserveParachute == &r1)
            {
                fr1->displaySide(r1);
            }
            else
            {
                fr2->displaySide(r2);
            }

            this->changerTailleLabelJ(lastJ);
            lastJ = (lastJ) % 2 + 1;
            if (lastJ == 1)
            {
                fr1->setSelect(-1);
                fr2->setSelect(0);
            }
            else
            {
                fr1->setSelect(0);
                fr2->setSelect(-1);
            }
            QApplication::restoreOverrideCursor();
            select[0] = 0;
            nbLastMoves = 0;

            verifSuivantPromo();
        }
        else
        {
            QApplication::restoreOverrideCursor();
            (fr1->getSelect() == -1)?fr2->setSelect(0):fr1->setSelect(0);
            select[0] = 0;
            (*reserveParachute)[indiceParachute]->setSelectionnee(false);
        }
        movePlayed();
    }
    else
    {
        if (select[0] == 0)
        {
            if (xPoint != -1 && yPoint != -1 &&
                    plateau[xPoint][yPoint] != NULL && plateau[xPoint][yPoint]->getJoueur() != lastJ &&
                    fr1->getSelect() != 1 && fr2->getSelect() != 1)
            {
                select[0] = 1;
                select[1] = xPoint;
                select[2] = yPoint;
                plateau[xPoint][yPoint]->setSelectionnee(true);

                fr1->setSelect(-1);
                fr2->setSelect(-1);

                QApplication::setOverrideCursor(Qt::CrossCursor);
            }
        }
        else
        {
            bool autorise = true;
            QApplication::restoreOverrideCursor();
            if (((taille == 1 &&
                  (xPoint < 4 && yPoint < 3)) ||
                 (taille == 2 &&
                  (xPoint < 6 && yPoint < 5))) &&
                    (xPoint != select[1] || yPoint != select[2]) &&
                    plateau[select[1]][select[2]]->deplacement(select[1],select[2],xPoint,yPoint))
            {
                int xKoro = rechercheKoro(plateau[select[1]][select[2]]->getJoueur()).first;
                int yKoro = rechercheKoro(plateau[select[1]][select[2]]->getJoueur()).second;

                Piece* tmp = plateau[xPoint][yPoint];
                plateau[xPoint][yPoint] = plateau[select[1]][select[2]];
                plateau[select[1]][select[2]] = NULL;

                if (select[1] != xKoro || select[2] != yKoro)
                {
                    if ((chess(xKoro,yKoro,plateau[xKoro][yKoro]->getJoueur())).first != -1)
                        autorise = false;
                }
                else
                {
                    if ((chess(xPoint,yPoint,plateau[xPoint][yPoint]->getJoueur())).first != -1)
                        autorise = false;
                }

                plateau[select[1]][select[2]] = plateau[xPoint][yPoint];
                plateau[xPoint][yPoint] = tmp;
                tmp = NULL;

                if (autorise &&
                        (plateau[xPoint][yPoint] == NULL ||
                         (plateau[xPoint][yPoint] != NULL && plateau[xPoint][yPoint]->getJoueur() != plateau[select[1]][select[2]]->getJoueur())))
                {
                    if (plateau[xPoint][yPoint] != NULL)
                    {
                        addReserve(xPoint,yPoint,plateau[select[1]][select[2]]->getJoueur());
                        nbLastMoves = -1;
                    }

                    plateau[select[1]][select[2]]->setSelectionnee(false);

                    // Déplace la pièce
                    changerPlace(select[1],select[2],xPoint,yPoint);
                    this->changerTailleLabelJ(lastJ);
                    lastJ = (lastJ) % 2 + 1;
                    if (lastJ == 1)
                    {
                        fr1->setSelect(-1);
                        fr2->setSelect(0);
                        QString tmp = QString("Yokaï no Mori ") + (QString)((taille == 1)?"3x4":"5x6") + " - Au tour de " + j2;
                        this->setWindowTitle(tmp);
                    }
                    else
                    {
                        fr1->setSelect(0);
                        fr2->setSelect(-1);
                        QString tmp = QString("Yokaï no Mori ") + (QString)((taille == 1)?"3x4":"5x6") + " - Au tour de " + j1;
                        this->setWindowTitle(tmp);
                    }
                    select[0] = 0;
                    movePlayed();


                    int joueur = plateau[xPoint][yPoint]->getJoueur();
                    bool fin = addLastMove(plateau[xPoint][yPoint]);

                    //Vérification de l'arrivée du Koropokkuru sur la dernière ligne(3x4)
                    if (!fin &&
                            taille == 1 &&
                            plateau[xPoint][yPoint] != NULL &&
                            plateau[xPoint][yPoint]->getType() == 1 &&
                            ((joueur == 1 && xPoint == 3) ||
                             (joueur == 2 && xPoint == 0)))
                    {
                        endedGame(plateau[xPoint][yPoint]->getJoueur());
                        fin = true;
                    }

                    //Vérification de la promotion
                    if (!fin)
                        promotion(xPoint, yPoint);
                }
                else
                {
                    plateau[select[1]][select[2]]->setSelectionnee(false);
                    if (lastJ == 1)
                    {
                        fr1->setSelect(-1);
                        fr2->setSelect(0);
                    }
                    else
                    {
                        fr1->setSelect(0);
                        fr2->setSelect(-1);
                    }
                    select[0] = 0;
                    movePlayed();
                }
            }
            else
            {
                plateau[select[1]][select[2]]->setSelectionnee(false);
                if (lastJ == 1)
                {
                    fr1->setSelect(-1);
                    fr2->setSelect(0);
                }
                else
                {
                    fr1->setSelect(0);
                    fr2->setSelect(-1);
                }
                select[0] = 0;
                movePlayed();
            }
        }
    }
}
void Partie::parachutage(int place, QVector<Piece*>* reserve)
{
    reserveParachute = reserve;
    indiceParachute = place;
    if (place != -1)
        select[0] = 2;
    else
        select[0] = 0;
}
void Partie::promotionAcceptee()
{
    plateau[select[1]][select[2]]->setTransforme(1);
    plateau[select[1]][select[2]]->setTailleImage();
    soundPromotion();
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::connect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::connect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    darkback->setVisible(false);
    questionPromotion->setVisible(false);
    yes->setVisible(false);
    no->setVisible(false);
    QObject::disconnect(yes,SIGNAL(clicked()),this,SLOT(promotionAcceptee()));
    QObject::disconnect(no,SIGNAL(clicked()),this,SLOT(promotionRefusee()));
    verifSuivantPromo();
}
void Partie::promotionRefusee()
{
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::connect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::connect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    darkback->setVisible(false);
    questionPromotion->setVisible(false);
    yes->setVisible(false);
    no->setVisible(false);
    QObject::disconnect(yes,SIGNAL(clicked()),this,SLOT(promotionAcceptee()));
    QObject::disconnect(no,SIGNAL(clicked()),this,SLOT(promotionRefusee()));
    verifSuivantPromo();
}
void Partie::finMiseEchec()
{
    QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(finMiseEchec()));
    QObject::disconnect(this,SIGNAL(clicked()),this,SLOT(finMiseEchec()));

    darkback->setVisible(false);
    echec->setVisible(false);

    QObject::connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
    QObject::connect(fr1,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
    QObject::connect(fr2,SIGNAL(parachutSelect(int, QVector<Piece*>*)),this,SLOT(parachutage(int, QVector<Piece*>*)));
}
void Partie::replayEvent()
{
    delete fr1;
    delete fr2;
    emit finIaFailed();
    emit replayed();
}
void Partie::mousePressEvent (QMouseEvent*)
{
    emit clicked();
}
void Partie::keyPressEvent(QKeyEvent * k)
{
    emit konaPressed(k);
}
void Partie::closeEvent(QCloseEvent*)
{
    delete fr1;
    delete fr2;
    emit finIaFailed();
    emit closed();
}

/*****************/
/*Gestion de l'IA*/
/*****************/
QVector <pair<int,int>> Partie::recherchePieces(int joueur)
{
    QVector<pair<int,int>> posPiece;
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;

    for (int i = 0; i < tailleX; i++)
    {
        for (int j = 0; j < tailleY;j++)
        {
            if (plateau[i][j] != NULL && plateau[i][j]->getJoueur() == joueur)
            {
                posPiece.push_back(make_pair(i,j));
            }
        }
    }
    return posPiece;
}
QVector<pair<pair<int,int>,pair<int,int>>> Partie::recherchePossibilites(QVector<pair<int,int>> posPiece, int joueur)
{
    QVector<pair<pair<int,int>,pair<int,int>>> liste;
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;
    QVector<pair<int,int>>::const_iterator pieceTest = posPiece.begin();
    pair <int,int> posKoro = rechercheKoro(joueur);

    //Recherche des possibilités avec les pièces sur le plateau
    for(;pieceTest < posPiece.end();pieceTest++)
    {
        int xTest = pieceTest->first;
        int yTest = pieceTest->second;

        for(int i = -1; i < 2; i++)
        {
            for(int j = -1; j < 2; j++)
            {
                if (xTest + i > -1 && xTest + i < tailleX && yTest + j > -1 && yTest + j < tailleY && (i != 0 || j != 0))
                {
                    if ((plateau[xTest+i][yTest+j] != NULL && plateau[xTest+i][yTest+j]->getJoueur() != joueur) ||
                            (plateau[xTest+i][yTest+j] == NULL))
                    {
                        if (plateau[xTest][yTest]->getType() != 1)
                        {
                            if (plateau[xTest][yTest]->deplacement(xTest,yTest,xTest+i,yTest+j))
                            {
                                Piece* tmp = plateau[xTest + i][yTest + j];
                                plateau[xTest + i][yTest + j] = plateau[xTest][yTest];
                                plateau[xTest][yTest] = NULL;

                                if (chess(posKoro.first,posKoro.second,joueur).first == -1)
                                {
                                    liste.push_back(make_pair(make_pair(xTest,yTest),make_pair(xTest+i,yTest+j)));
                                }

                                plateau[xTest][yTest] = plateau[xTest + i][yTest + j];
                                plateau[xTest + i][yTest + j] = tmp;
                                tmp = NULL;
                            }
                        }
                        else
                        {
                            if(chess(xTest+i,yTest+j,plateau[xTest][yTest]->getJoueur()).first == -1 && plateau[xTest][yTest]->deplacement(xTest,yTest,xTest+i,yTest+j))
                            {
                                liste.push_back(make_pair(make_pair(xTest,yTest),make_pair(xTest+i,yTest+j)));
                            }
                        }
                    }
                }
            }
        }
    }

    //Recherche des possibilités avec les pièces dans la réserve
    if (joueur == 1)
    {
        for (int i = 0; i < r1.size(); i++)
        {
            for (int j = 0; j < tailleX; j++)
            {
                for (int k = 0; k < tailleY; k++)
                {
                    if (plateau[j][k] == NULL && parachutageAutorise(1,i,j,k))
                    {
                        plateau[j][k] = r1[i];
                        if (chess(posKoro.first,posKoro.second,joueur).first == -1)
                        {
                            liste.push_back(make_pair(make_pair(-1,i),make_pair(j,k)));
                        }
                        plateau[j][k] = NULL;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < r2.size(); i++)
        {
            for (int j = 0; j < tailleX; j++)
            {
                for (int k = 0; k < tailleY; k++)
                {
                    if (plateau[j][k] == NULL && parachutageAutorise(2,i,j,k))
                    {
                        plateau[j][k] = r2[i];
                        if (chess(posKoro.first,posKoro.second,joueur).first == -1)
                        {
                            liste.push_back(make_pair(make_pair(-2,i),make_pair(j,k)));
                        }
                        plateau[j][k] = NULL;
                    }
                }
            }
        }
    }
    return liste;
}
void Partie::choix()
{
    int tailleX = (taille == 1)?4:6;
    int tailleY = (taille == 1)?3:5;

    QMultiMap<int,pair<pair<int,int>,pair<int,int>>> triChoix ;

    QVector <Piece*> attaquantes;
    QVector <Piece*> protectrices;
    QVector <pair<Piece*,pair<int,int>>> attaque;

    /*Cases attaquées par l'adversaire*/
    QVector<pair<int,int>> listePiecesAdverses = recherchePieces(ia%2+1);
    bool **casesAttaquees = new bool*[tailleX];
    for (int i = 0; i < tailleX; i++)
        casesAttaquees[i] = new bool[tailleY];

    for (int i = 0; i < tailleX; i++)
    {
        for(int j = 0; j < tailleY; j++)
            casesAttaquees[i][j] = false;
    }
    for (int i = 0; i < listePiecesAdverses.size(); i++)
    {
        for(int j = -1; j < 2; j++)
        {
            for(int k = -1; k < 2; k++)
            {
                if (listePiecesAdverses[i].first + j > -1 && listePiecesAdverses[i].first + j < tailleX
                        && listePiecesAdverses[i].second + k > -1 && listePiecesAdverses[i].second + k < tailleY)
                {
                    if (plateau[listePiecesAdverses[i].first][listePiecesAdverses[i].second]->deplacement(listePiecesAdverses[i].first, listePiecesAdverses[i].second, listePiecesAdverses[i].first + j, listePiecesAdverses[i].second + k))
                        casesAttaquees[listePiecesAdverses[i].first + j][listePiecesAdverses[i].second + k] = true;
                }
            }
        }
    }


    for(int coup = 0; coup < choixPossibles.size(); ++coup)
    {
        int valeur = 0;
        bool miseEchec = false;

        if (choixPossibles[coup].first.first > -1) //Si ce n'est pas une pièce de la réserve
        {
            int xD = choixPossibles[coup].first.first;
            int yD = choixPossibles[coup].first.second;
            int xA = choixPossibles[coup].second.first;
            int yA = choixPossibles[coup].second.second;
            int valPiece = plateau[xD][yD]->getValeur();
            int joueur = plateau[xD][yD]->getJoueur();
            QVector<Piece*> pieceAllieeAttaquees;
            QVector <Piece*> actuellementAttaquantes;
            QVector <Piece*> actuellementProtectrices;
            int bonusAttaque = 0;

            attaquantes.clear();
            protectrices.clear();
            attaque.clear();

            /*******************************************************/
            /* Tests pour récupérer les différentes valeurs utiles */
            /*******************************************************/

            /* Le Koropokkuru peut-il se rendre sur la dernière case ? (3x4) */
            if (plateau[xD][yD]->getType() == 1 && taille == 1)
            {
                if (joueur == 1)
                {
                    if (xA == 3)
                        valeur += 800;
                }
                else
                {
                    if (xA == 0)
                        valeur += 800;
                }
            }

            /* La pièce peut-elle mater ?*/         // Note : il est plus classe de mater, donc la priorité sera donnée au mat par rapport à l'arrivée sur la dernière case du Koropokkuru en 3x4 :p
            Piece* tmp = plateau[xA][yA];
            plateau[xA][yA] = plateau[xD][yD];
            plateau[xD][yD] = NULL;

            if (chessAndMat())
            {
                valeur += 1000;
            }

            /*Certaines de nos pièces seront-elles encore attaquées ?*/
            for(int i=0; i < tailleX; i++)
            {
                for(int j=0; j < tailleY; j++)
                {
                    if (i != xA || j != yA)
                    {
                        if (plateau[i][j] != NULL && plateau[i][j]->getJoueur() == joueur)
                        {
                            for(int k = -1; k < 2; k++)
                            {
                                for(int l = -1; k < 2; k++)
                                {
                                    if (i + k > -1 && i + k < tailleX && j + l > -1 && j + l < tailleY)
                                    {
                                        if (plateau[i + k][j + l] != NULL && plateau[i + k][j + l]->getJoueur() != joueur
                                                && plateau[i + k][j + l]->deplacement(i + k, j + l, i, j))
                                            pieceAllieeAttaquees.push_back(plateau[i][j]);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            plateau[xD][yD] = plateau[xA][yA];
            plateau[xA][yA] = tmp;
            tmp = NULL;

            /*La pièce sera-t-elle promue ?*/
            bool promo = false;
            if (plateau[xD][yD]->getType() == 4 || plateau[xD][yD]->getType() == 6)
            {
                if (taille == 1)
                {
                    if ((joueur == 1 && xA == 3) ||
                            (joueur == 2 && xA == 0))
                        promo = true;
                }
                else
                {
                    if ((joueur == 1 && (xA == 4 || xA == 5)) ||
                            (joueur == 2 && (xA == 1 || xA == 0)))
                        promo = true;
                }
            }

            /*La pièce avance-t-elle vers la promotion/la victoire (Koropokkuru 3x4) ?*/
            bool avance = false;
            if ((plateau[xD][yD]->getType() == 1 && taille == 1) ||
                    (plateau[xD][yD]->getType() == 4 && plateau[xD][yD]->getTransforme() == false) ||
                    (plateau[xD][yD]->getType() == 6 && plateau[xD][yD]->getTransforme() == false))
            {
                if (joueur == 1 && xA > xD)
                    avance = true;
                if (joueur == 2 && xA < xD)
                    avance = true;
            }


            /*La pièce sera-t-elle attaquée et/ou protégée ? Attaquera-t-elle d'autres pièces ? Est-elle actuellement attaquée ?*/
            for(int i =-1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if((xA + i != xD || yA + j != yD) && xA + i > -1 && xA + i < tailleX && yA + j > -1 && yA + j < tailleY)
                    {
                        if (plateau[xA + i][yA + j] != NULL)
                        {
                            if(plateau[xA + i][yA + j]->deplacement(xA + i, yA + j, xA, yA))
                            {
                                if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                                {
                                    attaquantes.push_back(plateau[xA + i][yA + j]); //La pièce sera attaquée.
                                }
                                else
                                {
                                    protectrices.push_back(plateau[xA + i][yA + j]); //La pièce sera protégée.
                                }
                            }
                            if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                            {
                                if (promo)
                                    plateau[xD][yD]->testTransforme();
                                if(plateau[xD][yD]->deplacement(xA, yA, xA + i, yA + j))
                                {
                                    attaque.push_back(make_pair(plateau[xA + i][yA + j],make_pair(xA + i,yA + j))); //La pièce sera attaquante.
                                    if (plateau[xA + i][yA + j]->getType() == 1)
                                        miseEchec = true;
                                }
                                if (promo)
                                    plateau[xD][yD]->testTransforme();
                            }
                        }
                    }

                    if (xD + i > -1 && xD + i < tailleX && yD + j > -1 && yD + j < tailleY)
                    {
                        if (plateau[xD + i][yD + j] != NULL && plateau[xD + i][yD + j]->deplacement(xD + i, yD + j, xD, yD))
                        {
                            if (plateau[xD + i][yD + j]->getJoueur() != joueur)
                                actuellementAttaquantes.push_back(plateau[xD + i][yD + j]); //La pièce est attaquée.
                            else
                                actuellementProtectrices.push_back(plateau[xD + i][yD + j]);
                        }
                    }
                }
            }

            /*******************************************************/
            /*  Attribution des valeurs pour chaque coup possible  */
            /*******************************************************/

            /*La pièce en prendra-elle une autre ?*/
            if (plateau[xA][yA] != NULL)
            {
                if (attaquantes.size() == 0)
                    valeur += plateau[xA][yA]->getValeur() + 1;
                else
                {
                    if (promo)
                        plateau[xD][yD]->testTransforme();
                    valPiece = plateau[xD][yD]->getValeur();
                    if (attaquantes.size() == 1 && attaquantes[0]->getType() == 1
                            && protectrices.size() == 1 && protectrices[0]->getType() == 1)
                        valeur += plateau[xA][yA]->getValeur() + 2; //Si la pièce est attaquée seulement par le Koropokkuru adverse et défendue par le Koropokkuru allié, la valeur du coup reste la même.
                    else
                        valeur += plateau[xA][yA]->getValeur() + 2 - valPiece; //Si elle est attaquée par d'autres pièces que le Koropokkuru, la valeur du coup est moins élevé.
                    if (promo)
                        plateau[xD][yD]->testTransforme();
                    valPiece = plateau[xD][yD]->getValeur();
                }
            }

            /*La pièce attaquera-t-elle d'autres pièces ; celles-ci sont-elles protégées ?*/
            for(int i = 0; i < attaque.size(); i++)
            {
                if(!casesAttaquees[attaque[i].second.first][attaque[i].second.second])
                    bonusAttaque += attaque[i].first->getValeur();
            }
            valeur += bonusAttaque/5;

            /*La pièce est actuellement attaquée.*/
            if (actuellementAttaquantes.size() > 0)
            {
                int valActuellementAttaquantes = 0;
                int minValActuellementAttaquantes = 10;
                for(int i = 0; i < actuellementAttaquantes.size(); i++)
                {
                    valActuellementAttaquantes += actuellementAttaquantes[i]->getValeur();
                    (minValActuellementAttaquantes > actuellementAttaquantes[i]->getValeur())?minValActuellementAttaquantes = actuellementAttaquantes[i]->getValeur():0;
                }
                int valActuellementProtectrices = valPiece;
                for(int i = 0; i < actuellementProtectrices.size(); i++)
                    valActuellementProtectrices += actuellementProtectrices[i]->getValeur();

                if ((valActuellementAttaquantes < valActuellementProtectrices
                     && actuellementAttaquantes.size() <= valActuellementProtectrices)
                        || valPiece > minValActuellementAttaquantes)
                {
                    if(attaquantes.size() == 0)
                        valeur += valPiece + 1;
                    else
                    {
                        int valAttaquantes = 0;
                        for(int i = 0; i < attaquantes.size(); i++)
                            valAttaquantes += attaquantes[i]->getValeur();
                        int valProtectrices = 0;
                        for(int i = 0; i < protectrices.size(); i++)
                            valProtectrices += protectrices[i]->getValeur();
                        if (valAttaquantes > valProtectrices && attaquantes.size() <= protectrices.size())
                            valeur += valPiece;
                    }
                }
            }

            /*La pièce sera attaquée*/
            if (attaquantes.size() > 0)
            {
                int valAttaquantes = 0;
                int minValAttaquantes = 10;
                for (int i = 0; i < attaquantes.size(); i++)
                {
                    valAttaquantes += attaquantes[i]->getValeur();
                    (minValAttaquantes > attaquantes[i]->getValeur())?minValAttaquantes = attaquantes[i]->getValeur():0;
                }
                int valProtectrices = valPiece;
                int minValProtectrices = 10;
                for (int i = 0; i < protectrices.size(); i++)
                {
                    valProtectrices += protectrices[i]->getValeur();
                    (minValProtectrices > protectrices[i]->getValeur())?minValProtectrices = protectrices[i]->getValeur():0;
                }

                if ((valAttaquantes > valProtectrices && attaquantes.size() <= protectrices.size()
                     && valPiece < minValAttaquantes) || minValAttaquantes > minValProtectrices+valPiece)
                {
                    valeur += minValAttaquantes - 1;
                    if (miseEchec)
                        valeur += 2;
                }
                if (attaquantes.size() > 0 && protectrices.size() == 0)
                    valeur -= valPiece*2;
            }

            /***********************/
            /*Evite un mat immédiat*/
            /***********************/
            tmp = plateau[xA][yA];
            plateau[xA][yA] = plateau[xD][yD];
            plateau[xD][yD] = NULL;

            QVector<pair<pair<int,int>,pair<int,int>>> possiblesAdversaire = recherchePossibilites(listePiecesAdverses, joueur%2+1);
            bool mat = false;

            for(int i = 0; i < possiblesAdversaire.size(); i++)
            {
                int xABoucle = possiblesAdversaire[i].second.first;
                int yABoucle = possiblesAdversaire[i].second.second;

                if (possiblesAdversaire[i].first.first > -1)
                {
                    int xDBoucle = possiblesAdversaire[i].first.first;
                    int yDBoucle = possiblesAdversaire[i].first.second;

                    Piece* tmpBoucle = plateau[xABoucle][yABoucle];
                    plateau[xABoucle][yABoucle] = plateau[xDBoucle][yDBoucle];
                    plateau[xDBoucle][yDBoucle] = NULL;

                    pair<pair<int,int>,pair<int,int>> koro = make_pair(rechercheKoro(1),rechercheKoro(2));

                    if (koro.first.first == -1 || koro.second.first == -1)
                        valeur = -5000;
                    else
                        if (chessAndMat())
                        {
                            valeur -= 300;
                            mat = true;
                        }

                    plateau[xDBoucle][yDBoucle] = plateau[xABoucle][yABoucle];
                    plateau[xABoucle][yABoucle] = tmpBoucle;
                    tmpBoucle = NULL;

                    if (mat)
                        break;
                }
                else
                {
                    int place = possiblesAdversaire[i].first.second;
                    if (possiblesAdversaire[i].first.first == -1)
                    {
                        plateau[xABoucle][yABoucle] = r1[place];
                        if (chessAndMat())
                        {
                            valeur -= 300;
                            mat = true;
                        }
                        plateau[xABoucle][yABoucle] = NULL;
                        if (mat)
                            break;
                    }
                    else
                    {
                        plateau[xABoucle][yABoucle] = r2[place];
                        if (chessAndMat())
                        {
                            valeur -= 300;
                            mat = true;
                        }
                        plateau[xABoucle][yABoucle] = NULL;
                        if (mat)
                            break;
                    }
                }
            }

            plateau[xD][yD] = plateau[xA][yA];
            plateau[xA][yA] = tmp;
            tmp = NULL;
        }
        else //Si la pièce est dans la réserve
        {
            int place = choixPossibles[coup].first.second;
            int xA = choixPossibles[coup].second.first;
            int yA = choixPossibles[coup].second.second;
            attaquantes.clear();
            protectrices.clear();

            if (choixPossibles[coup].first.first == -1)
            {
                int joueur = r1[place]->getJoueur();
                int valPiece = r1[place]->getValeur();

                /*******************************************************/
                /* Tests pour récupérer les différentes valeurs utiles */
                /*******************************************************/


                /*Certaines de nos pièces seront-elles encore attaquées ?*/
                plateau[xA][yA] = r1[place];
                QVector<Piece*> pieceAllieeAttaquees;
                for(int i=0; i < tailleX; i++)
                {
                    for(int j=0; j < tailleY; j++)
                    {
                        if (i != xA || j != yA)
                        {
                            if (plateau[i][j] != NULL && plateau[i][j]->getJoueur() == joueur)
                            {
                                for(int k = -1; k < 2; k++)
                                {
                                    for(int l = -1; k < 2; k++)
                                    {
                                        if (i + k > -1 && i + k < tailleX && j + l > -1 && j + l < tailleY)
                                        {
                                            if (plateau[i + k][j + l] != NULL && plateau[i + k][j + l]->getJoueur() != joueur
                                                    && plateau[i + k][j + l]->deplacement(i + k, j + l, i, j))
                                                pieceAllieeAttaquees.push_back(plateau[i][j]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                plateau[xA][yA] = NULL;

                for(int i =-1; i < 2; i++)
                {
                    for(int j = -1; j < 2; j++)
                    {
                        if(xA + i > -1 && xA + i < tailleX && yA + j > -1 && yA + j < tailleY)
                        {
                            if (plateau[xA + i][yA + j] != NULL)
                            {
                                if(plateau[xA + i][yA + j]->deplacement(xA + i, yA + j, xA, yA))
                                {
                                    if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                                    {
                                        attaquantes.push_back(plateau[xA + i][yA + j]); //La pièce sera attaquée.
                                    }
                                    else
                                    {
                                        protectrices.push_back(plateau[xA + i][yA + j]); //La pièce sera protégée.
                                    }
                                }
                                if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                                {
                                    if(r1[place]->deplacement(xA, yA, xA + i, yA + j))
                                    {
                                        attaque.push_back(make_pair(plateau[xA + i][yA + j],make_pair(xA + i,yA + j))); //La pièce sera attaquante.
                                        if (plateau[xA + i][yA + j]->getType() == 1)
                                            miseEchec = true;
                                    }
                                }
                            }
                        }
                    }
                }


                /*******************************************************/
                /*  Attribution des valeurs pour chaque coup possible  */
                /*******************************************************/

                /*La pièce attaquera-t-elle d'autres pièces ; celles-ci sont-elles protégées ?*/
                int bonusAttaque = 0;
                for(int i = 0; i < attaque.size(); i++)
                {
                    if(!casesAttaquees[attaque[i].second.first][attaque[i].second.second])
                        bonusAttaque += attaque[i].first->getValeur();
                }
                valeur += bonusAttaque/5;

                /*La pièce sera attaquée*/
                if (attaquantes.size() > 0)
                {
                    int valAttaquantes = 0;
                    int minValAttaquantes = 10;
                    for (int i = 0; i < attaquantes.size(); i++)
                    {
                        valAttaquantes += attaquantes[i]->getValeur();
                        (minValAttaquantes > attaquantes[i]->getValeur())?minValAttaquantes = attaquantes[i]->getValeur():0;
                    }
                    int valProtectrices = valPiece;
                    int minValProtectrices = 10;
                    for (int i = 0; i < protectrices.size(); i++)
                    {
                        valProtectrices += protectrices[i]->getValeur();
                        (minValProtectrices > protectrices[i]->getValeur())?minValProtectrices = protectrices[i]->getValeur():0;
                    }

                    if ((valAttaquantes > valProtectrices && attaquantes.size() <= protectrices.size()
                         && valPiece < minValAttaquantes) || minValAttaquantes > minValProtectrices+valPiece)
                    {
                        valeur += minValAttaquantes - 1;
                        if (miseEchec)
                            valeur += 2;
                    }
                    if (attaquantes.size() > 0 && protectrices.size() == 0)
                        valeur -= valPiece*2;
                }

                /***********************/
                /*Evite un mat immédiat*/
                /***********************/

                plateau[xA][yA] = r1[place];
                QVector<pair<pair<int,int>,pair<int,int>>> possiblesAdversaire = recherchePossibilites(listePiecesAdverses, ia%2+1);

                bool mat = false;
                for(int i = 0; i < possiblesAdversaire.size(); i++)
                {
                    if (possiblesAdversaire[i].first.first > -1)
                    {
                        int xDBoucle = possiblesAdversaire[i].first.first;
                        int yDBoucle = possiblesAdversaire[i].first.second;
                        int xABoucle = possiblesAdversaire[i].second.first;
                        int yABoucle = possiblesAdversaire[i].second.second;
                        Piece* tmpBoucle = plateau[xABoucle][yABoucle];
                        plateau[xABoucle][yABoucle] = plateau[xDBoucle][yDBoucle];
                        plateau[xDBoucle][yDBoucle] = NULL;
                        if (chessAndMat())
                        {
                            valeur -= 300;
                            mat = true;
                        }
                        plateau[xDBoucle][yDBoucle] = plateau[xABoucle][yABoucle];
                        plateau[xABoucle][yABoucle] = tmpBoucle;
                        tmpBoucle = NULL;
                        if (mat)
                            break;
                    }
                    else
                    {
                        int place = possiblesAdversaire[i].first.second;
                        int xABoucle = possiblesAdversaire[i].second.first;
                        int yABoucle = possiblesAdversaire[i].second.second;
                        if (possiblesAdversaire[i].first.first == -1)
                        {
                            plateau[xABoucle][yABoucle] = r1[place];
                            if (chessAndMat())
                            {
                                valeur -= 300;
                                mat = true;
                            }

                            plateau[xABoucle][yABoucle] = NULL;
                            if (mat)
                                break;
                        }
                        else
                        {
                            plateau[xABoucle][yABoucle] = r2[place];
                            if (chessAndMat())
                            {
                                valeur -= 300;
                                mat = true;
                            }

                            plateau[xABoucle][yABoucle] = NULL;
                            if (mat)
                                break;
                        }
                    }
                }
                plateau[xA][yA] = NULL;
            }
            else
            {
                int joueur = r2[place]->getJoueur();
                int valPiece = r2[place]->getValeur();

                /*******************************************************/
                /* Tests pour récupérer les différentes valeurs utiles */
                /*******************************************************/


                /*Certaines de nos pièces seront-elles encore attaquées ?*/
                plateau[xA][yA] = r2[place];
                QVector<Piece*> pieceAllieeAttaquees;
                for(int i=0; i < tailleX; i++)
                {
                    for(int j=0; j < tailleY; j++)
                    {
                        if (i != xA || j != yA)
                        {
                            if (plateau[i][j] != NULL && plateau[i][j]->getJoueur() == joueur)
                            {
                                for(int k = -1; k < 2; k++)
                                {
                                    for(int l = -1; k < 2; k++)
                                    {
                                        if (i + k > -1 && i + k < tailleX && j + l > -1 && j + l < tailleY)
                                        {
                                            if (plateau[i + k][j + l] != NULL && plateau[i + k][j + l]->getJoueur() != joueur
                                                    && plateau[i + k][j + l]->deplacement(i + k, j + l, i, j))
                                                pieceAllieeAttaquees.push_back(plateau[i][j]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                plateau[xA][yA] = NULL;

                for(int i =-1; i < 2; i++)
                {
                    for(int j = -1; j < 2; j++)
                    {
                        if(xA + i > -1 && xA + i < tailleX && yA + j > -1 && yA + j < tailleY)
                        {
                            if (plateau[xA + i][yA + j] != NULL)
                            {
                                if(plateau[xA + i][yA + j]->deplacement(xA + i, yA + j, xA, yA))
                                {
                                    if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                                    {
                                        attaquantes.push_back(plateau[xA + i][yA + j]); //La pièce sera attaquée.
                                    }
                                    else
                                    {
                                        protectrices.push_back(plateau[xA + i][yA + j]); //La pièce sera protégée.
                                    }
                                }
                                if (plateau[xA + i][yA + j]->getJoueur() != joueur)
                                {
                                    if(r2[place]->deplacement(xA, yA, xA + i, yA + j))
                                    {
                                        attaque.push_back(make_pair(plateau[xA + i][yA + j],make_pair(xA + i,yA + j))); //La pièce sera attaquante.
                                        if (plateau[xA + i][yA + j]->getType() == 1)
                                            miseEchec = true;
                                    }
                                }
                            }
                        }
                    }
                }


                /*******************************************************/
                /*  Attribution des valeurs pour chaque coup possible  */
                /*******************************************************/

                /*La pièce attaquera-t-elle d'autres pièces ; celles-ci sont-elles protégées ?*/
                int bonusAttaque = 0;
                for(int i = 0; i < attaque.size(); i++)
                {
                    if(!casesAttaquees[attaque[i].second.first][attaque[i].second.second])
                        bonusAttaque += attaque[i].first->getValeur();
                }
                valeur += bonusAttaque/5;

                /*La pièce sera attaquée*/
                if (attaquantes.size() > 0)
                {
                    int valAttaquantes = 0;
                    int minValAttaquantes = 10;
                    for (int i = 0; i < attaquantes.size(); i++)
                    {
                        valAttaquantes += attaquantes[i]->getValeur();
                        (minValAttaquantes > attaquantes[i]->getValeur())?minValAttaquantes = attaquantes[i]->getValeur():0;
                    }
                    int valProtectrices = valPiece;
                    int minValProtectrices = 10;
                    for (int i = 0; i < protectrices.size(); i++)
                    {
                        valProtectrices += protectrices[i]->getValeur();
                        (minValProtectrices > protectrices[i]->getValeur())?minValProtectrices = protectrices[i]->getValeur():0;
                    }

                    if ((valAttaquantes > valProtectrices && attaquantes.size() <= protectrices.size()
                         && valPiece < minValAttaquantes) || minValAttaquantes > minValProtectrices+valPiece)
                    {
                        valeur += minValAttaquantes - 1;
                        if (miseEchec)
                            valeur += 3;
                    }
                    if (attaquantes.size() > 0 && protectrices.size() == 0)
                        valeur -= valPiece*2;
                }


                /***********************/
                /*Evite un mat immédiat*/
                /***********************/

                plateau[xA][yA] = r2[place];
                QVector<pair<pair<int,int>,pair<int,int>>> possiblesAdversaire = recherchePossibilites(listePiecesAdverses, ia%2+1);

                bool mat = false;
                for(int i = 0; i < possiblesAdversaire.size(); i++)
                {
                    if (possiblesAdversaire[i].first.first > -1)
                    {
                        int xDBoucle = possiblesAdversaire[i].first.first;
                        int yDBoucle = possiblesAdversaire[i].first.second;
                        int xABoucle = possiblesAdversaire[i].second.first;
                        int yABoucle = possiblesAdversaire[i].second.second;
                        Piece* tmpBoucle = plateau[xABoucle][yABoucle];
                        plateau[xABoucle][yABoucle] = plateau[xDBoucle][yDBoucle];
                        plateau[xDBoucle][yDBoucle] = NULL;
                        if (chessAndMat())
                        {
                            valeur -= 300;
                            mat = true;
                        }
                        plateau[xDBoucle][yDBoucle] = plateau[xABoucle][yABoucle];
                        plateau[xABoucle][yABoucle] = tmpBoucle;
                        tmpBoucle = NULL;
                        if (mat)
                            break;
                    }
                    else
                    {
                        int place = possiblesAdversaire[i].first.second;
                        int xABoucle = possiblesAdversaire[i].second.first;
                        int yABoucle = possiblesAdversaire[i].second.second;
                        if (possiblesAdversaire[i].first.first == -1)
                        {
                            plateau[xABoucle][yABoucle] = r1[place];
                            if (chessAndMat())
                            {
                                valeur -= 300;
                                mat = true;
                            }
                            plateau[xABoucle][yABoucle] = NULL;
                            if (mat)
                                break;
                        }
                        else
                        {
                            plateau[xABoucle][yABoucle] = r2[place];
                            if (chessAndMat())
                            {
                                valeur -= 300;
                                mat = true;
                            }
                            plateau[xABoucle][yABoucle] = NULL;
                            if (mat)
                                break;
                        }
                    }
                }
                plateau[xA][yA] = NULL;
            }
        }
        triChoix.insert(valeur,choixPossibles[coup]);
    }

    for (int i = 0; i < tailleX; i++)
        delete []casesAttaquees[i];
    delete casesAttaquees;

    int valeurMax = (triChoix.end()-1).key();
    int nbMax = triChoix.count(valeurMax);
    int numChoix = rand()%nbMax;

    QMultiMap<int,pair<pair<int,int>,pair<int,int>>>::const_iterator elemChoisi = triChoix.find((triChoix.end()-1).key()) + numChoix;

    choisie = elemChoisi.value();

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(choixPart1()));
    if (danger) //Si le Koropokkuru est en échec, le texte s'affiche
        timer->start(2000);
    else
        timer->start(300);
}
void Partie::choixPart1()
{
    QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(choixPart1()));
    if (choisie.first.first < 0)
    {
        int nb = (taille == 1) ? 3 : 4;
        int min = 400/nb;

        if (choisie.first.first == -1)
        {
            cursor().setPos(choisie.first.second%nb * min + 10+fr1->pos().x() + min/2,choisie.first.second/nb * min + 30+fr1->pos().y() + min/2);
            QMouseEvent x(QEvent::None,cursor().pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
            fr1->mousePressEvent(&x);
        }
        else
        {
            cursor().setPos(choisie.first.second%nb * min + 10+fr2->pos().x() + min/2,choisie.first.second/nb * min + 30+fr2->pos().y() + min/2);
            QMouseEvent x(QEvent::None,cursor().pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
            fr2->mousePressEvent(&x);
        }
    }
    else
    {
        if (taille == 1)
            cursor().setPos(choisie.first.second*160+148+this->pos().x(),choisie.first.first*160+240+this->pos().y());
        else
            cursor().setPos(choisie.first.second*110+85+this->pos().x(),choisie.first.first*115+194+this->pos().y());
        emit clicked();
    }

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(choixPart2()));
    timer->start(400);
}
void Partie::choixPart2()
{
    QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(choixPart2()));

    this->setFocus();
    if (taille == 1)
        cursor().setPos(choisie.second.second*160+148+this->pos().x(),choisie.second.first*160+240+this->pos().y());
    else
        cursor().setPos(choisie.second.second*110+85+this->pos().x(),choisie.second.first*110+194+this->pos().y());

    emit clicked();
}
