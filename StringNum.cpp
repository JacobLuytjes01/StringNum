//
// Created by jacob on 3/17/2025.
//

#include "StringNum.h"

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
        number[0] = '0';
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
    trimBack();
    trimFront();
}
StringNum& StringNum::operator=(const StringNum& num) {
    number = num.number;
    decimal = num.decimal;
    negative = num.negative;
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
            if (num.decimal <= this->decimal) {
                return this->add(temp);
            }
            return temp.add(*this);
        }
        StringNum temp = *this;
        temp.number.append(std::string( num.number.length() - num.decimal - (this->number.length() - this->decimal), '0'));
        if (num.decimal <= this->decimal) {
            return temp.add(num);
        }
        return num.add(temp);
    }
    else {
        if (num.negative) {
            StringNum temp = num;
            temp.negative = false;
            return *this - temp;
        }
        else {
            StringNum temp = *this;
            temp.negative = false;
            temp = temp - num;
            temp.negative = !temp.negative;
            return temp;
        }
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
        ++result.decimal;
    }
    result.trimBack();
    return result;
}

StringNum StringNum::subsub(const StringNum& num) const& {
    if (num.decimal < this->decimal) {
        return this->sub(num);
    }
    else if (num.decimal == this->decimal && this->number > num.number) {
        return this->sub(num);
    }
    StringNum temp = num.sub(*this);
    temp.negative = true;
    return temp;
}

StringNum StringNum::operator- (const StringNum& num) const& {
    if (this->negative == num.negative) {
        if (this->number.length() - this->decimal == num.number.length() - num.decimal) {
            return this->subsub(num);
        }
        else if (this->number.length() - this->decimal >= num.number.length() - num.decimal) {
            StringNum temp = num;
            temp.number.append(std::string(this->number.length() - this->decimal - (num.number.length() - num.decimal), '0'));
            return this->subsub(temp);
        }
        else {
            StringNum temp = *this;
            temp.number.append(std::string( num.number.length() - num.decimal - (this->number.length() - this->decimal), '0'));
            return temp.subsub(num);
        }
    }
    else {
        StringNum temp = num;
        temp.negative = !num.negative;
        return *this + temp;
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
        else if (i != 0 && result.number[i] < '0') {
            result.number[i] = result.number[i] + 10;
            result.number[i-1]--;
        }
        else {break;}
    }
    result.trimBack();
    result.trimFront();
    return result;
}

StringNum StringNum::operator* (const StringNum& num) const& {
    if (this->negative == num.negative) {
        return this->mult(num);
    }
    else {
        StringNum result = *this;
        result = result.mult(num);
        result.negative = true;
        return result;
    }
}

StringNum StringNum::mult(const StringNum& num) const&{
    std::string resultString;
    const unsigned int numLength = this->number.length();
    const unsigned int numLength2 = num.number.length();
    resultString.append(numLength2 - 2 + numLength, '0');

    int numPos = resultString.length();
    int temp = 0;
    for (int i = numLength-1; i >= 0; --i) {
        if (this->number[i] == '0') {
            ++temp;
        }
        else if (this->number[i] == '.') {

        }
        else {
            int temp2 = 1;
            for (int j = numLength2-1; j >= 0; --j) {
                if (num.number[j] == '0') {
                    ++temp2;
                }
                else if (num.number[j] == '.') {

                }
                else {
                    resultString[numPos - (temp + temp2)] += ((this->number[i] - '0') * (num.number[j] - '0'));

                    while (resultString[numPos - (temp + temp2)] > '9' || resultString[numPos - (temp + temp2)] < '0') {
                        resultString[numPos - (temp + temp2)] -= 10;
                        resultString[numPos - (temp + temp2) - 1]++;
                    }
                    ++temp2;
                }
            }
            ++temp;
        }
    }
    std::string numBase = resultString.substr(0, (this->decimal + num.decimal));
    numBase.push_back('.');
    numBase += resultString.substr(numBase.length() - 1);
    return StringNum(numBase);
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
