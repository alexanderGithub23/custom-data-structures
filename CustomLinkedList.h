#ifndef CUSTOMLINKEDLIST_H_INCLUDED
#define CUSTOMLINKEDLIST_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list, std::exception
#include <iterator> // std::forward_iterator_tag


/*
 *
 * File:    CustomLinkedLinked.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom linked-list container in the form of a class template CustomLinkedList.
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


// Forward declarations of class template CustomLinkedList and associated friend functions begin here.
// Required to support class template functionality.


/*
 *
 *   Class Name: CustomLinkedList
 *
 *   Purpose:
 *
 *     A custom linked-list container class template.
 *
 *   Member Variables:
 *
 *     m_head_ptr
 *       A pointer of type Node that is pointing to the first node in the CustomLinkedList.
 *     m_tail_ptr
 *       A pointer of type Node that is pointing to the last node in the CustomLinkedList.
 *     m_length
 *       An unsigned integer (std::size_t) that tracks the number of nodes within the CustomLinkedList.
 *
 *   Member Functions:
 *
 *     display
 *       Prints the linked-list data to the specified output stream.
 *     deepCopy
 *       Performs a deep copy of another linked-list.
 *     size
 *       Returns the length of the linked-list.
 *     empty
 *       Returns true for a linked-list that has length equal to zero.
 *     clear
 *       Removes all nodes from memory and the linked-list.
 *     insert
 *       Inserts a new node into the linked-list with specified data (value) and index (position).
 *     erase
 *       Removes an existing node at the specified position from the linked-list.
 *     pushFront
 *       Adds a new node with the specified value to the front of the linked-list.
 *     popFront
 *       Removes an existing node from the front of the linked-list.
 *     pushBack
 *       Adds a new node with the specified value to the end of the linked-list.
 *     popBack
 *       Removes an existing node from the back of the linked-list.
 *     reverse
 *       Reverses the order of the linked-list nodes in place.
 *     linearSearch
 *       Searches linearly for the specified value.
 *     bubbleSort
 *       Sorts the linked-list in ascending order using the bubblesort algorithm.
 *     unique
 *       Produces a unique set of items in the linked-list.
 *     remove
 *       Deletes all instances of value from the linked-list.
 *     swap
 *       Swaps linked-list nodes with another linked-list.
 *
 */
template <typename T>
class CustomLinkedList;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, const CustomLinkedList<T>& list);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomLinkedList linked-list object.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privileges within the CustomLinkedList class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomLinkedList<T>& list);

/*
 *
 * template <typename T>
 * CustomLinkedList<T> merge(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);
 *
 * Summary:
 *
 *    Combines and sorts (ascending) two linked-lists.
 *
 * Return Value: tmp
 *
 * Description:
 *
 *   Function to merge two linked-lists that has friend privileges within the CustomLinkedList class.
 *   Node data for both linked-lists is sorted into ascending order.
 *   Returns the combined linked-list by value.
 *
 */
template <typename T>
CustomLinkedList<T> merge(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);

/*
 *
 * template <typename T>
 * CustomLinkedList<T> setUnion(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);
 *
 * Summary:
 *
 *    Returns the set that is the union of two linked-lists.
 *
 * Return Value: tmp
 *
 * Description:
 *
 *   Function to return the union of two linked-lists that has friend privileges within the CustomLinkedList class.
 *   Node data for both linked-lists is sorted into ascending order.
 *   Returns the new linked-list by value.
 *
 */
template <typename T>
CustomLinkedList<T> setUnion(CustomLinkedList<T> a, CustomLinkedList<T> b);

/*
 *
 * template <typename T>
 * CustomLinkedList<T> setDifference(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);
 *
 * Summary:
 *
 *    Returns the set that is the difference (relative compliment) between two linked-lists.
 *
 * Return Value: tmp
 *
 * Description:
 *
 *   Function to return difference between two linked-lists that has friend privileges within the CustomLinkedList class.
 *   Node data for both linked-lists is sorted into ascending order.
 *   Returns the new linked-list by value.
 *
 */
