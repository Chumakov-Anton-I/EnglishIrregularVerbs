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
    CWndLearning(QDomNodeList& dictionary, QWidget* parent = nullptr);
    //~CWndLearning();
private:    // GUI
    QVBoxLayout* m_topBox;
    CWordPane* m_currWordPane; // TODO: change class
    QHBoxLayout* m_formsBox;
    CWordPane* m_form2Pane;
    CWordPane* m_form3Pane;
    QTextEdit* m_translation;
    QPushButton* btnNext;
    QDomNodeList m_dictionary;  // active dictionary (reference)
public slots:
    void nextWord();
private:    // back-end
    void prepareDictionary();
    QVector<int> m_order;
    CWord* current_word;   // current word
};

#endif // WNDLEARNING_H
