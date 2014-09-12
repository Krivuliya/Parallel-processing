#include <iostream>
#include "conctants.h"
#include "include/Package.h"

using namespace std;

int main()
{
    char message[package_size];
    Package p;
    p.Scan("params_.txt");
    p.Parse(p.Pack());
    return 0;
}
