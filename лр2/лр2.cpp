#include <iostream>
#include <string>
#include<math.h>
using namespace std;

class Date
{
public:
    int day;
    int month;
    int year;
    Date() { // конструктор без параметров
        printf("Date()\n");
        day = 1;
        month = 1;
        year = 2001;
    }
    Date(int day, int month, int year) // конструктор с тремя параметрами
    {
        printf("Date(int d, int m, int y)\n");
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date(const Date& date) {//конструктор копирования
        printf("Date(const Date &date)\n");
        day = date.day;
        month = date.month;
        year = date.year;
    }

    ~Date() {// деструктор
        printf("~Date()\n");
    }
    void ShowDate() {
        string Month[12] = { "января", "февраля", "марта" , "апреля" , "мая" , "июня" , "июля" , "августа" , "сентября" , "октября" , "ноября" , "декабря" };
        printf("\n%d.%d.%d\n", day, month, year);
        cout << day << " " << Month[month - 1] << " " << year << endl;
    }

    int LeapYear(int year) {
        if ((year % 4 == 0 && (year % 100 != 0 || (year % 400 == 0 && year % 100 == 0)))) {
            return 1;
        }
        else
            return 0;
    }

    int DaysBetweenDates(int d1, int d2, int m1, int m2, int y1, int y2) {
    int iDays = 0;
    if (y1 > y2) {
        swap(y1, y2);
        swap(m1, m2);
        swap(d1, d2);
    }
    else if (y1 == y2 && m1 > m2) {
        swap(m1, m2);
        swap(d1, d2);
    }
    else if (y1 == y2 && m1 == m2 && d1 > d2) {
        swap(d1, d2);
    }
    bool Continue = true;
    if (y1 == y2 && m1 == m2)
        return d2 - d1 + 1;
    else
        iDays = d2;
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int y = y2; y >= y1; y--) {
        if (y != y1 && y == y2) {
            for (int m = m2; m >= 1; m--) {
                if (Continue == true) {
                    Continue = false;
                    iDays -= days[m];
                }
                iDays += days[m];
                if (LeapYear(y) == 1 && m == 2)
                    iDays += 1;
            }
        }
        else if (y != y1 && y != y2)
            for (int m = 12; m >= 1; m--) {
                if (Continue == true) {
                    Continue = false;
                    iDays -= days[m];
                }
                iDays += days[m];
                if (LeapYear(y) == 1 && m == 2)
                    iDays += 1;
            }

        else
            for (int m = 12; m >= m1; m--) {
                if (Continue == true) {
                    Continue = false;
                    iDays -= days[m];
                }
                iDays += days[m];
                if (LeapYear(y) == 1 && m == 2)
                    iDays += 1;
            }
    }
    iDays -= d1;
    return iDays;

}
};

class Datewtime: public Date
{
public:
    int minute;
    int hour;
    Datewtime(): Date() { // конструктор без параметров
        printf("Datewtime()\n");
        hour = 11;
        minute = 32;
    }
    Datewtime(int minute, int hour, int day, int month, int year): Date(day, month, year) // конструктор с тремя параметрами
    {
        printf("Datewtime(int minute, int hour, int day, int month, int year)\n");
        this->minute = minute;
        this->hour = hour;
    }

    Datewtime(const Datewtime &datewtime) {//конструктор копирования
        printf("Datewtime(const Datewtime &date)\n");
        day = datewtime.day;
        month = datewtime.month;
        year = datewtime.year;
        minute = datewtime.minute;
        hour = datewtime.hour;
    }

    ~Datewtime() {// деструктор
        printf("~Datewtime()\n");
    }
    void ShowDatewtime() {
        string Month[12] = { "января", "февраля", "марта" , "апреля" , "мая" , "июня" , "июля" , "августа" , "сентября" , "октября" , "ноября" , "декабря" };
        printf("\n%d:%d %d.%d.%d\n",hour, minute, day, month, year);
        cout << hour << ":" << minute << " " << day << " " << Month[month - 1] << " " << year << endl;
    }
};

class DaysBetweenDates
{
public:
    Date date1;
    Date* date2;

    DaysBetweenDates() { // конструктор без параметров
        printf("DaysBetweenDates()\n");
        date1 = Date();
        date2 = new Date();
    }
    DaysBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2) // конструктор с тремя параметрами
    {
        printf("DaysBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2)\n");
        date1 = Date(day1, month1, year1);
        date2 = new Date(day2, month2, year2);
    }

    DaysBetweenDates(const DaysBetweenDates& dbd) {//конструктор копирования
        printf("DaysBetweenDates(const DaysBetweenDates &dbd)\n");
        date1 = Date((dbd.date1));
        date2 = new Date(*(dbd.date2));
    }

    ~DaysBetweenDates() {// деструктор
        printf("~DaysBetweenDates()\n");
        delete date2;
    }
};


int main() {
    setlocale(LC_ALL, "RUS");
    { 
        Date first;
        Date *second = new Date(2, 4, 2020);
        Date third(*second);
        Date fourth;
        first.ShowDate();
        printf("\n");
        second->ShowDate();
        printf("\n");
        third.ShowDate();
        cout << "Дней между датами:" << fourth.DaysBetweenDates(first.day, third.day, first.month, third.month, first.year, third.year) << endl;
        Datewtime fifth;
        Datewtime sixth(10, 2, 26, 8, 2023);
        Datewtime seventh(fifth);
        fifth.ShowDatewtime();
        printf("\n");
        sixth.ShowDatewtime();
        printf("\n");
        seventh.ShowDatewtime();
       
        DaysBetweenDates* number = new DaysBetweenDates();
        delete second;
        delete number;
    }
}