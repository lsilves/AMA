// Final Project Milestone 5
//
// Version 1.0
// Date: November 27th, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the implementation code for the final project's Perishable module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include "Perishable.h"
#include "Good.h"
#include "Date.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace aid{
    // Constructs empty Perishable object
    Perishable::Perishable() : Good("P"){
        expiration = Date();
    }
    
    // Extracts object record from file
    fstream& Perishable::store(fstream& file, bool newLine) const{
        Good::store(file, false);
        file << "," << expiration;
        if (newLine == true) file << '\n';
        return file;
    }
    
    // Inserts object record into file
    fstream& Perishable::load(fstream& file){
        char singleChar;
        Good::load(file);
        expiration.Date::read(file);
        file >> singleChar;
        return file;
    }
    
    // Outputs data from Perishable object using ostream
    ostream& Perishable::write(ostream& os, bool linear) const{
        Good::write(os, linear);
        if(Good::isClear() || Good::isEmpty()){
            if(linear) os << expiration;
            else os << endl << " Expiry date: " << expiration;
	}
        return os;
    }
    
    // Inserts data into Perishable object from istream
    istream& Perishable::read(std::istream& is){
        Date temp;
        
        Good::read(is);
        if(Good::isClear()){
        gType = 'P';    
	cout << " Expiry date (YYYY/MM/DD): ";
            temp.read(is);
            if(isClear()) expiration = temp;
            if(expiration.errCode() != 0){
                is.setstate(std::ios_base::failbit);
                if(expiration.errCode() == 1) message("Invalid Date Entry");
                else if(expiration.errCode() == 2) message("Invalid Day in Date Entry");
                else if(expiration.errCode() == 3) message("Invalid Month in Date Entry");
                else if(expiration.errCode() == 4) message("Invalid Year in Date Entry");
                else message("Invalid Expiry in Date Entry");
            }
        }
        
        return is;
    }
}

