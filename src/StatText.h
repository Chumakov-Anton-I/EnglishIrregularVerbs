#ifndef STATTEXT_H
#define STATTEXT_H

#include <QtWidgets>

class CStatText : public QWidget
{
    Q_OBJECT
public:
    CStatText(QWidget* parent = nullptr);
    ~CStatText();
private:
    QHBoxLayout* mainFrame;
    QLabel* Text;
public slots:
    void setText(const QString& text);
};

#endif // STATTEXT_H
