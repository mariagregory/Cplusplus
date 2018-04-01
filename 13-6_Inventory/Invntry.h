/* 
 * File:   Invntry.h
 * Author: Mariia Gregory
 *
 * Created on March 28, 2018, 10:25 PM
 */

#ifndef INVNTRY_H
#define INVNTRY_H

class Invntry {
private:
    short itemNo, qnty;
    float cost, total;
public:
    Invntry() { itemNo=0; qnty=0; cost=0.0; total=0.0; } //constructor, when no arguments are provided
    Invntry(short, short, float); //constructor, when all arguments are provided
    void setItNo(short);
    void setQnty(short);
    void setCost(float);
    void setTot();
    void setTotalCost();
    short getItNo() const { return itemNo; }
    short getQnty() const { return qnty; }
    float getCost() const { return cost; }
    float getTot() const { return total; }
};


#endif 
