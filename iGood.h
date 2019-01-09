// Final Project Milestone 4
//
// Version 1.0
// Date: November 22nd, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the virtual base code for the final project's interface module, iGood.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef IGOOD_H
#define IGOOD_H
#include <iostream>
#include <fstream>

namespace aid{
  class iGood {
  public:
    // Inserts Good's record into file
    virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;

    // Extracts Good's data from file
    virtual std::fstream& load(std::fstream& file) = 0;

    // Ouputs object record
    virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

    // Extracts object data
    virtual std::istream& read(std::istream& is) = 0;

    // Checks whether two SKUs are identical
    virtual bool operator == (const char*) const = 0;

    // Returns an object's end cost
    virtual double total_cost() const = 0;

    // Returns an object's name
    virtual const char* name() const = 0;

    // Sets the object's available quantity
    virtual void quantity(int) = 0;

    // Returns the quantity needed of the object
    virtual int qtyNeeded() const = 0;

    // Returns the object's available quantity
    virtual int quantity() const = 0;

    // Increases quantity of the object and returns object's quantity
    virtual int operator += (int) = 0;

    // Returns evaluation of whether current object is greater than object in parameters
    virtual bool operator > (const iGood&) const = 0;

    virtual ~iGood() {};
  };

  // Ouputs object record
  std::ostream& operator << (std::ostream&, const iGood&);

  // Extracts object data
  std::istream& operator >> (std::istream&, iGood&);

  // Returns sum of supplied cost and parameter object's total cost.
  double operator += (double&, const iGood&);

  // Returns the address of a Good object
  iGood* CreateGood();

  // Returns the address of a Perishable object
  iGood* CreatePerishable();
}
#endif

