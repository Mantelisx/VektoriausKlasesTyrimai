#pragma once
#include <stdexcept>

using std::out_of_range;

template <class T>
class  Vector
{
public:

    typedef T* iterator;

    // default konstruktorius
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T& initial);
    Vector(const std::initializer_list<int>& list);
    // copy konstruktorius
    Vector(const Vector<T>& v);
    // destruktorius
    ~Vector();

    // iteratoriai
    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;
    const iterator cbegin() const;
    const iterator cend() const;

    T& at(int n);
    const T& at(int n) const;
    T& front();
    T& back();
    const T& front() const;
    const T& back()const;

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    Vector<T>& operator=(const Vector<T>&);
    bool operator==(const Vector& rhs) const;
    bool operator!=(const Vector& rhs) const;

    void push_back(const T& value);
    void pop_back();
    void clear();

    //friend ostream& operator <<(ostream& ostr, const Vector<T>& rhs);

private:
    unsigned int my_size;
    unsigned int my_capacity;
    T* element;
};

template<class T>
Vector<T>::Vector()
{
    my_capacity = 0;
    my_size = 0;
    element = 0;
}



template<class T>
Vector<T>::Vector(const Vector<T>& v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    element = new T[my_size];   // ar capacity?
    for (unsigned int i = 0; i < my_size; i++)
        element[i] = v.element[i];
}

template<class T>
Vector<T>::Vector(unsigned int size)
{
    my_capacity = size;
    my_size = size;
    element = new T[size];
}

template<class T>
Vector<T>::Vector(unsigned int size, const T& initial)
{
    my_size = size;
    my_capacity = size;
    element = new T[size];
    for (unsigned int i = 0; i < size; i++)
        element[i] = initial;
    //T();
}

template<class T>
inline Vector<T>::Vector(const std::initializer_list<int>& list)
    :my_size(0),
    my_capacity(list.size() + 5),
    element(new T[my_capacity])
{
    for (int i : list) {
        push_back(i);
    }
}

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& v)
{
    if (&v != this) {
        delete[] element;
        my_size = v.my_size;
        my_capacity = v.my_capacity;
        element = new T[my_size];
        for (unsigned int i = 0; i < my_size; i++)
            element[i] = v.element[i];
    }
    return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& rhs) const {
    if (size() != rhs.size()) {
        return false;
    }

    for (unsigned int i = 0; i < size(); ++i) {
        if (element[i] != rhs.element[i]) {
            return false;
        }
    }

    return true;
}

template<class T>
inline bool Vector<T>::operator!=(const Vector<T>& rhs) const
{
    return !(*this == rhs);
}


template<class T>
bool Vector<T>::empty() const
{
    return (my_size == 0);
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return element;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return element + size();
}

template<class T>
typename const Vector<T>::iterator Vector<T>::begin() const
{
    return element;
}

template<class T>
typename const Vector<T>::iterator Vector<T>::end() const
{
    return element + size();
}

template<class T>
typename const Vector<T>::iterator Vector<T>::cbegin() const
{
    return element;
}

template<class T>
typename const Vector<T>::iterator Vector<T>::cend() const
{
    return element + size();
}


template<class T>
T& Vector<T>::front()
{
    return element[0];
}

template<class T>
inline const T& Vector<T>::front() const
{
    return element[0];
}

template<class T>
T& Vector<T>::back()
{
    return element[my_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const
{
    return element[my_size - 1];
}

template<class T>
void Vector<T>::push_back(const T& v)
{

    if (my_capacity == 0)
        reserve(7);
    else if (my_size == my_capacity)
        reserve(2 * my_capacity);

    element[my_size] = v;

    ++my_size;
    /*
    if (my_size >= my_capacity)
        reserve(my_capacity + 5); //+5
    element[my_size++] = v;
    */
}

template<class T>
void Vector<T>::pop_back()
{
    // element[my_size]->~T();
    my_size--;
}

template<class T>
void Vector<T>::reserve(unsigned int capacity)
{
    if (element == 0)
    {
        my_size = 0;
        my_capacity = 0;
    }
    T* Newelement = new T[capacity];
    unsigned int l_Size = capacity < my_size ? capacity : my_size;

    for (unsigned int i = 0; i < l_Size; i++)
        Newelement[i] = element[i];

    my_capacity = capacity;
    delete[] element;
    element = Newelement;
}

template<class T>
unsigned int Vector<T>::size()const
{
    return my_size;
}

template<class T>
void Vector<T>::resize(unsigned int size)
{
    reserve(size);
    my_size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index)
{
    if (index >= 0 && index <= my_size)
        return element[index];
    throw "Out of bounds element access";
    //throw std::out_of_range("Out of bounds element access");
    // throw std::runtime_error("Irasete netinkamai\n");
    //return element[index];
}

template<class T>
const T& Vector<T>::operator[](unsigned int index) const
{
    if (index >= 0 && index <= my_size)
        return element[index];
    throw "Out of bounds element access";
}

template<class T>
unsigned int Vector<T>::capacity()const
{
    return my_capacity;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] element;
}

template <class T>
void Vector<T>::clear()
{
    my_capacity = 0;    // standartiniam vectoriui nesikeicia capacity
    my_size = 0;
    element = 0;
}


template<class T>
inline T& Vector<T>::at(int n)
{
    if (n < 0 || my_size <= n) throw "out_of_range";      //throw out_of_range();
    return element[n];
}

template<class T>
inline const T& Vector<T>::at(int n) const
{
    if (n < 0 || my_size <= n) throw "out_of_range";      //throw out_of_range();
    return element[n];
}

/*
template <class T>
std::ostream& operator <<(std::ostream& ostr, const Vector<T>& rhs) {
    for (unsigned int i = 0; i < rhs.size(); ++i) {
        ostr << rhs.element[i] << " ";
    }

    return ostr;
}
*/

