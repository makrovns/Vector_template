#pragma once

#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iostream>

namespace mvec {

    template<typename _T>
    class _Vector_iterator
    {
    public:

        using iterator_type = _T;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = iterator_type;
        using difference_type = std::ptrdiff_t;
        using pointer = iterator_type*;
        using reference = iterator_type&;

        _Vector_iterator(pointer _Ptr) : _Ptr(_Ptr) {}

        _Vector_iterator(const _Vector_iterator& it) : _Ptr(it._Ptr) {}

        reference operator*() const noexcept { return *_Ptr; }

        pointer operator->() const noexcept { return _Ptr; }

        reference operator[](const difference_type _dif) const noexcept { return *(_Ptr + _dif); }

        bool operator==(const _Vector_iterator& other_it) const noexcept { return _Ptr == other_it._Ptr; }

        bool operator!=(const _Vector_iterator& other_it) const noexcept { return !(*this == other_it); }

        bool operator<(const _Vector_iterator& other_it) const noexcept { return _Ptr < other_it._Ptr; }

        bool operator>(const _Vector_iterator& other_it) const noexcept { return other_it < *this; }

        bool operator<=(const _Vector_iterator& other_it) const noexcept { return !(other_it < *this); }

        bool operator>=(const _Vector_iterator& other_it) const noexcept { return !(*this < other_it); }

        _Vector_iterator& operator++() noexcept
        {
            ++_Ptr;
            return *this;
        }

        _Vector_iterator operator++(int) noexcept
        {
            _Vector_iterator tmp = *this;
            ++* this;
            return tmp;
        }

        _Vector_iterator& operator--() noexcept
        {
            --_Ptr;
            return *this;
        }

        _Vector_iterator operator--(int) noexcept
        {
            _Vector_iterator tmp = *this;
            --* this;
            return tmp;
        }

        _Vector_iterator& operator+=(const difference_type _dif) noexcept
        {
            _Ptr += _dif;
            return *this;
        }

        _Vector_iterator operator+(const difference_type _dif) const noexcept
        {
            _Vector_iterator tmp = *this;

            return tmp += _dif;
        }

        _Vector_iterator& operator-=(const difference_type _dif) noexcept
        {
            _Ptr += -_dif;
            return *this;
        }

        _Vector_iterator operator-(const difference_type _dif) const noexcept
        {
            _Vector_iterator tmp = *this;

            return tmp -= _dif;
        }

        difference_type operator-(const _Vector_iterator& _dif_it) const noexcept
        {
            return _Ptr - _dif_it._Ptr;
        }

        operator _Vector_iterator<const value_type>() const
        {
            _Vector_iterator<const value_type> _Cast(_Ptr);

            return _Cast;
        }




        pointer _Ptr;

    };


    template<typename T>
    class vector
    {

    public:

        using iterator = _Vector_iterator<T>;
        using const_iterator = _Vector_iterator<const T>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        explicit vector(size_t size = 0, const T& value = T());
        vector(const vector& other);
        vector(vector&& other) noexcept;
        vector(const std::initializer_list<T>& list);
        ~vector();

        vector& operator=(const vector& other);
        vector& operator=(const std::initializer_list<T>& list);
        vector& operator=(vector&& other) noexcept;

        void swap(vector& other) noexcept;
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator rend() const noexcept;
        void reserve(size_t new_capacity);
        void resize(size_t new_size, const T& value = T());
        void shrink_to_fit();
        void clear() noexcept;

        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        void insert(iterator _Place, const T& value);
        void insert(iterator _Place, T&& value);
        void push_front(T&& value);
        void push_front(const T& value);

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        T& at(size_t index);
        const T& at(size_t index) const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T* data() noexcept;
        const T* data() const noexcept;


    private:
        void ExpandifNeed();

        size_t _size;
        size_t _capacity;
        T* _data;
    };

    template<typename T>
    vector<T>::vector(size_t _size, const T& value) : _size(_size), _capacity(_size), _data(new T[_size])
    {
        std::fill(begin(), end(), value);
    }

    template<typename T>
    vector<T>::vector(const vector& other) : _size(other._size), _capacity(other._size), _data(new T[_size])
    {
        std::copy(other.begin(), other.end(), begin());
    }

    template<typename T>
    vector<T>::vector(const std::initializer_list<T>& list) : _size(list.size()), _capacity(list.size()), _data(new T[_size])
    {
        std::copy(list.begin(), list.end(), begin());
    }

