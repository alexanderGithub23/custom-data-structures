#ifndef CUSTOMSPARSEMATRIX_H_INCLUDED
#define CUSTOMSPARSEMATRIX_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list, std::out_of_range
#include <cassert>
#include "CustomLinkedList.h"

/*
 *
 * File:    CustomSparseMatrix.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom sparse matrix container in the form of a class template CustomSparseMatrix.
 *   Member functions of the class are available to add, remove, or manipulate data.
 *   Friend functions of the class are available to override the standard output stream operator <<.
 *
 *   The template class has been tested with the following data types:
 *     * Integers
 *     * Floats
 *     * Doubles
 *
 */


// Forward declarations of class template CustomLinkedList and associated friend functions begin here.
// Required to support class template functionality.

/*
 *
 *   Class Name: CustomSparseMatrix
 *
 *   Purpose:
 *
 *     A custom sparse matrix container class template.
 *
 *   Member Variables:
 *
 *     m_rows
 *       An unsigned integer (std::size_t) that tracks the number of rows in the sparse matrix.
 *     m_cols
 *       An unsigned integer (std::size_t) that tracks the number of columns in the sparse matrix.
 *     element
 *       A struct that contains the element data and location within the sparse matrix.
 *
 *   Member Functions:
 *
 *     display
 *       Prints the linked-list data to the specified output stream.
 *
 *     isSorted
 *
 *     insert
 *
 *     erase
 *
 *     bubbleSort
 *
 *
 */
template <typename T>
class CustomSparseMatrix;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, CustomSparseMatrix<T>& M);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomSparseMatrix sparse matrix object.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privaleges within the CustomSparseMatrix class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, CustomSparseMatrix<T>& M);

// Forward declaration of template friend functions ends here.

template <typename T>
class CustomSparseMatrix
{
private:

    std::size_t m_rows{};
    std::size_t m_cols{};

    struct element
    {
        int row{};
        int col{};
        T value{};
    };

    CustomLinkedList<element> m_matrix{};

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
     *   Prints the data member variable of each CustomSparseMatrix element to the terminal as part of a matrix.
     *   Called by the overloaded operator << friend function.
     *
     */
    std::ostream& display(std::ostream& out) const;

public:

    // CustomSparseMatrix objects must be constructed with parameters.
    CustomSparseMatrix() = delete;

    /*
     *
     * CustomSparseMatrix(std::size_t rows, std::size_t cols) noexcept;
     *
     * Summary:
     *
     *   Initialises a null matrix with defined size.
     *
     * Parameters: std::size_t rows, std::size_t cols
     *
     * Description:
     *
     *   Initialises a null matrix with defined size = rows x cols.
     *
     */
    CustomSparseMatrix(std::size_t rows, std::size_t cols) noexcept;

    /*
     *
     * CustomSparseMatrix(const CustomSparseMatrix<T>& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a sparse matrix from another sparse matrix.
     *
     * Parameters: CustomSparseMatrix<T>& other
     *
     * Description:
     *
     *   Fundamental data type member variables are initialised with copy values.
     *   The CustomLinkedList m_matrix is initialised using its copy constructor.
     *
     */
    CustomSparseMatrix(const CustomSparseMatrix<T>& other) noexcept;

    /*
     *
     * CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a matrix from another matrix.
     *
     * Parameters: CustomSparseMatrix<T>&& other
     *
     * Description:
     *
     *   Fundamental data type member variables are initialised with copy values.
     *   The CustomLinkedList m_matrix is initialised using its move constructor.
     *
     */
    CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept;

    // An overloaded destructor that writes a message to the standard output.
    ~CustomSparseMatrix() noexcept;

    /*
     *
     * void insert(int position, const element& e);
     *
     * Summary:
     *
     *   Inserts a new matrix element into the sparse matrix at the given position.
     *
     * Parameters   : int position, const element& e
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the CustomLinkedList insert member function.
     *   Inserts a new matrix element into the sparse matrix at the given position.
     *
     */
    void insert(int position, const element& e);

