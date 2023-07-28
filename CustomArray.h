#ifndef CUSTOMARRAY_H_INCLUDED
#define CUSTOMARRAY_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list
#include <iterator> // std::forward_iterator_tag
#include <cassert>


/*
 *
 * File:    CustomArray.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom array container in the form of a class template CustomArray.
 *   Member functions of the class are available to add, remove, or manipulate data.
 *   Friend functions of the class are available to apply basic probability set type operations.
 *
 *   The template class has been tested with the following data types:
 *     * Integers
 *     * Floats
 *     * Doubles
 *     * Characters
 *     * C++ strings (std::string)
 *
 */


// Forward declarations of class template CustomArray and associated friend functions begin here.
// Required to support class template functionality.


/*
 *
 *   Class Name: CustomArray
 *
 *   Purpose:
 *
 *     A custom array container class template.
 *
 *   Member Variables:
 *
 *     m_length
 *       An unsigned integer (std::size_t) that tracks the number of elements in the array.
 *     m_array_ptr
 *       A pointer to dynamic array created in heap memory.
 *
 *
 *   Member Functions:
 *
 *     isNull
 *       Checks if m_array is a null pointer.
 *     display
 *       Prints the array data to the specified output stream.
 *     deepCopy
 *       Performs a deep copy of another array.
 *     linearSearch
 *       Searches linearly for the specified value.
 *     binarySearch
 *       Searches through a sorted array using the binary search algorithm.
 *     size
 *       Returns m_length
 *     empty
 *       Returns a bool False if m_length is zero. Else, returns True.
 *     clear
 *       Removes the array data from memory and the array.
 *     resize
 *       Slow resize function. All elements are kept in the array up to the new length.
 *     insert
 *       Inserts data into the array at the specified position.
 *     erase
 *       Removes data from the array at the specified position.
 *     pushBack
 *       Appends a new value to the end of the array.
 *     pushFront
 *       Inserts a new value at the start of the array.
 *     popBack
 *       Removes an existing value from the end of the array.
 *     popFront
 *       Removes an existing value from the start of the array.
 *     reverse
 *       Reverses the order of the array elements in place.
 *     bubbleSort
 *       Sorts the array in ascending order using the bubblesort algorithm.
 *     isSorted
 *       Function to state whether the array elements are in ascending order or not.
 *     search
 *       Searches the array for a specified value.
 *     swap
 *       Swaps array data nodes with another array.
 *
 */
template <typename T>
class CustomArray;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, const CustomArray<T>& arr);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomArray array object.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privileges within the CustomArray class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomArray<T>& arr);

/*
 *
 * template <typename T>
 * CustomArray<T> merge(const CustomArray<T>& A, const CustomArray<T>& B);
 *
 * Summary:
 *
 *    Combines and sorts (ascending) two arrays.
 *
 * Return Value: CustomArray merged
 *
 * Description:
 *
 *   Function to merge two arrays that has friend privileges within the CustomArray class.
 *   Items within both arrays are sorted into ascending order and placed into a new combined array.
 *   Returns the combined array by value.
 *
 */
template <typename T>
CustomArray<T> merge(const CustomArray<T>& A, const CustomArray<T>& B);

/*
 *
 * template <typename T>
 * CustomArray<T> setUnion(CustomArray<T> A, CustomArray<T> B);
 *
 * Summary:
 *
 *    Returns the set that is the union of arrays.
 *
 * Return Value: CustomArray unionArray
 *
 * Description:
 *
 *   Function to return the union of two arrays that has friend privileges within the CustomArray class.
 *   Items within both arrays are sorted into ascending order and placed into a new combined array.
 *   Returns the new combined array by value.
 *
 */
template <typename T>
CustomArray<T> setUnion(CustomArray<T> A, CustomArray<T> B);

/*
 *
 * template <typename T>
 * CustomArray<T> setDifference(CustomArray<T> A, CustomArray<T> B);
 *
 * Summary:
 *
 *    Returns the set that is the difference (relative compliment) of two arrays.
 *
 * Return Value: CustomArray difference
 *
 * Description:
 *
 *   Function to return the difference between two arrays that has friend privileges within the CustomArray class.
 *   Items within both arrays are sorted into ascending order and placed into a new resulting array.
 *   Returns the new resulting array by value.
 *
 */
