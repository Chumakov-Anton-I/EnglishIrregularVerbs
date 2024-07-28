/* ****************************************************************************
 * window.cpp
 * ****************************************************************************/

#include "WndTest.h"
#include <random>
#include <algorithm>
#include "settings_key.h"

CWndTest :: CWndTest(QDomDocument& dictionary, QWidget *parent/* = nullptr*/)
    : QDialog(parent, Qt::Window), m_document(dictionary)
{
    setMinimumSize(400, 290);
    //setFont(QFont("Segoe UI", 14));   // TODO: use CSS to tune a style
    setWindowIcon(QIcon(":/ico_run"));

    mainVbox = new QVBoxLayout();
    setLayout(mainVbox);
    /* The pane with the current word */
    WordLabel = new CWordPaneFull(this);
    ResultLabel = new CLabel(this);
    mainVbox->addWidget(WordLabel);
    mainVbox->addWidget(ResultLabel);

    /* Панель форм */
    formsHBLayout = new QHBoxLayout();
        /* Панель с формой прошедшего времени */
        Form2Edit = new CTextEdit(LANG_LAYOUT_ENG, this);
        Form2Edit->setPlaceholderText("<type the Past form>");
        Form2Edit->setToolTip("Type the past form");
        form2VBLayout = new QVBoxLayout();
        form2VBLayout->addWidget(Form2Edit);
        formsHBLayout->addLayout(form2VBLayout);
        /* Панель с формой причастия прошедшего времени */
        Form3Edit = new CTextEdit(LANG_LAYOUT_ENG, this);
        Form3Edit->setPlaceholderText("<type the Participle II form>");
        Form3Edit->setToolTip("Type the participle II form");
        form3VBLayout = new QVBoxLayout();
        form3VBLayout->addWidget(Form3Edit);
        formsHBLayout->addLayout(form3VBLayout);
    mainVbox->addLayout(formsHBLayout);

    /* translation pane */
    TranslationEdit = new CTextEdit(LANG_LAYOUT_RUS, this);
    TranslationEdit->setPlaceholderText("<type the Translation>");
    TranslationEdit->setToolTip("Type the word or the first letter of the word");
    mainVbox->addWidget(TranslationEdit);

    /* Панель с кнопками */
    hintLabel = new QLabel("<small><font color=\"#808080\">Press 'Tab' to switch edit,<br>press 'Enter' to check.</font></small>", this);
    hintLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    btnCheck = new QPushButton("Check", this);
    btnCheck->setDefault(true);
    btnCheck->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    btnResume = new QPushButton("Resume", this);
    btnResume->setIcon(QIcon(":/ico_xoctagon"));
    btnResume->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    commHBLayout = new QHBoxLayout();
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
    delete currentWord; // Надо ли это?
    currentWord = nullptr;
}

/** Prepare the dictionary */
void CWndTest :: prepareDictionary()
{
    QDomElement e = m_document.documentElement();
    dictionary = e.childNodes();
    count = dictionary.length();
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
    if (order.empty())
        return false;
    /* get random word */
    int i = order.back();
    order.pop_back();
    currentWordNode = dictionary.item(i);
    currentWord = new CWord(currentWordNode.toElement());
    /* fill card */
    WordLabel->setValues(currentWord->form1, currentWord->form1_transcr, currentWord->form1_sound);
    WordLabel->playSound(); // auto-play sound
    return true;
}

/** Begin test */
void CWndTest :: start()
{
    /* Clear all edit boxes; TODO: make special function? */
    Form2Edit->clear();
    Form3Edit->clear();
    TranslationEdit->clear();
    ResultLabel->reset();

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
    Result res = currentWord->check(Form2Edit->toPlainText(), Form3Edit->toPlainText(), TranslationEdit->toPlainText());
    Form2Edit->setText(res.form2);
    Form3Edit->setText(res.form3);
    TranslationEdit->setText(res.translation);
    if (res) {
        ResultLabel->setStatus(true);
        score_succ++;   // inc successiful score
        /* Update statistics */
        QString id = currentWord->id;
        int x = statistics.value(id, 0);
        statistics[id] = ++x;
        updateStatistics(bool(res));    // update general statistics
    }
    else
        ResultLabel->setStatus(false);   //"<b><font color=\"#8B0000\">Wrong!</font></b>");
    score++;    // inc general score
    // free memory
    delete currentWord;
    currentWord = nullptr;
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
    double percent = 100.0*score_succ/(double)count;
    QString msg = QString("Всего слов:\t%1\n").arg(count) +
                  QString("Изучено\t\t%1\n").arg(score) +
                  QString("Верно:\t\t%1 (%2%)").arg(score_succ).arg(percent, 0, 'f', 1);
    QMessageBox msgbox = QMessageBox(QMessageBox::Icon::Information, "Statistics", msg, QMessageBox::StandardButton::Ok);
    msgbox.exec();
    this->close();
}

/** Simulate button press */
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
    int c = appSettings->value(ini_system::count_to_done).toInt();
    if (statElement.attribute("status").toInt() >= c)
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

/* Intercept a closing */
// TODO
/*void CWndTest :: closeEvent(QCloseEvent* e)
{
    qDebug() << e->type();
    resume();
    this->close();
}*/
