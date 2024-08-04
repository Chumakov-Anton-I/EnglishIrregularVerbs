#ifndef FLIPPEDPANE_H
#define FLIPPEDPANE_H

/* ********************************************************************************************** **
 * File:    FlippedPane.h
 * Author:  Anton I. Chumakov
 * Purpose: class CFlippedPane
 * Date:    Aug 4, 2024
 * ********************************************************************************************** */

#include <QFrame>
#include <QStackedWidget>
#include "TextEdit.h"
#include "WordPanes.h"

class CFlippedPane : public QStackedWidget
{
    Q_OBJECT
public:
    CFlippedPane(QWidget* parent = nullptr);
    void setValues(QString& word, QString& trans, QString& soundfile) { m_wordPage->setValues(word, trans, soundfile); }
    void setPlaceholderText(const QString& text) { m_editPage->setPlaceholderText(text); }
private:
    //QStackedWidget* m_stack;
    CTextEdit* m_editPage;
    CWordPane* m_wordPage;
};

#endif // FLIPPEDPANE_H
