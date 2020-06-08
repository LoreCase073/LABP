#include <fstream>
#include "Conto.h"

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
class gps_position
{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& degrees;
        ar& minutes;
        ar& seconds;
    }
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position() {};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};



int main() {
    string dir = "C:\\Users\\lorec\\source\\repos\\Project1\\Project1";
    Conto conto1 = Conto("Lorenzo", "Principale", 1);
    conto1.insertGain(5700, 25, 05, 2020);
    conto1.insertExpense(2700, 25, 05, 2020);
    
    return 0;
}

