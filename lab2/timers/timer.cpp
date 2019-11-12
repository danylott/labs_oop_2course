#include "timer.h"

#include <stdexcept>
#include <QDebug>

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

bool Timer::getActive() const
{
    return is_active;
}

void Timer::setActive(int value)
{
    is_active = value;
}

bool Timer::changeTime()
{
    int hour = time.hour();
    int min = time.minute();
    int sec = time.second();
    if(hour == 0 && min == 0 && sec == 0)
        return true;
    if(min == 0 && sec == 0) {
        sec = 59;
        min = 59;
        hour--;
    }
    else if (sec == 0) {
        sec = 59;
        min--;
    }
    else {
        sec--;
    }
    time.setHMS(hour, min, sec);
    this->setTime(time);
    qDebug() << time.toString();

    return false;
}

QString Timer::display()
{
    QString display_name = QString("%1: time: %2 %3").arg(this->getName().c_str()).arg(this->getTime().toString()).arg(this->getTypeString().c_str());
    return display_name;
}



Timer::Timer()
{
    is_active = false;
}
