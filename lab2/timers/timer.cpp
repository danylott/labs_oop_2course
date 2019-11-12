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

QString Timer::display()
{
    QString display_name = QString("%1: time: %2 %3").arg(this->getName().c_str()).arg(this->getTime().toString()).arg(this->getTypeString().c_str());
    return display_name;
}



Timer::Timer()
{

}