template <typename T>
CustomArray<T> setDifference(CustomArray<T> A, CustomArray<T> B);

/*
 *
 * template <typename T>
 * CustomArray<T> setIntersection(CustomArray<T> A, CustomArray<T> B);
 *
 * Summary:
 *
 *    Returns the set that is the intersection of two arrays.
 *
 * Return Value: CustomArray intersection
 *
 * Description:
 *
 *   Function to return the intersection of two arrays that has friend privileges within the CustomArray class.
 *   Items within both arrays are sorted into ascending order and placed into a new resulting array.
 *   Returns the new resulting array by value.
 *
 */
template <typename T>
CustomArray<T> setIntersection(CustomArray<T> A, CustomArray<T> B);


// Forward declaration of template friend functions ends here.


template <typename T>
class CustomArray
{
private:

    std::size_t m_length{};
    T* m_array_ptr{};

    // isNull is used primarily as a check for dynamic memory deletion within member functions.
    bool isNull() const { return m_array_ptr == nullptr; }

    /*
     *
     * std::ostream& display(std::ostream& out) const;
     *
     * Summary:
     *
     *   Sends the array data to the standard output.
     *
     * Parameters   : std::ostream& out
     *
     * Return Value : std::ostream& out
     *
     * Description:
     *
     *   Prints each item in the array data to the terminal.
     *   Called by the overloaded operator << friend function.
     *   Contains specific overloads for a CustomArray<char> type.
     *
     * Example Output (default):
     *   1 2 3
     *
     * Example Output (char)
     *   abc
     *
     */
    std::ostream& display(std::ostream& out) const;

    /*
     *
     * void deepCopy(const CustomArray<T>& other);
     *
     * Summary:
     *
     *   Performs a deep copy of another array.
     *
     * Parameters   : CustomArray<T>& other
     *
     * Return Value : None
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other linked-list.
     *   Copies the values of the other linked-list to the newly allocated memory.
     *   Called by the CustomArray copy constructor and overloaded copy assignment member function.
     *
     */
    void deepCopy(const CustomArray<T>& other);

    /*
     *
     * bool linearSearch(const T& value);
     *
     * Summary:
     *
     *   Searches linearly for the specified value.
     *
     * Parameters   : const T& value
     *
     * Return Value : int index or -1.
     *
     * Description:
     *
     *   Beginning at the first element in array, searches linearly for the specified value.
     *   Returns either the element index of the first element that is equal to value, or -1.
     *
     */
    int linearSearch(const T& value);

    /*
     *
     * int binarySearch(const T& value);
     *
     * Summary:
     *
     *   Searches through a sorted array using the binary search algorithm.
     *
     * Parameters   : const T& value
     *
     * Return Value : int index or -1.
     *
     * Description:
     *
     *   Beginning at the first element in array, searches for the specified value using a binary search.
     *   Returns either the element index of the first element that is equal to value, or -1.
     *
     */
    int binarySearch(const T& value);

public:

    // An overloaded default constructor that writes a message to the standard output.
    CustomArray() noexcept;

    /*
     *
     * CustomArray(std::initializer_list<T> elements) noexcept;
     *
     * Summary:
     *
     *   Initialises an array from a std::initializer_list.
     *
     * Parameters: std::initializer_list<T> elements
     *
     * Description:
     *
     *   Copies the values of a std::initializer_list to an array in heap memory.
     *   Matches the length of the array to the length of the std::initializer_list.
     *
     */
    CustomArray(std::initializer_list<T> elements) noexcept;

    /*
     *
     * CustomArray(const CustomArray<T>& other) noexcept;
     *
     * Summary:
     *
     *   Initialises an array from another array.
     *
     * Parameters: CustomArray<T>& other
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other array.
     *   Using deepCopy, copies the values of the other array to the newly allocated memory.
     *
     */
    CustomArray(const CustomArray<T>& other) noexcept;

    /*
     *
     * CustomArray(CustomArray<T>&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises an array from another array, using move semantics.
     *
     * Parameters   : CustomLinkedList<T>&& other
     *
     * Description:
     *
     *   Switches the memory addreses of the linked-list and other linked-list pointers.
     *   Sets the pointer addresses of the linked-list other to nullptr.
     *
     */
    CustomArray(CustomArray<T>&& other) noexcept;

