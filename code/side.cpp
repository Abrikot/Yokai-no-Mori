/***********************************************************************************
Classe gérant la réserve (affichage)
Emette les signaux :
    - clicked() : émis lorsqu'une pièce de la réserve est cliquée
    - parachutageSelect(int, QVector<Piece*>*) : émis lorsque la pièce est sélectionnée
Utilisée dans :
    -la classe Partie
************************************************************************************/


#include "side.h"

//Accesseur
int Side::getSelect() const
{
    return select[0];
}

//Mutateur
void Side::setSelect(int i)
{
    select[0] = i;
}

//Constructeur
Side::Side(int placeX, int placeY, QString joueur, int t) : taille(t)
{
    this->setWindowIcon((QIcon)"data/koropokkuru.jpg");
    this->setGeometry(placeX,placeY,400,400);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Réserve de " + joueur);
    this->setPixmap(((QPixmap)"data/escalier.jpg").copy(350,25,460,400));
    this->setScaledContents(true);
    liste = NULL;
    this->show();

    QObject::connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

//Destructeur
Side::~Side()
{
    if (liste != NULL)
        liste->clear();
}

//Autre méthode
void Side::displaySide(QVector <Piece*>& reserve)
{
    int i=0;
    int tailleReserve = reserve.size();
    int nb = (taille == 1) ? 3 : 4;
    int min = ((this->width() < this->height()) ? this->width() : this->height())/nb;

    liste = &reserve;

    for (;i<tailleReserve;i++)
    {
        if (reserve[i]->parent() != this)
            reserve[i]->setParent(this);
        if (!reserve[i]->isVisible())
            reserve[i]->setVisible(true);
        reserve[i]->setSelectionnee(false);
        reserve[i]->setGeometry(min*(i%nb),min*(i/nb),min,min);
    }
}

//Slots & méthodes associées
void Side::slotClicked()
{
    if (select[0] != -1)
    {
        int nb = (taille == 1) ? 3 : 4;
        int min = 400/nb;

        int yPoint = (cursor().pos().y() - this->pos().y() - 30)/min;
        int xPoint = (cursor().pos().x() - this->pos().x() - 10)/min;

        if (liste != NULL && liste->size() == 0)
        {
            liste = NULL;
        }
        if (select[0] == 0)
        {
            if (liste != NULL && xPoint + yPoint * nb < liste->size())
            {
                ((*liste)[xPoint + yPoint * nb])->setSelectionnee(true);
                select[0] = 1;
                select[1] = xPoint;
                select[2] = yPoint;
                QApplication::setOverrideCursor(Qt::CrossCursor);

                emit parachutSelect(xPoint + yPoint * nb, liste);
            }
        }
        else
        {
            if (liste != NULL)
            {
                (*liste)[select[1] + select[2] * nb]->setSelectionnee(false);
                select[0] = 0;
                QApplication::restoreOverrideCursor();
                emit parachutSelect(-1, liste);
            }
        }
    }
}
void Side::mousePressEvent (QMouseEvent*)
{
    emit clicked();
}
void Side::closeEvent(QCloseEvent* event)
{
    event->ignore();
}
