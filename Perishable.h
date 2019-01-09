// Final Project Milestone 5
//
// Version 1.0
// Date: November 27th, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the header code for the final project's Perishable module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#pragma once
#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "Good.h"
#include "Date.h"
namespace aid{
    class Perishable : public Good {
        Date expiration;
        
    public:
        Perishable(); //file record tag? (25 22:48)
        fstream& store(fstream& file, bool newLine = true) const;
        fstream& load(fstream& file);
        ostream& write(ostream& os, bool linear) const;
        istream& read(std::istream& is);
    };
}
#endif

