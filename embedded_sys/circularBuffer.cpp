#include <mutex>
#include <optional>
#include <vector>
#include <stdexcept>

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t capacity)
        : buffer_(capacity)
        , capacity_(capacity)
        , size_(0)
        , head_(0)
        , tail_(0) {
        if (capacity == 0) throw std::invalid_argument("Buffer capacity must be positive");
    }

    // Push element to the buffer. Returns false if buffer is full
    bool push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_full()) return false;

        buffer_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
        size_++;
        return true;
    }

    // Pop element from the buffer. Returns nullopt if buffer is empty
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_empty()) return std::nullopt;

        T item = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        size_--;
        return item;
    }

    // Peek at the front element without removing it
    std::optional<T> peek() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_empty()) return std::nullopt;
        return buffer_[head_];
    }

    bool is_empty() const { return size_ == 0; }
    bool is_full() const { return size_ == capacity_; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

private:
    mutable std::mutex mutex_;
    std::vector<T> buffer_;
    const size_t capacity_;
    size_t size_;
    size_t head_;    // Read position
    size_t tail_;    // Write position
};