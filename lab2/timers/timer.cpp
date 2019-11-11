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

std::string Timer::getTypeString() const
{
    string type_string;
    if(type == 0)
        type_string = "Timer";
    else
        type_string = "Alarm";
    return type_string;
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
