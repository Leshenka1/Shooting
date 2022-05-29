#include "inputdialog.h"
#include <QtDebug>
#include <QApplication>
#include <QValidator>

InputDialog::InputDialog(QWidget* pwgt):
QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    m_rad1 = new QLineEdit;
    m_rad2 = new QLineEdit;
    QLabel* plblRad1 = new QLabel();
    QLabel* plblRad2 = new QLabel();
    plblRad1->setText( tr( "<font size=4> <b>Diameter of 1-st cicle</b></font>" ) );
    plblRad2->setText( tr( "<font size=4> <b>Diameter of 2-nd cicle</b></font>" ) );

    plblRad1->setBuddy(m_rad1);
    plblRad2->setBuddy(m_rad2);
    m_rad1->setValidator(new QIntValidator(this));
    m_rad2->setValidator(new QIntValidator(this));

    inWinSize = 500;

    QPushButton* pcmdOk = new QPushButton("&Ok");
   // QPushButton* pcmdCancel = new QPushButton("&Cancel");
    pcmdCancel = new QPushButton("&Cancel");
    connect(pcmdOk, SIGNAL(clicked()), SLOT(pcmdOk_clicked()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(pcmdCancel_clicked()));
    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblRad1, 0, 0);
    ptopLayout->addWidget(plblRad2, 1, 0);
    ptopLayout->addWidget(m_rad1, 0, 1);
    ptopLayout->addWidget(m_rad2, 1, 1);
    ptopLayout->addWidget(pcmdOk, 2,0);
    ptopLayout->addWidget(pcmdCancel, 2, 1);
    setLayout(ptopLayout);
}

int InputDialog::getInputRad1() const
{
    QString strRad1 = m_rad1->text();
    int numRad1 = strRad1.toInt();
    return numRad1;
}

int InputDialog::getInputRad2() const
{
    QString strRad2 = m_rad2->text();
    int numRad2 = strRad2.toInt();
    return numRad2;
}

void InputDialog::pcmdCancel_clicked()
{
    exit(0);
}

void InputDialog::pcmdOk_clicked()
{
    if(getInputRad1() <= getInputRad2())
    {
        QMessageBox::information(this,tr("Ошибка"),tr("Диаметр внутренней окружности должен быть меньше внешней"));
        return;
    }
    else if(getInputRad1() > inWinSize )
    {
        QString sWinSize = "Диаметр внешней окружности не должен первосходить высоты окна (" + QString::number(inWinSize) + "пк)";
        QMessageBox::information(this,tr("Ошибка"),sWinSize);
        return;
    }
    else
    {
        this->accept();
    }
}
