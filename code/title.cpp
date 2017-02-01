/***************************************************************************************************************
Classe gérant l'écran titre et le lancement d'une partie
Emet les signaux
    - endedMusic() : émis lorsque la musique est terminée
    - clicked() : émis lorsqu'un clic est effectué sur la fenêtre
    - keyPressed(QKeyEvent*) : émis lorsqu'une touche est enfoncée
    - konaPressed(QKeyEvent*) : émis lorsqu'une touche est enfoncée - gère l'Easter egg
****************************************************************************************************************/


#include "title.h"

//Constructeur
Title::Title()
{
    this->setWindowTitle("Yokaï No Mori");
    this->setWindowIcon((QIcon)"data/koropokkuru.jpg");
    QPixmap fond = (QPixmap)"data/escalier.jpg";
    this->setPixmap(fond);
    this->setScaledContents(true);
    this->setFixedSize(fond.width(),fond.height());

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/ambiance.mp3"));
    player->play();
    volume = 3;

    titre1 = new QLabel(this);
    titre1->setStyleSheet("color : #FFFFFF; font-size : 100px; font-family : \"shanghai\";");
    titre1->setText("YOKAÏ");
    titre1->adjustSize();
    titre1->setGeometry(150,50,titre1->width(),titre1->height());

    titre2 = new QLabel(this);
    titre2->setStyleSheet("color : #FFFFFF; font-size : 100px; font-family : \"shanghai\";");
    titre2->setText("NO");
    titre2->adjustSize();
    titre2->setGeometry(515,50,titre2->width(),titre2->height());

    titre3 = new QLabel(this);
    titre3->setStyleSheet("color : #FFFFFF; font-size : 100px; font-family : \"shanghai\"");
    titre3->setText("MORI");
    titre3->adjustSize();
    titre3->setGeometry(765,50,titre3->width(),titre3->height());

    b1 = new HoverButton("Jouer en 3x4", this);
    b1->setGeometry(850,150,b1->width(),b1->height());
    b1->setVisible(false);

    b2 = new HoverButton("Jouer en 5x6", this);
    b2->setGeometry(850,350,b2->width(),b2->height());
    b2->setVisible(false);

    question = new QLabel(this);
    question->setStyleSheet("color : #FFFFFF; font-size : 60px; font-family : \"shanghai\";");
    question->setText("");
    question->adjustSize();
    question->setGeometry(140,50,question->width(),question->height());
    question->setVisible(false);

    lj = new QLabel(this);
    lj->setStyleSheet("color : #FFFFFF; font-size : 60px; font-family : \"shanghai\";");
    lj->adjustSize();
    lj->setGeometry(0,250,lj->width(),lj->height());
    lj->setVisible(false);

    iaYes = new HoverButton("Jouer contre l'ordinateur !", this);
    iaYes->setGeometry((this->width()-iaYes->width())/2,(this->height()-iaYes->height())/3,iaYes->width(),iaYes->height());
    iaYes->setVisible(false);

    iaNo = new HoverButton("Jouer contre un autre joueur !", this);
    iaNo->setGeometry((this->width()-iaNo->width())/2,(this->height()-iaYes->height())/3*2,iaNo->width(),iaNo->height());
    iaNo->setVisible(false);

    goTitle1 = new QGraphicsOpacityEffect;
    goTitle1->setOpacity(1);
    titre1->setGraphicsEffect(goTitle1);

    goTitle2 = new QGraphicsOpacityEffect;
    goTitle2->setOpacity(1);
    titre2->setGraphicsEffect(goTitle2);

    goTitle3 = new QGraphicsOpacityEffect;
    goTitle3->setOpacity(1);
    titre3->setGraphicsEffect(goTitle3);

    go1 = new QGraphicsOpacityEffect;
    go1->setOpacity(0);
    b1->setGraphicsEffect(go1);

    go2 = new QGraphicsOpacityEffect;
    go2->setOpacity(0);
    b2->setGraphicsEffect(go2);

    goQuestion = new QGraphicsOpacityEffect;
    goQuestion->setOpacity(0);
    question->setGraphicsEffect(goQuestion);

    goLj = new QGraphicsOpacityEffect;
    goLj->setOpacity(0);
    lj->setGraphicsEffect(goLj);

    goIaYes = new QGraphicsOpacityEffect;
    goIaYes->setOpacity(0);
    iaYes->setGraphicsEffect(goIaYes);

    goIaNo = new QGraphicsOpacityEffect;
    goIaNo->setOpacity(0);
    iaNo->setGraphicsEffect(goIaNo);

    hp = new Hp(this);
    hp->setGeometry(1150,480,25,25);

    timer = new QTimer;

    p = NULL;

    QObject::connect(b1,SIGNAL(clicked()),this,SLOT(firstButtonClicked()));
    QObject::connect(b2,SIGNAL(clicked()),this,SLOT(secondButtonClicked()));
    QObject::connect(iaYes,SIGNAL(clicked()),this,SLOT(iaYesClicked()));
    QObject::connect(iaNo,SIGNAL(clicked()),this,SLOT(iaNoClicked()));
    QObject::connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(endMusic(QMediaPlayer::State)));
    QObject::connect(hp,SIGNAL(volume(int)),this,SLOT(volumeChanged(int)));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(animatedTitle()));
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(animatedTitle()));
    QObject::connect(this,SIGNAL(konaPressed(QKeyEvent*)),this,SLOT(konaVerif(QKeyEvent*)));
}

