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
    //setWindowIcon();  // TODO
    /* Read settings */
    m_dictionaryPath = QDir(appSettings->value(ini_system::dictionary_path).toString());
    /* Make the window form */
    QVBoxLayout* topBox = new QVBoxLayout();    // top-level layout
    setLayout(topBox);
    // ComboBox is on the top
    m_listOfDicts = new QComboBox(this);
    topBox->addWidget(m_listOfDicts);
    QHBoxLayout* hBox = new QHBoxLayout();  // hor. sub-box
    topBox->addLayout(hBox);
    QGroupBox* g_abOut = new QGroupBox("Dictionary info", this);
    g_abOut->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    hBox->addWidget(g_abOut);
    QFormLayout* aboutDictionary = new QFormLayout();
    aboutDictionary->setRowWrapPolicy(QFormLayout::WrapLongRows);
    aboutDictionary->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    aboutDictionary->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    aboutDictionary->setLabelAlignment(Qt::AlignRight);
        lblDictName = new QLabel(this); // dict name
        lblDictName->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        aboutDictionary->addRow("Dictionary name:", lblDictName);
        lblDictVers = new QLabel(this); // dict version
        lblDictVers->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        aboutDictionary->addRow("Dictionary version:", lblDictVers);
        lblDictAuth = new QLabel(this); // dict author
        lblDictAuth->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        aboutDictionary->addRow("Author:", lblDictAuth);
        lblDictDate = new QLabel(this); // dict date
        lblDictDate->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        aboutDictionary->addRow("Date:", lblDictDate);
        lblDictSize = new QLabel(this); // dict size
        lblDictSize->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        aboutDictionary->addRow("Count:", lblDictSize);
        QFrame* delim = new QFrame(this);
        delim->setFrameStyle(QFrame::HLine | QFrame::Sunken);
        aboutDictionary->addRow(delim);
        // ... TODO: add statistics
    g_abOut->setLayout(aboutDictionary);
    QVBoxLayout* cmdBox = new QVBoxLayout();    // buttons column
        // buttons
        btnAddDict = new QPushButton("Add dictionary...", this);
        btnRemoveDict = new QPushButton("Remove dictionary", this);
        btnEditDict = new QPushButton("Edit", this);
        //btnSelectDict = new QPushButton("Select dictionary", this);
        btnStartLearn = new QPushButton("Start learning", this);
        btnStartTest = new QPushButton("Start test", this);
        cmdBox->addWidget(btnAddDict);
        cmdBox->addWidget(btnRemoveDict);
        cmdBox->addWidget(btnEditDict);
        cmdBox->addStretch();
        cmdBox->addWidget(btnStartLearn);
        cmdBox->addWidget(btnStartTest);
    hBox->addLayout(cmdBox);
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

/** @Look the directory of dictionaries */
void CMainWindow :: indexDicts()
{
    m_dictionaryPath.setFilter(QDir::Files | QDir::NoSymLinks);
    m_dictList = m_dictionaryPath.entryList();
    m_listOfDicts->clear();
    /* Update List --> TODO: make function */
    foreach (QString itemname, m_dictList) {    // add only xml-files
        if (itemname.endsWith("xml", Qt::CaseInsensitive))  //TODO: fix magic constant
            m_listOfDicts->addItem(itemname);
    }
}

/** @Load a dictionary */
bool CMainWindow :: loadDictionary(const QString& fpath)
{
    /* Try to open the file */
    QFile dictfile(fpath);
    if (!dictfile.open(QIODevice::OpenModeFlag::ReadWrite)) {
        qDebug() << "{loadDictionary}: Can not open file" << fpath;   // TODO
        return false;
    }
    /* Try to parse the opened file */
    auto res = m_dictionary.setContent(&dictfile);
    if (!res) {
        dictfile.close();
        qDebug() << "{loadDictionary}: This dictionary has errors";   // TODO
        return false;
    }
    dictfile.close();
    /* Read the dictionary */
    if (!readDictionary()) {
        qDebug() << "{loadDictionary}: Can not read dictionary";  // TODO
        return false;
    }
    return true;
}

/** @Read the current dictionary */
bool CMainWindow :: readDictionary()
{
    //if (!checkDict()) return false;   // TODO: add checking the structure of a dictionary
    QDomElement root = m_dictionary.documentElement();
    QDomNodeList words = root.elementsByTagName(XML_DICT::TAG_WORD);
    dict_name = root.attribute("title");
    dict_vers = root.attribute("version");
    dict_auth = root.attribute("author");
    dict_date = root.attribute("date");
    lblDictName->setText(dict_name);
    lblDictVers->setText(dict_vers);
    lblDictAuth->setText(dict_auth);
    lblDictDate->setText(dict_date);
    lblDictSize->setText(QString::number(words.length()));
    return true;
}

/* ----------------------- SLOTS --------------------------- */
/** [slot] On changing a dictionary */
void CMainWindow :: selectDictionary()
{
    QString fname = m_listOfDicts->currentText();
    m_curDictFile = m_dictionaryPath.absoluteFilePath(fname);
    loadDictionary(m_curDictFile);
}

/** [slot] Add a new dictionary */
void CMainWindow :: addDictionary() // TODO: remake this very ugly function
{
    QString addedFileName = QFileDialog::getOpenFileName(this, "Choose file", "", "Dictionaries (*.xml)");
    if (addedFileName.isEmpty())
        return;
    QString dictpath(appSettings->value(ini_system::dictionary_path).toString());
    QFileInfo addedFileInfo(addedFileName);
    QString newFileName = dictpath + "/" + addedFileInfo.fileName();
    while (!QFile::copy(addedFileName, newFileName)) {
        newFileName = QFileDialog::getSaveFileName(this, "Save dictionary as", dictpath, "Dictionaries (*.xml)");
        if (newFileName.isEmpty())
            return;
    }
    QFileInfo newFileInfo(newFileName);
    m_listOfDicts->addItem(newFileInfo.fileName());
}

/** [slot] Remove the dictionary */
void CMainWindow :: removeDictionary()
{
    int ret = QMessageBox::warning(this, "Delete dictionary",
                                   "Do you want to delete the cirrent dictonary?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        QFile::remove(m_curDictFile);
        m_listOfDicts->removeItem(m_listOfDicts->currentIndex());
    }
}

/** [slot] Edit the dictionary */
void CMainWindow :: editDictionary()
{
    qDebug() << "Editing the dictionary";
}

/** [slot] Start learning */
void CMainWindow :: startLearning()
{
    CWndLearning* learnWnd = new CWndLearning(m_dictionary);
    hide();
    learnWnd->exec();
    show();
    delete learnWnd;
}

/** [slot] Start test */
void CMainWindow :: startTest()
{
    CWndTest* testWnd = new CWndTest(m_dictionary);
    hide();
    testWnd->exec();
    QFile wfile(m_curDictFile); // save statistics
    if (wfile.open(QIODevice::WriteOnly)) {
        QTextStream out(&wfile);
        m_dictionary.save(out, 2);
        wfile.close();
    }
    else
        qDebug() << "Can not save file";    // TODO
    show();
    delete testWnd;
}
