#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>

namespace tt
{
    template <typename T> class vector
    {
        public:
            static size_t initCapacity;
            static size_t capToIncrease;

            // Constructor and destructor
            vector();
            vector(size_t amount, const T& value);
            vector(T* aBegin, T* aEnd);
            vector(const vector<T>& vecToCopy) = delete;
            ~vector();

            // Assignment
            vector<T>& operator=(const vector<T>& vecToCopy);
            void assign(T* aBegin, T* aEnd);

            // Pointers
            T* begin();
            T* end();

            // Capacity
            size_t size() const;
            size_t capacity() const;
            void shrink_to_fit();

            // Comparison
            bool operator==(const vector<T>& vecParam) const;
            bool operator!=(const vector<T>& vecParam) const;
            bool operator<=(const vector<T>& vecParam) const;
            bool operator>=(const vector<T>& vecParam) const;
            bool operator<(const vector<T>& vecParam) const;
            bool operator>(const vector<T>& vecParam) const;

            // Access
            T& operator[](size_t pos);
            T& at(size_t pos);
            T& front();
            T& back();

            // Modifier
            void push_back(const T& value);
            void pop_back();
            void insert(size_t pos, const T& value);
            void erase(size_t pos);
            void eraseSelect(size_t aSize, const T pos[]);
            void reserve(size_t newCap);
            void clear();
            void resize(size_t newSize);
            void resize(size_t newSize, const T& value);
            void swap(vector<T>& vecToSwap);

        private:
            T* ptr = nullptr;
            size_t _capacity;
            size_t _size;

            void reallocate(size_t newCap);
    };

    template <typename T> size_t vector<T>::initCapacity = 50;
    template <typename T> size_t vector<T>::capToIncrease = 50;

    // Constructor
    template <typename T> vector<T>::vector()
    {
        _capacity = initCapacity;
        ptr = new T[_capacity];
        _size = 0;
    }

    template <typename T> vector<T>::vector(size_t amount, const T& value)
    {
        _size = amount;
        _capacity = initCapacity + _size;
        ptr = new T[_capacity];
        std::fill(ptr, ptr + _size, value);
    }

    template <typename T> vector<T>::vector(T* aBegin, T* aEnd)
    {
        assign(aBegin, aEnd);
    }

    // Destructor
    template <typename T> vector<T>::~vector()
    {
        delete [] ptr;
    }

    // Assignment
    template <typename T> vector<T>& vector<T>::operator=(const vector<T>& vecToCopy)
    {
        delete [] ptr;

        _capacity = vecToCopy.capacity();
        _size = vecToCopy.size();
        ptr = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
            ptr[i] = vecToCopy.ptr[i];

        return *this;
    }

    template <typename T> void vector<T>::assign(T* aBegin, T* aEnd)
    {
        _size = aEnd - aBegin;
        if (_size <= 0) throw std::invalid_argument("Assigned range is invalid");
        _capacity = _size + capToIncrease;
        delete [] ptr;
        ptr = new T[_capacity];

        for (size_t i = 0; i < _size; ++i)
            ptr[i] = aBegin[i];
    }

    // Pointer
    template <typename T> inline T* vector<T>::begin()
    {
        return ptr;
    }

    template <typename T> inline T* vector<T>::end()
    {
        return ptr + _size;
    }

    // Capacity
    template <typename T> inline size_t vector<T>::size() const
    {
        return _size;
    }

    template <typename T> inline size_t vector<T>::capacity() const
    {
        return _capacity;
    }

    // Comparison
    template <typename T> bool vector<T>::operator==(const vector<T>& vecParam) const
    {
        if (_size != vecParam._size) return false;

        for (size_t i = 0; i < _size; ++i)
            if (ptr[i] != vecParam.ptr[i]) return false;

        return true;
    }

    template <typename T> inline bool vector<T>::operator!=(const vector<T>& vecParam) const
    {
        return !(this == vecParam);
    }

    template <typename T> bool vector<T>::operator<=(const vector<T>& vecParam) const
    {
        size_t lim = std::min(_size, vecParam._size);
        for (size_t i = 0; i < lim; ++i)
            if (ptr[i] > vecParam.ptr[i]) return false;
        return _size <= vecParam._size;
    }

    template <typename T> bool vector<T>::operator>=(const vector<T>& vecParam) const
    {
        size_t lim = std::min(_size, vecParam._size);
        for (size_t i = 0; i < lim; ++i)
            if (ptr[i] < vecParam.ptr[i]) return false;
        return _size >= vecParam._size;
    }

