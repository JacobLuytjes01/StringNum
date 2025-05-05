//
// Created by Jacob Luytjes on 3/17/2025.
//

#include "StringNum.h"
#include <iostream>

StringNum::StringNum() {
    number = "0.0";
    decimal = 1;
    negative = false;
}
StringNum::StringNum(const int& num) {
    std::string temp = std::to_string(num);
    if (temp.at(0) == '-') {
        negative = true;
        number = temp.substr(1, temp.length() - 1);
    }
    else {
        number = std::to_string(num);
    }
    decimal = number.length();
    number += ".0";
}
StringNum::StringNum(const StringNum& num) {
    number = num.number;
    decimal = num.decimal;
    negative = num.negative;
}
StringNum::StringNum(const std::string& num): decimal(-1) {
    number = num;
    int i = 0;

    if (number[0] == '-') {
        ++i;
        negative = true;
    }
    while (i < number.length() && decimal == -1) {
        if (number[i] == '.') {
            decimal = i;
        }
        else {
            if (number[i] < '0') {
                number[i] = '0';
            }
            else if (number[i] > '9') {
                number[i] = '9';
            }
        }
        ++i;
    }
    if (decimal == -1) {
        decimal = number.length();
        number += ".0";
    }
}
StringNum& StringNum::operator=(const StringNum& num) {
    number = num.number;
    decimal = num.decimal;
    return *this;
}
StringNum StringNum::operator+ (const StringNum& num) const& {
    if (this->negative == num.negative) {
        if (this->number.length() - this->decimal == num.number.length() - num.decimal) {
            if (num.number.length() <= this->number.length()) {
                return this->add(num);
            }
            return num.add(*this);
        }

        if (this->number.length() - this->decimal >= num.number.length() - num.decimal) {
            StringNum temp = num;
            temp.number.append(std::string(this->number.length() - this->decimal - (num.number.length() - num.decimal), '0'));
            if (num.number.length() <= this->number.length()) {
                return this->add(temp);
            }
            return temp.add(*this);
        }
        StringNum temp = *this;
        temp.number.append(std::string( num.number.length() - num.decimal - (this->number.length() - this->decimal), '0'));
        if (num.number.length() <= this->number.length()) {
            return temp.add(num);
        }
        return num.add(temp);
    }
    else {
        // todo: negative section
        std::cout << "fail" << std::endl;
        return StringNum();
    }
}

StringNum StringNum::add(const StringNum& num) const&{
    StringNum result(*this);
    const unsigned int numLength = result.number.length();
    const int numOffset = (result.decimal) - (num.decimal);

    for (int i = numLength-1; i >= 0; --i) {
        if (i - numOffset >= 0) {
            if (result.number[i] != '.' && result.number[i] != '-') {
                result.number[i] = (result.number[i] + (num.number[i - numOffset] - '0'));

                if (result.number[i] > '9' && i != 0) {
                    result.number[i] = result.number[i] - 10;
                    if (i-1 == result.decimal) {
                        result.number[i-2]++;
                    }
                    else {
                        result.number[i-1]++;
                    }
                }
            }
        }
        else {
            if (i != 0 && result.number[i] > '9') {
                result.number[i] = result.number[i] - 10;
                result.number[i-1]++;
            }
            else {break;}
        }
    }
    if (result.number[0] > '9') {
        result.number[0] = result.number[0] - 10;
        result.number = "1" + result.number;
    }
    result.trimBack();
    return result;
}