template <typename T>
CustomLinkedList<T> setDifference(CustomLinkedList<T> a, CustomLinkedList<T> b);

/*
 *
 * template <typename T>
 * CustomLinkedList<T> setIntersection(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);
 *
 * Summary:
 *
 *    Returns the set that is the intersection of two linked-lists.
 *
 * Return Value: tmp
 *
 * Description:
 *
 *   Function to return the intersection of two linked-lists that has friend privileges within the CustomLinkedList class.
 *   Node data for both linked-lists is sorted into ascending order.
 *   Returns the new linked-list by value.
 *
 */
template <typename T>
CustomLinkedList<T> setIntersection(CustomLinkedList<T> a, CustomLinkedList<T> b);


// Forward declarations of class CustomLinkedList and associated friend functions end here.


template <typename T>
class CustomLinkedList
{
protected:

    struct Node
    {
        T data{};
        Node* prev_ptr{};
        Node* next_ptr{};
    };

    Node* m_head_ptr{};
    Node* m_tail_ptr{};
    std::size_t m_length{};

    /*
     *
     * std::ostream& display(std::ostream& out) const;
     *
     * Summary:
     *
     *   Prints the linked-list data to the terminal.
     *
     * Parameters   : std::ostream& out
     *
     * Return Value : std::ostream& out
     *
     * Description:
     *
     *   Prints the data member variable of each CustomLinkedList Node to the terminal.
     *   Called by the overloaded operator << friend function.
     *
     * Example Output:
     *   1 - 2 - 3 - 4 - 5
     *
     */
    std::ostream& display(std::ostream& out) const;

    /*
     *
     * void deepCopy(const CustomLinkedList& other);
     *
     * Summary:
     *
     *   Performs a deep copy of another linked-list.
     *
     * Parameters   : CustomLinkedList<T>& other
     *
     * Return Value : None
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other linked-list.
     *   Copies the values of the other linked-list to the newly allocated memory.
     *   Called by the CustomLinkedList copy constructor and overloaded copy assignment member function.
     *
     */
    void deepCopy(const CustomLinkedList<T>& other);

public:

    // An overloaded default constructor that writes a message to the standard output.
    CustomLinkedList() noexcept;

    /*
     *
     * CustomLinkedList(std::initializer_list<T> elements) noexcept;
     *
     * Summary:
     *
     *   Initialises a linked-list from a std::initializer_list.
     *
     * Parameters: std::initializer_list<T> elements
     *
     * Description:
     *
     *   Copies the values of a std::initializer_list to a series of linked-list nodes.
     *
     */
    CustomLinkedList(std::initializer_list<T> elements) noexcept;

    /*
     *
     * CustomLinkedList(const CustomLinkedList<T>& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a linked-list from another linked-list.
     *
     * Parameters: CustomLinkedList<T>& other
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other linked-list.
     *   Using deepCopy, copies the values of the other linked-list to the newly allocated memory.
     *
     */
    CustomLinkedList(const CustomLinkedList<T>& other) noexcept;

    /*
     *
     * CustomLinkedList(CustomLinkedList<T>&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a linked-list from another linked-list, using move semantics.
     *
     * Parameters   : CustomLinkedList<T>&& other
     *
     * Description:
     *
     *   Switches the memory addresses of the linked-list and other linked-list pointers.
     *   Sets the pointer addresses of the linked-list other to nullptr.
     *
     */
    CustomLinkedList(CustomLinkedList<T>&& other) noexcept;

    /*
     *
     * template <typename InputIterator>
     * CustomLinkedList(InputIterator first, InputIterator last);
     *
     * Summary:
     *
     *   Initialises a linked-list from another standard library container.
     *
     * Parameters   : InputIterator first, InputIterator last
     *
     * Description:
     *
     *   Uses two iterators that are compatible with containers in the standard library.
     *   Copies the data within a standard library container to a series of linked-list nodes.
     *
     */
    template <typename InputIterator>
    CustomLinkedList(InputIterator first, InputIterator last) noexcept;

