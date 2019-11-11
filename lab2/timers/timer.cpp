#include "timer.h"

#include <stdexcept>

string Timer::getName() const
{
    return name;
}

void Timer::setName(const string &value)
{
    name = value;
}

int Timer::getType() const
{
    return type;
}

void Timer::setType(int value)
{
    type = value;
}

QTime Timer::getTime() const
{
    return time;
}

void Timer::setTime(QTime t)
{
    time = t;
}



Timer::Timer()
{

}
