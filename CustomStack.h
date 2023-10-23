#ifndef CUSTOMSTACK_H_INCLUDED
#define CUSTOMSTACK_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list
#include <iterator> // std::forward_iterator_tag
#include <memory>   // std::unique_ptr

/*
 *
 * File:    CustomStack.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom stack container in the form of a class template CustomStack.
 *   Member functions of the class are available to add, remove, or manipulate data.
 *   CustomStack contains its own interators for traversing forwards and backwards through its items.
 *
 *   The template class has been tested with the following data types:
 *     * Integers
 *     * Floats
 *     * Doubles
 *     * Characters
 *     * C++ strings (std::string)
 *
 */

// Forward declarations of class template CustomStack and associated friend functions begin here.
// Required to support class template functionality.

/*
 *
 *   Class Name: CustomStack
 *
 *   Purpose:
 *
 *     A custom stack container class template.
 *
 *   Member Variables:
 *
 *     m_size
 *       An unsigned integer (std::size_t) that indicates the maximum number of elements contained in the stack.
 *     m_items
 *       An unsigned integer (std::size_t) that tracks the number of elements in the array.
 *     m_stack
 *       An array specialised unique pointer containing data.
 *
 *
 *   Member Functions:
 *
 *     deepCopy
 *       Performs a deep copy of another stack.
 *     size
 *       Returns m_size.
 *     items
 *       returns m_items.
 *     empty
 *       Returns a bool False if m_length is zero. Else, returns True.
 *     full
 *       returns a bool to indicate whether the number of items in the stack is equal to its size.
 *     clear
 *       Resets the stack data back to default initialised values.
 *     push
 *       Appends a new value to the end of the stack.
 *     pop
 *       Removes an existing value from the end of the stack.
 *     swap
 *       Swaps stack data with another stack.
 *
 */
template <typename T>
class CustomStack;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, const CustomStack<T>& stack);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomStack array object.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privileges within the CustomStack class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomStack<T>& stack);

template <typename T>
class CustomStack
{
private:

    std::size_t m_size{};
    std::size_t m_items{};
    std::unique_ptr<T[]> m_stack{ std::make_unique<T[]>(m_size) };

    /*
     *
     * void deepCopy(const CustomStack& other);
     *
     * Summary:
     *
     *   Performs a deep copy of another stack.
     *
     * Parameters   : CustomStack& other
     *
     * Return Value : None
     *
     * Description:
     *
     *   Resets the unique pointer to point to a new portion of memory equal in size to other.
     *   Copies the values of the other stack to the newly allocated memory.
     *   Called by the CustomStack copy constructor and overloaded copy assignment member function.
     *
     */
    void deepCopy(const CustomStack& other);

public:

    // CustomStack should be called with parameters in order to build a unique pointer with specified size.
    CustomStack() = delete;

    /*
     *
     * constexpr CustomStack(std::size_t stack_size) noexcept;
     *
     * Summary:
     *
     *   Parameterised constructor that builds a unique pointer (array specialised) with specified size.
     *
     * Parameters: std::size_t stack_size
     *
     * Description:
     *
     *   Allocates a new portion of memory equal to stack_size.
     *   Supports constexpr for reduced runtime processing.
     *
     */
    constexpr CustomStack(std::size_t stack_size) noexcept;

    /*
     *
     * constexpr CustomStack(const CustomStack& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a stack from another stack.
     *
     * Parameters: CustomStack& other
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other stack.
     *   Using deepCopy, copies the values of the other stack to the newly allocated memory.
     *   Supports constexpr for reduced runtime processing.
     *
     */
    constexpr CustomStack(const CustomStack& other) noexcept;

    /*
     *
     * constexpr CustomStack(CustomStack&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a stack from another stack, using move semantics.
     *
     * Parameters   : CustomStack&& other
     *
     * Description:
     *
     *   Initalises the stack unique pointer using supported move semantics.
     *   Copies the member variables that have fundamental data types.
     *   Clears the stack now owned by other.
     *   Supports constexpr for reduced runtime processing.
     *
     */
    constexpr CustomStack(CustomStack&& other) noexcept;

