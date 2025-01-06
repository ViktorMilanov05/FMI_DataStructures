#include <vector>
#include <optional>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class UnorderedMap {
public:
	using Element = std::pair<Key, Value>;

	UnorderedMap(size_t tableSize = 10, size_t k = 3);

	class ConstIterator {
	public:
		ConstIterator& operator++();
		ConstIterator operator++(int);
		const Element& operator*() const;
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	private:
		ConstIterator(int ind, const UnorderedMap<Key, Value, Hash>& context)
		int ind;
		const UnorderedMap<Key, Value, Hash>& context;
		friend class UnorderedMap<Key, Value, Hash>;
	};

	void add(const Key& key, const Value& value);
	void remove(const Key& key);
	ConstIterator find(const Key& key) const;
	size_t getSize() const;
	ConstIterator cend() const;
	ConstIterator cbegin() const;
private:
	std::vector<std::optional<Element>> data;
	const Element tombstone;
	size_t size;
	size_t k;
	Hash getHash;
	const double maxLoadFactor = 0.8;
	void resize(size_t newSize);

	static bool containsElement(const std::vector<std::optional<Element>>& data, size_t ind) {
		return data[ind] != std::nulopt && data[ind] != tombstone;
	}
};

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::UnorderedMap(size_t tableSize, size_t k) : k(k), size(0), tombstone(std::make_pair(Key(), Value()))
{
	data.resize(tableSize);
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator& UnorderedMap<Key, Value, Hash>::ConstIterator::operator++()
{
	while(++ind < context.data.size() && !context.containsElement(context.data, ind)){}
	if (ind == context.data.size()) {
		ind = -1;
	}
	return *this;
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::ConstIterator::operator++(int)
{
	int oldInd = ind;
	while (++ind < context.data.size() && !context.containsElement(context.data, ind)) {}
	if (ind == context.data.size()) {
		ind = -1;
	}
	return ConstIterator(oldInd, context);
}

template<typename Key, typename Value, typename Hash>
const UnorderedMap<Key, Value, Hash>::Element& UnorderedMap<Key, Value, Hash>::ConstIterator::operator*() const
{
	return (*context.data[ind]);
}

template<typename Key, typename Value, typename Hash>
bool UnorderedMap<Key, Value, Hash>::ConstIterator::operator==(const ConstIterator& other) const
{
	return ind == other.ind;
}

template<typename Key, typename Value, typename Hash>
bool UnorderedMap<Key, Value, Hash>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return ind != other.ind;
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::add(const Key& key, const Value& value)
{
	double loadFactor = (double)size / data.size();
	if (loadFactor > maxLoadFactor) {
		resize(data.size() * 2);
	}
	size_t ind = getHash(key) % data.size();
	while (containsElement(data, ind)) {
		if (data[ind]->first == key) {
			throw std::exception("Already Exist");
		}
		(ind += k) %= data.size();
	}
	data[ind] = { key, value };
	size++;
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::remove(const Key& key)
{
	size_t ind = getHash(key) % data.size();
	while (data[ind] != std::nullopt) {
		if (data[ind] != tombstone && data[ind]->first == key) {
			data[ind] = tombstone;
			size--;
			break;
		}
		(ind += k) %= data.size();
	}
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::find(const Key& key) const
{
	size_t ind = getHash(key) % data.size();
	while (data[ind] != std::nullopt) {
		if (data[ind] != tombstone && data[ind]->first == key) {
			return ConstIterator(ind, *this);
		}
		(ind += k) %= data.size();
	}
	return cend();
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::cend() const
{
	return ConstIterator(-1, *this);
}

template<typename Key, typename Value, typename Hash>
UnorderedMap<Key, Value, Hash>::ConstIterator UnorderedMap<Key, Value, Hash>::cbegin() const
{
	if (size == 0) {
		return cend();
	}
	for (size_t i = 0;; i++)
	{
		if (containsElement(data, i)) {
			return ConstIterator(i, *this)
		}
	}
}

template<typename Key, typename Value, typename Hash>
size_t UnorderedMap<Key, Value, Hash>::getSize() const
{
	return size;
}

template<typename Key, typename Value, typename Hash>
void UnorderedMap<Key, Value, Hash>::resize(size_t newSize)
{
	std::vector<std::optional<Element>> oldData(newSize);
	oldData.swap(data);
	size = 0;
	for (size_t i = 0; i < oldData.size(); i++)
	{
		if (containsElement(oldData, i)) {
			add(oldData[i]->first, oldData[i]->second);
		}
	}
}