    template <typename T> bool vector<T>::operator<(const vector<T>& vecParam) const
    {
        size_t lim = std::min(_size, vecParam._size);
        for (size_t i = 0; i < lim; ++i)
            if (ptr[i] > vecParam.ptr[i]) return false;
        return _size < vecParam._size;
    }

    template <typename T> bool vector<T>::operator>(const vector<T>& vecParam) const
    {
        size_t lim = std::min(_size, vecParam._size);
        for (size_t i = 0; i < lim; ++i)
            if (ptr[i] < vecParam.ptr[i]) return false;
        return _size > vecParam._size;
    }

    template <typename T> void vector<T>::shrink_to_fit()
    {
        T* tmp = new T[_size];

        for (size_t i = 0; i < _size; ++i)
            tmp[i] = ptr[i];

        delete [] ptr;
        ptr = tmp;
        _capacity = _size;
    }

    // Access
    template <typename T> inline T& vector<T>::operator[](size_t pos)
    {
        return ptr[pos];
    }

    template <typename T> inline T& vector<T>::at(size_t pos)
    {
        if (pos >= _size || pos < 0) throw std::out_of_range("Out of range");
        return ptr[pos];
    }

    template <typename T> inline T& vector<T>::front()
    {
        return ptr[0];
    }

    template <typename T> inline T& vector<T>::back()
    {
        return ptr[_size - 1];
    }

    // Modifier
    template <typename T> inline void vector<T>::push_back(const T& value)
    {
        if (_size >= _capacity) reserve(_capacity + capToIncrease);
        ptr[_size] = value;
        ++_size;
    }

    template <typename T> inline void vector<T>::pop_back()
    {
        --_size;
    }

    template <typename T> void vector<T>::insert(size_t pos, const T& value)
    {
        if (pos > _size || pos < 0) throw std::out_of_range("Out of range");

        if (_size >= _capacity) reserve(_size + capToIncrease);

        for (size_t i = _size; i > pos; --i)
            ptr[i] = ptr[i - 1];
        ptr[pos] = value;
        ++_size;
    }

    template <typename T> void vector<T>::erase(size_t pos)
    {
        if (pos >= _size || pos < 0) throw std::out_of_range("Out of range");

        for (size_t i = pos; i < _size; ++i)
            ptr[i] = ptr[i + 1];
        --_size;
    }

    template <typename T> void vector<T>::eraseSelect(size_t aSize, const T pos[])
    {
        for (size_t i = 0; i < aSize; ++i)
            if (pos[i] < 0 || pos[i] > _size) throw std::out_of_range("Out of range");

        for (size_t i = pos[0], j = 0; i < _size; ++i)
            if (i == pos[j]) ++j;
            else ptr[i] = ptr[i - j];

        _size -= aSize;
    }

    template <typename T> inline void vector<T>::reserve(size_t newCap)
    {
        if (newCap < _capacity) throw std::invalid_argument("New capacity is smaller than old capacity");
        reallocate(newCap);
    }

    template <typename T> inline void vector<T>::clear()
    {
        _size = 0;
    }

    template <typename T> inline void vector<T>::resize(size_t newSize)
    {
        _size = newSize;
        if (newSize > _capacity) reserve(newSize + capToIncrease);
    }

    template <typename T> void vector<T>::resize(size_t newSize, const T& value)
    {
        if (newSize > _capacity) reserve(newSize + capToIncrease);
        for (size_t i = _size; i < newSize; ++i)
            ptr[i] = value;
        _size = newSize;
    }

    template <typename T> inline void vector<T>::swap(vector<T>& vecToSwap)
    {
        std::swap(_size, vecToSwap._size);
        std::swap(_capacity, vecToSwap._capacity);
        std::swap(ptr, vecToSwap.ptr);
    }

    template <typename T> void vector<T>::reallocate(size_t newCap)
    {
        T* tmp = new T[newCap];
        for (size_t i = 0; i < _size; ++i)
            tmp[i] = ptr[i];
        delete [] ptr;
        ptr = tmp;
        _capacity = newCap;
    }

    // Clear for input stream (cin, ifstream,...)
    template <typename T> bool cinIg(std::istream& stream, T& val, const bool clr = true)
    {
        stream >> val;
        bool res = !stream.fail();
        if (clr) {
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return res;
    }

    // Return all cap version of input string, support YYYY-MM-DD and MM/DD/YYY
    std::string capitalize(const std::string& str);

    // Create folder
    int makeFolder(const std::string& s);

    // Create directory from string. String must be in format: "./subdir1/subdir2/.../"
    // Return true if the last folder in the directory is created,
    // false otherwise (folder already existed, no permission,...)
    bool makeDir(const std::string& dir);

    void clearConsole();
}

#endif // UTILITY_H_INCLUDED
