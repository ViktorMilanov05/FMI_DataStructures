#include <iostream>
#include "VectorSet.h"

size_t VectorSet::calculateBucketsCount() const
{
    if (bucketsCount == 0)
        return 1;
    return bucketsCount * GROWTH_FACTOR;
}

void VectorSet::copyFrom(const VectorSet& other)
{
    bucketsCount = other.bucketsCount;
    buckets = myAlloc.allocate(bucketsCount);
    for (size_t i = 0; i < bucketsCount; i++)
    {
        buckets[i] = other.buckets[i];
    }
    cap = other.cap;
}

void VectorSet::moveFrom(VectorSet&& other)
{
    buckets = other.buckets;
    bucketsCount = other.bucketsCount;
    cap = other.cap;
    size = other.size;
    other.bucketsCount = other.size = other.cap = 0;
    other.buckets = nullptr;
}

void VectorSet::free()
{
    myAlloc.deallocate(buckets, bucketsCount);
    buckets = nullptr;
    bucketsCount = cap = 0;
}

size_t VectorSet::getBucketIndex(unsigned num) const
{
    return num / ELEMENTS_IN_BUCKET;
}

size_t VectorSet::getBitIndex(unsigned num) const
{
    return num % ELEMENTS_IN_BUCKET;
}

VectorSet::VectorSet(size_t count)
{
    bucketsCount = count / ELEMENTS_IN_BUCKET + 1;
    buckets = myAlloc.allocate(bucketsCount);
    cap = size = bucketsCount * ELEMENTS_IN_BUCKET;
    for (size_t i = 0; i < bucketsCount; i++)
    {
        buckets[i] = 0;
    }
}

VectorSet::VectorSet(const VectorSet& other)
{
    copyFrom(other);
}

VectorSet::VectorSet(VectorSet&& other) noexcept
{
    moveFrom(std::move(other));
}

VectorSet& VectorSet::operator=(const VectorSet& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

VectorSet& VectorSet::operator=(VectorSet&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

VectorSet::~VectorSet()
{
    free();
}

void VectorSet::push_back(bool value)
{
    if (size == cap) {
        reserve(calculateBucketsCount());
    }
    size_t bitIndex = getBitIndex(size);
    size_t bucketIndex = getBucketIndex(size);
    int mask = 1 << bitIndex;
    if (value) {
        buckets[bucketIndex] |= mask;
    }
    else {
        mask = ~(mask);
        buckets[bucketIndex] &= mask;
    }
    size++;
}

void VectorSet::pop_back()
{
    if (isEmpty())
        throw std::exception("Vector is empty");
    size--;
}

void VectorSet::pop_front()
{
    if (isEmpty())
        throw std::exception("Vector is empty");
    int mask = 1 << 7;
    for (size_t i = 0; i < bucketsCount - 1; i++)
    {
        int bit = mask & buckets[i + 1];
        buckets[i] >>= 1;
        if (bit) {
            buckets[i] |= bit;
        }
    }
    buckets[bucketsCount - 1] >>= 1;
    size--;
}

void VectorSet::insert(const c_iter& iter, bool value)
{
    if (size == cap) {
        reserve(calculateBucketsCount());
    }
    if (iter == c_end()) {
        push_back(value);
    }
    else {
        size_t getInd = iter.getBitInSet();
        bool tempVal = (*this)[getInd];
        for (size_t i = getInd; i < size; i++)
        {
            (*this)[i] = value;
            value = tempVal;
            tempVal = (*this)[i + 1];
        }
        (*this)[size++] = value;
    }
}

void VectorSet::remove(const c_iter& iter)
{
    if (isEmpty())
        throw std::exception("Vector is empty");
    if (iter == c_begin()) {
        pop_front();
    }
    else if (iter == c_end()) {
        pop_back();
    }
    else {
        size_t getInd = iter.getBitInSet();
        for (size_t i = getInd; i < size - 1; i++)
        {
            bool value = (*this)[i + 1];
            (*this)[i] = value;
        }
        size--;
    }

}

void VectorSet::reserve(size_t newBucketsCount)
{
    if (newBucketsCount <= bucketsCount)
        return;

    uint8_t* newBuckets = myAlloc.allocate(newBucketsCount);

    for (size_t i = 0; i < bucketsCount; i++)
    {
        newBuckets[i] = buckets[i];
    }
    myAlloc.deallocate(buckets, bucketsCount);
    buckets = newBuckets;
    bucketsCount = newBucketsCount;
    cap = bucketsCount * ELEMENTS_IN_BUCKET;
}

void VectorSet::shrink_to_fit()
{
    if ((cap - 8) <= size)
        return;

    bucketsCount = (size / ELEMENTS_IN_BUCKET) + 1;
    uint8_t* newBuckets = myAlloc.allocate(bucketsCount);

    for (size_t i = 0; i < bucketsCount; i++)
    {
        newBuckets[i] = buckets[i];
    }
    myAlloc.deallocate(buckets, bucketsCount);

    cap = bucketsCount * 8;
    buckets = newBuckets;
}

iterator VectorSet::begin()
{
    return iterator(buckets, 0, 0);
}

iterator VectorSet::end()
{
    return iterator(buckets + size, 0, size);
}

const_iterator VectorSet::c_begin() const
{
    return const_iterator(buckets, 0, 0);
}

const_iterator VectorSet::c_end() const
{
    return const_iterator(buckets + size, 0, size);
}

reverse_iterator VectorSet::rbegin()
{
    return size > 0 ? reverse_iterator(buckets + size - 1, 7, size - 1) : reverse_iterator();
}

reverse_iterator VectorSet::rend()
{
    return size > 0 ? reverse_iterator(buckets - 1, 7, -1) : reverse_iterator();
}

bool VectorSet::operator[](int ind) const
{
    size_t bitIndex = getBitIndex(ind);
    size_t bucketIndex = getBucketIndex(ind);
    int mask = 1 << bitIndex;
    return mask & buckets[bucketIndex];
}

BitReference VectorSet::operator[](int ind)
{
    size_t bitIndex = getBitIndex(ind);
    size_t bucketIndex = getBucketIndex(ind);
    return BitReference(buckets[bucketIndex], bitIndex);
}

size_t VectorSet::getSize() const
{
    return size;
}

bool VectorSet::isEmpty() const
{
    return size == 0;
}
