/* ****************************************************************************
 * File:    WndLearning.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 7, 2024
 * ***************************************************************************/

#include "WndLearning.h"
#include <random>
#include <algorithm>

CWndLearning :: CWndLearning(QDomNodeList& dictionary, QWidget* parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), m_dictionary(dictionary)
{
    /* Make gui */
    m_topBox = new QVBoxLayout();
    setLayout(m_topBox);
    m_currWordPane = new CWordPane();
    m_topBox->addWidget(m_currWordPane);
    m_formsBox = new QHBoxLayout();
        m_form2Pane = new CWordPane();
        m_form3Pane = new CWordPane();
        m_formsBox->addWidget(m_form2Pane);
        m_formsBox->addWidget(m_form3Pane);
    m_topBox->addLayout(m_formsBox);
    m_translation = new QTextEdit();
    m_translation->setReadOnly(true);
    m_topBox->addWidget(m_translation);
    btnNext = new QPushButton("Next word");
    m_topBox->addWidget(btnNext);

    /* Connect signal & slots */
    connect(btnNext, SIGNAL(clicked()), SLOT(nextWord()));

    prepareDictionary();
    nextWord();
}

/** [slot] Sets a next word */
void CWndLearning :: nextWord()
{
    if (m_order.isEmpty()) {
        btnNext->setDisabled(true);
        return;
    }
    int i = m_order.back();
    m_order.pop_back();
    QDomNode node = m_dictionary.item(i);
    current_word = new CWord(node.toElement());
    /* Init panes with word */ // TODO: исправить это чудовищное безобразие
    m_currWordPane->setValues(current_word->form1, current_word->form1_transcr, current_word->form1_sound);
    m_form2Pane->setValues(current_word->form2, current_word->form2_transcr, current_word->form2_sound);
    m_form3Pane->setValues(current_word->form3, current_word->form3_transcr, current_word->form3_sound);
    m_translation->setText(current_word->getTranslation());

    delete current_word;
    current_word = nullptr;
}

/** Make a random order of words */
void CWndLearning :: prepareDictionary()
{
    int count = m_dictionary.length();
    for (int i = 0; i < count; i++)
        m_order.push_back(i);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(m_order.begin(), m_order.end(), rng);
}
