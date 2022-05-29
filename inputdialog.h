#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QString>

class InputDialog: public QDialog {
    Q_OBJECT
private:
    QLineEdit* m_rad1;
    QLineEdit* m_rad2;
public:
    InputDialog(QWidget* pwgt = 0);
    int getInputRad1() const;
    int getInputRad2() const;
    QPushButton* pcmdCancel;
    QMessageBox* radMessage;
    int inWinSize;

protected:

private slots:
     void pcmdCancel_clicked();
     void pcmdOk_clicked();
    };
#endif // INPUTDIALOG_H
