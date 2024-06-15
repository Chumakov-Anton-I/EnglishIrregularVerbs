#include "TextEdit.h"

CTextEdit :: CTextEdit(LPCWSTR lang, QTextEdit *parent)
    : QTextEdit(parent), lang_id(lang)
{
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    this->setTabChangesFocus(true);
}

CTextEdit :: ~CTextEdit()
{
}

/* Intercepts focus event and switches keyboard language */
void CTextEdit :: focusInEvent(QFocusEvent *e)
{
#if defined(Q_OS_WIN)
    LoadKeyboardLayoutW(lang_id, KLF_ACTIVATE);
#endif
    QTextEdit::focusInEvent(e);
}

/* Intercept 'Enter' press event */
void CTextEdit :: keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        emit enter();
        return;
    }
    QTextEdit::keyPressEvent(e);
}
