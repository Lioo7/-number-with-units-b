#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main()
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{1, "km"};     // 1km = 1,000m = 100,000cm
    NumberWithUnits b{200, "m"};    // 0.2km = 200m = 20,000cm
    NumberWithUnits c{30, "cm"};    // 0.0003km = 0.3m = 30cm
    NumberWithUnits a_n{-1, "km"};  // -1km = -1,000m = -100,000cm
    NumberWithUnits b_n{-200, "m"}; // -0.2km = -200m = -20,000cm
    NumberWithUnits c_n{-30, "cm"}; // -0.0003km = -0.3m = -30cm

    cout << a << endl;       // Prints "1[km]".
    cout << (-a) << endl;    // Prints "-1[km]"
    cout << (2 * a) << endl; // Prints "2[km]"

    cout << b << endl;       // Prints "200[m]".
    cout << (+b) << endl;    // Prints "200[m]"
    cout << (b * 3) << endl; // Prints "600[m]"
    //+
    cout << a + b << endl; //(1.2, "km")
    cout << a + a << endl; //(2, "km")
    cout << b + a << endl; //(1200, "m")
    //-
    cout << a - b << endl; //(0.8, "km")
    cout << b - a << endl; //(-800, "m")

    // +=
    a += NumberWithUnits{2, "km"};
    cout << a << endl; //(3, "km")
    // -=
    a -= NumberWithUnits{2, "km"};
    cout << a << endl; //(1, "km")

    //true
    cout << (a != c) << endl;
    cout << (a > b) << endl;
    cout << (c < b) << endl;
    cout << (c >= c) << endl;

    // false
    bool result;
    result = (a != a);
    cout << result << endl;
    result = (a == c);
    cout << result << endl;
    result = (a < b);
    cout << result << endl;
    result = (b <= c);
    cout << result << endl;
    result = (b == b_n);
    cout << result << endl;
    result = (c < c_n);
    cout << result << endl;

    NumberWithUnits input_2(6, "km");
    istringstream my_stream_2("200 [ m ]");
    my_stream_2 >> input_2;

    ostringstream output2;
    output2 << b;
    cout << b << endl;  //print(200[m])

    // operator with no the same type
    NumberWithUnits e{60, "ILS"};   
    cout << a + e << endl; // should throw an error

    return 0;
}
