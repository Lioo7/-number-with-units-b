#include <iostream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
static map<string, map<string, double>> units_map;
const double epsilon = 0.001;

namespace ariel
{
    //==============================================constructor=============================================
    NumberWithUnits::NumberWithUnits(const double number, const string unit)
    {
        if (is_valid(unit))
        {
            this->number = number;
            this->unit = unit;
        }
        else
        {
            throw invalid_argument("Error: does not recognize this unit");
        }
    }

    //==========================================ultilize functions==========================================

    // This function throws an error when gets invalid input
    void NumberWithUnits::throw_error(const NumberWithUnits &unit_element_1, const NumberWithUnits &unit_element_2)
    {
        string a = unit_element_1.unit;
        string b = unit_element_2.unit;
        throw std::invalid_argument("Units do not match [" + a + "] cannot be converted to [" + b + "]");
    }

    // This function check is the element is valid
    bool NumberWithUnits::is_valid(const string &unit)
    {
        return (units_map.count(unit) == 1);
    }

    // This function convert the unit if it's possible and necessary
    double NumberWithUnits::unit_convert(const NumberWithUnits &unit_element_1, const NumberWithUnits &unit_element_2)
    {
        double ans = unit_element_2.number;
        // checks if both the elments have the same unit
        if (unit_element_1.unit == unit_element_2.unit)
        {
        }
        // checks if is it possible to convert
        else if (units_map[unit_element_1.unit].count(unit_element_2.unit) < 1)
        {
            throw_error(unit_element_1, unit_element_2);
        }
        // returns the convert number(second number * ratio)
        else
        {
            double second_number = unit_element_2.number;
            double ratio = units_map[unit_element_2.unit][unit_element_1.unit];
            ans = second_number * ratio;
        }
        return ans;
    }

    // finds transitive relations between the units in the unit map
    void NumberWithUnits::find_transitive(const string &unit_1, const string &unit_2)
    {
        double sum = 0;
        // iterates through the units_map
        for (const auto &pair : units_map[unit_1])
        {
            sum = units_map[unit_2][unit_1] * pair.second;
            units_map[unit_2][pair.first] = sum;
            units_map[pair.first][unit_2] = 1 / sum;
        }
    }

    //==========================================method operators============================================

    void NumberWithUnits::read_units(ifstream &file_name)
    {
        double num_1 = 0;
        double num_2 = 0;
        string unit_1, unit_2, garbage;
        // iterates through the file
        while (file_name >> num_1 >> unit_1 >> garbage >> num_2 >> unit_2)
        {
            units_map[unit_1][unit_2] = num_2;         // adds the first direction ->
            units_map[unit_2][unit_1] = num_1 / num_2; // adds the opposite direction <-

            find_transitive(unit_1, unit_2); // finds the first direction ->
            find_transitive(unit_2, unit_1); // finds the opposite direction <-
        }
    }

    // overloading the arithmetic operators
    // positive
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &unit_element)
    {
        double sum = unit_convert(*this, unit_element);
        return NumberWithUnits(this->number + sum, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits &unit_element)
    {
        double sum = unit_convert(*this, unit_element);
        this->number += sum;
        return NumberWithUnits(*this);
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits{this->number, this->unit};
    }
    // negative
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &unit_element)
    {
        double sum = unit_convert(*this, unit_element);
        return NumberWithUnits(this->number - sum, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &unit_element)
    {
        double sum = unit_convert(*this, unit_element);
        this->number -= sum;
        return NumberWithUnits(*this);
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits{-(this->number), this->unit};
    }
    //
    NumberWithUnits &NumberWithUnits::operator++()
    {
        number++;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
           number--;
            return *this;
    }

        NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits original = *this;
        number++;
        return original;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
            NumberWithUnits original = *this;
            number--;
            return original;
    }

    // overloading equality operators
    bool NumberWithUnits::operator>(const NumberWithUnits &unit_element) const
    {
        double num_1 = this->number;
        double num_2 = unit_convert(*this, unit_element);
        return (num_1 > num_2);
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &unit_element) const
    {
        return (*this > unit_element || *this == unit_element);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &unit_element) const
    {
        double num_1 = this->number;
        double num_2 = unit_convert(*this, unit_element);
        return (num_1 < num_2);
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &unit_element) const
    {
        return (*this < unit_element || *this == unit_element);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &unit_element) const
    {
        double num_1 = this->number;
        double num_2 = unit_convert(*this, unit_element);
        return abs(num_1 - num_2) < epsilon;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &unit_element) const
    {
        double num_1 = this->number;
        double num_2 = unit_convert(*this, unit_element);
        return (num_1 != num_2);
    }

    // overloading multiplication operator
    // direction: ->
    NumberWithUnits NumberWithUnits::operator*(double num)
    {
        return NumberWithUnits{this->number * num, this->unit};
    }
    // (friend) direction: <-
    NumberWithUnits operator*(double num, const NumberWithUnits &unit_element)
    {
        return NumberWithUnits{unit_element.number * num, unit_element.unit};
    }

    // friend global overloading I/O operators
    std::istream &operator>>(istream &input, NumberWithUnits &unit_element)
    {
        string unit;
        string number;
        string line;
        getline(input, line, ']');
        bool flag_num = false; // flag true: number have been added

        // iterates through the characters of the line
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
            }
            else if ((line[i] >= '0' && line[i] <= '9') || (line[i] == '-') || (line[i] == '.'))
            {
                number += line[i];
                flag_num = true;
            }
            else if (line[i] != '[' && flag_num)
            {
                unit += line[i];
            }
        }

        if (!NumberWithUnits::is_valid(unit))
        {
            throw invalid_argument("Error: does not recognize this unit");
        }

        unit_element.unit = unit;
        unit_element.number = stod(number);
        return input;
    }

    std::ostream &operator<<(ostream &output, const NumberWithUnits &unit_element)
    {
        output << unit_element.number << '[' << unit_element.unit << ']';
        return output;
    }

}
