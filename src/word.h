#ifndef WORD_H
#define WORD_H

/* ****************************************************************************
 * File:    word.h
 * Author:  Chumakov Anton I.
 * Purpose: class CWord
 *          an object, which contains the information about a word
 *          This class keeps the reference to the passed element, reads data
 *          from it [and updates this data (TODO)]
 * Date:    June 15, 2024
 * TODO: remake the interface of this class
 * ****************************************************************************/

#include <QtXml>
#include <QString>

struct Result
{
    QString form2;
    QString form3;
    QString translation;
    bool state;

    explicit operator bool() const noexcept { return state; }
};

class CWord
{
public:
    CWord();

    QString getWord() { return QString("<big>%1</big><br>[%2]").arg(form1, form1_transcr); }
    QString getForm2() { return QString("%1<br>%2").arg(form2, form2_transcr); }
    QString getForm3() { return QString("%1<br>%2").arg(form3, form3_transcr); }
    QString getTranslation() { return translation.join("; "); }
    QString getExample() { return example.join("\n"); }
    QString getExampleTrans() { return example_transl.join("\n"); }
    Result check(const QString&, const QString&, const QString&);
    QString id = "";    // why?
    bool setWord(const QDomElement&);
    void reset();
public: // TODO: hide this members
    QString form1;  // infinitive
    QString form1_transcr;
    QString form1_sound;

    QString form2;  // past
    QString form2_transcr;
    QString form2_sound;

    QString form3;  // participle II
    QString form3_transcr;
    QString form3_sound;

    QStringList translation;    // translation
    QStringList example;        // examples
    QStringList example_transl; // examples with translation
private:
    QDir m_sound_path;
    int m_countToDone;
    QString format(QString s, QString color = "", bool bold = false, bool italic = false);
    QString getFormattedText(const QDomElement&);
    const QString colorRed      = "#8B0000";
    const QString colorGreen    = "#006400";
    //const QString XML_ID        = "id";
    //const QString XML_SOUND     = "sound";
    //const QString XML_TEXT      = "text";
    //const QString XML_FORM1     = "form1";
    //const QString XML_FORM2     = "form2";
    //const QString XML_FORM3     = "form3";
    //const QString XML_TRANSLATION = "translation";
    //const QString XML_EXAMPLE   = "example";
    //const QString XML_STATISTICS = "statistics";
};

#endif // WORD_H
