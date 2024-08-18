/* ********************************************************************************************** **
 *
 * ********************************************************************************************** */

#include "ReportWnd.h"

CReportWnd :: CReportWnd(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Statistics");
    QVBoxLayout* vbox = new QVBoxLayout(this);
    setLayout(vbox);
    QFormLayout* form = new QFormLayout(this);
    vbox->addLayout(form);
    form->setRowWrapPolicy(QFormLayout::DontWrapRows);
    form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    form->setLabelAlignment(Qt::AlignRight);
    lblTotal = new QLineEdit(this);
    lblTotal->setReadOnly(true);
    form->addRow("Size of dictionary", lblTotal);
    lblScore = new QLineEdit(this);
    lblScore->setReadOnly(true);
    form->addRow("Learned", lblScore);
    lblRight = new QLineEdit(this);
    lblRight->setReadOnly(true);
    form->addRow("Right", lblRight);

    QPushButton* btnOK = new QPushButton("OK");
    vbox->addWidget(btnOK);

    connect(btnOK, SIGNAL(clicked()), SLOT(accept()));
}

void CReportWnd :: setData(int total, int score, int right)
{
    double percent = 100.0*right/total;
    lblTotal->setText(QString::number(total));
    lblScore->setText(QString::number(score));
    lblRight->setText(QString("%1 (%2)").arg(right).arg(percent, 0, 'f', 1));
}

/*void CReportWnd :: onOK()
{
    this->close();
    accept();
}*/