    /*
     *
     * ~CustomLinkedList() noexcept;
     *
     * Summary:
     *
     *   Frees each linked-list node in memory before destroying the linked-list.
     *
     * Description:
     *
     *   Uses clear to erase all linked-list nodes before destroying the linked-list.
     *
     */
    ~CustomLinkedList() noexcept;

    /*
     *
     * CustomLinkedList& operator=(const CustomLinkedList<T>& other);
     *
     * Summary:
     *
     *   Copy assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Clears the existing linked-list.
     *   Allocates a new portion of memory equal in size and structure to the other linked-list.
     *   Using deepCopy, copies the values of the other linked-list to the newly allocated memory.
     *
     */
    CustomLinkedList& operator=(const CustomLinkedList<T>& other);

    /*
     *
     * CustomLinkedList& operator=(CustomLinkedList<T>&& other);
     *
     * Summary:
     *
     *   Move assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Switches pointer addresses with the temporary/anonymous linked-list object other.
     *
     */
    CustomLinkedList& operator=(CustomLinkedList<T>&& other);

    /*
     *
     * CustomLinkedList& operator=(std::initializer_list<T> elements);
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
     *   Creates a temporary linked-list with the std::initializer_list values.
     *   Switches pointer addresses with the temporary linked-list.
     *
     */
    CustomLinkedList& operator=(std::initializer_list<T> elements);

    /*
     *
     * T& operator[](int index);
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: it->data
     *
     * Description:
     *
     *   Uses an iterator it of type Iterator to return data from the node at the the specified index.
     *   Support negative indexing!
     *
     */
    T& operator[](int index);

    /*
     *
     * const T& operator[](int index) const;
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: it->data
     *
     * Description:
     *
     *   Uses an iterator it of type ConstIterator to return data from the node at the the specified index.
     *   Support negative indexing!
     *
     */
    const T& operator[](int index) const;

    std::size_t size() const { return m_length; }
    bool empty() const { return !m_length; }

    /*
     *
     * void clear();
     *
     * Summary:
     *
     *   Removes all nodes from memory and the linked-list.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Removes the front node of the linked-list from memory until there are no nodes remaining.
     *
     */
    void clear();

    /*
     *
     * void insert(int position, const T& value);
     *
     * Summary:
     *
     *   Inserts a new node into the linked-list with specified data (value) and index (position).
     *
     * Parameters   : int position, const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a new node in memory with data equal to the value given.
     *   Links pointers of the nodes before and after to the newly created node.
     *
     */
    void insert(int position, const T& value);

    /*
     *
     * void erase(int position);
     *
     * Summary:
     *
     *   Removes an existing node at the specified position from the linked-list.
     *
     * Parameters   : int position
     *
     * Return Value : None
     *
     * Description:
     *
     *   Removes the specified node from memory.
     *   Points the node before to node immediately after the specified position.
     *
     */
    void erase(int position);

    /*
     *
     * void pushFront(const T& value);
     *
     * Summary:
     *
     *   Adds a new node with the specified value to the front of the linked-list.
     *
     * Parameters   : const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a new node in memory with data equal to the value given.
     *   Links pointers of the first node to the newly created node.
     *   Updates the linked-list head pointer to point to the new node.
     *
     */
    void pushFront(const T& value);

    /*
     *
     * void popFront();
     *
     * Summary:
     *
     *   Removes an existing node from the front of the linked-list.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Unlinks the first node and removes it from memory.
     *   Updates the linked-list head pointer to the new first node.
     *
     */
    void popFront();

