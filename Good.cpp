// Final Project Milestone 3
//
// Version 1.0
// Date: November 21st, 2018
// Author: Laura Ilves, #141785170, Section A
// Description: This file contains the implementation code for the final project's Error module.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include "Good.h"
#include "iGood.h" 
#include "Error.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <ctype.h>
using namespace std;
using namespace aid;


// Assigns the item's name
void Good::name(const char* newName){
    if(newName == nullptr) delete [] gName;
  else{
    gName = new char [max_name_length + 1];
    for(int i = 0; i < static_cast<int>(strlen(newName)) + 1; i++) gName[i] = newName[i];
      gName[strlen(newName) + 1] = '\0';
  }
}

// Returns the item's name
const char* Good::name() const{
    return gName;
}

// Returns the Stock Keeping Unit (sku) of the item
const char* Good::sku() const{
    return gSku;
}

// Returns the unit name of the item
const char * Good::unit() const{
    return gUnit;
}

// Returns the tax status of the item
bool Good::taxed() const{
    return gTaxStatus;
}

// Returns the price of the item
double Good::itemPrice() const{
    return gPrice;
}

// Returns the cost of the item
double Good::itemCost() const{
    return (gTaxStatus == true) ? gPrice * TAX : gPrice;
}

// Assigns error message
void Good::message(const char* errMsg){
    err.Error::message(errMsg);
}

// Checks whether object in error state
bool Good::isClear() const{
    return err.Error::isClear();
}
// 0-1 argument constructor with optional argument for sku
Good::Good(const char* _sku){
    strcmp(_sku, "P") ? gType = 'P' : 'N';
    gUnit[0] = '\0';
    gName = nullptr;
    gQtyAvail = 0;
    gQtyNeed = 0;
    gPrice = 0.0;
    gTaxStatus = true;
}

// 7 argument constructor with default values for qtyAvail, taxStatus, price, and qtyNeed
 Good::Good(const char* _sku, const char* _name, const char* _unit, int _qtyAvail, bool _taxStatus, double _price, int _qtyNeed){
    if(_sku[0] != '\0'){
        strcpy(gSku, _sku);
        gSku[strlen(_sku)] = '\0';
     }
    else gSku[0] = '\0';
     name(_name);
     for(int i = 0; (unsigned)i < strlen(_unit); i++){
         gUnit[i] = _unit[i];
     }
     gUnit[strlen(_unit)] = '\0';
     gQtyAvail = _qtyAvail;
     gTaxStatus = _taxStatus;
     gPrice = _price;
     gQtyNeed = _qtyNeed;
 }

// Copy constructor
Good::Good(const Good& copy){
    *this = copy;
}

// Copy assignment constructor
void Good::operator= (const Good& copy){
    if(this != &copy){
    gType = copy.gType;
    for(int i = 0; (unsigned)i < strlen(copy.gSku); i++){
        gSku[i] = copy.gSku[i];
        gSku[strlen(copy.gSku)] = '\0';
    }
    if(copy.gUnit[0] != '\0'){
        for(int i = 0; (unsigned)i < strlen(copy.gUnit); i++){
            gUnit[i] = copy.gUnit[i];
        }
        gUnit[strlen(copy.gUnit)] = '\0';
    }
    else gUnit[0] = '\0';
    name(copy.gName);
    gQtyAvail = copy.gQtyAvail;
    gTaxStatus = copy.gTaxStatus;
    gPrice = copy.gPrice;
    gQtyNeed = copy.gQtyNeed;
  }
}

// Destructor
Good::~Good() {
    delete [] gName;
    gName = nullptr;
}

// Stores object data into file
fstream& Good::store(fstream& file, bool newLine) const{
        file << (gType == 'P' ? 'P' : 'N') << "," << sku() << "," << gName << "," << unit() << "," << taxed() << "," << itemPrice() << "," << quantity() << "," << qtyNeeded() << err;
	if(newLine == true) file << endl;
    return file;
}

// Extracts object data from file
fstream& Good::load(fstream& file){
    Good temp;
    char skuHold[max_sku_length];
    char nameHold[max_name_length];
    char unitHold[max_unit_length];
    char taxHold[10];
    char priceHold[10];
    char qAvailHold[10];
    char qNeedHold[10];

    file.getline(skuHold, max_sku_length, ',');
    file.getline(nameHold, max_name_length, ',');
    file.getline(unitHold, max_unit_length, ',');
    file.getline(taxHold, 10, ',');
    file.getline(priceHold, 10, ',');
    file.getline(qAvailHold, 10, ',');
    file.getline(qNeedHold, 10, ',');
    
    bool actTax = (strcmp(taxHold, "0")? true : false);
    int actQtyAvail = atoi(qAvailHold);
    int actQtyNeed = atoi(qNeedHold);
    double actPrice = atof(priceHold);
    
    *this = Good(skuHold, nameHold, unitHold, actQtyAvail, actTax, actPrice, actQtyNeed);
    return file;
}