    // Overloaded default constructor to write a statement to the standard output when destroying.
    ~CustomStack() noexcept;

    /*
     *
     * constexpr CustomStack<T>& operator=(const CustomStack& other);
     *
     * Summary:
     *
     *   Copy assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Using deepCopy, copies the values of the other stack to the newly allocated memory.
     *   Supports constexpr for reduced runtime processing.
     *
     */
    constexpr CustomStack& operator=(const CustomStack& other);

    /*
     *
     * constexpr CustomStack<T>& operator=(CustomStack&& other);
     *
     * Summary:
     *
     *   Move assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Switches unique pointer addresses and lengths with the temporary/anonymous stack object other.
     *   Supports constexpr for reduced runtime processing.
     *
     */
    constexpr CustomStack& operator=(CustomStack&& other);

    /*
     *
     * const T& operator[](int index) const;
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: m_stack[index]
     *
     * Description:
     *
     *   Calls the unique pointer index operator overload.
     *   Support negative indexing!
     *
     */
    const T& operator[](int index) const;


    constexpr std::size_t size() { return m_size; }
    constexpr std::size_t items() { return m_items; }
    constexpr bool empty() { return m_stack == nullptr; }
    constexpr bool full() { return m_size == m_items; }

    /*
     *
     * constexpr CustomStack& clear();
     *
     * Summary:
     *
     *   Resets the unique pointer array data to the default initialised values.
     *
     * Parameters   : None
     *
     * Return Value : *this
     *
     * Description:
     *
     *   Resets the unique pointer with an array of the same size.
     *   Values in the array are replaced with their initialised defaults.
     *   Supports constexpr for reduced runtime processing.
     *   Returns the stack to support member function chaining.
     *
     */
    constexpr CustomStack& clear();

    /*
     *
     * CustomStack& push(const T& item);
     *
     * Summary:
     *
     *   Adds an items to the top of the stack if there is space.
     *
     * Parameters   : T& item
     *
     * Return Value : *this
     *
     * Description:
     *
     *   Checks if m_items is equal to m_size.
     *   If so, raises and catches a stack overflow exception.
     *   Otherwise, adds the item to the top of the stack.
     *   Returns the stack to support member function chaining.
     *
     */
    CustomStack& push(const T& item);

    /*
     *
     * constexpr CustomStack& pop();
     *
     * Summary:
     *
     *   Replaces the item with default initialised value, if the number of items in the stack is greater than zero.
     *
     * Parameters   : None
     *
     * Return Value : *this
     *
     * Description:
     *
     *   Replaces the item with default initialised value, if the number of items in the stack is greater than zero.
     *   Supports constexpr for reduced runtime processing.
     *   Returns the stack to support member function chaining.
     *
     */
    constexpr CustomStack& pop();

    /*
     *
     * constexpr CustomStack& swap(CustomStack<T>& other);
     *
     * Summary:
     *
     *   Switches the member variables of the stack with other.
     *
     * Parameters   : CustomStack& other
     *
     * Return Value : *this
     *
     * Description:
     *
     *   Switches the member variables of the stack with other.
     *   Supports constexpr for reduced runtime processing.
     *   Returns the stack to support member function chaining.
     *
     */
    constexpr CustomStack& swap(CustomStack& other);

    friend std::ostream& operator<<<T>(std::ostream& out, const CustomStack<T>& stack);

