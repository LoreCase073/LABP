#include <fstream>
#include "Conto.h"
#include "Date.h"







int main() {
    try {
    Date d = Date(28,6,2003);
    cout << d.getDay() << endl;

    cout << d.getMonth() << endl;

    cout << d.getYear() << endl;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    
    

    return 0;
}

