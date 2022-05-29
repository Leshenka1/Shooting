#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QtDebug>
#include <QValidator>
#include <target.h>
#include <vector>
#include <QPair>
#include <inputdialog.h>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLineEdit *m_numberInputX;
    QLineEdit *m_numberInputY;
    Target *target;
    InputDialog *pInputDialog;
private:
    Ui::MainWindow *ui;
    int winSize;
    int m_rad1;
    int m_rad2;
    int shotsCount;
    QLabel *m_statusMessage;
    QPushButton *startButton;
    QPushButton *shotButton;
    QLineEdit *m_numberInput;
//    QLineEdit *m_numberInputX;
//    QLineEdit *m_numberInputY;
    QLabel *m_shotsCount;
    QLabel *m_koord;
    QLabel *m_tar;
    QLabel *m_miss;
    QLabel *m_tarCount;;




protected:
    /* Определяем виртуальный метод родительского класса
     * для отрисовки содержимого виджета
     * */
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeWin();
private slots:
    void m_shot();
    void startGame();
    //void checkGame();


};
#endif // MAINWINDOW_H
