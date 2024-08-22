/* ****************************************************************************
 * File:    WndLearning.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 7, 2024
 * ***************************************************************************/

#include "WndLearning.h"
#include <random>
#include <algorithm>

CWndLearning :: CWndLearning(QDomDocument& dictionary, QWidget* parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), m_document(dictionary)
{
    QVBoxLayout* topBox = new QVBoxLayout();
    setLayout(topBox);
    m_currWordPane = new CWordPane(true, this);
    topBox->addWidget(m_currWordPane);
    QHBoxLayout* formsBox = new QHBoxLayout();
        m_form2Pane = new CWordPane(false, this);
        m_form3Pane = new CWordPane(false, this);
        formsBox->addWidget(m_form2Pane);
        formsBox->addWidget(m_form3Pane);
    topBox->addLayout(formsBox);
    m_translation = new QTextEdit(this);
    m_translation->setReadOnly(true);
    topBox->addWidget(m_translation);
    btnNext = new QPushButton("Next word", this);
    topBox->addWidget(btnNext);

    /* Connect signal & slots */
    connect(btnNext, SIGNAL(clicked()), this, SLOT(nextWord()));

    prepareDictionary();
    nextWord();
}

/** Reads the dictionary and makes a random order of words */
void CWndLearning :: prepareDictionary()
{
    QDomElement e = m_document.documentElement();
    QString d_name = e.attribute("title");
    m_dictionary = e.childNodes();
    int count = m_dictionary.length();
    setWindowTitle(QString("Learning {%1, %2 words}").arg(d_name).arg(count));  // TODO
    for (int i = 0; i < count; i++)
        m_order.push_back(i);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(m_order.begin(), m_order.end(), rng);
}

/** [slot] Sets a next word */
void CWndLearning :: nextWord()
{
    while (true) {
        if (m_order.isEmpty()) {
            btnNext->setDisabled(true);
            return;
        }
        int i = m_order.back();
        m_order.pop_back();
        QDomNode node = m_dictionary.item(i);
        if (current_word.setWord(node.toElement()))
            break;
    }
    /* Init panes with word */ // TODO: исправить это чудовищное безобразие
    m_currWordPane->setValues(current_word.form1, current_word.form1_transcr, current_word.form1_sound);
    m_currWordPane->setExample(current_word.getExampleTrans());
    m_form2Pane->setValues(current_word.form2, current_word.form2_transcr, current_word.form2_sound);
    m_form3Pane->setValues(current_word.form3, current_word.form3_transcr, current_word.form3_sound);
    m_translation->setText(current_word.getTranslation());
    m_currWordPane->playSound();    //auto-play

    //current_word.reset();
}
