#include "../include/BigArray.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <cstring>


BitArray::BitArray() {}

BitArray::~BitArray() {}

BitArray::BitArray(int num_bits, unsigned long value) {
    bits = (bool*)calloc(num_bits, sizeof(bool));
    for (int i = 0; i < num_bits; i++) bits[i] = value;
    numBits = num_bits;
}

BitArray::BitArray(const BitArray& b) : bits(b.bits), numBits(b.numBits) {
}

BitArray& BitArray::operator=(const BitArray& b) {
    numBits = b.numBits;
    bits = (bool*)calloc(b.numBits, sizeof(bool));
    if (b.bits != NULL) memcpy(bits, b.bits, sizeof(bits));
    return *this;
}

void BitArray::swap(BitArray& b) {
    BitArray A(b);
    int tmpNum = numBits;
    numBits = b.numBits;
    bool* tmp = b.bits;
    b.bits = bits;
    bits = tmp;
    b.numBits = tmpNum;
}

void BitArray::resize(int num_bits, bool value) {
    bool* newArray = (bool*)calloc(num_bits, sizeof(bool));
    for (int i = 0; i < num_bits; i++) {
        if (i < numBits) newArray[i] = bits[i];
        else newArray[i] = value;
    }
    bits = newArray;
    numBits = num_bits;
}

void BitArray::clear() {
    bits = NULL;
    numBits = 0;
}

void BitArray::push_back(bool bit) {
    numBits++;
    bits = (bool*)calloc(numBits, sizeof(bool));
    bits[numBits - 1] = bit;
}

BitArray& BitArray::operator&=(const BitArray& b)
{
    if (numBits == b.numBits) {
        for (int i = 0; i < numBits; i++) bits[i] *= b.bits[i];
        return *this;
    }
    else std::cout << "size error" << std::endl;
    return *this;
}


BitArray& BitArray::operator|=(const BitArray& b)
{
    if (numBits == b.numBits) {
        for (int i = 0; i < numBits; i++) bits[i] += b.bits[i];
        return *this;
    }
    else std::cout << "size error" << std::endl;
    return *this;

}

BitArray& BitArray::operator^=(const BitArray& b)
{
    if (numBits == b.numBits) {
        for (int i = 0; i < numBits; i++) {
            if (bits[i] != b.bits[i]) bits[i] = 1;
        }
    }
    else std::cout << "size error" << std::endl;
    return *this;
}

BitArray& BitArray::operator<<=(int n)
{
    for (int i = 0; i < numBits - n; i++) {
        bits[i] = bits[i + 1];
    }
    for (int i = numBits - n; i < numBits; i++) {
        bits[i] = 0;
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n)
{

    for (int i = numBits; i >= n; i--) {
        int tmp = bits[i];
        bits[i] = bits[i - n];
        bits[i - n] = tmp;
    }
    for (int i = 0; i < n; i++) {
        bits[i] = 0;
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const
{
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const
{
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set(int bit, bool value) {
    if (bit < numBits) {
        bits[bit] = value;
        return *this;
    }
    else {
        std::cout << "size error" << std::endl;
        return *this;
    }
}

BitArray& BitArray::set() {
    for (int i = 0; i < numBits; i++) bits[i] = true;
    return *this;
}

BitArray& BitArray::reset(int n)
{

    if (n >= 0 && n < numBits) {
        bits[n] = false;
    }
    else std::cout << "size error" << std::endl;
    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < numBits; i++) bits[i] = false;
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < numBits; i++) {
        if (bits[i] == true) return true;
    }
    return false;
}

bool BitArray::none() const {
    for (int i = 0; i < numBits; i++) {
        if (bits[i] == true) return false;
    }
    return true;
}

BitArray BitArray::operator~() const {

    BitArray result(*this);
    for (int i = 0; i < numBits; i++) {
        if (result.bits[i] == false) result.bits[i] = true;
        else result.bits[i] = false;
    }
    return result;

}

int BitArray::count() const
{
    int count = 0;
    for (int i = 0; i < numBits; i++) {
        if (bits[i] == true) count++;
    }
    return count;
}

bool BitArray::operator[](int i) const
{
    if (i < numBits) return bits[i];
    else {
        std::cout << "size error" << std::endl;
        return false;
    }
}

int BitArray::size() const {
    return numBits;
}

bool BitArray::empty() const {
    if (bits == NULL) return true;
    else return false;
}

std::string BitArray::to_string() const {
    std::string str;
    for (int i = 0; i < numBits; i++) {
        if (bits[i] == true) str += '1';
        else str += '0';
    }
    return str;
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) return false;
        }
    }
    else {
        return false;
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) return true;
        }
    }
    else {
        return true;
    }
    return false;
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}