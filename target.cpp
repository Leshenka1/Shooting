#include "target.h"



void Target::setRad1(int _rad1)
{
    //qDebug() << _rad1;
    rad1 = _rad1;
    //qDebug() << rad1;

}

void Target::setRad2(int _rad2)
{
    rad2 = _rad2;
}

bool Target::shot(int _x, int _y)
{


    int x = _x + 250;
    int y = -_y + 250;
    if (_x >= 0 && _y >= 0 && _y * _y <= rad1 * rad1 * 0.25 - _x * _x && _y * _y >= rad2*rad2 * 0.25 - _x * _x)
    {
        vec.push_back(QPair<int, int>(x, y));
        tar++;
        return true;
    }
    if (_x <= 0 && _y <= 0 && _y * _y <= rad1 * rad1 * 0.25 - _x * _x && _y * _y >= rad2*rad2 * 0.25 - _x * _x)
    {
        vec.push_back(QPair<int, int>(x, y));
        tar++;
        return true;
    }
        vec2.push_back(QPair<int, int>(x, y));
        miss++;
        return false;
}

void Target::setShootsNum(int _shoots)
{
    shootsNum = _shoots;
}

int Target::getRad1()
{
    return rad1;
}

int Target::getRad2()
{
    return rad2;
}

int Target::getTar()
{
    return tar;
}

int Target::getMiss()
{
    return miss;
}