    /*
     *
     * void erase(int position);
     *
     * Summary:
     *
     *   Removes an existing element at the specified position from the sparse matrix.
     *
     * Parameters   : int position
     *
     * Return Value : None
     *
     * Description:
     *
     *   Calls the CustomLinkedList erase member function.
     *   Removes an existing element at the specified position from the sparse matrix.
     *
     */
    void erase(int position);

    /*
     *
     * void bubbleSort();
     *
     * Summary:
     *
     *   Sorts the sparse matrix in ascending order using the bubblesort algorithm.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Sorts the sparse matrix elements in ascending order using the bubblesort algorithm.
     *   Switches the data of two elements when the algorithm requires re-ordering.
     *
     */
    void bubbleSort();

    /*
     *
     * bool isSorted();
     *
     * Summary:
     *
     *   Function to state whether the sparse matrix elements are in ascending order or not.
     *
     * Parameters   : None
     *
     * Return Value : None
     *
     * Description:
     *
     *   Iterates through the sparse matrix.
     *   Returns false if an element is found to be larger than the next element to the right.
     *   Elements are considered sorted if they are in ascending order.
     *
     */
    bool isSorted();

    /*
     *
     * T operator()(int row, int col) const;
     *
     * Summary:
     *
     *   Parenthesis operator overload.
     *
     * Return Value: elem_it->value
     *
     * Description:
     *
     *   Returns the sparse matrix element data given a specified row and column.
     *
     */
    T operator()(int row, int col) const;

    /*
     *
     * element& operator[](int position);
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: m_matrix[position]
     *
     * Description:
     *
     *   Calls the CustomLinkedList index operator overload.
     *
     */
    element& operator[](int position);

    /*
     *
     * const element& operator[](int position) const;
     *
     * Summary:
     *
     *   Index operator overload.
     *
     * Return Value: m_matrix[position]
     *
     * Description:
     *
     *   Calls the CustomLinkedList index operator overload.
     *
     */
    const element& operator[](int position) const;

    /*
     *
     * CustomSparseMatrix& operator=(const CustomSparseMatrix<T>& other);
     *
     * Summary:
     *
     *   Copy assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Overloads the assignment operator from an l-value reference.
     *   Fundamental data types are copied from other.
     *   The CustomLinkedList m_matrix from other is copied using its own copy assignment overload.
     *
     */
    CustomSparseMatrix& operator=(const CustomSparseMatrix<T>& other);

    /*
     *
     * CustomSparseMatrix& operator=(CustomSparseMatrix<T>&& other);
     *
     * Summary:
     *
     *   Move assignment operator overload.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Overloads the assignment operator from an l-value reference.
     *   Fundamental data types are copied from other.
     *   The CustomLinkedList m_matrix from other is moved using its own move assignment overload.
     *
     */
    CustomSparseMatrix& operator=(CustomSparseMatrix<T>&& other);

    // Fully specialised template friend function declarations.
    friend std::ostream& operator<<<T>(std::ostream& out, CustomSparseMatrix<T>& M);
};

// Private member function definitions begin here.

template <typename T>
std::ostream& CustomSparseMatrix<T>::display(std::ostream& out) const
{
    if (!m_matrix.empty())
    {
        auto elem_it{ m_matrix.begin() };
        for (auto i{ 0 }; i < static_cast<int>(m_rows); ++i)
        {
            for (auto j{ 0 }; j < static_cast<int>(m_cols); ++j)
            {
                if ((elem_it != m_matrix.end()) && (i == elem_it->data.row) && (j == elem_it->data.col))
                {
                    out << elem_it->data.value << " ";
                    if (elem_it != m_matrix.end())
                    {
                        ++elem_it;
                    }
                }
                else
                {
                    out << 0 << " ";
                }
            }
            out << "\n";
        }
    }
    return out;
}

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(std::size_t rows, std::size_t cols) noexcept
    : m_rows{ rows }, m_cols{ cols }
{
    std::cout << "Parameterised CustomSparseMatrix constructor called.\n";
}

