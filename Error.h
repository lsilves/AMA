// Final Project Milestone 2
//
// Version 1.0
// Date: November 9th, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the header code for the final project's Error module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AID_Error_hpp
#define AID_Error_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
namespace aid {
    class Error {
        char * msg;
    public:
        explicit Error(const char* errorMessage = nullptr);
        Error(const Error& em) = delete; //
        Error& operator=(const Error& em) = delete; //
        virtual ~Error(); //
        void clear();
        bool isClear() const;
        void message(const char* str);
        const char* message() const;
    };

    ostream& operator << (ostream& ostr, const Error& err);
}

#endif /* Error_hpp */

