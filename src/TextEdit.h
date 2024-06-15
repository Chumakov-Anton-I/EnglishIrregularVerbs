#ifndef TEXTEDIT_H
#define TEXTEDIT_H

/* ****************************************************************************
 * TextEdit.h
 * ****************************************************************************/

#include <QtWidgets>
#if defined(Q_OS_WIN)
    #include <WinUser.h>
#elif defined(Q_OS_UNIX)
// TODO
#elif defined(Q_OS_OSX)
// TODO
#endif

#define LANG_LAYOUT_RUS L"00000419"
#define LANG_LAYOUT_ENG L"00000409"

class CTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    CTextEdit(LPCWSTR lang = LANG_LAYOUT_ENG, QTextEdit *parent = nullptr);
    ~CTextEdit();

private:
    LPCWSTR lang_id;

signals:
    void enter();
private slots:
    void focusInEvent(QFocusEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // TEXTEDIT_H