    /*
     *
     * template <typename InputIterator>
     * CustomArray(InputIterator first, InputIterator last);
     *
     * Summary:
     *
     *   Initialises an array from another standard library container.
     *
     * Parameters   : InputIterator first, InputIterator last
     *
     * Description:
     *
     *   Uses two iterators that are compatible with containers in the standard library.
     *   Copies the data within a standard library container to the array.
     *
     */
    template <typename InputIterator>
    CustomArray(InputIterator first, InputIterator last) noexcept;

    /*
     *
     * ~CustomArray() noexcept;
     *
     * Summary:
     *
     *   Frees each linked-list node in memory before destoying the linked-list.
     *
     * Description:
     *
     *   Uses clear to erase all linked-list nodes before destroying the linked-list.
     *
     */
    ~CustomArray() noexcept;

    // Public member function declarations.
    std::size_t size() const { return m_length; }
    bool empty() const { return !m_length; }

    /*
     *
     * void clear();
     *
     * Summary:
     *
     *   Removes the array data from memory and the array.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Removes the array data from the heap.
     *   Sets the array pointer to nullptr.
     *   Sets the array size to zero.
     *
     */
    void clear();

    /*
     *
     * void resize(std::size_t length);
     *
     * Summary:
     *
     *   Slow resize function. All elements are kept in the array up to the new length.
     *
     * Parameters   : int length
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a temporary array with the size specified length.
     *   Copies elements from the existing array to the new temporary array
     *   Deletes the existing array from memory and assigns the array pointer to the new arrary
     *   Warning! Elements at a position greater than the new length will be dropped from the array.
     *
     */
    void resize(std::size_t length);

    /*
     *
     * void insert(int position, const T& value);
     *
     * Summary:
     *
     *   Inserts data into the array at the specified position.
     *
     * Parameters   : int position, const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a new temporary array in the heap.
     *   Copies values from the array to the new temporary array, with the additional value.
     *   Deletes the existing array from heap memory.
     *   Points the CustomArray pointer to the newly created temporary array.
     *   Increments the length by one.
     *   Support negative indexing!
     *
     */
    void insert(int position, const T& value);

    /*
     *
     * void erase(int position);
     *
     * Summary:
     *
     *   Removes data from the array at the specified position.
     *
     * Parameters   : int position
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a new temporary array in the heap.
     *   Copies values from the array to the new temporary array, except data at the specified position.
     *   Deletes the existing array from heap memory.
     *   Points the CustomArray to the newly created temporary array.
     *   Decrements the length by one.
     *   Support negative indexing!
     *
     */
    void erase(int position);

    /*
     *
     * void pushBack(const T& value);
     *
     * Summary:
     *
     *   Appends a new value to the end of the array.
     *
     * Parameters   : const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the insert function with position equal to the current length of the array.
     *
     */
    void pushBack(const T& value);

    /*
     *
     * void pushFront(const T& value);
     *
     * Summary:
     *
     *   Inserts a new value at the start of the array.
     *
     * Parameters   : const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the insert function with position equal to zero.
     *
     */
    void pushFront(const T& value);

    /*
     *
     * void popBack();
     *
     * Summary:
     *
     *   Removes an existing value from the end of the array.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the erase function with position equal to the current length of the array.
     *
     */
    void popBack();

    /*
     *
     * void popFront();
     *
     * Summary:
     *
     *   Removes an existing value from the start of the array.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the erase function with position equal to zero.
     *
     */
    void popFront();

    /*
     *
     * void reverse();
     *
     * Summary:
     *
     *   Reverses the order of the array elements in place.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Iterates forwards and backwards through the array (from the start and end).
     *   Each iteration, the iterator values are swapped using std::swap.
     *   This results in a permanent change to the array.
     *
     */
    void reverse();

    /*
     *
     * void bubbleSort();
     *
     * Summary:
     *
     *   Sorts the array in ascending order using the bubblesort algorithm.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Sorts the array in ascending order using the bubblesort algorithm.
     *   This results in a permanent change to the array.
     *
     */
    void bubbleSort();

