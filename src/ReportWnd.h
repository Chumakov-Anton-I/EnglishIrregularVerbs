#ifndef REPORTWND_H
#define REPORTWND_H

/************************************************************************************************ **
 * File:    ReportWnd.h
 * Author:  Chumakov Anton I.
 * Date:    August 6, 2024
 * Purpose: CReportWnd class
 * ********************************************************************************************** */

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

class CReportWnd : public QDialog
{
    Q_OBJECT
public:
    CReportWnd(QWidget* parent = nullptr);
    void setData(int total, int score, int right);
private:
    QLineEdit* lblTotal;  // Size of the dictionary
    QLineEdit* lblScore;  // Count of learned words
    QLineEdit* lblRight;  // Number of right answers
};

#endif // REPORTWND_H
