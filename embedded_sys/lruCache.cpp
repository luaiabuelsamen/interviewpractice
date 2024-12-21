/*
Basically there is a heap that contains data at memory addresses
if I get something from that heap, it will overrite the oldest value in my cache

it will put it in my cache which is a hashmap mapping addresses to data
and when I get from it, I have to update it's most recently used timestamp
*/
#include <unordered_map>
#include <ctime>

template <typename T>

typedef struct{
    T data;
    uint64_t timeStamp;
} lruCache;

typedef enum {
    SUCCESS = 0,
    FAIL = 1
} eReturnState;

class LRUCache{
    public:
        eReturnState put(uint64_t pData){
            cacheMap[pData] = {.data = *pData, .timeStamp = getTimeStamp()};
        }

        eReturnState get(){

        }
    private:
        std::unordered_map <uint64_t, lruCache> cacheMap;
        std::vector<
        uint64_t getTimeStamp(){
            std::time_t t = std::time(0);
            return t;
        }
};


#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        // Move the accessed node to the tail
        lru_list.splice(lru_list.end(), lru_list, cache[key]);
        return cache[key]->second;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update the value and move the node to the tail
            cache[key]->second = value;
            lru_list.splice(lru_list.end(), lru_list, cache[key]);
            return;
        }

        if (lru_list.size() == capacity) {
            // Remove the least recently used item
            cache.erase(lru_list.front().first);
            lru_list.pop_front();
        }

        // Insert the new key-value pair at the tail
        lru_list.push_back({key, value});
        cache[key] = --lru_list.end();
    }

private:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    list<pair<int, int>> lru_list;  // Doubly linked list of (key, value) pairs
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;    // returns 1
    cache.put(3, 3);                // evicts key 2
    cout << cache.get(2) << endl;    // returns -1 (not found)
    cache.put(4, 4);                // evicts key 1
    cout << cache.get(1) << endl;    // returns -1 (not found)
    cout << cache.get(3) << endl;    // returns 3
    cout << cache.get(4) << endl;    // returns 4

    return 0;
}



// Thus, your challenge is to write a new Geo Distributed LRU (Least Recently Used) cache with time expiration. 
// This library will be used extensively by many of our services so it needs to meet the following criteria: 

//   

//     1 - Simplicity. Integration needs to be dead simple. 

//     2 - Resilient to network failures or crashes. 

//     3 - Near real time replication of data across Geolocation. Writes need to be in real time. 

//     4 - Data consistency across regions 

//     5 - Locality of reference, data should almost always be available from the closest region 

//     6 - Flexible Schema 

//     7 - Cache can expire  