    /*
     *
     * bool isSorted();
     *
     * Summary:
     *
     *   Function to state whether the array elements are in ascending order or not.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Iterates through the array.
     *   Returns false if an element is found to be larger than the next element to the right.
     *   Elements are considered sorted if they are in ascending order.
     *
     */
    bool isSorted();

    /*
     *
     * int search(const T& value);
     *
     * Summary:
     *
     *   Searches the array for a specified value.
     *
     * Parameters   : const T& value
     *
     * Return Value : int index or -1.
     *
     * Description:
     *
     *   Identifies whether the array is sorted or not, using isSorted().
     *   If the array is sorted, performs a binary search using binarySearch().
     *   If the array isn't sorted, performs a linear search using linearSearch().
     *   Returns either the index position of the elements that matches value, or -1.
     *
     */
    int search(const T& value);

    /*
     *
     * void swap(CustomArray<T>& other);
     *
     * Summary:
     *
     *   Swaps array data nodes with another array.
     *
     * Parameters   : CustomArray<T>& other
     *
     * Return Value : None
     *
     * Description:
     *
     *   Switches the m_array_ptr of the array with other.
     *
     */
    void swap(CustomArray<T>& other);

    /*
     *
     * T& operator[](int position);
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: T& m_array_ptr[position]
     *
     * Description:
     *
     *   Returns the element of the array at the specified position.
     *   Support negative indexing!
     *
     */
    T& operator[](int position);

    /*
     *
     * T& operator[](int position);
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: const T& m_array_ptr[position]
     *
     * Description:
     *
     *   Returns the element of the array at the specified position.
     *   Support negative indexing!
     *
     */
    const T& operator[](int position) const;

    /*
     *
     * CustomArray& operator=(const CustomArray<T>& other);
     *
     * Summary:
     *
     *   Copy assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Clears the existing array.
     *   Allocates a new portion of memory equal in size and structure to the array other.
     *   Using deepCopy, copies the values of the other linked-list to the newly allocated memory.
     *
     */
    CustomArray& operator=(const CustomArray<T>& other);

    /*
     *
     * CustomArray& operator=(CustomArray<T>&& other);
     *
     * Summary:
     *
     *   Move assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Switches array pointer addresses and lengths with the temporary/anonymous array object other.
     *
     */
    CustomArray& operator=(CustomArray<T>&& other);

    /*
     *
     * CustomArray& operator=(std::initializer_list<T> elements);
     *
     * Summary:
     *
     *   Copy assignment operator overload from a std::initializer_list.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Uses the copy and swap idiom.
     *   Creates a temporary array with the std::initializer_list elements.
     *   Switches pointer addresses and lengths with the temporary array.
     *
     */
    CustomArray& operator=(std::initializer_list<T> elements);

    // Fully specialised template friend function declarations.
    friend std::ostream& operator<<<T>(std::ostream& out, const CustomArray<T>& arr);
    friend CustomArray<T> merge<T>(const CustomArray<T>& A, const CustomArray<T>& B);
    friend CustomArray<T> setUnion<T>(CustomArray<T> A, CustomArray<T> B);
    friend CustomArray<T> setDifference<T>(CustomArray<T> A, CustomArray<T> B);
    friend CustomArray<T> setIntersection<T>(CustomArray<T> A, CustomArray<T> B);

    /*
     *
     *   Class Name: Iterator
     *
     *   Purpose:
     *     A bidirectional non-const iterator for CustomArray<T> objects.
     *
     */
    class Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    private:
        pointer m_ptr;
    public:
        Iterator(pointer ptr = nullptr) : m_ptr{ ptr } {}
        Iterator(const Iterator& other) : m_ptr{ other.m_ptr } {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        Iterator& operator++() { ++m_ptr; return *this; }
        Iterator operator++(int) { Iterator tmp{ *this }; ++(*this); return tmp; }
        Iterator& operator--() { --m_ptr; return *this; }
        Iterator operator--(int) { Iterator tmp{ *this }; --(*this); return tmp; }
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
    };

    Iterator begin() { return Iterator{ m_array_ptr }; }
    Iterator end() { return Iterator{ m_array_ptr + m_length }; }

