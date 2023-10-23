#ifndef CUSTOMQUEUE_H_INCLUDED
#define CUSTOMQUEUE_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list, std::exception
#include <iterator> // std::forward_iterator_tag
#include "CustomLinkedList.h"

/*
 *
 * File:    CustomQueue.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom queue container in the form of a class template CustomLinkedList.
 *   Member functions of the class are available to add, remove, or manipulate data.
 *   The queue is double-ended, meaning additions and removals can be done from both the front and back.
 *
 *   The template class has been tested with the following data types:
 *     * Integers
 *     * Floats
 *     * Doubles
 *     * Characters
 *     * C++ strings (std::string)
 *
 */


// Forward declarations of class template CustomQueue and associated friend functions begin here.
// Required to support class template functionality.

/*
 *
 *   Class Name: CustomQueue
 *
 *   Purpose:
 *
 *     A custom queue container class template.
 *
 *   Member Variables:
 *
 *     m_head_ptr
 *       A pointer of type Node that is pointing to the first node in the CustomQueue.
 *     m_tail_ptr
 *       A pointer of type Node that is pointing to the last node in the CustomQueue.
 *     m_length
 *       An unsigned integer (std::size_t) that tracks the number of nodes within the CustomQueue.
 *
 *   Member Functions:
 *
 *     display
 *       Prints the queue data to the specified output stream.
 *     deepCopy
 *       Performs a deep copy of another queue (inherited from CustomLinkedList).
 *     size
 *       Returns the length of the queue.
 *     empty
 *       Returns true for a queue that has length equal to zero.
 *     clear
 *       Removes all nodes from memory and the queue.
 *     pushFront
 *       Adds a new node with the specified value to the front of the queue.
 *     popFront
 *       Removes an existing node from the front of the queue.
 *     pushBack
 *       Adds a new node with the specified value to the end of the queue.
 *     popBack
 *       Removes an existing node from the back of the queue.
 *     swap
 *       Swaps queue nodes with another queue.
 *
 */
template <typename T>
class CustomQueue;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, const CustomLinkedList<T>& list);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomQueue queue object.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privaleges within the CustomQueue class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomQueue<T>& queue);


// Forward declarations of class CustomQueue and associated friend functions end here.


template <typename T>
class CustomQueue : private CustomLinkedList<T>
{
private:

    /*
     *
     * std::ostream& display(std::ostream& out) const;
     *
     * Summary:
     *
     *   Prints the queue data to the terminal.
     *
     * Parameters   : std::ostream& out
     *
     * Return Value : std::ostream& out
     *
     * Description:
     *
     *   Prints the data member variable of each CustomQueue Node to the terminal.
     *   Called by the overloaded operator << friend function.
     *
     * Example Output:
     *   1 - 2 - 3 - 4 - 5
     *
     */
    std::ostream& display(std::ostream& out) const { return CustomLinkedList<T>::display(out); }
public:

    // An overloaded default constructor that writes a message to the standard output.
    CustomQueue() noexcept;

    /*
     *
     * CustomQueue(std::initializer_list<T> elements) noexcept;
     *
     * Summary:
     *
     *   Initialises a queue from a std::initializer_list.
     *
     * Parameters: std::initializer_list<T> elements
     *
     * Description:
     *
     *   Copies the values of a std::initializer_list to a series of linked-list nodes.
     *   Works with the move assigment overload to allow allow assignment from a std::initializer_list.
     *
     */
    CustomQueue(std::initializer_list<T> elements) noexcept;

    /*
     *
     * CustomQueue(const CustomQueue<T>& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a queue from another queue.
     *
     * Parameters: CustomQueue<T>& other
     *
     * Description:
     *
     *   Allocates a new portion of memory equal in size and structure to the other queue.
     *   Using deepCopy, copies the values of the other queue to the newly allocated memory.
     *
     */
    CustomQueue(const CustomQueue<T>& other) noexcept;

    /*
     *
     * CustomQueue(CustomQueue<T>&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a queue from another queue, using move semantics.
     *
     * Parameters   : CustomQueue<T>&& other
     *
     * Description:
     *
     *   Switches the memory addreses of the queue and other queue pointers.
     *   Sets the pointer addresses of the queue other to nullptr.
     *
     */
    CustomQueue(CustomQueue<T>&& other) noexcept;

    /*
     *
     * template <typename InputIterator>
     * CustomQueue(InputIterator first, InputIterator last);
     *
     * Summary:
     *
     *   Initialises a queue from another standard library container.
     *
     * Parameters   : InputIterator first, InputIterator last
     *
     * Description:
     *
     *   Uses two iterators that are compatible with containers in the standard library.
     *   Copies the data within a standard library container to a series of queue nodes.
     *
     */
    template <typename InputIterator>
    CustomQueue(InputIterator first, InputIterator last) noexcept;

