#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <QString>
#include <QTime>
using std::string;


class Timer {
private:
    string name;
    QTime time;
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
    bool getActive() const;
    void setActive(int value);
    bool changeTime(); // return true if timer is finish working
    QString display();
};

#endif // TIMER_H
