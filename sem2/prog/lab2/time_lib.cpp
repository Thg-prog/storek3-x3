#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#include "time_lib.h"

DateTime::DateTime() {
    date_st.year = 0;
    date_st.month = 1;
    date_st.day = 1;
    time_st.hour = 0;
    time_st.minute = 0;
    time_st.second = 0;
}

DateTime::DateTime( int _year, int _month, int _day, int _hour, int _minute, int _second ) {
    //?
    date_st.year = _year;
    date_st.month = _month;
    date_st.day = _day;
    time_st.hour = _hour;
    time_st.minute = _minute;
    time_st.second = _second;
}

DateTime::DateTime( const DateTime&& date_time ) : DateTime::DateTime( date_time.getYear(), date_time.getMonth(), date_time.getDay(), date_time.getHour(), date_time.getMinute(), date_time.getMinute() ) {};
DateTime::DateTime( DateTime&& date_time ) = default;

inline int DateTime::getYear() const { return date_st.year; };
inline void DateTime::setYear( int _year ) { date_st.year = _year; }//?

inline int DateTime::getMonth() const { return date_st.month; }
inline void DateTime::setMonth( int _month ) { date_st.month = _month; }

inline int DateTime::getDay() const { return date_st.day; }
inline void DateTime::setDay( int _day ) { date_st.day = _day; }

inline int DateTime::getHour() const { return time_st.hour; }
inline void DateTime::setHour( int _hour ) { time_st.hour = _hour; }

inline int DateTime::getMinute() const { return time_st.minute; }
inline void DateTime::setMinute( int _minute ) { time_st.minute = _minute; }

inline int DateTime::getSecond() const { return time_st.second; }
inline void DateTime::setSecond( int _second ) { time_st.second = _second; }

std::string DateTime::format( const std::string& format ) const {
    std::stringstream ss;
    ss << std::setfill( '0' );
    for ( char c : format ) {
        if ( c == 'Y' ) {
            ss << std::setw( 4 ) << date_st.year;
        } else if ( c == 'm' ) {
            ss << std::setw( 2 ) << date_st.month;
        } else if ( c == 'd' ) {
            ss << std::setw( 2 ) << date_st.day;
        } else if ( c == 'H' ) {
            ss << std::setw( 2 ) << time_st.hour;
        } else if ( c == 'M' ) {
            ss << std::setw( 2 ) << time_st.minute;
        } else if ( c == 'S' ) {
            ss << std::setw( 2 ) << time_st.second;
        } else {
            ss << c;
        }
    }

    return ss.str();
}

bool DateTime::isValidDate( int year, int month, int day ) {
    if ( month > 12 || day > 30 ) {//?
        return false;
    }

    return true;
};

bool DateTime::isValidTime( int hour, int minute, int second ) {
    if ( hour > 23 || minute > 60 || second > 60 ) {//?
        return 0;
    }

    return 1;
};

void DateTime::setCurrentDateTime() {
    time_t now = time( 0 );
    tm *ltm = localtime( &now );
    addSecs( ltm->tm_sec );
    addMinutes( ltm->tm_min );
    addHours( ltm->tm_hour );
    addDays( ltm->tm_mday );
    addMonths( ltm->tm_mon );
    addYears( 1900 + ltm->tm_year );
};

inline DateTime::Date DateTime::getDate() const { return date_st; };
inline DateTime::Time DateTime::getTime() const { return time_st; };

DateTime DateTime::fromString( const std::string& str, const std::string& format ) {
    DateTime dt;
    std::string del = " ";
    int start = 0;
    int end = str.find( del );
    int start_2 = 0;
    int end_2 = format.find( del );
    int a_w = 0;
    
    while ( 1 ) {
        std::string num_str = str.substr( start, end - start );
        std::string sub = format.substr( start_2, end_2 - start_2 );

        if ( sub == "Y" ) {
            dt.setYear( std::stoi( num_str ) );
        } else if ( sub == "m" ) {
            dt.setMonth( std::stoi( num_str ) );
        } else if ( sub == "d" ) {
            dt.setDay( std::stoi( num_str ) );
        } else if ( sub == "H" ) {
            dt.setHour( std::stoi( num_str ) );
        } else if ( sub == "M" ) {
            dt.setMinute( std::stoi( num_str ) );
        } else if ( sub == "S" ) {
            dt.setSecond( std::stoi( num_str ) );
        }
        
        if ( end == -1 ) {
            break;
        }

        start = end + del.size();
        start_2 = end_2 + del.size();

        end = str.find( del, start );
        end_2 = format.find( del, start_2 );
    };

    return dt;
};

void DateTime::addSecs( int secs ) { 
    if ( isValidTime( getHour(), getMinute(), getSecond() + secs ) ) {
        setSecond( getSecond() + secs );
    } else {
        setSecond( secs % 60 );
        addMinutes( ( secs / 60 ) );
    }
};

void DateTime::addMinutes( int minutes ) { 
    if ( isValidTime( getHour(), getMinute() + minutes, getSecond() ) ) {
        setMinute( getMinute() + minutes );
    } else {
        setMinute( minutes % 60 );
        addHours( ( minutes / 60 ) );
    }
};

void DateTime::addHours( int hours ) {     
    if ( isValidTime( getHour() + hours, getMinute(), getSecond() ) ) {
        setHour( getHour() + hours );
    } else {
        setHour( hours % 24 );
        addDays( ( hours / 24 ) );
    }
};

void DateTime::addDays( int days ) { 
    if ( isValidDate( getYear(), getMonth(), getDay() + days ) ) {
        setDay( getDay() + days );
    } else {
        setDay( days % 30 + 1 );
        addMonths( ( days / 30 ) );
    }
};

void DateTime::addMonths( int months ) { 
    if ( isValidDate( getYear(), getMonth() + months, getDay() ) ) {
        setMonth( getMonth() + months );
    } else {
        setMonth( months % 12 + 1 );
        addYears( ( months / 12 ) );
    }
};
void DateTime::addYears( int years ) {
    setYear( getYear() + years );
};

// Методы определения дней и секунд до конкретной даты
int DateTime::daysTo( const DateTime& other ) {
    int days = 0;
    days = other.getYear() * 360 + other.getMonth() * 30 + other.getDay();

    int nw = 0;
    nw = getYear() * 360 + getMonth() * 30 + getDay();

    return days - nw;
};

int DateTime::secsTo( const DateTime& other ) {
    int secs = 0;
    secs = other.getYear() * 360 * 24 * 60 * 60 + other.getMonth() * 30 * 24 * 60 * 60 + other.getDay() * 24 * 60 * 60 + other.getHour() * 60 * 60 + other.getMinute() * 60 + other.getSecond();

    int nw = 0;
    nw = getYear() * 360 * 24 * 60 * 60 + getMonth() * 30 * 24 * 60 * 60 + getDay() * 24 * 60 * 60 + getHour() * 60 * 60 + getMinute() * 60 + getSecond();

    return secs - nw;
};

