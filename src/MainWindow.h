#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* ****************************************************************************
 * File:    MainWindow.h
 * Author:  Chumakov Anton I.
 * Purpose: class CMainWindow
 *          provides the form of the main window of the application
 * Date:    July 6, 2024
 * ***************************************************************************/

#include <QtWidgets>
#include <QSettings>
#include <QtXml>

class CMainWindow : public QWidget
{
    Q_OBJECT
public:
    CMainWindow(QWidget* parent = nullptr);
private:    // GUI
    //QVBoxLayout* m_topBox;  // top-level layout
    //QHBoxLayout* m_hBox;    // hor. sub-box
    //QVBoxLayout* m_cmdBox;  // buttons column
    //QFormLayout* m_aboutDictionary;
    QComboBox* m_listOfDicts;   // available dictionaries
    QPushButton* btnAddDict;
    QPushButton* btnRemoveDict;
    QPushButton* btnEditDict;
    QPushButton* btnSelectDict; // TODO: maybe delete this button
    QPushButton* btnStartLearn;
    QPushButton* btnStartTest;

    QLabel* lblDictName;
    QLabel* lblDictVers;
    QLabel* lblDictDate;
    QLabel* lblDictAuth;
    QLabel* lblDictSize;
private:    // back-end
    QDir m_dictionaryPath;  // the directory of dictionaries
    QString m_curDictFile;  // the path of the current dictionary file
    void indexDicts();
    QStringList m_dictList;
    bool loadDictionary(const QString& fpath);
    bool readDictionary();
    QDomDocument m_dictionary;  // allows read/write file
    //QDomNodeList m_dictionary;

    QString dict_name;
    QString dict_vers;
    QString dict_date;
    QString dict_auth;
    int dict_size;
public slots:
    void selectDictionary();

    void addDictionary();
    void removeDictionary();
    void editDictionary();
    void startLearning();
    void startTest();
};

#endif // MAINWINDOW_H