    /*
     *
     * ~CustomQueue() noexcept;
     *
     * Summary:
     *
     *   Frees each queue node in memory before destoying the queue.
     *
     * Description:
     *
     *   Uses clear to erase all queue nodes before destroying the queue.
     *
     */
    ~CustomQueue() noexcept;

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
    const T& operator[](int index) const { return CustomLinkedList<T>::operator[](index); }

    /*
     *
     * CustomQueue& operator=(const CustomQueue<T>& other);
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
     *   Allocates a new portion of memory equal in size and structure to the other queue.
     *   Using deepCopy, copies the values of the other queue to the newly allocated memory.
     *
     */
    CustomQueue& operator=(const CustomQueue<T>& other);

    /*
     *
     * CustomQueue& operator=(CustomQueue<T>&& other);
     *
     * Summary:
     *
     *   Move assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Switches pointer addresses with the temporary/anonymous queue object other.
     *
     */
    CustomQueue& operator=(CustomQueue<T>&& other);

    // Inherited public member functions.
    // Explicitly declared because of CustomQueue's private inheritence from CustomLinkedList.
    std::size_t size() { return CustomLinkedList<T>::m_length; }
    bool empty() const { return !CustomLinkedList<T>::m_length; }
    void clear() { return CustomLinkedList<T>::clear(); }
    void pushFront(const T& value) { return CustomLinkedList<T>::pushFront(value); }
    void popFront() { return CustomLinkedList<T>::popfront(); }
    void pushBack(const T& value) { return CustomLinkedList<T>::pushBack(value); }
    void popBack() { return CustomLinkedList<T>::popBack(); }
    void swap(CustomQueue<T>& other) { return CustomLinkedList<T>::swap(other); }

    typename CustomLinkedList<T>::Iterator begin() { return CustomLinkedList<T>::begin(); }
    typename CustomLinkedList<T>::Iterator end() { return CustomLinkedList<T>::end(); }
    typename CustomLinkedList<T>::ConstIterator begin() const { return CustomLinkedList<T>::begin(); }
    typename CustomLinkedList<T>::ConstIterator end() const { return CustomLinkedList<T>::end(); }

    friend std::ostream& operator<<<T>(std::ostream& out, const CustomQueue<T>& queue);
};

// Private member function definitions begin here.

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
CustomQueue<T>::CustomQueue() noexcept
    : CustomLinkedList<T>{}
{
    std::cout << "CustomQueue default constructor called.\n";
}

template <typename T>
CustomQueue<T>::CustomQueue(std::initializer_list<T> elements) noexcept
    : CustomLinkedList<T>{ elements }
{
    std::cout << "CustomQueue list-initialised constructor called.\n";
}

template <typename T>
CustomQueue<T>::CustomQueue(const CustomQueue<T>& other) noexcept
    : CustomLinkedList<T>{ other }
{
    std::cout << "CustomQueue copy constructor called.\n";
}

template <typename T>
CustomQueue<T>::CustomQueue(CustomQueue<T>&& other) noexcept
    : CustomLinkedList<T>{ std::move(other) }
{
    std::cout << "CustomQueue move constructor called.\n";
}

template <typename T>
template <typename InputIterator>
CustomQueue<T>::CustomQueue(InputIterator first, InputIterator last) noexcept
    : CustomLinkedList<T>{ first, last }
{
    std::cout << "CustomQueue (iterator) copy constructor called.\n";
}

template <typename T>
CustomQueue<T>::~CustomQueue() noexcept
{
    std::cout << "CustomQueue destructor called.\n";
    // return CustomLinkedList<T>::~CustomLinkedList{};
}

// Constructors and Destructors end here.

// Operator overload definitions begin here.

template <typename T>
CustomQueue<T>& CustomQueue<T>::operator=(const CustomQueue<T>& other)
{
    std::cout << "CustomQueue copy assignment operator called.\n";
    CustomLinkedList<T>::operator=(other);
    return *this;
}

template <typename T>
CustomQueue<T>& CustomQueue<T>::operator=(CustomQueue<T>&& other)
{
    std::cout << "CustomQueue move assignment operator called.\n";
    CustomLinkedList<T>::operator=(std::move(other));
    return *this;
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

// Public member function definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomQueue<T>& queue)
{
    return queue.display(out);
}

// Friend functions definitions end here.

#endif // CUSTOMQUEUE_H_INCLUDED