    /*
     *
     *   Class Name: Iterator
     *
     *   Purpose:
     *     A bidirectional non-const iterator for CustomStack<T> objects.
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

    constexpr Iterator begin() { return Iterator{ m_stack.get() }; }
    constexpr Iterator end() { return Iterator{ m_stack.get() + m_size }; }

    /*
     *
     *   Class Name: ConstIterator
     *
     *   Purpose:
     *     A bidirectional const iterator for const CustomStack<T> objects.
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

    constexpr ConstIterator begin() const { return ConstIterator{ m_stack.get() }; }
    constexpr ConstIterator end() const { return ConstIterator{ m_stack.get() + m_size }; }

};

// Private member function definitions begin here.

template<typename T>
void CustomStack<T>::deepCopy(const CustomStack& other)
{
    if (other.m_size > 0)
    {
        m_stack.reset(new T[other.m_size]{});
        for (std::size_t idx{ 0 }; idx < other.m_items; ++idx)
        {
            m_stack[idx] = other.m_stack[idx];
        }
    }
    else
    {
        m_stack.reset(nullptr);
    }
    m_size = other.m_size;
    m_items = other.m_items;
}

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
constexpr CustomStack<T>::CustomStack(std::size_t stack_size) noexcept
    : m_size{ stack_size }
{
    std::cout << "Parameterised CustomStack constructor called.\n";
}

template <typename T>
constexpr CustomStack<T>::CustomStack(const CustomStack<T>& other) noexcept
{
    std::cout << "CustomStack copy constructor called.\n";
    deepCopy(other);
}

template <typename T>
constexpr CustomStack<T>::CustomStack(CustomStack<T>&& other) noexcept
    : m_size{ other.m_size }
    , m_items{ other.m_items }
    , m_stack{ std::move(other.m_stack) }
{
    std::cout << "CustomStack move constructor called.\n";
    other.m_items = other.m_size = 0;
    other.m_stack.reset(nullptr);
}

template <typename T>
CustomStack<T>::~CustomStack() noexcept
{
    std::cout << "CustomStack destructor called.\n";
}

// Constructor and Destructor definitions end here.

// Operator overload definitions begin here.

template <typename T>
constexpr CustomStack<T>& CustomStack<T>::operator=(const CustomStack<T>& other)
{
    std::cout << "Overloaded copy assignment operator called.\n";
    deepCopy(other);
    return *this;
}

template <typename T>
constexpr CustomStack<T>& CustomStack<T>::operator=(CustomStack<T>&& other)
{
    std::cout << "Overloaded move assignment operator called.\n";
    swap(other);
    return *this;
}

template <typename T>
const T& CustomStack<T>::operator[](int index) const
{
    if (index > static_cast<int>(m_size) - 1) { return m_stack[m_size - 1]; }
    if (index < 0) { index = static_cast<int>(m_size) - (abs(index) % static_cast<int>(m_size)); }

    return m_stack[index];
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

template <typename T>
constexpr CustomStack<T>& CustomStack<T>::clear()
{
    m_stack.reset(new T[m_size]{});
    m_items = 0;
    return *this;
}

template <typename T>
CustomStack<T>& CustomStack<T>::push(const T& item)
{
    try
    {
        if (m_items == m_size)
        {
            throw std::overflow_error("Stack overflow!");
        }
        m_stack[m_items] = item;
        ++m_items;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Standard exception caught: " << e.what() << "\n"
                  << "Items within stack remains: " << items() << "\n";
    }
    return *this;
}

template <typename T>
constexpr CustomStack<T>& CustomStack<T>::pop()
{
    if (!m_items) { return *this; }
    T temp{};
    m_stack[m_items - 1] = temp;
    --m_items;
    return *this;
}

template <typename T>
constexpr CustomStack<T>& CustomStack<T>::swap(CustomStack<T>& other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_items, other.m_items);
    m_stack.swap(other.m_stack);
    return *this;
}

// Public member functions definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomStack<T>& stack)
{
    auto print = [&out](T* ptr, std::size_t count)
    {
        while (count != 0)
        {
            out << count << ". " << *ptr;
            --count;
            --ptr;
            if (count > 0)
            {
                out << "\n";
            }
        }
    };
    print(stack.m_stack.get() + stack.m_size - 1, stack.m_size);
    return out;
}

// Friend functions definitions end here.

#endif // CUSTOMSTACK_H_INCLUDED
