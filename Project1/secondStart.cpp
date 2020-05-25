#include <fstream>
#include <string>
#include <iostream>
#include "Conto.h"
using namespace std;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>



int maina() {

    string dir = "C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\1\\1.txt";

    Conto conto1;
    {
        
        ifstream file(dir);
        boost::archive::text_iarchive ar(file);
        ar >> conto1;
    }
    printf("Soldi nel conto: %d",conto1.getBalance());


    return 0;
}