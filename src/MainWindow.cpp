/* ****************************************************************************
 * File:    MainWindow.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 6, 2024
 * ***************************************************************************/

#include "MainWindow.h"
#include "WndLearning.h"

extern QSettings* appSettings;  // Settings of the application (see main.cpp)

CMainWindow :: CMainWindow(QWidget* parent/* =nullptr*/)
    : QWidget(parent)
{
    /* Read settings */
    // readSettings();
    m_dictionaryPath = QDir(appSettings->value("system/dictionary_path").toString());
    /* Make the window form */
    m_topBox = new QVBoxLayout();
    setLayout(m_topBox);
    m_hBox = new QHBoxLayout();
    m_topBox->addLayout(m_hBox);
    m_listOfDicts = new QListWidget();
    m_hBox->addWidget(m_listOfDicts);
    m_cmdBox = new QVBoxLayout();
        // buttons
        btnAddDict = new QPushButton("Add dictionary...");
        btnRemoveDict = new QPushButton("Remove dictionary");
        btnEditDict = new QPushButton("Edit");
        btnSelectDict = new QPushButton("Select dictionary");
        btnStartLearn = new QPushButton("Start learning");
        btnStartTest = new QPushButton("Start test");
        m_cmdBox->addWidget(btnAddDict);
        m_cmdBox->addWidget(btnRemoveDict);
        m_cmdBox->addWidget(btnEditDict);
        m_cmdBox->addWidget(btnSelectDict);
        m_cmdBox->addSpacing(32);
        m_cmdBox->addWidget(btnStartLearn);
        m_cmdBox->addWidget(btnStartTest);
    m_hBox->addLayout(m_cmdBox);
    // ...

    /* Connect signals & slots */
    connect(btnAddDict, SIGNAL(clicked()), SLOT(addDictionary()));
    connect(btnRemoveDict, SIGNAL(clicked()), SLOT(removeDictionary()));
    connect(btnEditDict, SIGNAL(clicked()), SLOT(editDictionary()));
    connect(btnStartLearn, SIGNAL(clicked()), SLOT(startLearning()));
    connect(btnStartTest, SIGNAL(clicked()), SLOT(startTest()));

    indexDicts();   // Update list of dictionaries
}

/** Read application settings */
/*void CMainWindow :: readSettings()
{
    return;
}*/

/** Look the directory of dictionaries */
void CMainWindow :: indexDicts()
{
    m_dictionaryPath.setFilter(QDir::Files | QDir::NoSymLinks);
    //m_dictionaryPath.setSorting(QDir::Name); // Remove it!
    m_dictList = m_dictionaryPath.entryList();
    /* Update List --> TODO: make function */
    foreach (QString itemname, m_dictList) {    // add only xml-files
        if (itemname.endsWith("xml", Qt::CaseInsensitive))  //TODO: fix magic constant
            m_listOfDicts->addItem(itemname);
    }
}

/** Load a dictionary */
bool CMainWindow :: loadDictionary(const QString& fpath)
{
    /* Try to open the file */
    QFile dictfile(fpath);
    if (!dictfile.open(QIODevice::OpenModeFlag::ReadWrite)) {
        qDebug() << "Can not open file" << fpath;// TODO
        return false;
    }
    /* Try to open the opened file */
    auto res = m_dictionaryDoc.setContent(&dictfile);
    if (!res) {
        dictfile.close();
        qDebug() << "This dictionary has errors";// TODO
        return false;
    }
    dictfile.close();
    /* Read the dictionary */
    if (!readDictionary()) {
        qDebug() << "Can not read dictionary";
        return false;
    }

    return true;
}

/** Read the current dictionary */
bool CMainWindow :: readDictionary()
{
    //if (!checkDict()) return false;   // TODO: add checking the structure of a dictionary
    QDomElement root = m_dictionaryDoc.documentElement();
    m_dictionary = root.childNodes();
    return true;
}

/** Set the selected item in the List as the current item */
void CMainWindow :: selectItem()
{
    QListWidgetItem* current = m_listOfDicts->currentItem();
    m_curDictFile = m_dictionaryPath.filePath(current->text());
}

/** [slot] Add a new dictionary */
void CMainWindow :: addDictionary()
{
    qDebug() << "Adding of new dictionary";
    return;
}

/** [slot] Remove the dictionary */
void CMainWindow :: removeDictionary()
{
    selectItem();
    qDebug() << QString("Removing of the dictionary [%1]").arg(m_curDictFile);
}

/** [slot] Edit the dictionary */
void CMainWindow :: editDictionary()
{
    selectItem();
    qDebug() << "Editing the dictionary";
}

/** [slot] Start learning */
void CMainWindow :: startLearning()
{
    selectItem();
    loadDictionary(m_curDictFile);
    CWndLearning* learnWnd = new CWndLearning(m_dictionary);
    hide();
    learnWnd->exec();
    show();
    delete learnWnd;
}

/** [slot] Start test */
void CMainWindow :: startTest()
{
    selectItem();
    qDebug() << "Start test";
}