template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(const CustomSparseMatrix<T>& other) noexcept
    : m_rows{ other.m_rows }, m_cols{ other.m_cols }, m_matrix{ other.m_matrix }
{
    std::cout << "CustomSparseMatrix copy constructor called.\n";
}

template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept
    : m_rows { other.m_rows }
    , m_cols{ other.m_cols }
    , m_matrix{ static_cast<CustomLinkedList<element>&&>(other.m_matrix)}
{
    std::cout << "CustomSparseMatrix move constructor called.\n";
}

template <typename T>
CustomSparseMatrix<T>::~CustomSparseMatrix() noexcept
{
    std::cout << "CustomSparseMatrix destructor called.\n";
}

// Constructors and Destructors end here.

// Operator overload definitions begin here.

template <typename T>
T CustomSparseMatrix<T>::operator()(int row, int col) const
{
    for (auto elem_it{ m_matrix.begin() }; elem_it != m_matrix.end(); ++elem_it)
    {
        if ((elem_it->data.row == row) && (elem_it->data.col == col))
        {
            return elem_it->data.value;
        }
    }
    return static_cast<T>(0);
}

template <typename T>
typename CustomSparseMatrix<T>::element& CustomSparseMatrix<T>::operator[](int position)
{
    return m_matrix[position];
}

template <typename T>
const typename CustomSparseMatrix<T>::element& CustomSparseMatrix<T>::operator[](int position) const
{
    return m_matrix[position];
}

template <typename T>
CustomSparseMatrix<T>& CustomSparseMatrix<T>::operator=(const CustomSparseMatrix<T>& other)
{
    std::cout << "Overloaded copy assignment operator called.\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = other.m_matrix;
    return *this;
}

template <typename T>
CustomSparseMatrix<T>& CustomSparseMatrix<T>::operator=(CustomSparseMatrix<T>&& other)
{
    std::cout << "Overloaded move assignment operator called.\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = static_cast<CustomLinkedList<element>&&>(other.m_matrix);
    return *this;
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

template <typename T>
void CustomSparseMatrix<T>::insert(int position, const element& e)
{
    try
    {
        if (e.row >= static_cast<int>(m_rows) || e.col >= static_cast<int>(m_cols))
        {
            throw std::out_of_range("Element must be within matrix!");
        }
        m_matrix.insert(position, e);
    }
    catch (const std::out_of_range& exception)
    {
        std::cerr << "Standard exception caught: " << exception.what()
                  << "\nElement not added to matrix\n";
        return;
    }
}

template <typename T>
void CustomSparseMatrix<T>::erase(int position)
{
    m_matrix.erase(position);
}

template <typename T>
void CustomSparseMatrix<T>::bubbleSort()
{
    for (auto i{ 0 }; i < static_cast<int>(m_matrix.size()) - 1; ++i)
    {
        for (auto j{ 0 }; j < static_cast<int>(m_matrix.size()) - 1 - i; ++j)
        {
            if (m_matrix[j].row > m_matrix[j + 1].row)
            {
                std::swap(m_matrix[j],m_matrix[j + 1]);
            }
            else if ((m_matrix[j].row == m_matrix[j + 1].row) && (m_matrix[j].col > m_matrix[j + 1].col))
            {
                std::swap(m_matrix[j],m_matrix[j + 1]);
            }
        }
    }
}

template <typename T>
bool CustomSparseMatrix<T>::isSorted()
{
    for (auto i{ 0 }; i < static_cast<int>(m_matrix.size()) - 1; ++i)
    {
        if (m_matrix[i].row > m_matrix[i + 1].row)
        {
            return 0;
        }
        else if ((m_matrix[i].row == m_matrix[i + 1].row) && (m_matrix[i].col > m_matrix[i + 1].col))
        {
            return 0;
        }
    }
    return 1;
}

// Public member function definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, CustomSparseMatrix<T>& M)
{
    if (!M.isSorted())
    {
        M.bubbleSort();
    }
    return M.display(out);
}

// Friend functions definitions end here.

#endif // CUSTOMSPARSEMATRIX_H_INCLUDED
