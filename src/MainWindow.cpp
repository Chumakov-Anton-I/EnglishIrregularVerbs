/* ****************************************************************************
 * File:    MainWindow.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 6, 2024
 * ***************************************************************************/

#include "MainWindow.h"
#include "WndLearning.h"
#include "WndTest.h"

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
    // ComboBox is on the top
    m_listOfDicts = new QComboBox();
    m_topBox->addWidget(m_listOfDicts);
    m_hBox = new QHBoxLayout();
    m_topBox->addLayout(m_hBox);
    m_aboutDictionary = new QFormLayout();
    m_aboutDictionary->setRowWrapPolicy(QFormLayout::WrapLongRows);
    m_aboutDictionary->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    m_aboutDictionary->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_aboutDictionary->setLabelAlignment(Qt::AlignRight);
        lblDictName = new QLabel();
        m_aboutDictionary->addRow("Dictionary name:", lblDictName);
        lblDictVers = new QLabel();
        m_aboutDictionary->addRow("Dictionary version:", lblDictVers);
        lblDictAuth = new QLabel();
        m_aboutDictionary->addRow("Author:", lblDictAuth);
        lblDictDate = new QLabel();
        m_aboutDictionary->addRow("Date:", lblDictDate);
    m_hBox->addLayout(m_aboutDictionary);
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
    connect(m_listOfDicts, SIGNAL(currentIndexChanged(int)), SLOT(selectDictionary()));
    connect(btnAddDict, SIGNAL(clicked()), SLOT(addDictionary()));
    connect(btnRemoveDict, SIGNAL(clicked()), SLOT(removeDictionary()));
    connect(btnEditDict, SIGNAL(clicked()), SLOT(editDictionary()));
    connect(btnStartLearn, SIGNAL(clicked()), SLOT(startLearning()));
    connect(btnStartTest, SIGNAL(clicked()), SLOT(startTest()));

    indexDicts();   // Update list of dictionaries
}

/* * Read application settings */
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
    dict_name = root.attribute("title");
    dict_vers = root.attribute("version");
    dict_auth = root.attribute("author");
    dict_date = root.attribute("date");
    lblDictName->setText(dict_name);
    lblDictVers->setText(dict_vers);
    lblDictAuth->setText(dict_auth);
    lblDictDate->setText(dict_date);
    return true;
}

/* --------------- SLOTS ----------------- */
/** [slot] On changing a dictionary */
void CMainWindow :: selectDictionary()
{
    QString fname = m_listOfDicts->currentText();
    m_curDictFile = m_dictionaryPath.absoluteFilePath(fname);
    loadDictionary(m_curDictFile);
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
    qDebug() << QString("Removing of the dictionary [%1]").arg(m_curDictFile);
}

/** [slot] Edit the dictionary */
void CMainWindow :: editDictionary()
{
    qDebug() << "Editing the dictionary";
}

/** [slot] Start learning */
void CMainWindow :: startLearning()
{
    //loadDictionary(m_curDictFile);
    CWndLearning* learnWnd = new CWndLearning(m_dictionary);
    hide();
    learnWnd->exec();
    show();
    delete learnWnd;
}

/** [slot] Start test */
void CMainWindow :: startTest()
{
    //loadDictionary(m_curDictFile);
    CWndTest* testWnd = new CWndTest(m_dictionary);
    hide();
    testWnd->exec();
    show();
    delete testWnd;
}
