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
public:
    Timer();

    string getName() const;
    void setName(const string &value);
    int getType() const;
    string getTypeString() const;
    void setType(int value);
    QTime getTime() const;
    void setTime(QTime t);
    QString display();
};

#endif // TIMER_H