    template<typename T>
    vector<T>::vector(vector&& other) noexcept
    {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    template<typename T>
    vector<T>& vector<T>::operator=(const vector& other)
    {
        if (this != &other)
        {
            vector<T>(other).swap(*this);
        }

        return *this;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(const std::initializer_list<T>& list)
    {
        vector(list).swap(*this);

        return *this;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(vector&& other) noexcept
    {
        if (this != &other)
        {
            swap(other);
        }

        return *this;
    }

    template<typename T>
    vector<T>::~vector() { delete[] _data; }

    template<typename T>
    T& vector<T>::operator[](size_t index)
    {
        return *(_data + index);
    }

    template<typename T>
    const T& vector<T>::operator[](size_t index) const
    {
        return *(_data + index);
    }

    template<typename T>
    T& vector<T>::at(size_t index)
    {
        if (index < _size)
            return *(_data + index);
        else
            throw std::invalid_argument("Out of range");
    }

    template<typename T>
    const T& vector<T>::at(size_t index) const
    {
        if (index < _size)
            return *(_data + index);
        else
            throw std::invalid_argument("Out of range");
    }

    template<typename T>
    void vector<T>::swap(vector& other) noexcept
    {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    template<typename T>
    size_t vector<T>::size() const noexcept { return _size; }

    template<typename T>
    size_t vector<T>::capacity() const noexcept { return _capacity; }

    template<typename T>
    bool vector<T>::empty() const noexcept
    {
        return _size == 0;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::begin() noexcept { return iterator(_data); }

    template<typename T>
    typename vector<T>::iterator vector<T>::end() noexcept { return iterator(_data + _size); }

    template<typename T>
    typename vector<T>::const_iterator vector<T>::begin() const noexcept { return const_iterator(_data); }

    template<typename T>
    typename vector<T>::const_iterator vector<T>::end() const noexcept { return const_iterator(_data + _size); }

    template<typename T>
    typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept { return reverse_iterator(end()); }

    template<typename T>
    typename vector<T>::reverse_iterator vector<T>::rend() noexcept { return reverse_iterator(begin()); }

    template<typename T>
    typename vector<T>::const_reverse_iterator vector<T>::rbegin() const noexcept { return const_reverse_iterator(end()); }

    template<typename T>
    typename vector<T>::const_reverse_iterator vector<T>::rend() const noexcept { return const_reverse_iterator(begin()); }

    template<typename T>
    void vector<T>::reserve(size_t new_capacity)
    {
        if (new_capacity > _capacity)
        {
            auto new_data = new T[new_capacity];

            std::move(begin(), end(), new_data);

            _capacity = new_capacity;
            delete[] _data;
            _data = new_data;
        }
    }

    template<typename T>
    void vector<T>::resize(size_t new_size, const T& value)
    {
        if (new_size > _size)
        {
            auto new_data = new T[new_size];

            std::move(begin(), end(), new_data);
            std::fill(new_data + _size, new_data + new_size, value);

            delete[] _data;
            _data = new_data;
            _size = new_size;
            _capacity = new_size;
        }
        else
        {
            _size = new_size;
        }
    }

    template<typename T>
    void vector<T>::shrink_to_fit()
    {
        vector<T>(*this).swap(*this);
    }

    template<typename T>
    void vector<T>::clear() noexcept { _size = 0; }

    template<typename T>
    void vector<T>::push_back(const T& value)
    {
        ExpandifNeed();

        _data[_size++] = value;
    }

    template<typename T>
    void vector<T>::push_back(T&& value)
    {
        ExpandifNeed();

        _data[_size++] = std::move(value);
    }

    template<typename T>
    void vector<T>::pop_back()
    {
        --_size;
    }

    template<typename T>
    void vector<T>::insert(iterator _Place, const T& value)
    {
        if (_Place <= this->end()) {

            auto _dist = std::distance(_Place, end());
            ExpandifNeed();

            auto _new_Place = rbegin() + _dist;
            ++_size;

            std::move(std::next(rbegin()), _new_Place, rbegin());

            *(_new_Place.base()) = value;
        }
        else {
            throw std::invalid_argument("Iterator out of range");
        }
    }

    template<typename T>
    void vector<T>::insert(iterator _Place, T&& value)
    {
        if (_Place <= this->end()) {

            auto _dist = std::distance(_Place, end());
            ExpandifNeed();

            auto _new_Place = rbegin() + _dist;
            ++_size;

            std::move(std::next(rbegin()), _new_Place, rbegin());

            *(_new_Place.base()) = std::move(value);
        }
        else {
            throw std::invalid_argument("Iterator out of range");
        }
    }

    template<typename T>
    void vector<T>::push_front(const T& value)
    {
        ExpandifNeed();
        ++_size;

        std::move(std::next(rbegin()), rend(), rbegin());

        *begin() = std::move(value);

    }
    
    template<typename T>
    void vector<T>::push_front(T&& value)
    {
        ExpandifNeed();
        ++_size;

        std::move(std::next(rbegin()), rend(), rbegin());

        *begin() = std::move(value);

    }

    template<typename T>
    T& vector<T>::front()
    {
        return *_data;
    }

    template<typename T>
    const T& vector<T>::front() const
    {
        return *_data;
    }

    template<typename T>
    T& vector<T>::back()
    {
        return *std::prev(end());
    }

    template<typename T>
    const T& vector<T>::back() const
    {
        return *std::prev(end());
    }

    template<typename T>
    T* vector<T>::data() noexcept
    {
        return _data;
    }

    template<typename T>
    const T* vector<T>::data() const noexcept
    {
        return _data;
    }

    template<typename T>
    void vector<T>::ExpandifNeed()
    {
        if (_size >= _capacity)
        {
            auto new_capacity = (_capacity == 0) ? 1 : 2 * _capacity;
            auto new_data = new T[new_capacity];

            std::move(begin(), end(), new_data);

            delete[] _data;
            _data = new_data;
            _capacity = new_capacity;
        }
    }

    template<typename T>
    bool operator==(const vector<T>& lhs,const vector<T>& rhs )
    {
        if(lhs.size() == rhs.size())
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());

        return false;        
    }

    template<typename T>
    bool operator!=(const vector<T>& lhs,const vector<T>& rhs )
    {
        return !(lhs == rhs);        
    }

}