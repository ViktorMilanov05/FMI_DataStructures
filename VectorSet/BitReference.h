#include <iostream>

//използваме го заради неконстантния оператор [] за да можем да правим промяна на битовете и за оператор * при итераторите
class BitReference {
    uint8_t& byte;
    uint8_t mask;

public:
    BitReference(uint8_t& byte, size_t bitIndex)
        : byte(byte), mask(1 << bitIndex) {}

    operator bool() const;

    BitReference& operator=(bool value);
};