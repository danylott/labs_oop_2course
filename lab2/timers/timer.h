#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <QString>
#include <QTime>
using std::string;


class Timer {
private:
    string name;
    QTime time; // for Timer remaining_time = time (at first) // for Alarm remaining_time = sec_to(time)
    QTime remaining_time;
    int type;
    bool is_active;
public:
    Timer();

    string getName() const;
    void setName(const string &value);
    int getType() const;
    string getTypeString() const;
    void setType(int value);
    QTime getTime() const;
    void setTime(QTime t);
    QTime getRemainingTime() const;
    void setRemainingTime(QTime t);
    bool getActive() const;
    void setActive(int value);
    bool changeRemainingTime(); // return true if timer is finish working
    QTime calculateRemainingTime();
    QString display();
};

#endif // TIMER_H
