#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace ariel
{
    class NumberWithUnits
    {
    private:
        // variables
        double number;
        string unit;

        // functions
        static void throw_error(const NumberWithUnits &unit_element_1, const NumberWithUnits &unit_element_2);
        static bool is_valid(const string &unit);
        static double unit_convert(const NumberWithUnits &unit_element_1, const NumberWithUnits &unit_element_2);
        static void find_transitive(const string &unit_1, const string &unit_2);

    public:
        // constructor
        NumberWithUnits(const double number, const string unit);
        static void read_units(std::ifstream &file_name);

        // overloading the arithmetic operators
        // positive
        NumberWithUnits operator+(const NumberWithUnits &unit_element);
        NumberWithUnits operator+=(const NumberWithUnits &unit_element);
        NumberWithUnits operator+();

        // negative
        NumberWithUnits operator-(const NumberWithUnits &unit_element);
        NumberWithUnits operator-=(const NumberWithUnits &unit_element);
        NumberWithUnits operator-();

        // overloading equality operators 
        bool operator>(const NumberWithUnits &unit_element) const;
        bool operator>=(const NumberWithUnits &unit_element) const;
        bool operator<(const NumberWithUnits &unit_element) const;
        bool operator<=(const NumberWithUnits &unit_element) const;
        bool operator==(const NumberWithUnits &unit_element) const;
        bool operator!=(const NumberWithUnits &unit_element) const;

        // overloading increment and decrement operators
        // prefix
        NumberWithUnits &operator++();
        NumberWithUnits &operator--();
        // postfix
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);


        // overloading multiplication operator
        // direction: ->
        NumberWithUnits operator*(double num);
        // direction: <-
        friend NumberWithUnits operator*(double num, const NumberWithUnits &unit_element);

        // friend global overloading I/O operators
        friend istream &operator>>(istream &input, NumberWithUnits &unit_element);
        friend ostream &operator<<(ostream &output, const NumberWithUnits &unit_element);
    };
}
