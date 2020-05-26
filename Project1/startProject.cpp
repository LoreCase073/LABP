#include <fstream>
#include <string>
#include "Conto.h"
using namespace std;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>




int mainaaaa() {
    
    string dir = "C:\\Users\\lorec\\source\\repos\\Project1\\Project1";
    
    Conto conto1 = Conto("Lorenzo", "Principale", 1);
    conto1.insertGain(500, 25, 05, 2020);


    
    return 0;
}