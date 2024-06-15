/* ******************************************************************
 * learnwindow.cpp
 * *****************************************************************/

#include "learnwindow.h"
#include <random>
#include <algorithm>

CLearnWindow :: CLearnWindow(const QDomNodeList& dictionary, QWidget* parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), dictionary(dictionary)
{
    setFont(QFont("Segoe UI", 14)); // TODO: make global font
    setWindowIcon(QIcon(":/ico_obook"));

    mainFrame = new QVBoxLayout();
    setLayout(mainFrame);
    /*  */
    WordLabel = new QLabel();
    WordLabel->setAlignment(Qt::AlignCenter);
    WordLabel->setFrameStyle(QFrame::Shape::WinPanel | QFrame::Shadow::Sunken);
    WordLabel->setFont(QFont("Times New Roman", 16));
    WordLabel->setStyleSheet("QLabel { background-color: #FFFFFF; }");
    mainFrame->addWidget(WordLabel);

    /* The pane of forms */
    formsHBLayout = new QHBoxLayout();
        lblForm2 = new CStatText();
        lblForm2->setMinimumWidth(300);
        formsHBLayout->addWidget(lblForm2);
        lblForm3 = new CStatText();
        lblForm3->setMinimumWidth(300);
        formsHBLayout->addWidget(lblForm3);
    mainFrame->addLayout(formsHBLayout);

    /* The pane of a translation */
    txtTransl = new QTextEdit();
    mainFrame->addWidget(txtTransl);

    /* Buttons */
    btnNext = new QPushButton("Next word");
    mainFrame->addWidget(btnNext);

    /* Connect signals and slots */
    connect(btnNext, SIGNAL(clicked()), SLOT(nextWord()));

    /* start work */
    prepareDictionary();
    nextWord();
}

CLearnWindow :: ~CLearnWindow()
{
}

void CLearnWindow :: prepareDictionary()
{
    int count = dictionary.length();
    for (int i = 0; i < count; i++)
        order.push_back(i);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(order), std::end(order), rng);
}

void CLearnWindow :: nextWord()
{
    if (order.empty()) {
        btnNext->setDisabled(true);
        return;
    }
    int i = order.back();
    order.pop_back();
    QDomNode node = dictionary.item(i);
    current_word = new CWord(node.toElement());
    //
    WordLabel->setText(QString("<br>%1<br>").arg(current_word->getWord()));
    lblForm2->setText(QString("<br>%1<br>").arg(current_word->getForm2()));
    lblForm3->setText(QString("<br>%1<br>").arg(current_word->getForm3()));
    txtTransl->setText(current_word->getTranslation());
    delete current_word;
    current_word = nullptr;
}
