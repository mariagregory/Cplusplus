/* 
 * File:   Person.h
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:38 AM
 */

#ifndef PERSON_H
#define PERSON_H

class Person {
    private:
        char *name;
        short age;
        char *address;
        char *phone;
    public:
        Person();
        Person(const char*, short, const char*, const char*);
        void setName(const char*);
        void setAge(short);
        void setAddr(const char*);
        void setPhon(const char*);
        char *getName() const { return name; }
        short getAge() const { return age; }
        char *getAddr() const { return address; }
        char *getPhon() const { return phone; }
        ~Person() { delete name; delete address; delete phone; }
};

#endif /* PERSON_H */

