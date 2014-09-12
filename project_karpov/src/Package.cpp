#include "../include/Package.h"
#define compress(data_addr,pos,n) memcpy(MESSAGE+pos, data_addr,n)

using namespace std;

size_t strlen(const unsigned char *str)
{
    size_t c;
    for(c=0;str[c]!=0;c++);
    return c;
}

Package::Package()
{
    //ctor
}

char *Package::Pack()
{
    char exp_d = (EXP_DATE[0]<<4)+EXP_DATE[1];
    unsigned char pan_ =min(strlen(PAN),(size_t)pan_size);
    int c;
    char chs=min(strlen(CARD_HOLDER),(size_t)card_holder_size);
    compress(MTI, 0, 4);
    compress(&pan_, 4, 1);
    for(int i=0;i<pan_size/2;i++)
    {
        pan_ = ((PAN[i*2]-'0')<<4)+(PAN[i*2+1]-'0');
        compress(&pan_, 5+i, 1);
    }
    compress(&exp_d, 17, 2);
    compress(&CVV2, 19, 2);
    compress(PRICE, 21, price_size);
    compress(&CURRENCY, 33, 2);
    sprintf(MESSAGE+35,"%2d%2d%2d", DATE_OPERATION[0],DATE_OPERATION[1],DATE_OPERATION[2]);
    sprintf(MESSAGE+41,"%2d%2d%2d", TIME_OPERATION[0],TIME_OPERATION[1],TIME_OPERATION[2]);
    compress(&chs, 47, 1);
    compress(CARD_HOLDER, 48, card_holder_size);
    compress(MSG, 88, 3);
    return MESSAGE;
}

void Package::Print()
{
    unsigned short sh;
    for(int i=0;i<package_size;i++)
    {
        printf("%c",MESSAGE[i]);          ///1, PAN, EXD
    }
    printf("\n");
    char mas[40];
    memcpy(mas,MESSAGE,4);
    for(int i=0;i<4;i++)
        printf("%c",mas[i]);                       //MTI
    for(int i=0;i<pan_size/2+3;i++)
    {
        printf("%c",MESSAGE[i+4]);          ///1, PAN, EXD
    }
    memcpy(&sh,MESSAGE+19,2);
    cout<<(sh);          ///CVV2
    memcpy(mas,MESSAGE+21,price_size);
    cout<<mas;
    memcpy(&sh,MESSAGE+33,2);         ///summ
    cout<<sh;          ///val
    memcpy(mas,MESSAGE+35,12);              ///d, t
    for(int i=0;i<12;i++)
        printf("%c",mas[i]);
    printf("%X",MESSAGE[47]);               ///1
    memcpy(mas,MESSAGE+48,43);
    cout<<mas<<endl;                        ///ch, 9
    cin>>mas;
}

void Package::Scan(const char* name)
{
    for(int i=0;i<pan_size;i++)
    {
        PAN[i]=0;
    }
    ifstream file(name);
    file>>MTI[0]>>MTI[1]>>MTI[2]>>MTI[3];
    file>>PAN;
    file>>EXP_DATE[0]>>EXP_DATE[1];
    file>>CVV2;
    file>>PRICE;
    file>>CURRENCY;
    file>>DATE_OPERATION[0]>>DATE_OPERATION[1]>>DATE_OPERATION[2];
    file>>TIME_OPERATION[0]>>TIME_OPERATION[1]>>TIME_OPERATION[2];
    file.get(CARD_HOLDER,card_holder_size,';') ;
    while (CARD_HOLDER[0]=='\n')
        memcpy(CARD_HOLDER,CARD_HOLDER+1,card_holder_size-1);


    cout<<MTI[0]<<MTI[1]<<MTI[2]<<MTI[3]<<endl;
    cout<<PAN<<endl;
    cout<<EXP_DATE[0]<<" "<<EXP_DATE[1]<<endl;
    cout<<CVV2<<endl;
    cout<<PRICE<<endl;
    cout<<CURRENCY<<endl;
    cout<<DATE_OPERATION[0]<<DATE_OPERATION[1]<<DATE_OPERATION[2]<<endl;
    cout<<TIME_OPERATION[0]<<TIME_OPERATION[1]<<TIME_OPERATION[2]<<endl;
    cout<<CARD_HOLDER<<endl;
}

Package::~Package()
{
    //dtor
}
void Package::Parse(const char* name)
{
    unsigned short sh;
    size_t p_s=0, ch_s=0;
    char mas[40];
    unsigned char pan_1,pan_2,ed;
    char str[17];


    memcpy(MTI,MESSAGE,mti_size);           ///MTI
    memcpy(&p_s,MESSAGE+4, 1);

    for(int i=0;i<pan_size/2;i++)
    {
        memcpy(&pan_2,MESSAGE+5+i, 1);
        pan_1=(pan_2>>4);
        pan_2-=(pan_1<<4);
        PAN[i*2]=pan_1+'0';
        PAN[i*2+1]=pan_2+'0';
    }
    EXP_DATE[0]=0,EXP_DATE[1]=0;
    memcpy(&EXP_DATE[1],MESSAGE+17, 1);
    EXP_DATE[0]=(EXP_DATE[1]>>4);
    EXP_DATE[1]-=(EXP_DATE[0]<<4);
    memcpy(&CVV2,MESSAGE+19,2);
    memcpy(&PRICE,MESSAGE+21,price_size);
    memcpy(&CURRENCY,MESSAGE+33,2);
    sprintf(str,"%c%c %c%c %c%c %c%c %c%c %c%c",
            *(MESSAGE+35),*(MESSAGE+36), *(MESSAGE+37),*(MESSAGE+38), *(MESSAGE+39),*(MESSAGE+40),
            *(MESSAGE+41),*(MESSAGE+42), *(MESSAGE+43),*(MESSAGE+44), *(MESSAGE+45),*(MESSAGE+46));
    sscanf(str,"%d %d %d %d %d %d",DATE_OPERATION,DATE_OPERATION+1,DATE_OPERATION+2,
                                   TIME_OPERATION,TIME_OPERATION+1,TIME_OPERATION+2);
    memcpy(&ch_s,MESSAGE+47,1);
    memcpy(CARD_HOLDER,MESSAGE+48,card_holder_size);
    memcpy(MSG,MESSAGE+88,3);
    /*
    for(int i=0;i<pan_size/2+3;i++)
    {
        printf("%c",MESSAGE[i+4]);          ///1, PAN, EXD
    }
    memcpy(&sh,MESSAGE+19,2);
    cout<<(sh);          ///CVV2
    memcpy(mas,MESSAGE+21,price_size);
    cout<<mas;
    memcpy(&sh,MESSAGE+33,2);         ///summ
    cout<<sh;          ///val
    memcpy(mas,MESSAGE+35,12);              ///d, t
    for(int i=0;i<12;i++)
        printf("%c",mas[i]);
    printf("%X",MESSAGE[47]);               ///1
    memcpy(mas,MESSAGE+48,43);
    cout<<mas<<endl;                        ///ch, 9
    cin>>mas;*/
}
