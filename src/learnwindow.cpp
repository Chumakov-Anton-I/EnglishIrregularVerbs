/* ******************************************************************
 * learnwindow.cpp
 * *****************************************************************/

#include "learnwindow.h"
#include <random>
#include <algorithm>

CLearnWindow :: CLearnWindow(const QDomNodeList& dictionary, QWidget* parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), dictionary(dictionary)
{
    //setFont(QFont("Segoe UI", 14)); // TODO: make global font
    setWindowIcon(QIcon(":/ico_obook"));

    mainFrame = new QVBoxLayout();
    setLayout(mainFrame);
    /* The pane of the current word */
    WordLabel = new CWordCardSmall(); //new QLabel();
    mainFrame->addWidget(WordLabel);

    /* The pane of forms */
    formsHBLayout = new QHBoxLayout();
        lblForm2 = new CWordCardSmall();
        lblForm2->setMinimumWidth(300);
        formsHBLayout->addWidget(lblForm2);
        lblForm3 = new CWordCardSmall();
        lblForm3->setMinimumWidth(300);
        formsHBLayout->addWidget(lblForm3);
    mainFrame->addLayout(formsHBLayout);

    /* The pane of a translation */
    txtTransl = new QTextEdit();
    mainFrame->addWidget(txtTransl);

    /* Buttons */
    btnNext = new QPushButton("Next word");
    btnNext->setDefault(true);
    btnNext->setToolTip("Go to next word");
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

/* [slot] Reads a word from the dictionary and sets its values */
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
    //WordLabel->setText(QString("<br>%1<br>").arg(current_word->getWord()));
    //lblForm2->setText(QString("<br>%1<br>").arg(current_word->getForm2()));
    //lblForm3->setText(QString("<br>%1<br>").arg(current_word->getForm3()));
    QString path = QDir::currentPath() + "/sound/";
    QString fname1 = path + current_word->form1_sound;
    QString fname2 = path + current_word->form2_sound;
    QString fname3 = path + current_word->form3_sound;
    //qDebug() << "\nPath 1: " << fname1 << "\nPath 2: " << fname2 << "\nPath 3: " << fname3;
    WordLabel->setValues(current_word->form1, current_word->form1_transcr, fname1);
    lblForm2->setValues(current_word->form2, current_word->form2_transcr, fname2);
    lblForm3->setValues(current_word->form3, current_word->form3_transcr, fname3);
    txtTransl->setText(current_word->getTranslation());
    WordLabel->playSound(); // auto-play sound
    delete current_word;
    current_word = nullptr;
}
