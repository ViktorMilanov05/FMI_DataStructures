#include <iostream>
#include "Iterators.h"

const size_t GROWTH_FACTOR = 2;

class VectorSet {
	uint8_t* buckets = nullptr;
	size_t bucketsCount = 0;
	size_t cap = 0;
	size_t size = 0;
	const unsigned ELEMENTS_IN_BUCKET = sizeof(uint8_t) * 8;
	std::allocator<uint8_t> myAlloc;

	size_t calculateBucketsCount() const;
	void copyFrom(const VectorSet& other);
	void moveFrom(VectorSet&& other);
	void free();

	size_t getBucketIndex(unsigned num) const;
	size_t getBitIndex(unsigned num) const;

public:
	using iter = iterator;
	using c_iter = const_iterator;
	using r_iter = reverse_iterator;

	VectorSet() = default;
	explicit VectorSet(size_t count);
	VectorSet(const VectorSet& other);
	VectorSet(VectorSet&& other) noexcept;
	VectorSet& operator=(const VectorSet& other);
	VectorSet& operator=(VectorSet && other) noexcept;
	~VectorSet();

	void push_back(bool value);
	void pop_back();
	void pop_front();
	void insert(const c_iter& iter, bool value);
	void remove(const c_iter& iter);

	void reserve(size_t newBucketsCount);
	void shrink_to_fit();

	iterator begin();
	iterator end();

	const_iterator c_begin() const;
	const_iterator c_end() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

	
	bool operator[](int ind) const;
	BitReference operator[](int ind);
	size_t getSize() const;
	bool isEmpty() const;
};
