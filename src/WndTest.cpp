/* ****************************************************************************
 * window.cpp
 * ****************************************************************************/

#include "window.h"
#include <random>
#include <algorithm>

CWidget :: CWidget(QDomNodeList& dictionary, QSettings* settings, QWidget *parent)
    : QDialog(parent, Qt::Window), dictionary(dictionary), app_settings(settings)
{
    setMinimumSize(400, 290);
    setFont(QFont("Segoe UI", 14));
    setWindowIcon(QIcon(":/ico_run"));

    mainVbox = new QVBoxLayout();
    setLayout(mainVbox);
    /* The pane with the current word */
    WordLabel = new CWordCardSmall(); //QLabel();
    WordLabel->setFrameStyle(QFrame::Shape::WinPanel | QFrame::Shadow::Sunken);
    //WordLabel->setFont(QFont("Times New Roman", 16));
    //WordLabel->setStyleSheet("QLabel { background-color: #FFFFFF; }");
    ResultLabel = new CLabel();
    mainVbox->addWidget(WordLabel);
    mainVbox->addWidget(ResultLabel);

    /* Панель форм */
    formsHBLayout = new QHBoxLayout();
        /* Панель с формой прошедшего времени */
        Form2Edit = new CTextEdit();
        Form2Edit->setPlaceholderText("<type the Past form>");
        Form2Edit->setToolTip("Type the past form");
        form2VBLayout = new QVBoxLayout();
        form2VBLayout->addWidget(Form2Edit);
        formsHBLayout->addLayout(form2VBLayout);
        /* Панель с формой причастия прошедшего времени */
        Form3Edit = new CTextEdit();
        Form3Edit->setPlaceholderText("<type the Participle II form>");
        Form3Edit->setToolTip("Type the participle II form");
        form3VBLayout = new QVBoxLayout();
        form3VBLayout->addWidget(Form3Edit);
        formsHBLayout->addLayout(form3VBLayout);
    mainVbox->addLayout(formsHBLayout);

    /* translation pane */
    TranslationEdit = new CTextEdit(LANG_LAYOUT_RUS);
    TranslationEdit->setPlaceholderText("<type the Translation>");
    TranslationEdit->setToolTip("Type the word or the first letter of the word");
    mainVbox->addWidget(TranslationEdit);

    /* Панель с кнопками */
    hintLabel = new QLabel("<small><font color=\"#808080\">Press 'Tab' to switch edit,<br>press 'Enter' to check.</font></small>");
    hintLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    btnCheck = new QPushButton("Check");
    btnCheck->setDefault(true);
    btnCheck->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    btnResume = new QPushButton("Resume");
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

CWidget :: ~CWidget()
{
    delete currentWord; // Надо ли это?
    currentWord = nullptr;
}

/* Подготовка словаря */
void CWidget :: prepareDictionary()
{
    count = dictionary.length();
    /* Make the random order of words */
    //order.clear();
    for (int i = 0; i < count; i++)
        order.push_back(i);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(order), std::end(order), rng);
}

/* Читать слово */
bool CWidget :: readWord()
{
    if (order.empty())
        return false;
    /* get random 'i' */
    int i = order.back();
    order.pop_back();
    /* get word */
    QDomNode node = dictionary.item(i);
    currentWord = new CWord(node.toElement());
    // Заполнить поля
    QString sndfname = app_settings->value("system/sound_path").toString() + "/" + currentWord->form1_sound;
    WordLabel->setValues(currentWord->form1, currentWord->form1_transcr, sndfname);
    WordLabel->playSound(); // auto-play sound
    return true;
}

/* Начать работу */
void CWidget :: start()
{
    /* Очистить все поля ввода; TODO: вынести в отдельную функцию? */
    Form2Edit->clear();
    Form3Edit->clear();
    TranslationEdit->clear();
    ResultLabel->reset();

    if (!readWord()) {  // go to resume
        //btnCheck->setText("Resume");
        //disconnect(btnCheck, SIGNAL(clicked()), this, SLOT(start()));
        //connect(btnCheck, SIGNAL(clicked()), this, SLOT(resume()));
        btnCheck->hide(); //setEnabled(false);
        return;
    }
    //
    btnCheck->setText("Check");
    disconnect(btnCheck, SIGNAL(clicked()), this, SLOT(start()));
    connect(btnCheck, SIGNAL(clicked()), SLOT(check()));
    Form2Edit->setFocus();
}

/* Проверить слово */
void CWidget :: check()
{
    Result res = currentWord->check(Form2Edit->toPlainText(), Form3Edit->toPlainText(), TranslationEdit->toPlainText());
    Form2Edit->setText(res.form2);
    Form3Edit->setText(res.form3);
    TranslationEdit->setText(res.translation);
    if (res) {
        ResultLabel->setStatus(true);  //"<b><font color=\"#006400\">Right!</font></b>"
        score_succ++;   // inc successiful score
        /* Update statistics */
        QString id = currentWord->id;
        int x = statistics.value(id, 0);
        statistics[id] = ++x;
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

/* Завершить работу и вывести итог */
void CWidget :: resume()
{
    double percent = 100.0*score_succ/(double)count;
    QString msg = QString("Всего слов:\t%1\n").arg(count) +
                  QString("Изучено\t\t%1\n").arg(score) +
                  QString("Верно:\t\t%1 (%2%)").arg(score_succ).arg(percent, 0, 'f', 1);
    QMessageBox msgbox = QMessageBox(QMessageBox::Icon::Information, "Statistics", msg, QMessageBox::StandardButton::Ok);
    msgbox.exec();
    this->close();
}

void CWidget :: getReport()
{
    return; // TODO: удалить функцию?
}

/* Simulate button press */
void CWidget :: on_enter()
{
    if (!btnCheck->isEnabled())
        btnResume->click();
    btnCheck->click();
}

/* Intercepts a closing */
// TODO
/*void CWidget :: closeEvent(QCloseEvent* e)
{
    qDebug() << e->type();
    resume();
    this->close();
}*/
