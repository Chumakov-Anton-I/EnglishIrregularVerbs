/* ****************************************************************************
 * window.cpp
 * ****************************************************************************/

#include "WndTest.h"
#include <random>
#include <algorithm>
#include "settings_key.h"
#include "ReportWnd.h"

CWndTest :: CWndTest(QDomDocument& dictionary, QWidget *parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), m_document(dictionary)
{
    setMinimumSize(600, 320);
    setWindowIcon(QIcon(":/ico_run"));

    QVBoxLayout* mainVbox = new QVBoxLayout(this);  // top-level layout
    setLayout(mainVbox);
    /* The pane with the current word */
    WordLabel = new CWordPane(true, this);
    //ResultLabel = new CLabel(this);
    mainVbox->addWidget(WordLabel);
    //mainVbox->addWidget(ResultLabel);

    /* Pane of verb forms */
    QHBoxLayout* formsHBLayout = new QHBoxLayout();
        /* the pane of the Past Simple (Form 2) */
        Form2Stack = new QStackedWidget(this);
            Form2Edit = new CTextEdit(LANG_LAYOUT_ENG, this);
            Form2Edit->setPlaceholderText("<type the Past form>");
            Form2Edit->setToolTip("Type the past form");
            Form2Pane = new CWordPane(false, this);
            Form2Stack->addWidget(Form2Edit);
            Form2Stack->addWidget(Form2Pane);
        formsHBLayout->addWidget(Form2Stack);
        /* the pane of the Participle II (Form 3) */
        Form3Stack = new QStackedWidget(this);
            Form3Edit = new CTextEdit(LANG_LAYOUT_ENG, this);
            Form3Edit->setPlaceholderText("<type the Participle II form>");
            Form3Edit->setToolTip("Type the participle II form");
            Form3Pane = new CWordPane(false, this);
            Form3Stack->addWidget(Form3Edit);
            Form3Stack->addWidget(Form3Pane);
        formsHBLayout->addWidget(Form3Stack);
    mainVbox->addLayout(formsHBLayout);

    /* translation pane */
    TranslationEdit = new CTextEdit(LANG_LAYOUT_RUS, this);
    TranslationEdit->setPlaceholderText("<type the Translation>");
    TranslationEdit->setToolTip("Type the word or the first letter of the word");
    TranslationEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    mainVbox->addWidget(TranslationEdit);

    /* Buttons pane */
    QHBoxLayout* commHBLayout = new QHBoxLayout();
        QLabel* hintLabel = new QLabel("Press 'Tab' to switch edit,<br>press 'Enter' to check.", this);
        hintLabel->setObjectName("TestHintLabel");
        hintLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        btnCheck = new QPushButton("Check", this);
        btnCheck->setDefault(true);
        btnCheck->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        btnResume = new QPushButton("Resume", this);
        btnResume->setIcon(QIcon(":/ico_xoctagon"));
        btnResume->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        commHBLayout->addWidget(hintLabel);
        commHBLayout->addSpacing(25);
        commHBLayout->addWidget(btnResume);
        commHBLayout->addWidget(btnCheck);
    mainVbox->addLayout(commHBLayout);

    // set tab order
    QWidget::setTabOrder(Form2Edit, Form3Edit);
    QWidget::setTabOrder(Form3Edit, TranslationEdit);
    QWidget::setTabOrder(TranslationEdit, btnCheck);
    // Add signals
    connect(btnCheck, SIGNAL(clicked()), this, SLOT(check()));
    connect(btnResume, SIGNAL(clicked()), this, SLOT(resume()));
    connect(Form2Edit, SIGNAL(enter()), this, SLOT(on_enter()));
    connect(Form3Edit, SIGNAL(enter()), this, SLOT(on_enter()));
    connect(TranslationEdit, SIGNAL(enter()), this, SLOT(on_enter()));

    prepareDictionary();
    start();
}

CWndTest :: ~CWndTest()
{
    //delete currentWord; // Надо ли это?
    //currentWord = nullptr;
}

/** Prepare the dictionary */
void CWndTest :: prepareDictionary()
{
    QDomElement e = m_document.documentElement();
    QString d_name = e.attribute("title");
    dictionary = e.childNodes();
    count = dictionary.length();
    setWindowTitle(QString("Test {%1, %2 words}").arg(d_name).arg(count));
    /* Make the random order of words */
    for (int i = 0; i < count; i++)
        order.push_back(i);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(order), std::end(order), rng);
}

