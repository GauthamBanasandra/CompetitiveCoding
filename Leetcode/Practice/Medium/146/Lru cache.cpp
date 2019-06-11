#include <list>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(const int capacity)
      : capacity_(static_cast<std::size_t>(capacity)) {}

  int get(int key);
  void put(int key, int value);

private:
  const std::size_t capacity_;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> keys_;
  std::list<std::pair<int, int>> storage_;
};

int LRUCache::get(const int key) {
  const auto find_it = keys_.find(key);
  if (find_it == keys_.end()) {
    return -1;
  }

  storage_.emplace_front(*find_it->second);
  storage_.erase(find_it->second);
  find_it->second = storage_.begin();
  return find_it->second->second;
}

void LRUCache::put(int key, int value) {
  const auto value_exists = get(key);
  if (value_exists != -1) {
    storage_.front().second = value;
    return;
  }

  if (storage_.size() >= capacity_) {
    keys_.erase(storage_.back().first);
    storage_.pop_back();
  }

  storage_.emplace_front(key, value);
  keys_[key] = storage_.begin();
}

int main(int argc, char *argv[]) { return 0; }
