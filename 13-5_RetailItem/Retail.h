/* 
 * File:   Retail.h
 * Author: Maria Gregory
 *
 * Created on March 28, 2018, 7:22 PM
 */

#ifndef RETAIL_H
#define RETAIL_H

class Retail {
    private:
        char *descr;
        short onHand;
        float price;
    public:
        Retail();
        Retail(const char*, short, float);
        void setDesc(const char*);
        void setQnty(short);
        void setPrce(float);
        char *getDesc() const { return descr; }
        short getQnty() const { return onHand; }
        float getPrce() const { return price; }
        ~Retail() { delete descr; }
};

#endif /* RETAIL_H */

