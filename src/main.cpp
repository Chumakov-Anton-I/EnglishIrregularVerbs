/* ******************************************************************** **
** ** A simple application to learning of English irregular verbs ***** **
** ******************************************************************** */

#include "startwnd.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/ico_obook"));

    CStartWindow window;

    QFile stylef("styles/style.css");
    stylef.open(QFile::ReadOnly);
    QString sCSS = QLatin1String(stylef.readAll());
    qApp->setStyleSheet(sCSS);

    window.show();

    return app.exec();
}
