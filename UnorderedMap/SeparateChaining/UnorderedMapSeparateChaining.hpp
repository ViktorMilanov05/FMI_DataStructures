#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>

template <typename Key, typename Value, typename Hash=std::hash<Key>>
class UnorderedMap {
public:
	using Element = std::pair<Key, Value>;

	class ConstIterator {
	public:
		ConstIterator& operator++();
		ConstIterator operator++(int);
		const Element& operator*() const;
		const Element* operator->() const;
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	private:
		typename std::list<Element>::const_iterator curr;
		ConstIterator(typename std::list<Element>::const_iterator curr) : curr(curr) {};
		friend class UnorderedMap;
	};

	UnorderedMap();
	void add(const Key& key, const Value& value);
	void remove(const Key& key);
	ConstIterator find(const Key& key) const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	double getLoadFactor() const;
private:
	std::list<Element> data;
	std::vector<std::forward_list<typename std::list<Element>::iterator>> hashTable;
	Hash getHash;
	const double maxLoadFactor = 0.75;
	void resize();
	size_t getHashCode(const Key& key) const;
};

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator& UnorderedMap<Key, Value, Hash>::ConstIterator::operator++()
{
	++curr;
	return *this;
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::ConstIterator::operator++(int)
{
	ConstIterator temp(*this);
	++(*this);
	return temp;
}

template<typename Key, typename Value, typename Hash>
const UnorderedMap<Key, Value, Hash>::Element& UnorderedMap<Key, Value, Hash>::ConstIterator::operator*() const
{
	return (*curr)
}

template<typename Key, typename Value, typename Hash>
const UnorderedMap<Key, Value, Hash>::Element* UnorderedMap<Key, Value, Hash>::ConstIterator::operator->() const
{
	return &(*curr);
}

template<typename Key, typename Value, typename Hash>
bool UnorderedMap<Key, Value, Hash>::ConstIterator::operator==(const ConstIterator& other) const
{
	return this->curr == other.curr;
}

template<typename Key, typename Value, typename Hash>
bool UnorderedMap<Key, Value, Hash>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return !((*this) == other);
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::UnorderedMap()
{
	resize(8);
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::add(const Key& key, const Value& value)
{
	if (getLoadFactor() >= maxLoadFactor) {
		resize();
	}
	size_t ind = getHashCode(key);
	auto& bucket = hashTable[ind];
	auto it = std::find_if(bucket.begin(), bucket.end(), [&key](const auto& iter) {return iter->first == key});
	if (it != bucket.end())
		return;
	data.emplace_back(key, value);
	bucket.push_front(--data.end());
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::remove(const Key& key)
{
	size_t ind = getHashCode(key);
	auto& bucket = hashTable[ind];
	std::remove_if(bucket.begin(), bucket.end(), [this,&key](const auto& iter) {
		if (iter->first == key) {
			data.erase(iter);
			return true;
		}
		else {
			false;
		}
		});
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::find(const Key& key) const
{
	size_t ind = getHashCode(key);
	auto& bucket = hashTable[ind];
	auto it = std::find_if(bucket.begin(), bucket.end(), [&key](const auto& iter) {return iter->first == key});
	if (it == bucket.end())
		return cend();
	return ConstIterator(*it);
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::cbegin() const
{
	return ConstIterator(data.cbegin());
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::cend() const
{
	return ConstIterator(data.cend());
}

template<typename Key, typename Value, typename Hash>
double UnorderedMap<Key, Value, Hash>::getLoadFactor() const
{
	return static_cast<double>(data.size()) /hashTable.size());
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::resize()
{
	size_t newSize = hashTable.size() * 2;
	std::vector<std::forward_list<typename std::list<Element>::iterator>> newHashTable(newSize);
	for (auto it = data.begin(); it != data.end(); it++)
	{
		size_t ind = getHash(it->first) % newSize;
		newHashTable[ind].push_front(it);
	}
	hashTable = std::move(newHashTable);
}

template<typename Key, typename Value, typename Hash>
size_t UnorderedMap<Key, Value, Hash>::getHashCode(const Key& key) const
{
	return getHash(key) % hashTable.size();
}
