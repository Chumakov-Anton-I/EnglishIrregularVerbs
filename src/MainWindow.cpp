/* ****************************************************************************
 * File:    MainWindow.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 6, 2024
 * ***************************************************************************/

#include "MainWindow.h"
#include "WndLearning.h"
#include "WndTest.h"
#include "settings_key.h"

extern QSettings* appSettings;  // Settings of the application (see main.cpp)

CMainWindow :: CMainWindow(QWidget* parent/* =nullptr*/)
    : QWidget(parent)
{
    /* Read settings */
    // readSettings();
    m_dictionaryPath = QDir(appSettings->value(ini_system::dictionary_path).toString());
    /* Make the window form */
    m_topBox = new QVBoxLayout();
    setLayout(m_topBox);
    // ComboBox is on the top
    m_listOfDicts = new QComboBox(this);
    //m_listOfDicts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_topBox->addWidget(m_listOfDicts);
    m_hBox = new QHBoxLayout();
    m_topBox->addLayout(m_hBox);
    QGroupBox* g_abOut = new QGroupBox("Dictionary info", this);
    m_hBox->addWidget(g_abOut);
    m_aboutDictionary = new QFormLayout();
    m_aboutDictionary->setRowWrapPolicy(QFormLayout::WrapLongRows);
    m_aboutDictionary->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    m_aboutDictionary->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_aboutDictionary->setLabelAlignment(Qt::AlignRight);
        lblDictName = new QLabel(this);
        lblDictName->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        m_aboutDictionary->addRow("Dictionary name:", lblDictName);
        lblDictVers = new QLabel(this);
        lblDictVers->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        m_aboutDictionary->addRow("Dictionary version:", lblDictVers);
        lblDictAuth = new QLabel(this);
        lblDictAuth->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        m_aboutDictionary->addRow("Author:", lblDictAuth);
        lblDictDate = new QLabel(this);
        lblDictDate->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        m_aboutDictionary->addRow("Date:", lblDictDate);
        QFrame* delim = new QFrame(this);
        delim->setFrameStyle(QFrame::HLine | QFrame::Sunken);
        m_aboutDictionary->addRow(delim);
        // ... TODO: add statistics
    g_abOut->setLayout(m_aboutDictionary);
    m_cmdBox = new QVBoxLayout();
        // buttons
        btnAddDict = new QPushButton("Add dictionary...", this);
        //btnAddDict->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btnRemoveDict = new QPushButton("Remove dictionary", this);
        btnEditDict = new QPushButton("Edit", this);
        btnSelectDict = new QPushButton("Select dictionary", this);
        btnStartLearn = new QPushButton("Start learning", this);
        btnStartTest = new QPushButton("Start test", this);
        m_cmdBox->addWidget(btnAddDict);
        m_cmdBox->addWidget(btnRemoveDict);
        m_cmdBox->addWidget(btnEditDict);
        m_cmdBox->addWidget(btnSelectDict);
        //m_cmdBox->addSpacing(32);
        m_cmdBox->addStretch();
        m_cmdBox->addWidget(btnStartLearn);
        m_cmdBox->addWidget(btnStartTest);
    m_hBox->addLayout(m_cmdBox);
    // ...

    /* Connect signals & slots */
    connect(m_listOfDicts, SIGNAL(currentIndexChanged(int)), this, SLOT(selectDictionary()));
    connect(btnAddDict, SIGNAL(clicked()), this, SLOT(addDictionary()));
    connect(btnRemoveDict, SIGNAL(clicked()), this, SLOT(removeDictionary()));
    connect(btnEditDict, SIGNAL(clicked()), this, SLOT(editDictionary()));
    connect(btnStartLearn, SIGNAL(clicked()), this, SLOT(startLearning()));
    connect(btnStartTest, SIGNAL(clicked()), this, SLOT(startTest()));

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