    /*
     *
     *   Class Name: ConstIterator
     *
     *   Purpose:
     *     A bidirectional const iterator for const CustomArray<T> objects.
     *
     */
    class ConstIterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
    private:
        pointer m_ptr;
    public:
        ConstIterator(pointer ptr = nullptr) : m_ptr{ ptr } {}
        ConstIterator(const ConstIterator& other) : m_ptr{ other.m_ptr } {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        ConstIterator& operator++() { ++m_ptr; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp{ *this }; ++(*this); return tmp; }
        ConstIterator& operator--() { --m_ptr; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp{ *this }; --(*this); return tmp; }
        friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; }
    };

    ConstIterator begin() const { return ConstIterator{ m_array_ptr }; }
    ConstIterator end() const { return ConstIterator{ m_array_ptr + m_length }; }

};


// Private member function definitions begin here.

template<typename T>
std::ostream& CustomArray<T>::display(std::ostream& out) const
{
    auto it{ begin() };
    T* last{ m_array_ptr + m_length - 1 };
    if (m_length)
    {
        do
        {
            if (it == last)
            {
                out << *it;
            }
            else
            {
                out << *it << " ";
            }
        }
        while (++it != end());
    }
    return out;
}

template<>
std::ostream& CustomArray<char>::display(std::ostream& out) const
{
    for (auto it{begin()}; it != end(); ++it)
    {
        out << *it;
    }
    return out;
}

template<typename T>
void CustomArray<T>::deepCopy(const CustomArray<T> &other)
{
    if (other.m_length > 0)
    {
        m_length = other.m_length;
        m_array_ptr = new T[m_length];
        for (int idx{ 0 }; idx < static_cast<int>(m_length); ++idx)
        {
            m_array_ptr[idx] = other.m_array_ptr[idx];
        }
    }
}

template <typename T>
int CustomArray<T>::linearSearch(const T& value)
{
    for (int index{ 0 }; index < static_cast<int>(m_length); ++index)
    {
        if (value == m_array_ptr[index])
        {
            return index;
        }
    }
    return -1;
}

template <typename T>
int CustomArray<T>::binarySearch(const T& value)
{
    assert(isSorted() && "Array elements must be in ascending order.");
    int index{};
    int low{};
    int high{ static_cast<int>(m_length) - 1 };
    while (low <= high)
    {
        index = (low + high ) / 2;
        if (value == m_array_ptr[index])
        {
            return index;
        }
        else if (value < m_array_ptr[index])
        {
            high = index - 1;
        }
        else
        {
            low = index + 1;
        }
    }
    return -1;
}

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
CustomArray<T>::CustomArray() noexcept
{
    std::cout << "CustomArray default constructor called.\n";
}

template <typename T>
CustomArray<T>::CustomArray(std::initializer_list<T> elements) noexcept
{
    std::cout << "CustomArray list-initialised constructor called.\n" ;
    if (elements.size() > 0)
    {
        m_length = elements.size();
        m_array_ptr = new T[elements.size()];
        int counter{ 0 };
        for (auto element : elements)
        {
            m_array_ptr[counter++] = element;
        }
    }
}

template <typename T>
CustomArray<T>::CustomArray(const CustomArray<T>& other) noexcept
{
    std::cout << "CustomArray copy constructor called.\n";
    deepCopy(other);
}

template <typename T>
CustomArray<T>::CustomArray(CustomArray<T>&& other) noexcept
{
    std::cout << "CustomArray move constructor called.\n";
    if (other.m_length > 0)
    {
        m_length = other.m_length;
        m_array_ptr = other.m_array_ptr;
        other.m_length = 0;
        other.m_array_ptr = nullptr;
    }
}

template <typename T>
template <typename InputIterator>
CustomArray<T>::CustomArray(InputIterator first, InputIterator last) noexcept
{
    std::cout << "CustomLinkedList (iterator) copy constructor called.\n";
    while (first != last)
    {
        pushBack(*first);
        ++first;
    }
}

template <typename T>
CustomArray<T>::~CustomArray() noexcept
{
    std::cout << "CustomArray destructor called.\n";
    clear();
}

// Constructor and Destructor definitions end here.

// Operator overload definitions begin here.

