/* ******************************************************************** **
** ** A simple application to learning of English irregular verbs ***** **
** ******************************************************************** **
 * File:    main.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 6, 2024
** ******************************************************************** */

#include "MainWindow.h"
#include "settings_key.h"

QSettings* appSettings;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifndef _DEBUG
    app.setWindowIcon(QIcon(":/ico_obook"));
#endif
    const QString fname(ini_system::ini_file);
    if (!QFile::exists(fname)) { // make default settings
        appSettings = new QSettings(fname, QSettings::IniFormat);
        using namespace ini_system; //appSettings->beginGroup("system");
        appSettings->setValue(dictionary_path, "dictionaries");
        appSettings->setValue(sound_path, "sound");
        appSettings->setValue(dictionary, "");// while unused - TODO
        appSettings->setValue(count_to_done, "10");
        appSettings->setValue(to_learn, "20");
        //appSettings->endGroup();
        appSettings->sync();  // save settings now
    }
    else    // read existed settings
        appSettings = new QSettings(fname, QSettings::IniFormat);

    QFile stylef("styles/style.css");
    stylef.open(QFile::ReadOnly);
    qApp->setStyleSheet(QLatin1String(stylef.readAll()));
    qApp->setFont(QFont("Segoe UI", 12));

    CMainWindow window;
    window.show();

    return app.exec();
}