/** Read the word */
bool CWndTest :: readWord()
{
    while (true) {
        if (order.empty())
            return false;   // the dictionary is empty
        /* get random word */
        int i = order.back();
        order.pop_back();
        currentWordNode = dictionary.item(i);
        if (currentWord.setWord(currentWordNode.toElement()))
            break;  // the word was read
    }
    /* fill cards */
    WordLabel->setValues(currentWord.form1, currentWord.form1_transcr, currentWord.form1_sound);
    WordLabel->setExample(currentWord.getExample());
    Form2Pane->setValues(currentWord.form2, currentWord.form2_transcr, currentWord.form2_sound);
    Form3Pane->setValues(currentWord.form3, currentWord.form3_transcr, currentWord.form3_sound);
    WordLabel->playSound(); // auto-play sound
    return true;
}

/** Begin test */
void CWndTest :: start()
{
    // Clear all edit boxes
    Form2Stack->setCurrentIndex(0);
    Form3Stack->setCurrentIndex(0);
    Form2Edit->clear();
    Form3Edit->clear();
    TranslationEdit->clear();
    //ResultLabel->reset();

    if (!readWord()) {  // go to resume
        btnCheck->hide(); //setEnabled(false);
        return;
    }
    //
    btnCheck->setText("Check");
    disconnect(btnCheck, SIGNAL(clicked()), this, SLOT(start()));
    connect(btnCheck, SIGNAL(clicked()), SLOT(check()));
    Form2Edit->setFocus();
}

/** Check the word */
void CWndTest :: check()
{
    // flip stacked widgets
    Form2Stack->setCurrentIndex(1);
    Form3Stack->setCurrentIndex(1);
    WordLabel->setExample(currentWord.getExampleTrans());
    Result res = currentWord.check(Form2Edit->toPlainText(), Form3Edit->toPlainText(), TranslationEdit->toPlainText());
    Form2Edit->setText(res.form2);
    Form3Edit->setText(res.form3);
    TranslationEdit->setText(res.translation);
    if (res) {
        //ResultLabel->setStatus(true);
        score_succ++;   // inc successiful score
        /* Update statistics */
        //QString id = currentWord.id;
        //int x = statistics.value(id, 0);
        //statistics[id] = ++x;
        updateStatistics(bool(res));    // update general statistics
    }
    /*else
        ResultLabel->setStatus(false);*/
    score++;    // inc general score
    //currentWord.reset();  // reset the value of the word object (TODO)
    if (order.empty()) {
        btnCheck->setDefault(false);
        btnCheck->setEnabled(false);
        btnResume->setDefault(true);
        btnResume->setFocus(Qt::FocusReason::TabFocusReason);
        return;
    }
    // re-connect signals & slots
    btnCheck->setText("Next");
    disconnect(btnCheck, SIGNAL(clicked()), this, SLOT(check()));
    connect(btnCheck, SIGNAL(clicked()), SLOT(start()));
}

/** End working and show a report */
void CWndTest :: resume()
{
    CReportWnd* reportBox = new CReportWnd(this);
    reportBox->setData(count, score, score_succ);
    reportBox->exec();
    delete reportBox;
    this->close();
}

/** @Simulate button press */
void CWndTest :: on_enter()
{
    if (!btnCheck->isEnabled())
        btnResume->click();
    btnCheck->click();
}

/** @Check statistics of word */
bool CWndTest :: readStatistics(const QDomNode& node)
{
    QDomElement element = node.toElement();
    QDomNode statNode = element.namedItem("statistics");
    if (statNode.isNull())
        return true;
    QDomElement statElement = statNode.toElement();
    if (statElement.attribute("status").toInt() >= appSettings->value(ini_system::count_to_done).toInt())
        return false;   // this word is already learnt
    return true;
}

void CWndTest :: updateStatistics(bool state)
{
    if (!state) return;  // Do nothing if it isn't OK
    QDomNode statNode = currentWordNode.namedItem("statistics");
    if (statNode.isNull()) { // create statistics node
        QDomElement statElem = m_document.createElement("statistics");
        statElem.setAttribute("status", 1);
        currentWordNode.appendChild(statElem);
    }
    else { // rewrite node
        QDomElement statElem = statNode.toElement();
        int x = statElem.attribute("status").toInt();
        statElem.setAttribute("status", ++x);
    }
}
