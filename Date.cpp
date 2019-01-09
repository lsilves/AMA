// Final Project Milestone 1
//
// Version 1.0
// Date: November 2nd, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the implementation code for the final project's Date module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace std;

namespace aid {
    
    // Checks whether day of specified month is valid
    int Date::mdays (int mon, int year) const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    
    // Private member function that assigns error code
    void Date::errCode (int err) {
        error = err;
    }
    
    // Public member function that returns object's error type
    int Date::errCode () const {
        return error;
    }
    
    // No parameter constructor, creates empty object
    Date::Date () {
        year = 0;
        month = 0;
        day = 0;
        compare = 0;
        errCode(NO_ERROR);
    }
    
    // Three parameter constructor, validates and assigns year, month, and day
    Date::Date (int yr, int mn, int dy) {
        int comp = yr * 372 + mn * 31 + dy;

        *this = Date();
        if(yr < min_year || yr > max_year)
            errCode(YEAR_ERROR);
        else if(mn < 1 || mn > 12)
            errCode(MON_ERROR);
        else if (dy > mdays(mn, yr) || dy < 1)
            errCode(DAY_ERROR);
        else if(comp < min_date)
            errCode(PAST_ERROR);
        else{
            errCode(NO_ERROR);
            year = yr;
            month = mn;
            day = dy;
            compare = comp;
        }
    }
    
    // Checks whether dates are equivalent
    bool Date::operator == (const Date& rhs) const {
        if (compare == 0 || rhs.compare == 0) return false;
        else return (compare == rhs.compare);
    }
    
    // Checks whether dates are not equivalent
    bool Date::operator != (const Date& rhs) const {
        if (compare == 0 || rhs.compare == 0) return false;
        else return (!(*this == rhs));
    }
    
    // Checks whether current date is less than the date it passes as a parameter
    bool Date::operator < (const Date& rhs) const {
        if (compare == 0 || rhs.compare== 0) return false;
        else return (compare < rhs.compare);
    }

    // Checks whether current date is greater than the date it passes as a parameter
    bool Date::operator > (const Date& rhs) const {
        if (compare == 0 || rhs.compare == 0) return false;
        else return (compare > rhs.compare);
    }
    
    // Checks whether current date is less than or equal to the date it passes as a parameter
    bool Date::operator <= (const Date& rhs) const {
        if (compare == 0 || rhs.compare == 0) return false;
        else return (compare < rhs.compare|| compare == rhs.compare);
    }
    
    // Checks whether current date is greater than or equal to the date it passes as a parameter
    bool Date::operator >= (const Date& rhs) const {
        if (compare == 0 || rhs.compare == 0) return false;
        else return (compare > rhs.compare || compare == rhs.compare);
    }

    
    // Checks whether the current Date object has an error
    bool Date::bad () const {
        return !(errCode() == NO_ERROR);
    }
    
    // Reads a date from std::cin and inserts the values into a preexisting object if valid
    istream& Date::read (istream& istr) {
        int dateArray[3];
        char notNum;
        
        for (int i = 0; i < 3; i++) {
            istr >> dateArray[i];
            if(!isdigit(dateArray[i]) && i < 2){
                istr >> notNum;
                if (istr.fail()) errCode(CIN_FAILED);
            }
        }

        if(errCode() != CIN_FAILED) *this = Date(dateArray[0], dateArray[1], dateArray[2]);
        
        return istr;
    }

    // Outputs the formatted date held in the current object
    ostream& Date::write (ostream& ostr) const{
        ostr << setfill('0') << year << "/"  << setw(2) << month << "/" << setw(2) << day;
        return ostr;
    }
    
    // Inserts date values into the object on the right hand side
    istream& operator >> (istream& istr, Date& date){
        date.read(istr);
        return istr;
    }
    
    // Extracts the date values from the object on the right hand side
    ostream& operator << (ostream& ostr, const Date& date){
        date.write(ostr);
        return ostr;
    }
    
};


