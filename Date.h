// Final Project Milestone 1
//
// Version 1.0
// Date: November 2nd, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This is the header file for the final project's Date module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AMA_DATE_H
#define AMA_DATE_H

namespace aid {
#define NO_ERROR   0
#define CIN_FAILED 1
#define DAY_ERROR  2
#define MON_ERROR  3
#define YEAR_ERROR 4
#define PAST_ERROR 5
    
const int min_year = 2018;
const int min_date = 751098;
const int max_year = 2038;

    class Date {
        int year;
        int month;
        int day;
        int compare;
        int error;
        
    private:
        int mdays (int, int) const;
        void errCode (int);
        
    public:
        Date ();
        Date (int, int, int);
        
        bool operator == (const Date&) const;
        bool operator != (const Date&) const;
        bool operator < (const Date&) const;
        bool operator > (const Date&) const;
        bool operator <= (const Date&) const;
        bool operator >= (const Date&) const;
        
        int errCode() const;
        bool bad() const;
        
        std::istream& read (std::istream&);
        std::ostream& write (std::ostream&) const;
    };
    
    std::istream& operator >> (std::istream&, Date&);
    std::ostream& operator << (std::ostream&, const Date&);
    
}
#endif

