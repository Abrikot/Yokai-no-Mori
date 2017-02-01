#include <QApplication>
#include <time.h>
#include "partie.h"
#include "title.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    srand(time(NULL));

    Title ecranTitre;
    ecranTitre.show();

    return app.exec();
}