//Destructeur
Title::~Title()
{
    if (p != NULL)
        delete p;
}

//Autres méthodes
void Title::dismiss()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/deplacement.mp3"));
    if (volume != 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
}
void Title::agree()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/promotion.wav"));
    if (volume != 0)
        player->setVolume(20 + 20 * volume);
    else
        player->setVolume(0);
    player->play();
}

//Slots & autres méthodes
void Title::firstButtonClicked()
{
    taille = 1;
    this->fadeOut();
}
void Title::secondButtonClicked()
{
    taille = 2;
    this->fadeOut();
}
void Title::iaYesClicked()
{
    if (question->text() != "Quel est le nom du joueur ?")
    {
        question->setText("Quel est le nom du joueur ?");
        question->adjustSize();
        question->setGeometry((this->width()-question->width())/2,question->y(),question->width(),question->height());
    }
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOutIaYes()));
    this->fadeOutIaYes();
}
void Title::iaNoClicked()
{
    if (question->text() != "Quel est le nom du second joueur ?")
    {
        question->setText("Quel est le nom du second joueur ?");
        question->adjustSize();
        question->setGeometry((this->width()-question->width())/2,question->y(),question->width(),question->height());
    }
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOutIaNo()));
    this->fadeOutIaNo();
}
void Title::gameClosed()
{
    delete p;
    p = NULL;
    this->show();

    goTitle1->setOpacity(1);
    goTitle2->setOpacity(1);
    goTitle3->setOpacity(1);
    go1->setOpacity(1);
    go2->setOpacity(1);

    titre1->setVisible(true);
    titre2->setVisible(true);
    titre3->setVisible(true);
    b1->setVisible(true);
    b2->setVisible(true);
    b1->setEnabled(true);
    b2->setEnabled(true);

    QString tmp = j1;
    j1 = j2;
    j2 = tmp;

    question->setText("");

    QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOutName2()));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOut()));
    QObject::connect(iaYes,SIGNAL(clicked()),this,SLOT(iaYesClicked()));
    QObject::connect(iaNo,SIGNAL(clicked()),this,SLOT(iaNoClicked()));
}
void Title::replayGame()
{
    delete p;
    p = NULL;
    swap(j1,j2);
    p = new Partie(j2, j1, taille,hp->getSon());
    QObject::connect(p,SIGNAL(closed()),this,SLOT(gameClosed()));
    QObject::connect(p->getHp(),SIGNAL(volume(int)),this,SLOT(volumeChanged(int)));
    QObject::connect(p,SIGNAL(konaPressed(QKeyEvent*)),this,SLOT(konaVerif(QKeyEvent*)));
    QObject::connect(p,SIGNAL(replayed()),this,SLOT(replayGame()));
    QObject::connect(p,SIGNAL(iaFailed()),this,SLOT(iaFailed()));
}
void Title::endMusic(QMediaPlayer::State s)
{
    if (s == QMediaPlayer::StoppedState)
        player->play();
}
void Title::volumeChanged(int s)
{
    volume = s;
    if (s != 0)
        player->setVolume(25 + 25*s);
    else
        player->setVolume(0);
    b1->setVolume(s);
    b2->setVolume(s);
    iaYes->setVolume(s);
    iaNo->setVolume(s);
    if (p != NULL)
    {
        p->setVolume(s);
        p->getExit()->setVolume(s);
        p->getReplay()->setVolume(s);
        p->getYes()->setVolume(s);
        p->getNo()->setVolume(s);
    }
}
void Title::animatedTitle()
{
    nbT++;
    int tmp = 0.5*nbT*nbT - 15*nbT;
    if (nbT > 28)
    {
        timer->blockSignals(true);
        timer->stop();
        titre1->setGeometry(100, 100,titre1->width(),titre1->height());
        titre2->setGeometry(140, 200,titre2->width(),titre2->height());
        titre3->setGeometry(110, 300,titre3->width(),titre3->height());

        go1->setOpacity(1);
        go2->setOpacity(1);
        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(animatedTitle()));

        this->dismiss();

        nbT = 0;

        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOut()));
        timer->blockSignals(false);
    }
    else
    {
        timer->start(25);
        titre1->setGeometry(150 - ((150 - 100)/30.0) * nbT + tmp, 50 - ((50 - 100)/30.0) * nbT - tmp,titre1->width(),titre1->height());
        titre2->setGeometry(515 - ((515 - 140)/30.0) * nbT + tmp, 50 - ((50 - 200)/30.0) * nbT - tmp,titre2->width(),titre2->height());
        titre3->setGeometry(765 - ((765 - 110)/30.0) * nbT + tmp, 50 - ((50 - 300)/30.0) * nbT - tmp,titre3->width(),titre3->height());

        go1->setOpacity(nbT/30);
        go2->setOpacity(nbT/30);
    }
}
void Title::fadeOut()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        go1->setOpacity(0);
        go2->setOpacity(0);
        goTitle1->setOpacity(0);
        goTitle2->setOpacity(0);
        goTitle3->setOpacity(0);

        b1->setVisible(false);
        b1->setEnabled(false);
        b2->setVisible(false);
        b2->setEnabled(false);
        titre1->setVisible(false);
        titre2->setVisible(false);
        titre3->setVisible(false);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOut()));
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeInIa()));

        nbT = 0;
        iaYes->setVisible(true);
        iaYes->setEnabled(true);
        iaNo->setVisible(true);
        iaNo->setEnabled(true);
        timer->blockSignals(false);
        timer->start(100);
    }
    else
    {
        go1->setOpacity((20-nbT)/20.0);
        go2->setOpacity((20-nbT)/20.0);
        goTitle1->setOpacity((20-nbT)/20.0);
        goTitle2->setOpacity((20-nbT)/20.0);
        goTitle3->setOpacity((20-nbT)/20.0);
        timer->start(25);
    }
}
void Title::fadeOutIaYes()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goIaYes->setOpacity(0);
        goIaNo->setOpacity(0);

        iaYes->setVisible(false);
        iaYes->setEnabled(false);
        iaNo->setVisible(false);
        iaNo->setEnabled(false);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOutIaYes()));
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeInName()));

        nbT = 0;
        j1 = "IA";
        question->setText("Quel est le nom du joueur ?");
        question->adjustSize();
        question->setGeometry((this->width()-question->width())/2,question->y(),question->width(),question->height());
        question->setVisible(true);
        timer->blockSignals(false);
        timer->start(100);
    }
    else
    {
        goIaYes->setOpacity((20-nbT)/20.0);
        goIaNo->setOpacity((20-nbT)/20.0);
        timer->start(25);
    }
}
void Title::fadeOutIaNo()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goIaYes->setOpacity(0);
        goIaNo->setOpacity(0);

        iaYes->setVisible(false);
        iaYes->setEnabled(false);
        iaNo->setVisible(false);
        iaNo->setEnabled(false);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOutIaNo()));
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeIn()));

        nbT = 0;
        question->setText("Quel est le nom du premier joueur ?");
        question->adjustSize();
        question->setGeometry((this->width()-question->width())/2,question->y(),question->width(),question->height());
        question->setVisible(true);
        timer->blockSignals(false);
        timer->start(100);
    }
    else
    {
        goIaYes->setOpacity((20-nbT)/20.0);
        goIaNo->setOpacity((20-nbT)/20.0);
        timer->start(25);
    }
}
void Title::fadeOutName()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goQuestion->setOpacity(0);
        goLj->setOpacity(0);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOutName()));
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeInName()));

        nbT = 0;
        question->setText("Quel est le nom du second joueur ?");
        question->adjustSize();
        question->setGeometry((this->width()-question->width())/2,question->y(),question->width(),question->height());
        lj->setText(j2);
        lj->adjustSize();
        lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        timer->blockSignals(false);
        timer->start(200);
    }
    else
    {
        goQuestion->setOpacity((20-nbT)/20.0);
        goLj->setOpacity((20-nbT)/20.0);
        timer->start(25);
    }
}
void Title::fadeOutName2()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goQuestion->setOpacity(0);
        goLj->setOpacity(0);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeOutName()));

        nbT = 0;
        timer->blockSignals(false);

        this->hide();
        p = new Partie(j2, j1, taille,hp->getSon());
        QObject::connect(p,SIGNAL(closed()),this,SLOT(gameClosed()));
        QObject::connect(p->getHp(),SIGNAL(volume(int)),this,SLOT(volumeChanged(int)));
        QObject::connect(p,SIGNAL(konaPressed(QKeyEvent*)),this,SLOT(konaVerif(QKeyEvent*)));
        QObject::connect(p,SIGNAL(replayed()),this,SLOT(replayGame()));
        QObject::connect(p,SIGNAL(iaFailed()),this,SLOT(iaFailed()));
        QObject::connect(p,SIGNAL(finIaFailed()),this,SLOT(finIaFailed()));
    }
    else
    {
        goQuestion->setOpacity((20-nbT)/20.0);
        goLj->setOpacity((20-nbT)/20.0);
        timer->start(25);
    }
}
void Title::fadeInIa()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goIaYes->setOpacity(1);
        goIaNo->setOpacity(1);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeInIa()));

        nbT = 0;
        timer->blockSignals(false);
    }
    else
    {
        goIaYes->setOpacity(nbT/20.0);
        goIaNo->setOpacity(nbT/20.0);
        timer->start(25);
    }
}
void Title::fadeIn()
{
    if (lj->text() != j1)
    {
        lj->setText(j1);
        lj->adjustSize();
        lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        lj->setVisible(true);
    }
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goQuestion->setOpacity(1);
        goLj->setOpacity(1);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeIn()));
        QObject::connect(this,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(changedNameJ1(QKeyEvent*)));

        nbT = 0;
        timer->blockSignals(false);
    }
    else
    {
        goQuestion->setOpacity(nbT/20.0);
        goLj->setOpacity(nbT/20.0);
        timer->start(25);
    }
}
void Title::fadeInName()
{
    nbT++;
    if (nbT > 20)
    {
        timer->blockSignals(true);
        timer->stop();
        goQuestion->setOpacity(1);

        QObject::disconnect(timer,SIGNAL(timeout()),this,SLOT(fadeInName()));
        QObject::connect(this,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(changedNameJ2(QKeyEvent*)));

        timer->blockSignals(false);
        nbT = 0;
    }
    else
    {
        goQuestion->setOpacity(nbT/20.0);
        goLj->setOpacity(nbT/20.0);
        timer->start(25);
    }
}
void Title::changedNameJ1(QKeyEvent* k)
{
    if (!lj->isVisible())
        lj->setVisible(true);
    if (k->key() == Qt::Key_Backspace)
    {
        if (j1.length() != 0)
        {
            j1.remove(j1.length()-1,1);
            lj->setText(j1);
            lj->adjustSize();
            lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        }
    }
    else
    {
        if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
        {
            if (j1.length() > 2 || j1.toLower() == "ia")
            {
                agree();
                if (j1.toLower() == "ia")
                    j1 = "IA";
                else
                    j1 = j1[0].toUpper() + j1.mid(1).toLower();
                QObject::disconnect(this,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(changedNameJ1(QKeyEvent*)));
                QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOutName()));

                timer->start(100);
            }
            else
                dismiss();
        }
        else if (j1.length() < 8)
        {
            j1 = j1 + k->text();
            lj->setText(j1);
            lj->adjustSize();
            lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        }
    }
}
void Title::changedNameJ2(QKeyEvent* k)
{
    if (!lj->isVisible())
        lj->setVisible(true);
    if (k->key() == Qt::Key_Backspace)
    {
        if (j2.length() != 0)
        {
            j2.remove(j2.length()-1,1);
            lj->setText(j2);
            lj->adjustSize();
            lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        }
    }
    else
    {
        if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
        {
            if (j2.length() > 2 || j2.toLower() == "ia")
            {
                agree();
                if (j2.toLower() == "ia")
                    j2 = "IA";
                else
                    j2 = j2[0].toUpper() + j2.mid(1).toLower();
                if (j1.toLower() == "ia" || j2.toLower() == "ia")   //Choisis un premier joueur aléatoire si l'un des deux est l'IA
                    if (rand()%2)
                        swap(j1,j2);
                QObject::disconnect(this,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(changedNameJ2(QKeyEvent*)));
                QObject::connect(timer,SIGNAL(timeout()),this,SLOT(fadeOutName2()));
                timer->start(100);
            }
            else
                dismiss();
        }
        else if (j2.length() < 8)
        {
            j2 = j2 + k->text();
            lj->setText(j2);
            lj->adjustSize();
            lj->setGeometry((this->width()-lj->width())/2,250,lj->width(),lj->height());
        }
    }
}
void Title::konaVerif(QKeyEvent* k)
{
    if (k->key() == Qt::Key_Up)
    {
        if (nbKona == 0 || nbKona == 1)
            nbKona++;
        else
            nbKona = 0;
    }
    else
    {
        if (k->key() == Qt::Key_Down)
        {
            if (nbKona == 2 || nbKona == 3)
                nbKona++;
            else
                nbKona = 0;
        }
        else
        {
            if (k->key() == Qt::Key_Left)
            {
                if (nbKona == 4 || nbKona == 6)
                    nbKona++;
                else
                    nbKona = 0;
            }
            else
            {
                if (k->key() == Qt::Key_Right)
                {
                    if (nbKona == 5 || nbKona == 7)
                        nbKona++;
                    else
                        nbKona = 0;
                }
                else
                {
                    if (k->key() == Qt::Key_B)
                    {
                        if (nbKona == 8)
                            nbKona++;
                        else
                            nbKona = 0;
                    }
                    else
                    {
                        if (k->key() == Qt::Key_A)
                        {
                            if (nbKona == 9)
                            {
                                if (!kona)
                                {
                                    player->setMedia(QUrl::fromLocalFile("data/code.mp3"));
                                    kona = true;
                                }
                                else
                                {
                                    player->setMedia(QUrl::fromLocalFile("data/ambiance.mp3"));
                                    kona = false;
                                }
                            }
                            nbKona = 0;
                        }
                        else
                            nbKona = 0;
                    }
                }
            }
        }
    }
}
void Title::iaFailed()
{
    QObject::disconnect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(endMusic(QMediaPlayer::State)));
    player->stop();
    //player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/iaFailed.mp3"));
    player->play();
    QObject::connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(endMusic(QMediaPlayer::State)));
}
void Title::finIaFailed()
{
    QObject::disconnect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(endMusic(QMediaPlayer::State)));
    player->stop();
    //player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("data/ambiance.mp3"));
    player->play();
    QObject::connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(endMusic(QMediaPlayer::State)));
}
void Title::mousePressEvent (QMouseEvent*)
{
    b1->setVisible(true);
    b2->setVisible(true);
    emit clicked();
    QObject::disconnect(this,SIGNAL(clicked()),this,SLOT(animatedTitle()));
}
void Title::keyPressEvent(QKeyEvent * k)
{
    emit konaPressed(k);
    if ((k->key() >= Qt::Key_A && k->key() <= Qt::Key_Z) ||
            k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter || k->key() == Qt::Key_Backspace)
        emit keyPressed(k);
}
