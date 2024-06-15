#ifndef STARTWND_H
#define STARTWND_H

#include <QtWidgets>
#include <QSettings>
#include <QtXml>

enum loadStatus: int {OK, CHOOSE, EXIT};

class CStartWindow : public QWidget
{
    Q_OBJECT
public:
    CStartWindow(QWidget* parent = nullptr);
    ~CStartWindow();
    //void run();

private:    // GUI
    QVBoxLayout* mainFrame;
    QVBoxLayout* boxDictInfoLayout;
    //QVBoxLayout* boxLearnSettingsLayout;
    QGridLayout* gridDictInfo;
    QVBoxLayout* boxStatisticsLayout;
    QGroupBox* boxDictInfo;
    //QGroupBox* boxLearnSettings;
    QGroupBox* boxStatistics;
    QHBoxLayout* aboutFrame;

    QLabel* lbDictName;
    QLabel* lbDictNameV;
    QLabel* lbDictVersion;
    QLabel* lbDictVersionV;
    QLabel* lblDictDate;
    QLabel* lblDictDateV;
    QLabel* lbDictAuthor;
    QLabel* lbDictAuthorV;
    QLabel* lbDictSize;
    QLabel* lbDictSizeV;

    QLabel* dummyLbl;

    QPushButton* btnChooseDict;
    QPushButton* btnResetStatistics;
    QPushButton* btnStartLearning;
    QPushButton* btnStartTest;
    QPushButton* btnAbout;
    QPushButton* btnAboutQt;

    void readSettings();
    //void readStatistics();
    bool loadDictionary(const QString& fpath);
    bool readDictionary(const QDomDocument&);
private:
    QSettings* app_settings;
    QSettings* statistics;
    QMap<QString, int> wordBase;
    QDir current_dictionary;
    QString dict_file;
    QString dict_name;
    QString dict_vers;
    QString dict_date;
    QString dict_auth;
    QDomNodeList dictionary;
    int count;
    int count_to_learn;
private slots:
    void startLearning();
    void startTest();
    void about();
    void aboutQt() { QMessageBox::aboutQt(this); }
    bool chooseDictionary();
};

#endif // STARTWND_H
