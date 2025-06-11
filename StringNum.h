//
// Created by jacob on 3/17/2025.
//

#ifndef STRINGNUM_H
#define STRINGNUM_H
#include <string>

class StringNum {
private:
    unsigned int decimal;
    bool negative = false;
    std::string number;

    StringNum add(const StringNum& num)const&;
    StringNum sub(const StringNum& num)const&;
    StringNum subsub(const StringNum& num) const&;
    StringNum mult(const StringNum& num)const&;
    void trimBack();
    void trimFront();

public:
    StringNum();
    StringNum(const int& num);
    StringNum(const StringNum& num);
    StringNum(const std::string& num);

    StringNum& operator=(const StringNum& num);
    StringNum operator+ (const StringNum& num) const&;
    StringNum operator- (const StringNum& num) const&;
    StringNum operator* (const StringNum& num) const&;

    bool operator==(const StringNum& num)const&;
    bool operator!=(const StringNum& num)const&;
    bool operator>=(const StringNum& num)const&;
    bool operator<=(const StringNum& num)const&;
    bool operator>(const StringNum& num)const&;
    bool operator<(const StringNum& num)const&;

    std::string getNumber() const;
};
#endif //STRINGNUM_H
