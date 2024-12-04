#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>

// TODO: decomposition

template <typename T>
class DynamicArray {
public:
    DynamicArray() : chunk_size_(100), current_chunk_idx_(0), current_element_idx(0) {
        grow();
    }

    void push_back(const T& x) {
        if (current_element_idx == chunk_size_ - 1) {
            grow();
        }
        chunks_[current_chunk_idx_][current_element_idx] = x;
        ++current_element_idx;
    }

    T& operator[](size_t i) {
        auto [chunk_idx, element_idx] = get_indices(i);
        return chunks_[chunk_idx][element_idx];
    }

    T& at(size_t i) {
        auto [chunk_idx, element_idx] = get_indices(i);
        validate_idx(chunk_idx, element_idx);

        return chunks_[chunk_idx][element_idx];
    }

    class iterator {
    public:
        iterator() : chunk_idx_(0), element_idx_(0) {}
        
        iterator (const iterator& it) {
            chunk_idx_ = it.chunk_idx_;
            element_idx_ = it.element_idx_;
        }
        
        iterator (size_t i) {
            iterator temp = *this;
            auto [c, e] = get_indices(i);
            
            temp.chunk_idx_ = c;
            temp.element_idx_ = e;
        }

        T& operator* () {
            return chunks_[chunk_idx_][element_idx_];
        }

        bool operator!= (const iterator& other) { 
            return (chunk_idx_ != other.chunk_idx_) || (element_idx_ != other.element_idx_); 
        }
        
        iterator operator++() { 
            if (element_idx_ == chunk_size_-1) {
                chunk_idx_++;
                element_idx_ = 0;
                return *this;
            }

            element_idx_++;
            return *this;
        }
    
    private:
        size_t chunk_idx_;
        size_t element_idx_;
    };

private:
    std::vector<std::unique_ptr<T[]>> chunks_;
    size_t current_chunk_idx_;
    size_t current_element_idx;
    size_t chunk_size_;

    void validate_idx(size_t chunk_idx, size_t element_idx) {
        // check for invalid inputs.
        if (chunk_idx >= chunks_.size() || chunk_idx < 0 || element_idx >= chunk_size_ || element_idx < 0) { 
            throw std::out_of_range("");
        }

        // although we allocated the block, user shouldn't be able to access uninitialized elements.
        if (chunk_idx == chunks_.size()-1 && element_idx >= current_element_idx) {
            throw std::out_of_range("");
        } 
    }

    void grow() {
        chunks_.emplace_back(std::make_unique<T[]>(chunk_size_));
    }

    std::pair<size_t, size_t> get_indices(size_t i) {
        size_t c = i / chunk_size_;
        size_t e = i % chunk_size_;
        
        if (i == chunks_.size() * chunk_size_) {
            c = chunks_.size() - 1;
            e = chunk_size_ - 1;
        }
        return {c, e};
    }
};

int main() {
    DynamicArray<int> a;
    a.push_back(100);
    a.push_back(102);
    a.push_back(200);
    a.push_back(300);
    std::cout << a.at(4) << std::endl;
    return 0;
}