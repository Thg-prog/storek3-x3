#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

class DateTime {
    private:
        // Структуры даты и времени
        struct Date {
            int year = 0;
            int month = 0;
            int day = 0;
        } date_st;

        struct Time {
            int hour = 0;
            int minute = 0;
            int second = 0;
        } time_st;

    public:
        // 4 конструктора
        // 1) Конструктор по умолчанию
        DateTime();

        // 2) Конструктор с параметрами
        DateTime( int _year, int _month, int _day, int _hour, int _minute, int _second );

        // 3) Конструктор копирования
        DateTime( const DateTime&& date_time );

        // 4) Конструктор перемещения
        DateTime( DateTime&& date_time );

        // Методы get и set в inline
        inline int getYear() const;
        inline void setYear( int _year );

        inline int getMonth() const;
        inline void setMonth( int _month );

        inline int getDay() const;
        inline void setDay( int _day );

        inline int getHour() const;
        inline void setHour( int _hour );

        inline int getMinute() const;
        inline void setMinute( int _minute );

        inline int getSecond() const;
        inline void setSecond( int _second );

        // Метод печати даты и времени по заданному шаблону 
        std::string format( const std::string& format ) const;

        // Метод проверки набора чисел на корректность дате и времени
        static bool isValidDate( int year, int month, int day );
        static bool isValidTime( int hour, int minute, int second );

        // Метод текущего времени и даты
        void setCurrentDateTime();

        // Методы возрата даты и времени в виде структур
        inline Date getDate() const;
        inline Time getTime() const ;

        // Метод получения даты и времени из строки
        static DateTime fromString( const std::string& str, const std::string& format );

        // Методы добавления
        void addSecs( int secs );
        void addMinutes( int minutes );
        void addHours( int hours );
        void addDays( int days );
        void addMonths( int months );
        void addYears( int years );

        // Методы определения дней и секунд до конкретной даты
        int daysTo( const DateTime& other );
        int secsTo( const DateTime& other );
};
