// Final Project Milestone 2
//
// Version 1.0
// Date: November 9th, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the implementation code for the final project's Error module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include "Error.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace aid{

// Constructor assigns valid message, else empty state
Error::Error(const char* errorMessage){
    if(errorMessage == nullptr || errorMessage[0] == '\0')
        msg = nullptr;
    else{
        msg = new (nothrow) char [strlen(errorMessage) + 1];
        strncpy(msg, errorMessage, strlen(errorMessage));
    }
}

// Destructor, deallocating memory associated with object
Error::~Error(){
    delete [] msg;
}

// Clears the message held in the Error object
void Error::clear() {
    delete [] msg;
    msg = nullptr;
}
// Checks whether Error object is empty
bool Error::isClear() const{
    return (msg == nullptr ? true : false);
}

// Assigns new message to object
void Error::message(const char* str){
    if(!(str == nullptr) && !(str[0] == '\0')){
        delete [] msg;
        msg = new (nothrow) char [strlen(str) + 1];
        strncpy(msg, str, strlen(str));
        msg[strlen(str)] = '\0';
    }
    else msg = nullptr;
}

// Returns the message held in an object, else nullpt
const char* Error::message() const{
    return (!isClear() ? msg : nullptr);
}

// Passes Error message into output stream
ostream& operator << (ostream& ostr, const Error& err){
    if(!err.isClear())
        ostr << err.message();
    return ostr;
}
}