template <typename T>
T& CustomArray<T>::operator[](int position)
{
    if (position < 0)
    {
        position = static_cast<int>(m_length) - (abs(position) % static_cast<int>(m_length));
        return m_array_ptr[position];
    }

    if (position > static_cast<int>(m_length))
    {
        return m_array_ptr[m_length];
    }

    return m_array_ptr[position];
}

template <typename T>
const T& CustomArray<T>::operator[](int position) const
{
    if (position < 0)
    {
        position = static_cast<int>(m_length) - (abs(position) % static_cast<int>(m_length));
        return m_array_ptr[position];
    }

    if (position > static_cast<int>(m_length))
    {
        return m_array_ptr[m_length];
    }

    return m_array_ptr[position];
}

template <typename T>
CustomArray<T>& CustomArray<T>::operator=(const CustomArray<T>& other)
{
    clear();
    deepCopy(other);
    return *this;
}

template <typename T>
CustomArray<T>& CustomArray<T>::operator=(CustomArray<T>&& other)
{
    swap(other);
    return *this;
}

template <typename T>
CustomArray<T>& CustomArray<T>::operator=(std::initializer_list<T> elements)
{
    CustomArray<T> temp{ elements };
    swap(temp);
    return *this;
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

template <typename T>
void CustomArray<T>::clear()
{
    m_length = 0;
    if (!isNull()) { delete[] m_array_ptr; }
    m_array_ptr = nullptr;
}

template <typename T>
void CustomArray<T>::resize(std::size_t length)
{
    if (m_length == length) { return; }

    try
    {
        T* new_array_ptr { new T[length]{} };
        auto elementsToCopy{ (length > m_length) ? m_length : length };
        for (auto position{ 0 }; position < static_cast<int>(elementsToCopy); ++position)
        {
            new_array_ptr[position] = m_array_ptr[position];
        }
        delete[] m_array_ptr;
        m_array_ptr = new_array_ptr;
        m_length = length;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Standard exception caught: " << e.what() << "\n"
                  << "Length of array remains " << size() << "\n";
        return;
    }
}

template <typename T>
void CustomArray<T>::insert(int position, const T& value)
{
    if (position < 0)
    {
        position = static_cast<int>(m_length) - (abs(position) % static_cast<int>(m_length));
        insert(position, value);
        return;
    }

    if (position > static_cast<int>(m_length))
    {
        insert(static_cast<int>(m_length), value);
        return;
    }

    T* new_array_ptr { new T[m_length + 1] };
    if (!isNull())
    {
        for (int before{ 0 }; before < position; ++before)
        {
            new_array_ptr[before] = m_array_ptr[before];
        }
        for (int after{ position }; after < static_cast<int>(m_length); ++after)
        {
            new_array_ptr[after + 1] = m_array_ptr[after];
        }
        delete[] m_array_ptr;
    }
    new_array_ptr[position] = value;
    m_array_ptr = new_array_ptr;
    new_array_ptr = nullptr;
    ++m_length;
}

template <typename T>
void CustomArray<T>::erase(int position)
{
    if (empty()) { return; }

    if (m_length == 1)
    {
        clear();
        return;
    }

    if (position < 0)
    {
        position = static_cast<int>(m_length) - (abs(position) % static_cast<int>(m_length));
        erase(position);
        return;
    }

    if (position > static_cast<int>(m_length))
    {
        erase(static_cast<int>(m_length));
        return;
    }

    T* new_array_ptr { new T[m_length - 1] };
    for (int before{ 0 }; before < position; ++before)
    {
        new_array_ptr[before] = m_array_ptr[before];
    }
    for (int after{ position + 1 }; after < m_length; ++after)
    {
        new_array_ptr[after - 1] = m_array_ptr[after];
    }
    delete[] m_array_ptr;
    m_array_ptr = new_array_ptr;
    new_array_ptr = nullptr;
    --m_length;
}

template <typename T>
void CustomArray<T>::pushBack(const T& value)
{
    insert(static_cast<int>(m_length),value);
}

template <typename T>
void CustomArray<T>::pushFront(const T& value)
{
    insert(0,value);
}

template <typename T>
void CustomArray<T>::popBack()
{
    erase(static_cast<int>(m_length));
}

template <typename T>
void CustomArray<T>::popFront()
{
    erase(0);
}

template <typename T>
void CustomArray<T>::reverse()
{
    auto forward_it{ begin() };
    auto backward_it{ m_array_ptr + m_length  - 1 };
    do
    {
        std::swap(*forward_it,*backward_it);
        ++forward_it;
        --backward_it;
    }
    while (forward_it != backward_it);
}

template <typename T>
void CustomArray<T>::bubbleSort()
{
    for (int i{ 0 }; i < static_cast<int>(m_length) - 1; ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(m_length) - 1 - i; ++j)
        {
            if (m_array_ptr[j] > m_array_ptr[j + 1])
            {
                std::swap(m_array_ptr[j],m_array_ptr[j + 1]);
            }
        }
    }
}

