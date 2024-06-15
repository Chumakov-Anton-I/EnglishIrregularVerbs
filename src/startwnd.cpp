/* ****************************************************************************
 * startwnd.cpp
 * ****************************************************************************/

#include <QCoreApplication>
#include "window.h"
#include "startwnd.h"
#include "learnwindow.h"

CStartWindow :: CStartWindow(QWidget* parent/* = nullptr */)
    : QWidget(parent)
{
    mainFrame = new QVBoxLayout();
    setLayout(mainFrame);

    /* Block "About dictionary" */
    boxDictInfo = new QGroupBox("About dictionary");
        boxDictInfoLayout = new QVBoxLayout();
        boxDictInfo->setLayout(boxDictInfoLayout);
        gridDictInfo = new QGridLayout();
        boxDictInfoLayout->addLayout(gridDictInfo);
            lbDictName = new QLabel("Dictionary");
            lbDictNameV = new QLabel("");
            lbDictNameV->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            lbDictAuthor = new QLabel("Author");
            lbDictAuthorV = new QLabel("");
            lbDictAuthorV->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            lbDictVersion = new QLabel("Verion");
            lbDictVersionV = new QLabel("");
            lbDictVersionV->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            lblDictDate = new QLabel("Date");
            lblDictDateV = new QLabel("");
            lblDictDateV->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            lbDictSize = new QLabel("Number of words");
            lbDictSizeV = new QLabel("");
            lbDictSizeV->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            gridDictInfo->addWidget(lbDictName, 0, 0, Qt::AlignRight);
            gridDictInfo->addWidget(lbDictNameV, 0, 1/*, Qt::AlignLeft*/);
            gridDictInfo->addWidget(lbDictVersion, 1, 0, Qt::AlignRight);
            gridDictInfo->addWidget(lbDictVersionV, 1, 1/*, Qt::AlignLeft*/);
            gridDictInfo->addWidget(lbDictAuthor, 2, 0, Qt::AlignRight);
            gridDictInfo->addWidget(lbDictAuthorV, 2, 1/*, Qt::AlignLeft*/);
            gridDictInfo->addWidget(lbDictSize, 3, 0, Qt::AlignRight);
            gridDictInfo->addWidget(lbDictSizeV, 3, 1/*, Qt::AlignLeft*/);
        btnChooseDict = new QPushButton("Choose dictionary...");
        btnStartLearning = new QPushButton("Learn words");
        btnStartTest = new QPushButton("Run test");
        boxDictInfoLayout->addWidget(btnChooseDict);
        boxDictInfoLayout->addWidget(btnStartLearning);
        boxDictInfoLayout->addWidget(btnStartTest);
    mainFrame->addWidget(boxDictInfo);

    /* Block "Settings"
    boxLearnSettings = new QGroupBox("Settings");
        boxLearnSettingsLayout = new QVBoxLayout();
        boxLearnSettings->setLayout(boxLearnSettingsLayout);
        boxLearnSettingsLayout->addWidget(btnStartTest);
    mainFrame->addWidget(boxLearnSettings); */

    /* Block "Statistics" */
    boxStatistics = new QGroupBox("Statistics");
        boxStatisticsLayout = new QVBoxLayout();
        boxStatistics->setLayout(boxStatisticsLayout);
        dummyLbl = new QLabel("Statistics - TODO");
        boxStatisticsLayout->addWidget(dummyLbl);
        btnResetStatistics = new QPushButton("Reset statistics");
        boxStatisticsLayout->addWidget(btnResetStatistics);
    mainFrame->addWidget(boxStatistics);

    /* ab out */
    aboutFrame = new QHBoxLayout();
    mainFrame->addLayout(aboutFrame);
    btnAbout = new QPushButton("About...");
    btnAboutQt = new QPushButton("About Qt...");
    aboutFrame->addWidget(btnAbout);
    aboutFrame->addWidget(btnAboutQt);

    /* Connect signals */
    connect(btnStartTest, SIGNAL(clicked()), this, SLOT(startTest()));
    connect(btnAbout, SIGNAL(clicked()), SLOT(about()));
    connect(btnAboutQt, SIGNAL(clicked()), SLOT(aboutQt()));
    connect(btnChooseDict, SIGNAL(clicked()), SLOT(chooseDictionary()));
    connect(btnStartLearning, SIGNAL(clicked()), SLOT(startLearning()));

    /* === Begin work === */
    readSettings();
    if (!loadDictionary(current_dictionary.path())) exit(EXIT_FAILURE);
}

CStartWindow :: ~CStartWindow()
{
}

void CStartWindow :: readSettings()
{
    QString fname = "settings.ini";
    if (!QFile::exists(fname)) {
        app_settings = new QSettings(fname, QSettings::IniFormat);
        app_settings->beginGroup("system");
            app_settings->setValue("dictionary_path", "dictionaries");
            app_settings->setValue("sound_path", "sound");
            app_settings->setValue("dictionary", "dictionary.xml");
            app_settings->setValue("count_done", "10");
            app_settings->setValue("words_to_learn", "20");
        app_settings->endGroup();
    }
    else
        app_settings = new QSettings(fname, QSettings::IniFormat);
    QString dirpath = app_settings->value("system/recent", "").toString();
    if (dirpath.isEmpty())
        dirpath = app_settings->value("system/dictionary_path").toString() + "/"
                      + app_settings->value("system/dictionary").toString();
    current_dictionary = QDir(dirpath);
}