// Outputs object's data
std::ostream& Good::write(std::ostream& os, bool linear) const{
    if(!this->err.isClear()) {
        os << err;
        return os;
    }
    else if(isEmpty()){
        os << "";
        return os;
    }
    if(linear == false){
        os << " Sku: " << gSku << endl;
        os << " Name (no spaces): " << gName << endl;
        os << " Price: " << setprecision(2) << gPrice << endl;
        os << " Price after tax: ";
        (gTaxStatus == true) ? os << setprecision(2) << itemCost() << endl : os << " N/A" << endl;
        os << " Quantity on Hand: " << gQtyAvail << " " << gUnit << endl;
        os << " Quantity needed: " << gQtyNeed;
    }
    else if(linear == true){
        os << gSku << setfill(' ') << setw((static_cast<int>(max_sku_length)+1)-static_cast<int>(strlen(gSku))) << "|";
        os << gName << setfill(' ') << setw(21-static_cast<int>(strlen(gName))) << "|";
        os << setfill(' ') << setw(7) << fixed << setprecision(2) << itemCost() << "|";
        os << setfill(' ') << setw(4) << gQtyAvail << "|";
        os << setfill(' ') << gUnit << setw(11-static_cast<int>(strlen(gUnit)))<< "|";
        os << setfill(' ') << setw(4) << gQtyNeed << "|";
    }
    return os;
}

// Extracts new item data from istream object
std::istream& Good::read(std::istream& is){
    char newSku[max_sku_length];
    char * newName = new char[max_name_length];
    char newUnit[max_unit_length];
    char taxed;
    bool taxStatus;
    double newPrice;
    int newQuantHand;
    int newQuantNeed;
    Error newErr;
    
    cout << " Sku: ";
    is >> newSku;
    cout << " Name (no spaces): ";
    is >> newName;
    cout << " Unit: ";
    is >> newUnit;
        cout << " Taxed? (y/n): ";
    is >> taxed;
    if(taxed != 'Y' && taxed != 'y' && taxed != 'N' && taxed != 'n'){
        err.message("Only (Y)es or (N)o are acceptable");
      is.setstate(std::ios::failbit);
    }
    else (taxed == 'y' || taxed == 'Y') ? taxStatus = true : taxStatus = false;
    if(!is.fail()){
      cout << " Price: ";
      is >> newPrice;
      if (is.fail()) err.message("Invalid Price Entry");
    }
    if(!is.fail()){
      cout << " Quantity on hand: ";
      is >> newQuantHand;
      if(is.fail()) err.message("Invalid Quantity Entry");
    }
    if(!is.fail()){
        cout << " Quantity needed: ";
      is >> newQuantNeed;
      if(is.fail()) err.message("Invalid Quantity Needed Entry");
    }
    if(!is.fail()){ 
        err.message(nullptr);
        is.clear();
        cin.ignore(1000, '\n');
        *this = Good(newSku, newName, newUnit, newQuantHand, taxStatus, newPrice, newQuantNeed);
    }
    return is;
}

// Outputs object data
std::ostream& aid::operator << (std::ostream& os, const iGood& gd){
    return gd.write(os, true);
}

// Inputs object data
std::istream& aid::operator>>(std::istream& is, iGood& gd){
    return gd.read(is);
}

// Checks whether objects have the same name
bool Good::operator==(const char* inputSku) const{
    return strncmp(inputSku, gSku, max_name_length);
}

// Returns the total cost of the object (item * quantity)
double Good::total_cost() const{
    return itemCost() * gQtyAvail;
}

// Increases quantity of item
void Good::quantity(int numUnits){
    if(numUnits >= 0) gQtyAvail = numUnits;
}

// Checks whether object in safe empty state
bool Good::isEmpty() const{
    if(gName[0] == '\0') return true;
    return false;
}

// Checks how much of the item is needed
int Good::qtyNeeded() const{
    return gQtyNeed;
}

// Checks the available quantity of the item
int Good::quantity() const{
    return gQtyAvail;
}

// Checks if the current object's name is alphabetically first
bool Good::operator > (const iGood& compareName) const{
    return (compareName.name() > gName);
}

// Increases the quantity of the item
int Good::operator += (int numItemsToAdd){
    if(numItemsToAdd > 0) gQtyAvail += numItemsToAdd;
    return gQtyAvail;
}
// Increases the cost of the object
double operator += (double& increase, const iGood& gd){
  double temp = increase + gd.total_cost();
  return temp;
}

