/* 
 * File:   main.cpp
 * Author: admin
 *
 * Created on March 27, 2018, 9:36 PM
 * Purpose: Specification file for the employee class
 */
#include <cstdlib>
#include <cstring>
#include "Emplyee.h"
using namespace std;

// definition of the static variable
int Emplyee::autoId = 1; //if employee ID is invalid or not provided, assign an auto number and increment it afterwards

//constructor, when no arguments are provided
Emplyee::Emplyee() {
    name = new char[50];
    depmnt = new char[50];
    positn = new char[30];
    strcpy(name,"");
    strcpy(depmnt,"");
    strcpy(positn,"");
    id = autoId; autoId++;
}
//constructor, when only the first 2 arguments are provided
Emplyee::Emplyee(const char *n, int i) {
    name = new char[50];
    depmnt = new char[50];
    positn = new char[30];
    strcpy(depmnt,"");
    strcpy(positn,"");
    setName(n);
    setId(i);
}
//constructor, when all arguments are provided
Emplyee::Emplyee(const char *n, int i, const char *dep, const char *pos) {
    name = new char[50];
    depmnt = new char[50];
    positn = new char[30];
    setName(n);
    setId(i);
    setDept(dep);
    setPosn(pos);
}
// Mutator functions:
//validate parameter values and assign them to member variables
void Emplyee::setId(int i) { // private
    if(i>=0 && i<=99999) id=i;
    else { id = autoId; autoId++; }
}
void Emplyee::setName(const char *n) {
//    if(strlen(n)<sizeof(name)) strcpy(name,n);
//    else { strncpy(name, n, sizeof(name)-1); name[sizeof(name)-1]='\0'; }
    strcpy(name,n);
}
void Emplyee::setDept(const char *dep) {
//    if(strlen(dep)<sizeof(depmnt)) strcpy(depmnt,dep);
//    else strncpy(depmnt, dep, sizeof(depmnt)-1);
    strcpy(depmnt,dep);
}
void Emplyee::setPosn(const char *pos) {
//    if(strlen(pos)<sizeof(positn)) strcpy(positn,pos);
//    else strncpy(positn, pos, sizeof(positn)-1);
    strcpy(positn,pos);
}
