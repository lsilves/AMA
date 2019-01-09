// Final Project Milestone 3
//
// Version 1.0
// Date: November 21st, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the header code for the final project's Good module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef Good_hpp
#define Good_hpp

#include <stdio.h>
#include "iGood.h"

#include "Error.h"
namespace aid{
    const int max_sku_length = 7;
    const int max_unit_length = 10;
    const int max_name_length = 75;
    const double TAX = 1.13;
    class Good : public iGood {
        char gSku [max_sku_length];
        char gUnit [max_unit_length];
        char * gName;
        int gQtyAvail;
        int gQtyNeed;
        double gPrice;
        bool gTaxStatus;
        aid::Error err;
    protected:
	char gType;
        void name(const char*);
        const char* name() const;
        const char* sku() const;
        const char * unit() const;
        bool taxed() const;
        double itemPrice() const;
        double itemCost() const;
        void message(const char*);
        bool isClear() const;
    public:
        Good(const char* = "N");
        Good(const char*, const char*, const char*, int = 0, bool = true, double = 0.0, int = 0);
        Good(const Good&);
        void operator= (const Good&);
        std::fstream& store(std::fstream& file, bool newLine=true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        bool operator==(const char*) const;
        double total_cost() const;
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        void quantity(int);
        bool operator>(const iGood&) const;
        int operator += (int);
        ~Good();
    };
    
    ostream& operator<< (std::ostream&, const iGood&);
    istream& operator>>(std::istream&, iGood&);
    double operator+=(double&, const iGood&);
}


#endif /* Good_hpp */

