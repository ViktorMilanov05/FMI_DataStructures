#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <unordered_map> 
#include <optional> //we need c++ 17

template <typename Key, typename Value>
class LRUC {
	using Cache = std::list<std::pair<Key, Value>>;
	using CacheIterator = typename Cache::iterator;
	using CacheMap = std::unordered_map<Key, CacheIterator>;

	Cache cache;
	CacheMap cacheMap;
	size_t cap;

	void markAsMostRecently(typename CacheMap::iterator mapIt) {
		CacheIterator cacheIt = mapIt->second;
		cache.splice(cache.end(), cache, cacheIt);
	}

	void handleSize() {
		if (cache.size() > cap) {
			Key toRemove = cache.front().first;
			cacheMap.erase(toRemove);
			cache.pop_front();
		}
	}
public:
	LCUR(size_t cap) : cap(cap) {};

	bool add(const Key& key, const Value& value) {
		auto [mapIt, added] = cacheMap.insert({ key, cache.end() });
		if (!added) {
			mapIt->second->second = value;
			markAsMostRecently(mapIt);
			return true;
		}
		cache.push_back({key, value});
		auto end = cache.end();
		--end;
		mapIt->second = end;
		handleSize();
		return true;
	}

	std::optional<Value> findInCache(const Key& key) {
		auto mapIt = cacheMap.find(key);
		if (mapIt == cacheMap.end()) {
			return std::nullopt;
		}
		markAsMostRecently(mapIt);
		return mapIt->second->second;
	}


};