template <typename T>
bool CustomArray<T>::isSorted()
{
    for (int i{ 0 }; i < static_cast<int>(m_length) - 1; ++i)
    {
        if (m_array_ptr[i] > m_array_ptr[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

template <typename T>
int CustomArray<T>::search(const T& value)
{
    if (isSorted())
    {
        return binarySearch(value);
    }
    return linearSearch(value);
}

template <typename T>
void CustomArray<T>::swap(CustomArray<T>& other)
{
    std::swap(m_array_ptr,other.m_array_ptr);
    std::swap(m_length,other.m_length);
}

// Public member functions definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomArray<T>& arr)
{
    return arr.display(out);
}

template <typename T>
CustomArray<T> merge(const CustomArray<T>& A, const CustomArray<T>& B)
{
    auto i{ A.begin() };
    auto j{ B.begin() };
    CustomArray<T> merged{};
    while (i != A.end() && j != B.end())
    {
        if (*i < *j)
        {
            merged.pushBack(*i);
            ++i;
        }
        else
        {
            merged.pushBack(*j);
            ++j;
        }
    }
    for (; i != A.end(); ++i) { merged.pushBack(*i); }
    for (; j != B.end(); ++j) { merged.pushBack(*j); }
    return merged;
}

template <typename T>
CustomArray<T> setUnion(CustomArray<T> A, CustomArray<T> B)
{
    A.bubbleSort();
    B.bubbleSort();
    auto i{ A.begin() };
    auto j{ B.begin() };
    CustomArray<T> unionArray{};
    while (i != A.end() && j != B.end())
    {
        if (*i < *j)
        {
            unionArray.pushBack(*i);
            ++i;
        }
        else if (*i > *j)
        {
            unionArray.pushBack(*j);
            ++j;
        }
        else if (*i == *j)
        {
            unionArray.pushBack(*i);
            ++i;
            ++j;
        }
    }
    for (; i != A.end(); ++i) { unionArray.pushBack(*i); }
    for (; j != B.end(); ++j) { unionArray.pushBack(*j); }
    return unionArray;
}

template <typename T>
CustomArray<T> setDifference(CustomArray<T> A, CustomArray<T> B)
{
    A.bubbleSort();
    B.bubbleSort();
    auto i{ A.begin() };
    auto j{ B.begin() };
    CustomArray<T> difference{};
    while (i != A.end() && j != B.end())
    {
        if (*i < *j)
        {
            difference.pushBack(*i);
            ++i;
        }
        else if (*i > *j)
        {
            ++j;
        }
        else if (*i == *j)
        {
            ++i;
            ++j;
        }
    }
    for (; i != A.end(); ++i) { difference.pushBack(*i); }
    return difference;
}

template <typename T>
CustomArray<T> setIntersection(CustomArray<T> A, CustomArray<T> B)
{
    A.bubbleSort();
    B.bubbleSort();
    auto i{ A.begin() };
    auto j{ B.begin() };
    CustomArray<T> intersection{};
    while (i != A.end() && j != B.end())
    {
        if (*i < *j)
        {
            ++i;
        }
        else if (*i > *j)
        {
            ++j;
        }
        else if (*i == *j)
        {
            intersection.pushBack(*i);
            ++i;
            ++j;
        }
    }
    return intersection;
}

// Friend functions definitions end here.

#endif // CUSTOMARRAY_H_INCLUDED

