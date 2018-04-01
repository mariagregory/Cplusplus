/* 
 * File:   Account.h
 * Author: Mariia Gregory
 *
 * Created on March 18, 2018, 8:39 PM
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account {
    char name[31];
    char addrs_1[51];
    char addrs_2[31];
    char phone[21];
    float balance;
    char payDate[11];
};

#endif /* ACCOUNT_H */