    /*
     *
     * void pushBack(const T& value);
     *
     * Summary:
     *
     *   Adds a new node with the specified value to the end of the linked-list.
     *
     * Parameters   : const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Creates a new node in memory with data equal to the value given.
     *   Links pointers of the last node to the newly created node.
     *   Updates the linked-list tail pointer to point to the new node.
     *
     */
    void pushBack(const T& value);

    /*
     *
     * void popBack();
     *
     * Summary:
     *
     *   Removes an existing node from the back of the linked-list.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Unlinks the last node and removes it from memory.
     *   Updates the linked-list tail pointer to what was the second last node.
     *
     */
    void popBack();

    /*
     *
     * void reverse();
     *
     * Summary:
     *
     *   Reverses the order of the linked-list nodes in place.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Switches the address that each node's prev and next pointers are pointing to.
     *
     */
    void reverse();

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
     * Return Value : bool 1 or bool 0
     *
     * Description:
     *
     *   Beginning at the head of the linked-list, searches linearly for the specified value.
     *   Returns true (1) if a node's data member variable is equal to value.
     *   Returns false (0) otherwise.
     *
     */
    bool linearSearch(const T& value);

    /*
     *
     * void bubbleSort();
     *
     * Summary:
     *
     *   Sorts the linked-list in ascending order using the bubblesort algorithm.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Sorts the linked-list in ascending order using the bubblesort algorithm.
     *   Switches the data of two nodes when the algorithm requires re-ordering.
     *
     */
    void bubbleSort();

    /*
     *
     * void unique();
     *
     * Summary:
     *
     *   Removes adjacent duplicates from the linked-list.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Iterates through the linked-list.
     *   Removes a node from the linked-list if the node data matches the previous node's data.
     *
     */
    void unique();

    /*
     *
     * void remove(const T& value);
     *
     * Summary:
     *
     *   Deletes all instances of value from the linked-list.
     *
     * Parameters   : const T& value
     *
     * Return Value : None
     *
     * Description:
     *
     *   Iterates through the linked-list.
     *   Removes a node from the linked-list if the node data the specified value.
     *
     */
    void remove(const T& value);

    /*
     *
     * void swap(CustomLinkedList<T>& other);
     *
     * Summary:
     *
     *   Swaps linked-list nodes with another linked-list.
     *
     * Parameters   : CustomLinkedList<T>& other
     *
     * Return Value : None
     *
     * Description:
     *
     *   Switches the head and tail pointers of the linked-list with other.
     *
     */
    void swap(CustomLinkedList<T>& other);

    friend std::ostream& operator<<<T>(std::ostream& out, const CustomLinkedList<T>& list);
    friend CustomLinkedList<T> merge<T>(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b);
    friend CustomLinkedList<T> setUnion<T>(CustomLinkedList<T> a, CustomLinkedList<T> b);
    friend CustomLinkedList<T> setDifference<T>(CustomLinkedList<T> a, CustomLinkedList<T> b);
    friend CustomLinkedList<T> setIntersection<T>(CustomLinkedList<T> a, CustomLinkedList<T> b);

    /*
     *
     *   Class Name: Iterator
     *
     *   Purpose:
     *     A bidirectional non-const iterator for CustomLinkedList<T> objects.
     *
     */
    class Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = Node*;
        using reference = Node&;
    private:
        pointer m_ptr;
    public:
        Iterator(pointer ptr = nullptr) : m_ptr{ ptr } {}
        Iterator(const Iterator& other) : m_ptr{ other.m_ptr } {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        Iterator& operator++() { m_ptr = m_ptr->next_ptr; return *this; }
        Iterator operator++(int) { Iterator tmp{ *this }; ++(*this); return tmp; }
        Iterator& operator--() { m_ptr = m_ptr->prev_ptr; return *this; }
        Iterator operator--(int) { Iterator tmp{ *this }; --(*this); return tmp; }
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
    };

    Iterator begin() { return Iterator{ m_head_ptr }; }
    Iterator end() { return Iterator{ m_tail_ptr->next_ptr }; }

