#ifndef PACKAGE_H
#define PACKAGE_H
#include "../conctants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

class Package
{
    public:
        Package();
        virtual ~Package();
        char *Pack();
        void Print();
        void Scan(const char* name);
        void Parse(const char* c);
    protected:
    private:
        char MTI[mti_size];
        unsigned char PAN[pan_size];
        int EXP_DATE[2];
        unsigned short CVV2;
        char PRICE[price_size];
        unsigned short CURRENCY;
        int DATE_OPERATION[3];
        int TIME_OPERATION[3];
        char CARD_HOLDER[card_holder_size];
        char MSG[3];


        char MESSAGE[package_size];

};

#endif // PACKAGE_H
