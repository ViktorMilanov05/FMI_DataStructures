#include "Iterators.h"

iterator& iterator::operator++()
{
    if (bitPosition != 7) {
        bitPosition++;
        bitInSet++;
        return *this;
    }
    bucketPtr++;
    bitInSet++;
    bitPosition = 0;
    return *this;
}

iterator iterator::operator++(int)
{
    iterator it = *this;
    ++(*this);
    return it;
}

iterator& iterator::operator--()
{
    if (bitPosition != 0) {
        bitPosition--;
        bitInSet--;
        return *this;
    }
    bucketPtr--;
    bitInSet--;
    bitPosition = 7;
    return *this;
}

iterator& iterator::operator--(int)
{
    iterator it = *this;
    --(*this);
    return it;
}

uint8_t* iterator::getBucketPtr()
{
    return bucketPtr;
}

size_t iterator::getBitInSet() const
{
    return bitInSet;
}

BitReference iterator::operator*()
{
    return BitReference((*bucketPtr), bitPosition);
}

bool iterator::operator==(const iterator& it) const
{
    return (bucketPtr == it.bucketPtr) && (bitPosition == it.bitPosition);
}

bool iterator::operator!=(const iterator& it) const
{
    return !(*this == it);
}

const_iterator& const_iterator::operator++()
{
    if (bitPosition != 7) {
        bitPosition++;
        bitInSet++;
        return *this;
    }
    bucketPtr++;
    bitInSet++;
    bitPosition = 0;
    return *this;
}

const_iterator const_iterator::operator++(int)
{
    const_iterator it = *this;
    ++(*this);
    return it;
}

const_iterator& const_iterator::operator--()
{
    if (bitPosition != 0) {
        bitPosition--;
        bitInSet--;
        return *this;
    }
    bucketPtr--;
    bitInSet--;
    bitPosition = 7;
    return *this;
}

const_iterator& const_iterator::operator--(int)
{
    const_iterator it = *this;
    --(*this);
    return it;
}

size_t const_iterator::getBitInSet() const
{
    return bitInSet;
}

bool const_iterator::operator*()
{
    return (*bucketPtr & (1 << bitPosition)) != 0;
}

bool const_iterator::operator==(const const_iterator& it) const
{
    return (bucketPtr == it.bucketPtr) && (bitPosition == it.bitPosition);
}

bool const_iterator::operator!=(const const_iterator& it) const
{
    return !(*this == it);
}

reverse_iterator& reverse_iterator::operator++()
{
    if (bitPosition != 0) {
        bitPosition--;
        bitInSet--;
        return *this;
    }
    bucketPtr--;
    bitInSet--;
    bitPosition = 7;
    return *this;
}

reverse_iterator reverse_iterator::operator++(int)
{
    reverse_iterator it = *this;
    --(*this);
    return it;
}

reverse_iterator& reverse_iterator::operator--()
{
    if (bitPosition != 7) {
        bitPosition++;
        bitInSet++;
        return *this;
    }
    bucketPtr++;
    bitInSet++;
    bitPosition = 0;
    return *this;
}

reverse_iterator reverse_iterator::operator--(int)
{
    reverse_iterator it = *this;
    ++(*this);
    return it;
}

size_t reverse_iterator::getBitInSet() const
{
    return bitInSet;
}

BitReference reverse_iterator::operator*()
{
    return BitReference((*bucketPtr), bitPosition);
}

bool reverse_iterator::operator==(const reverse_iterator& it) const
{
    return (bucketPtr == it.bucketPtr) && (bitPosition == it.bitPosition);
}

bool reverse_iterator::operator!=(const reverse_iterator& it) const
{
    return !(*this == it);
}
