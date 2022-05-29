#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Shooting");
    //setStyleSheet("background-color: white;");

    //QGridLayout *layout = new QGridLayout(this);

    pInputDialog = new InputDialog;


    target = new Target;

    pInputDialog->exec();

    m_statusMessage = new QLabel(this);

    winSize = pInputDialog->inWinSize;
    setGeometry(900, 200, winSize + 200, winSize);
    setFixedSize(winSize + 200, winSize);

    m_statusMessage->setText("Чтобы запустить стрельбу,\nвведите число выстрелов и \nнажмите кнопку 'Начать стрельбу!'...");
    //layout->addWidget(m_statusMessage, 2, 0);
    m_statusMessage->setGeometry(510, 0, 180, 70);


    startButton = new QPushButton("Начать стрельбу!", this);
    startButton->setGeometry(510, 70, 180, 70);

    m_numberInput = new QLineEdit(this);
    m_numberInput->setGeometry(590, 150, 95, 70);
    m_numberInput->setValidator(new QIntValidator(this));

    QString sShots = m_numberInput->text();
    int nShots = sShots.toInt();
    shotsCount = nShots;

    m_shotsCount = new QLabel(this);
    m_shotsCount->setText("Число \nвыстрелов:");
    m_shotsCount->setGeometry(510, 150, 70, 70);
//    QString cou = m_numberInputX->text();
//    shotsCount = cou.toInt();

    m_koord = new QLabel(this);
    m_koord->setText("Координаты\nв пикселях:\n(x и y)");
    m_koord->setGeometry(510, 230, 70, 70);

    m_numberInputX = new QLineEdit(this);
    m_numberInputX->setGeometry(590, 240, 45, 50);
    m_numberInputX->setValidator(new QIntValidator(this));

    m_numberInputY = new QLineEdit(this);
    m_numberInputY->setGeometry(640, 240, 45, 50);
    m_numberInputY->setValidator(new QIntValidator(this));

    m_numberInputX->setEnabled(false);
    m_numberInputY->setEnabled(false);

    shotButton = new QPushButton("Выстрелить!", this);
    shotButton->setGeometry(510, 310, 180, 70);
    shotButton->setEnabled(false);

    m_tar = new QLabel(this);
    m_tar->setText("Количество попаданий: 0");
    m_tar->setGeometry(510, 380, 180, 70);

    m_miss = new QLabel(this);
    m_miss->setText("Количество промахов: 0");
    m_miss->setGeometry(510, 420, 180, 70);


    m_rad1 = pInputDialog->getInputRad1();
    m_rad2 = pInputDialog->getInputRad2();

    //qDebug()<<m_rad1 << m_rad2;

//    target->setRad1(m_rad1);
//    target->setRad2(m_rad2);



    //setLayout(layout);

    connect(startButton, SIGNAL(clicked()), SLOT(startGame()));
    connect(shotButton, SIGNAL(clicked()), SLOT(m_shot()));


//    delete pInputDialog;
//    delete target;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    qDebug()<<target->mass[0][0];
//    qDebug()<<target->mass[0][1];
     QPainter painter(this); // Создаём объект отрисовщика
     // Устанавливаем кисть абриса
     painter.begin(this);
     painter.setPen(Qt::NoPen);
     int locationRad1 = winSize * 0.5 - m_rad1 * 0.5 ;
     int locationRad2 = winSize * 0.5 - m_rad2 * 0.5 ;
     painter.setBrush(Qt::gray);
     painter.drawEllipse(QRect(locationRad1, locationRad1, m_rad1, m_rad1));
     painter.setBrush(Qt::white);
     painter.setPen(Qt::NoPen);
     painter.drawEllipse(QRect(locationRad2, locationRad2,  m_rad2, m_rad2));
     painter.drawPie(QRect(locationRad1, locationRad1, m_rad1, m_rad1), 90 * 16, 90 * 16);
     painter.drawPie(QRect(locationRad1, locationRad1, m_rad1, m_rad1), 270 * 16, 90 * 16);
     painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
     painter.setBrush(Qt::gray);
     painter.drawLine(winSize + 2, 0, winSize + 2, winSize);

     painter.setPen(QPen(Qt::green, 5));

//     for(int i = 0; i < target->vec.size(); i++)
//     {
//         if(target->shot(target->getRad1(),target->getRad2()))
//         {
//             painter.setPen(QPen(Qt::green, 15));
//             painter.drawPoint(target->vec[i].first,target->vec[i].second);
//         }
//         else
//         {
//             painter.setPen(QPen(Qt::red, 15));
//             painter.drawPoint(target->vec[i].first,target->vec[i].second);
//         }
//     }

     for(int i = 0; i < target->vec.size(); i++)
     {
         painter.setPen(QPen(Qt::red, 5));
         painter.drawPoint(target->vec[i].first,target->vec[i].second);
     }

     for(int i = 0; i < target->vec2.size(); i++)
     {
         painter.setPen(QPen(Qt::lightGray, 5));
         painter.drawPoint(target->vec2[i].first,target->vec2[i].second);
     }

     painter.end();



}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
            int aX = event->x() - 250;
            int aY = 250 - event->y();
            m_numberInputX->setText(QString::number(aX));
            m_numberInputY->setText(QString::number(aY));
            if (aX < -250 || aX > 250|| aY <= -250|| aY >= 250) {
              //m_statusMessage->setText("Введите число");
              QMessageBox::about(this,"Уууупс... :(","Вы промахнулись мимо области стрельбы(размеры окна 500х500 пк)");
              return ;
            }
            this->m_shot();
        }
}

void MainWindow::m_shot()
{
    if(shotsCount <= 0) {
        return;
    }
    QString smX = m_numberInputX->text();
    int mX = smX.toInt();
    QString smY = m_numberInputY->text();
    int mY = smY.toInt();

    target->setRad1(m_rad1);
    target->setRad2(m_rad2);
    target->setShootsNum(shotsCount);

    target->shot(mX, mY);

    if (mX < -250 || mX > 250|| mY <= -250|| mY >= 250) {
      //m_statusMessage->setText("Введите число");
      QMessageBox::about(this,"Уууупс... :(","Вы промахнулись мимо области стрельбы(размеры окна 500х500 пк)");
      return ;
    }

    m_tar->setText("Количество попаданий: " + QString::number(target->getTar()));
    m_miss->setText("Количество промахов: " + QString::number(target->getMiss()));

    shotsCount--;
    repaint();

        if(shotsCount == 0)
        {
            if (QMessageBox::information(this,"Игра закончена!","Спасибо за игру"))
             QApplication::quit();
        }

//    if(shotsCount == 0)
//    {
//        if (QMessageBox::question(this,"Игра закончена!", "Победа!!! Желаете сыграть ещё раз?",
//                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
//         QApplication::quit();
//        else {
//            this->close();
//            MainWindow *a = new MainWindow();
//            a->show();

//        }
//    }

}

void MainWindow::startGame()
{
    QString value = m_numberInput->text();
    int ivalue = value.toInt();
      if (ivalue <= 0 || ivalue > 100) {
        //m_statusMessage->setText("Введите число");
        QMessageBox::about(this,"Уууупс... ):(","Вы должны ввести число выстрелов (не более 100)");
        return ;
      }
     QString cou = m_numberInput->text();
     shotsCount = cou.toInt();

     m_numberInputX->setEnabled(true);
     m_numberInputY->setEnabled(true);
     shotButton->setEnabled(true);
     m_numberInput->setEnabled(false);
     startButton->setEnabled(false);

}






