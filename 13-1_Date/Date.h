/* 
 * File:   Date.h
 * Author: Mariia Gregory
 *
 * Created on March 27, 2018, 12:10 PM
 */

#ifndef DATE_H
#define DATE_H



class Date {
    private:
        short month, day, year;
        char *monStr;
        void setMon(const short);
    public:
        Date(short = 1, short = 1, short = 1901 );
        void setDate(short, short, short);
        short getMon() const { return month; }
        char* monName() const { return monStr; };
        short getDay() const { return day; }
        short getYear() const {return year; }

        void print();//short,short,short);
        void print(char*);
        void print(short, char*);
        ~Date() { delete monStr; };
};

#endif /* DATE_H */

