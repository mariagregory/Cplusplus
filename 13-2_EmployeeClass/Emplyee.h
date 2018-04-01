/* 
 * File:   Emplyee.h
 * Author: Mariia Gregory
 *
 * Created on March 27, 2018, 9:38 PM
 */

#ifndef EMPLYEE_H
#define EMPLYEE_H

class Emplyee {
    private:
        char *name;
        int id;
        char *depmnt;
        char *positn;
        static int autoId;
    public: 
        Emplyee();
        Emplyee(const char*, int);
        Emplyee(const char*, int, const char*, const char*);
        void setName(const char*);
        void setId(int);
        void setDept(const char*);
        void setPosn(const char*);
        char* getName() const { return name; }
        int getId() const { return id; }
        char* getDept() const {return depmnt; }
        char* getPosn() const { return positn; }
        ~Emplyee() {
            delete name; delete depmnt; delete positn;
        }
};

#endif /* EMPLOYEE_H */

