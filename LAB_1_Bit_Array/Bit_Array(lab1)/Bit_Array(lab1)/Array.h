#pragma once
#include <string>
#include <iostream>
#include <cstdint>
#include <cstring>

class BitArray {
public:
    BitArray();
    ~BitArray();
    //������������ ������, �������� �������� ���������� ���.
    //������ sizeof(long) ��� ����� ��������������� � ������� ��������� value.
    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);
    //���������� �������� ���� ������� ��������.
    void swap(BitArray& b);
    BitArray& operator=(const BitArray& b);
    //�������� ������ �������. � ������ ����������, ����� �������� 
    //���������������� ��������� value.
    void resize(int num_bits, bool value = false);
    //������� ������.
    void clear();
    //��������� ����� ��� � ����� �������. � ������ ������������� 
    //���������� ����������������� ������.
    void push_back(bool bit);
    //������� �������� ��� ���������.
    //�������� ������ �� �������� ����������� �������.
    //����������� ������� �� �������� ��������� ������� ������ � ������.
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    //������� ����� � ����������� ������.
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;
    //������������� ��� � �������� n � �������� val.
    BitArray& set(int n, bool val = true);
    //��������� ������ �������.
    BitArray& set();
    //������������� ��� � �������� n � �������� false.
    BitArray& reset(int n);
    //��������� ������ �����.
    BitArray& reset();
    //true, ���� ������ �������� �������� ���.
    bool any() const;
    //true, ���� ��� ���� ������� �����.
    bool none() const;
    //������� ��������
    BitArray operator~() const;
    //������������ ���������� ��������� ���.
    int count() const;
    //���������� �������� ���� �� ������� i.
    bool operator[](int i) const;
    int size() const;
    bool empty() const;
    //���������� ��������� ������������� �������.
    std::string to_string() const;
private:
    bool* bits;
    int numBits;

};