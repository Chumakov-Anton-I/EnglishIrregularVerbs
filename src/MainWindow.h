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

//QSettings* appSettings;

class CMainWindow : public QWidget
{
    Q_OBJECT
public:
    CMainWindow(QWidget* parent = nullptr);
    //~CMainWindow();
private:    // GUI
    QVBoxLayout* m_topBox;    // top-level layout
    QHBoxLayout* m_hBox;
    QVBoxLayout* m_cmdBox;
    QListWidget* m_listOfDicts;   // available dictionaries
    QPushButton* btnAddDict;
    QPushButton* btnRemoveDict;
    QPushButton* btnEditDict;
    QPushButton* btnSelectDict; // TODO: maybe delete this button
    QPushButton* btnStartLearn;
    QPushButton* btnStartTest;
private:    // back-end
    //void readSettings();
    QDir m_dictionaryPath;  // the directory of dictionaries
    QString m_curDictFile;  // the path of the current dictionary file
    void indexDicts();
    QStringList m_dictList;
    bool loadDictionary(const QString& fpath);
    bool readDictionary();
    QDomDocument m_dictionaryDoc;  // allows read/write file
    QDomNodeList m_dictionary;
    void selectItem();
    //QSettings* appSettings;
public slots:
    void addDictionary();
    void removeDictionary();
    void editDictionary();
    //void selectDictionary();
    void startLearning();
    void startTest();
};

#endif // MAINWINDOW_H