StringNum StringNum::operator- (const StringNum& num) const& {
    if (this->number.length() - this->decimal == num.number.length() - num.decimal) {
        if (num.number.length() <= this->number.length()) {
            if (this->number < num.number) {
                StringNum temp = num.sub(*this);
                temp.negative = true;
                return temp;
            }
            return this->sub(num);
        }
        return num.sub(*this);
    }
    else if (this->number.length() - this->decimal >= num.number.length() - num.decimal) {
        StringNum temp = num;
        temp.number.append(std::string(this->number.length() - this->decimal - (num.number.length() - num.decimal), '0'));
        if (num.number.length() <= this->number.length()) {
            return this->sub(temp);
        }
        return temp.sub(*this);
    }
    else {
        StringNum temp = *this;
        temp.number.append(std::string( num.number.length() - num.decimal - (this->number.length() - this->decimal), '0'));
        if (num.number.length() <= this->number.length()) {
            return temp.sub(num);
        }
        return num.sub(temp);
    }
}
StringNum StringNum::sub(const StringNum& num) const&{
    StringNum result(*this);
    const unsigned int numLength = result.number.length();
    const int numOffset = (result.decimal) - (num.decimal);

    for (int i = numLength-1; i >= 0; --i) {
        if (i - numOffset >= 0) {
            if (result.number[i] != '.') {
                result.number[i] = result.number[i] + '0' - num.number[i - numOffset];

                if (result.number[i] < '0' && i != 0) {
                    result.number[i] = result.number[i] + 10;
                    if (i-1 == result.decimal) {
                        result.number[i-2]--;
                    }
                    else {
                        result.number[i-1]--;
                    }
                }
            }
        }
        else {
            if (i != 0 && result.number[i] < '0') {
                result.number[i] = result.number[i] + 10;
                result.number[i-1]++;
            }
            else {break;}
        }
    }
    if (result.number[0] > '9') {
        result.number[0] = result.number[0] - 10;
        result.number = "1" + result.number;
    }
    result.trimBack();
    result.trimFront();
    return result;
}

std::string StringNum::getNumber() const {
    if (negative) {
        std::string temp = "-";
        temp.append(number);
        return temp;
    }
    return number;
}
void StringNum::trimBack() {
    unsigned int i = number.length()-1;
    while (number[i] == '0') {
        --i;
    }
    if (number[i] == '.') {
        number = number.substr(0, i+2);
    }
    else {
        number = number.substr(0, i+1);
    }
}
void StringNum::trimFront() {
    unsigned int i = 0;
    while (number[i] == '0') {
        ++i;
    }
    if (number[i] == '.') {
        number = number.substr(i-1, number.length());
        decimal -= (i-1);
    }
    else {
        number = number.substr(i, number.length());
        decimal -= i;
    }
}

bool StringNum::operator==(const StringNum& num) const& {
    if (this == &num) {
        return true;
    }
    else if (this->negative == num.negative && this->decimal == num.decimal && this->number.length() == num.number.length()) {
        if (this->number == num.number) {
            return true;
        }
    }
    return false;
}
bool StringNum::operator!=(const StringNum& num) const& {
    return !(*this == num);
}
bool StringNum::operator>=(const StringNum& num) const& {
    if (this == &num) {
        return true;
    }
    else if (this->negative == num.negative) {
        bool result = false;

        if (this->decimal > num.decimal) {
            result = true;
        }
        else if (this->decimal == num.decimal) {
            result = this->number >= num.number;
        }

        if (this->negative) {
            return !result;
        }
        else {
            return result;
        }
    }
    else if (!this->negative && num.negative) {
        return true;
    }
    return false;
}
bool StringNum::operator<=(const StringNum& num) const& {
    return !(*this > num);
}
bool StringNum::operator<(const StringNum& num) const& {
    return !(*this >= num);
}
bool StringNum::operator>(const StringNum& num) const& {
    if (this == &num) {
        return false;
    }
    else if (this->negative == num.negative) {
        bool result = false;

        if (this->decimal > num.decimal) {
            result = true;
        }
        else if (this->decimal == num.decimal) {
            result = this->number > num.number;
        }

        if (this->negative) {
            return !result;
        }
        else {
            return result;
        }
    }
    else if (!this->negative && num.negative) {
        return true;
    }
    return false;
}
