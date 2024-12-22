#include <iostream>
#include "BitReference.h"

//използваме го заради неконстантния оператор [] за да можем да правим промяна на битовете и за оператор * при итераторите

class iterator
{
    uint8_t* bucketPtr;
    size_t bitPosition;
    int bitInSet;
public:
    iterator() : bucketPtr(nullptr), bitPosition(0) , bitInSet(0){};
    iterator(uint8_t* bucketPtr, size_t bitPosition, size_t bitInSet) : bucketPtr{ bucketPtr }, bitPosition {bitPosition}, bitInSet(bitInSet) {};

    iterator& operator++();

    iterator operator++(int);

    iterator& operator--();

    iterator& operator--(int);

    uint8_t* getBucketPtr();

    size_t getBitInSet() const;

    BitReference operator*();

    bool operator==(const iterator& it) const;

    bool operator!=(const iterator& it) const;
};


class const_iterator
{
    uint8_t* bucketPtr;
    size_t bitPosition;
    int bitInSet;
public:
    const_iterator() : bucketPtr(nullptr), bitPosition(0), bitInSet(0) {};
    const_iterator(uint8_t* bucketPtr, size_t bitPosition, size_t bitInSet) : bucketPtr{ bucketPtr }, bitPosition{ bitPosition }, bitInSet(bitInSet) {};

    const_iterator& operator++();

    const_iterator operator++(int);

    const_iterator& operator--();

    const_iterator& operator--(int);

    size_t getBitInSet() const;

    bool operator*();

    bool operator==(const const_iterator& it) const;

    bool operator!=(const const_iterator& it) const;
};

class reverse_iterator
{
    uint8_t* bucketPtr;
    size_t bitPosition;
    int bitInSet;
public:
    reverse_iterator() : bucketPtr(nullptr), bitPosition(0), bitInSet(0) {};
    reverse_iterator(uint8_t* bucketPtr, size_t bitPosition, size_t bitInSet) : bucketPtr{ bucketPtr }, bitPosition{ bitPosition }, bitInSet(bitInSet) {};

    reverse_iterator& operator++();

    reverse_iterator operator++(int);

    reverse_iterator& operator--();

    reverse_iterator operator--(int);

    size_t getBitInSet() const;

    BitReference operator*();

    bool operator==(const reverse_iterator& it) const;

    bool operator!=(const reverse_iterator& it) const;
};