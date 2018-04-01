/* 
 * File:   Mortgg.h
 * Author: Mariia Gregory
 *
 * Created on March 29, 2018, 12:09 PM
 */

#ifndef MORTGG_H
#define MORTGG_H

class Mortgg {
    private:
        float loanAmt, anRate, monPmt, total;
        short years;//, timesPY;
    public:
        Mortgg() { loanAmt=0.0; anRate=0.0; years=0; }
        Mortgg(float, float, short);
        void setPV(float);
        void setYRte(float);
        void setYrs(short);
        void setPmt();
        float getPV() const { return loanAmt; }
        float getRate() const { return anRate; }
        short getYrs() const { return years; }
        float getPmt() const { return monPmt; }
        float getTot();
};

#endif /* MORTGG_H */