    /*
     *
     *   Class Name: ConstIterator
     *
     *   Purpose:
     *     A bidirectional const iterator for const CustomLinkedList<T> objects.
     *
     */
    class ConstIterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const Node*;
        using reference = const Node&;
    private:
        pointer m_ptr;
    public:
        ConstIterator(pointer ptr = nullptr) : m_ptr{ ptr } {}
        ConstIterator(const ConstIterator& other) : m_ptr{ other.m_ptr } {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        ConstIterator& operator++() { m_ptr = m_ptr->next_ptr; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp{ *this }; ++(*this); return tmp; }
        ConstIterator& operator--() { m_ptr = m_ptr->prev_ptr; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp{ *this }; --(*this); return tmp; }
        friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; }
    };

    ConstIterator begin() const { return ConstIterator{ m_head_ptr }; }
    ConstIterator end() const { return ConstIterator{ m_tail_ptr->next_ptr }; }

};

// Private member function definitions begin here.

template <typename T>
void CustomLinkedList<T>::deepCopy(const CustomLinkedList<T>& other)
{
    if (other.m_head_ptr)
    {
        m_head_ptr = m_tail_ptr = new Node{ other.m_head_ptr->data, nullptr, nullptr };
        Node* current_ptr{ other.m_head_ptr->next_ptr };
        while (current_ptr)
        {
            m_tail_ptr = m_tail_ptr->next_ptr = new Node{ current_ptr->data, m_tail_ptr, nullptr };
            current_ptr = current_ptr->next_ptr;
        }
    }
}

template <typename T>
std::ostream& CustomLinkedList<T>::display(std::ostream& out) const
{
    if (m_head_ptr && m_tail_ptr)
    {

        for (auto it{ begin() }; it != end(); ++it)
        {
            if (it == m_tail_ptr)
            {
                out << it->data;
            }
            else
            {
                out << it->data << " - ";
            }
        }
    }
    return out;
}

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
CustomLinkedList<T>::CustomLinkedList() noexcept
{
    std::cout << "CustomLinkedList default constructor called.\n";
}

template <typename T>
CustomLinkedList<T>::CustomLinkedList(const CustomLinkedList<T>& other) noexcept
    : m_length { other.m_length }
{
    std::cout << "CustomLinkedList copy constructor called.\n";
    deepCopy(other);
}

template <typename T>
CustomLinkedList<T>::CustomLinkedList(CustomLinkedList<T>&& other) noexcept
    : m_length { other.m_length }
{
    std::cout << "CustomLinkedList move constructor called.\n";
    m_head_ptr = other.m_head_ptr;
    other.m_head_ptr = nullptr;
    m_tail_ptr = other.m_tail_ptr;
    other.m_tail_ptr = nullptr;
    other.m_length = 0;
}

template <typename T>
CustomLinkedList<T>::CustomLinkedList(std::initializer_list<T> elements) noexcept
    : m_length { elements.size() }
{
    std::cout << "CustomLinkedList list-initialised constructor called.\n";
    auto* elem_it{ elements.begin() };
    m_head_ptr = m_tail_ptr = new Node{ *elem_it, nullptr, nullptr };
    ++elem_it;
    while (elem_it != elements.end())
    {
        m_tail_ptr = m_tail_ptr->next_ptr = new Node{ *elem_it, m_tail_ptr, nullptr };
        ++elem_it;
    }
}

template <typename T>
template <typename InputIterator>
CustomLinkedList<T>::CustomLinkedList(InputIterator first, InputIterator last) noexcept
{
    std::cout << "CustomLinkedList (iterator) copy constructor called.\n";
    if (first != last)
    {
        m_head_ptr = m_tail_ptr = new Node { *first, nullptr, nullptr };
        ++m_length;
        while (++first != last)
        {
            m_tail_ptr = m_tail_ptr->next_ptr = new Node {*first, m_tail_ptr, nullptr };
            ++m_length;
        }
    }
}

