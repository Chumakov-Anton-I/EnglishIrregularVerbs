/* ********************************************************************************************** **
 * File:    FlippedPane.cpp
 * Author:  Anton I. Chumakov
 * Date:    Aug 4, 2024
 * Purpose: class CFlippedPane - implementation
 * ********************************************************************************************** */

#include "FlippedPane.h"

CFlippedPane :: CFlippedPane(QWidget* parent)
    : QStackedWidget(parent)
{
    m_editPage = new CTextEdit(LANG_LAYOUT_ENG, this);
    m_wordPage = new CWordPane(this);
    addWidget(m_editPage);
    addWidget(m_wordPage);
}
