#ifndef WNDLEARNING_H
#define WNDLEARNING_H

/* ****************************************************************************
 * File:    WndLearning.h
 * Author:  Chumakov Anton I.
 * Purpose: class CWndLearning
 *          allows learn words from a dictionary
 * Date:    July 6, 2024
 * ***************************************************************************/

#include <QtWidgets>
#include <QtXml>
#include "word.h"
#include "WordPanes.h"

class CWndLearning : public QDialog
{
    Q_OBJECT
public:
    CWndLearning(QDomDocument& dictionary, QWidget* parent = nullptr);
private:    // GUI
    CWordPane* m_currWordPane;
    CWordPane* m_form2Pane;
    CWordPane* m_form3Pane;
    QTextEdit* m_translation;
    QPushButton* btnNext;
    QDomDocument m_document;  // active dictionary (reference)
    QDomNodeList m_dictionary;
public slots:
    void nextWord();
private:    // back-end
    void prepareDictionary();
    QVector<int> m_order;
    CWord current_word;   // current word
};

#endif // WNDLEARNING_H