template <typename T>
CustomLinkedList<T>::~CustomLinkedList() noexcept
{
    std::cout << "CustomLinkedList destructor called.\n";
    clear();
}

// Constructors and Destructors end here.

// Operator overload definitions begin here.

template <typename T>
CustomLinkedList<T>& CustomLinkedList<T>::operator=(const CustomLinkedList<T>& other)
{
    std::cout << "Overloaded copy assignment operator called.\n";
    clear();
    deepCopy(other);
    m_length = other.m_length;
    return *this;
}

template <typename T>
CustomLinkedList<T>& CustomLinkedList<T>::operator=(CustomLinkedList<T>&& other)
{
    std::cout << "Overloaded move assignment operator called.\n";
    swap(other);
    return *this;
}

template <typename T>
CustomLinkedList<T>& CustomLinkedList<T>::operator=(std::initializer_list<T> elements)
{
    std::cout << "Overloaded assignment operator (list-initialised) called.\n";
    CustomLinkedList<T> tmp{ elements };
    swap(tmp);
    return *this;
}

template <typename T>
T& CustomLinkedList<T>::operator[](int index)
{
    if (index > static_cast<int>(m_length) - 1) { return m_tail_ptr->data; }

    auto it{ begin() };

    if (index < 0)
    {
        index = static_cast<int>(m_length) - (abs(index) % static_cast<int>(m_length));
    }

    while (index-- > 0) { ++it; }
    return it->data;
}