/* // TODO: doesn't use
void CStartWindow :: readStatistics()
{
    QString fname = "statistics.ini";
    if (!QFile::exists(fname)) {
        statistics = new QSettings(fname, QSettings::IniFormat);
        statistics->beginGroup("statistics");
        statistics->endGroup();
    }
    else
        statistics = new QSettings(fname, QSettings::IniFormat);
    statistics->beginGroup("statistics");
        QStringList base = statistics->childKeys();
    statistics->endGroup();
        foreach (auto item, base)
            wordBase[item] = statistics->value(item, 0).toInt();
}*/

/* [slot] It opens an open file dialog */
bool CStartWindow :: chooseDictionary()
{
    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Choose the dictionary...",
                                                 current_dictionary.absolutePath(),
                                                 "Dictionaries (*.xml);;All (*)");
    if (!fname.isEmpty()) {
        if (!loadDictionary(fname)) exit(EXIT_FAILURE);
        //loadDictionary(fname);
        return true;
    }
    return false;
}

/* Loading a sictionary */
bool CStartWindow :: loadDictionary(const QString &fpath)
{
    /* Open a file */
    QFile dictfile(fpath);
    if (!dictfile.open(QIODevice :: ReadOnly)) {
        QString msg = QString("Can not open file [%1]!").arg(fpath); // TODO: message
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox :: Icon :: Critical);
        msgBox.setText(msg);
        //msgBox.setInformativeText("Error!");
        msgBox.setStandardButtons(QMessageBox :: Ok | QMessageBox :: Close);
        msgBox.setDefaultButton(QMessageBox :: Ok);
        if (msgBox.exec() == QMessageBox :: Ok) {   // If the OK button was pressed, open dialog
            if (!chooseDictionary())
                return false;
        }
        else
            return false;
    }
    /* Read the file of a dictionary */
    QDomDocument dictDoc;
    auto res = dictDoc.setContent(&dictfile);
    if (!res) { // TODO
        dictfile.close();
        /*QErrorMessage err = QErrorMessage(this); err.showMessage(msg);*/
        QString msg = res.errorMessage + QString(" [%1, %2]").arg(res.errorLine).arg(res.errorColumn);
        QMessageBox dlg;
        dlg.setIcon(QMessageBox :: Icon :: Critical);
        dlg.setText("The dictionary has a wrong structure. Press OK to open another dictionary, press CLOSE to exit.");
        dlg.setInformativeText(msg);
        dlg.setStandardButtons(QMessageBox :: Ok | QMessageBox :: Close);
        dlg.setDefaultButton(QMessageBox :: Ok);
        if (dlg.exec() == QMessageBox :: Ok) {
            if (!chooseDictionary())
                return false;
        }
        else
            return false;
    }
    dictfile.close();
    /* Read a dictionary */
    if (!readDictionary(dictDoc)) {
        QString msg = QString("The dictionary [%1] has a wrong structure.").arg(fpath);
        QMessageBox dlg = QMessageBox(QMessageBox :: Icon :: Critical,
                                      "Error!", msg, QMessageBox :: Close);
        if (dlg.exec() == QMessageBox :: Ok) {
            if (!chooseDictionary())
                return false;//exit(EXIT_FAILURE);//
        }
        else
            return false;
    }
    current_dictionary = QDir(fpath);
    app_settings->setValue("system/recent", fpath);
    return true;
}

/* Reading a dictionary */
bool CStartWindow :: readDictionary(const QDomDocument& doc)
{
    //if (!checkDict()) return false;   // TODO: add checking the structure of a dictionary
    QDomElement root = doc.documentElement();
    dictionary = root.childNodes();
    count = dictionary.length();
    dict_name = root.attribute("title");//, "unnamed");
    dict_vers = root.attribute("version", "");
    dict_date = root.attribute("date", "");
    dict_auth = root.attribute("author", "");
    //QString title = QString("Dictionary {%1} ver. %2 [%3 words]").arg(dict_name, dict_vers, QString::number(count));
    //this->setWindowTitle(title);    // rename Window
    lbDictNameV->setText(dict_name);
    lbDictVersionV->setText(dict_vers);
    lblDictDateV->setText(dict_date);
    lbDictAuthorV->setText(dict_auth);
    lbDictSizeV->setText(QString::number(count));

    return true;
}

void CStartWindow :: startLearning()
{
    CLearnWindow *learn = new CLearnWindow(dictionary);
    learn->setWindowTitle("Learn"); // TODO
    hide();
    learn->exec();
    show();
    delete learn;
}

/* Start a test */
void CStartWindow :: startTest()
{
    CWidget *test = new CWidget(dictionary);
    test->setWindowTitle(QString("Test: {%1 %2}").arg(dict_name, dict_vers));
    hide();
    test->exec();
    show();
    delete test;
}

void CStartWindow :: about()
{
    QString msg = QString("A simply program for learning English irregular verbs.")
                  + "<br><br>(C) Chumakov Anton I. for LBI School, 2024";
    QMessageBox::about(this, "About program", msg);
}
