#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <vector>
#include <QPair>
#include <QDebug>


//#include "inputdialog.h"

class Target
{
public:
    //Target();
    void setRad1(int _rad1);
    void setRad2(int _rad2);
    bool shot(int _x, int _y);
    void setShootsNum(int _shoots);
    int getRad1();
    int getRad2();
    int getTar();
    int getMiss();


 //
    //std::vector<int> vec;
    //QVector<int> vec;
    std::vector<QPair<int, int>> vec;
    std::vector<QPair<int, int>> vec2;


private:
    int tar = 0;
    int miss = 0;
    int rad1, rad2;
    int shootsNum;
    //QVector<int> vec;



};

#endif // TARGET_H
