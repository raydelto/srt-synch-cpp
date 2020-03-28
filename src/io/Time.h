#pragma once
#include <string>
#include <QString>

namespace raydelto
{

class Time
{
  public:
    //Getters
    int GetHours() { return m_hours; }
    int GetMinutes() { return m_minutes; }
    int GetSeconds() { return m_seconds; }
    int GetMilliseconds() { return m_milliseconds; }

    Time(int hours, int minutes, int seconds, int milliseconds);
    Time(QString rawTime);
    void Change(Time variation);
    std::string ToStdString();

  private:
    int m_hours;
    int m_minutes;
    int m_seconds;
    int m_milliseconds;

    std::string AddZeros(int number);
    std::string AddZerosMilli(int number);
};
} // namespace raydelto
