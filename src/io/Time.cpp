#include "Time.h"
#include <QStringList>

raydelto::Time::Time(int hours, int minutes, int seconds, int milliseconds) : m_hours(hours),
                                                                              m_minutes(minutes),
                                                                              m_seconds(seconds),
                                                                              m_milliseconds(milliseconds)
{
}

raydelto::Time::Time(QString rawTime)
{
    QStringList parts = rawTime.split(","); // (hh:mm:ss)[0] (ms)[1]
    QStringList first = parts.at(0).split(":"); // hours, minutes, seconds
    m_hours = first.at(0).toInt();
    m_minutes = first.at(1).toInt();
    m_seconds = first.at(2).toInt();
    m_milliseconds = parts.at(1).toInt();
}

std::string raydelto::Time::AddZerosMilli(int number)
{
    if (number <= 9)
    {
        return "00" + std::to_string(number);
    }
    else if (number <= 99)
    {
        return "0" + std::to_string(number);
    }
    else
    {
        return std::to_string(number);
    }
}

std::string raydelto::Time::AddZeros(int number)
{
    return number <= 9 ? "0" + std::to_string(number) : std::to_string(number);
}

void raydelto::Time::Change(raydelto::Time variation)
{
    m_hours += variation.GetHours();
    m_minutes += variation.GetMinutes();
    m_seconds += variation.GetSeconds();
    m_milliseconds += variation.GetMilliseconds();

    //adjusting values, converting minutes to hours, seconds to minutes and milliseconds to seconds if necessary

    if (m_milliseconds < 0)
    {
        if (m_seconds > 0)
        {
            m_seconds -= 1;
            m_milliseconds += 1000;
        }
        else
        {
            m_seconds = 0;
            m_milliseconds = 0;
        }
    }

    if (m_seconds < 0)
    {
        if (m_minutes > 0)
        {
            m_minutes -= 1;
            m_seconds += 60;
        }
        else
        {
            m_minutes = 0;
            m_seconds = 0;
        }
    }

    if (m_minutes < 0)
    {
        if (m_hours > 0)
        {
            m_minutes += 60;
            m_hours -= 1;
        }
        else
        {
            m_minutes = 0;
            m_hours = 0;
        }
    }

    if (m_minutes > 59)
    {
        m_hours += (m_minutes / 60);
        m_minutes = m_minutes % 60;
    }

    if (m_seconds > 59)
    {
        m_minutes += (m_seconds / 60);
        m_seconds = m_seconds % 60;
    }

    if (m_milliseconds > 999)
    {
        m_seconds += (m_milliseconds / 1000);
        m_milliseconds = m_milliseconds % 1000;
    }

    if (m_hours < 0)
    {
        m_hours = 0;
    }
}
std::string raydelto::Time::ToStdString()
{
    return AddZeros(m_hours) + ":" + AddZeros(m_minutes) +":" + AddZeros(m_seconds) + "," + AddZerosMilli(m_milliseconds);
}