template <typename T>
const T& CustomLinkedList<T>::operator[](int index) const
{
    if (index > static_cast<int>(m_length) - 1) { return m_tail_ptr->data; }

    auto it{ begin() };

    if (index < 0)
    {
        index = static_cast<int>(m_length) - (abs(index) % static_cast<int>(m_length));
    }

    while (index-- > 0) { ++it; }
    return it->data;
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

template <typename T>
void CustomLinkedList<T>::clear()
{
    while (m_head_ptr)
    {
        popFront();
    }
    m_head_ptr = m_tail_ptr = nullptr;
    m_length = 0;
}

template <typename T>
void CustomLinkedList<T>::pushFront(const T& value)
{
    m_head_ptr = new Node{ value, nullptr, m_head_ptr };
    if (!m_tail_ptr)
    {
        m_tail_ptr = m_head_ptr;
    }
    else
    {
        m_head_ptr->next_ptr->prev_ptr = m_head_ptr;
    }
    ++m_length;
}

template <typename T>
void CustomLinkedList<T>::pushBack(const T& value)
{
    Node* node{ new Node{ value, m_tail_ptr, nullptr } };
    if (m_tail_ptr)
    {
        m_tail_ptr = m_tail_ptr->next_ptr = node;
    }
    else
    {
        m_head_ptr = m_tail_ptr = node;
    }
    ++m_length;
}

template <typename T>
void CustomLinkedList<T>::popFront()
{
    if (m_length == 1 && m_head_ptr == m_tail_ptr)
    {
        delete m_head_ptr;
        m_head_ptr = m_tail_ptr = nullptr;
        --m_length;
    }
    else if (m_length > 1 && m_head_ptr != m_tail_ptr)
    {
        Node* trailing_ptr{ m_head_ptr };
        m_head_ptr = m_head_ptr->next_ptr;
        delete trailing_ptr;
        trailing_ptr = nullptr;
        m_head_ptr->prev_ptr = nullptr;
        --m_length;
    }
    else
    {
        return;
    }
}

template <typename T>
void CustomLinkedList<T>::popBack()
{
    if (m_head_ptr == m_tail_ptr)
    {
        popFront();
    }
    else
    {
        Node* trailing_ptr{ m_tail_ptr };
        m_tail_ptr = m_tail_ptr->prev_ptr;
        delete trailing_ptr;
        m_tail_ptr->next_ptr = nullptr;
        --m_length;
    }
}

template <typename T>
void CustomLinkedList<T>::insert(int position, const T& value)
{
    if (position <= 0)
    {
        pushFront(value);
    }
    else if (position >= static_cast<int>(m_length))
    {
        pushBack(value);
    }
    else
    {
        Node* ptr{ m_head_ptr };
        while (--position)
        {
            ptr = ptr->next_ptr;
        }
        Node* node{ new Node{ value, ptr, ptr->next_ptr } };
        ptr->next_ptr = ptr->next_ptr->prev_ptr = node;
        ptr = nullptr;
        ++m_length;
    }
}

template <typename T>
void CustomLinkedList<T>::erase(int position)
{
    if (position <= 0)
    {
        popFront();
    }
    else if (position >= static_cast<int>(m_length) - 1)
    {
        popBack();
    }
    else
    {
        Node* ptr{ m_head_ptr };
        while (position--)
        {
            ptr = ptr->next_ptr;
        }
        ptr->prev_ptr->next_ptr = ptr->next_ptr;
        ptr->next_ptr->prev_ptr = ptr->prev_ptr;
        delete ptr;
        ptr = nullptr;
        --m_length;
    }
}

template <typename T>
void CustomLinkedList<T>::reverse()
{
    Node* ptr{ m_head_ptr };
    while (ptr)
    {
        Node* temp_ptr{ ptr->next_ptr };
        ptr->next_ptr = ptr->prev_ptr;
        ptr->prev_ptr = temp_ptr;
        if (!temp_ptr)
        {
            m_tail_ptr = m_head_ptr;
            m_head_ptr = ptr;
        }
        ptr = temp_ptr;
    }
}

template <typename T>
bool CustomLinkedList<T>::linearSearch(const T& value)
{
    for (auto it{ begin() }; it != end(); ++it)
    {
        if (it->data == value)
        {
            return 1;
        }
    }
    return 0;
}

template <typename T>
void CustomLinkedList<T>::bubbleSort()
{
    if (m_head_ptr != m_tail_ptr)
    {
        bool swapped{ 1 };
        Node* switching_ptr{ m_head_ptr };
        Node* last_ptr{ m_tail_ptr->next_ptr };
        do
        {
            swapped = 0;
            switching_ptr = m_head_ptr;
            while (switching_ptr->next_ptr != last_ptr)
            {
                if (switching_ptr->data > switching_ptr->next_ptr->data)
                {
                    std::swap(switching_ptr->data, switching_ptr->next_ptr->data);
                    swapped = 1;
                }
                switching_ptr = switching_ptr->next_ptr;
            }
            last_ptr = switching_ptr;
        }
        while (swapped);
    }
}

template <typename T>
void CustomLinkedList<T>::unique()
{
    if (m_head_ptr != m_tail_ptr)
    {
        Node* ptr{ m_head_ptr->next_ptr };
        while (ptr)
        {
            if (ptr->data == ptr->prev_ptr->data && ptr->next_ptr)
            {
                Node* temp_ptr{ ptr->next_ptr };
                ptr->prev_ptr->next_ptr = ptr->next_ptr;
                ptr->next_ptr->prev_ptr = ptr->prev_ptr;
                delete ptr;
                ptr = temp_ptr;
                temp_ptr = nullptr;
                --m_length;
            }
            else if (ptr->data == ptr->prev_ptr->data && !ptr->next_ptr)
            {
                ptr = ptr->next_ptr;
                popBack();
            }
            else
            {
                ptr = ptr->next_ptr;
            }
        }
    }
}

template <typename T>
void CustomLinkedList<T>::remove(const T& value)
{
    if (m_head_ptr != m_tail_ptr)
    {
        Node* ptr{ m_head_ptr->next_ptr };
        while (ptr)
        {
            if (ptr->data == value && ptr->next_ptr)
            {
                Node* temp_ptr{ ptr->next_ptr };
                ptr->prev_ptr->next_ptr = ptr->next_ptr;
                ptr->next_ptr->prev_ptr = ptr->prev_ptr;
                delete ptr;
                ptr = temp_ptr;
                temp_ptr = nullptr;
                --m_length;
            }
            else if (ptr->data == value && !ptr->next_ptr)
            {
                ptr = ptr->next_ptr;
                popBack();
            }
            else
            {
                ptr = ptr->next_ptr;
            }
        }
    }
    if (m_head_ptr->data == value) { popFront(); }
}

template <typename T>
void CustomLinkedList<T>::swap(CustomLinkedList<T>& other)
{
    std::swap(m_head_ptr, other.m_head_ptr);
    std::swap(m_tail_ptr, other.m_tail_ptr);
    std::swap(m_length, other.m_length);
}

// Public member function definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomLinkedList<T>& list)
{
    return list.display(out);
}

template <typename T>
CustomLinkedList<T> merge(const CustomLinkedList<T>& a, const CustomLinkedList<T>& b)
{
    auto i{ a.begin() };
    auto j{ b.begin() };
    CustomLinkedList<T> tmp{};
    while (i != a.end() && j != a.end())
    {
        if (i->data < j->data)
        {
            tmp.pushBack(i->data);
            ++i;
        }
        else
        {
            tmp.pushBack(j->data);
            ++j;
        }
    }
    for (; i != a.end(); ++i) { tmp.pushBack(i->data); }
    for (; j != b.end(); ++j) { tmp.pushBack(j->data); }
    return tmp;
}

template <typename T>
CustomLinkedList<T> setUnion(CustomLinkedList<T> a, CustomLinkedList<T> b)
{
    a.bubbleSort();
    b.bubbleSort();
    auto i{ a.begin() };
    auto j{ b.begin() };
    CustomLinkedList<T> tmp{};
    while (i != a.end() && j != b.end())
    {
        if (i->data < j->data)
        {
            tmp.pushBack(i->data);
            ++i;
        }
        else if (i->data > j->data)
        {
            tmp.pushBack(j->data);
            ++j;
        }
        else if (i->data == j->data)
        {
            tmp.pushBack(i->data);
            ++i;
            ++j;
        }
    }
    for (; i != a.end(); ++i) { tmp.pushBack(i->data); }
    for (; j != b.end(); ++j) { tmp.pushBack(j->data); }
    return tmp;
}

template <typename T>
CustomLinkedList<T> setDifference(CustomLinkedList<T> a, CustomLinkedList<T> b)
{
    a.bubbleSort();
    b.bubbleSort();
    auto i{ a.begin() };
    auto j{ b.begin() };
    CustomLinkedList<T> tmp{};
    while (i != a.end() && j != b.end())
    {
        if (i->data < j->data)
        {
            tmp.pushBack(i->data);
            ++i;
        }
        else if (i->data > j->data)
        {
            ++j;
        }
        else if (i->data == j->data)
        {
            ++i;
            ++j;
        }
    }
    for (; i != a.end(); ++i) { tmp.pushBack(i->data); }
    return tmp;
}

template <typename T>
CustomLinkedList<T> setIntersection(CustomLinkedList<T> a, CustomLinkedList<T> b)
{
    a.bubbleSort();
    b.bubbleSort();
    auto i{ a.begin() };
    auto j{ b.begin() };
    CustomLinkedList<T> tmp{};
    while (i != a.end() && j != b.end())
    {
        if (i->data < j->data)
        {
            ++i;
        }
        else if (i->data > j->data)
        {
            ++j;
        }
        else if (i->data == j->data)
        {
            tmp.pushBack(i->data);
            ++i;
            ++j;
        }
    }
    return tmp;
}

// Friend functions definitions end here.

#endif // CUSTOMLINKEDLIST_H_INCLUDED
