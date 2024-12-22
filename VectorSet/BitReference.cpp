#include "BitReference.h"

BitReference::operator bool() const {
    return (byte & mask) != 0;
}

BitReference& BitReference::operator=(bool value) {
    if (value)
        byte |= mask;
    else
        byte &= ~mask;
    return *this;
}
