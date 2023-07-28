#ifndef CUSTOMMATRIX_H_INCLUDED
#define CUSTOMMATRIX_H_INCLUDED

#include <iostream>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap, std::initializer_list
#include <cassert>
#include "CustomArray.h"


/*
 *
 * File:    CustomMatrix.h
 *
 * Author:  Alexander R.
 * Date:    2023
 *
 * Summary of File:
 *
 *   This file contains code for a custom matrix container in the form of a class template CustomMatrix.
 *   Member functions of the class are available to add, subtract and multiply matrices together.
 *
 *   The template class has been tested with the following data types:
 *     * Integers
 *     * Floats
 *     * Doubles
 *
 */


// Forward declarations of class template CustomMatrix and associated friend functions begin here.
// Required to support class template functionality.

/*
 *
 *   Class Name: CustomMatrix
 *
 *   Purpose:
 *
 *     A custom 2D matrix container class template.
 *
 *   Member Variables:
 *
 *   m_rows
 *     An unsigned integer (std::size_t) that tracks the number of rows in the matrix.
 *   m_cols
 *     An unsigned integer (std::size_t) that tracks the number of rows in the matrix.
 *   m_matrix
 *     A CustomArray<T> array that holds the 2D matrix elements.
 *
 *   Member Functions:
 *
 *   display
 *     Prints the matrix data to the specified output stream.
 *
 */
template <typename T>
class CustomMatrix;

/*
 *
 * template <typename T>
 * std::ostream& operator<<(std::ostream& out, const CustomMatrix<T>& mat);
 *
 * Summary:
 *
 *    Standard output operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Standard output operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the private member function display.
 *
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomMatrix<T>& mat);

/*
 *
 * template <typename T>
 * CustomMatrix<T> add(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
 *
 * Summary:
 *
 *    Returns the sum of two matrices.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function to return the sum of two matrices that has friend privileges within the CustomMatrix class.
 *   Returns the new summed matrix by value.
 *
 */
template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
 *
 * Summary:
 *
 *    Subtracts the second matrix from the first.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function that has friend privileges within the CustomMatrix class.
 *   Returns a resulting matrix that is equal to the first matrix minus the second.
 *
 */
template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
 *
 * Summary:
 *
 *    Returns the product of two matrices.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function to return the product of two matrices that has friend privileges within the CustomMatrix class.
 *   Returns the new summed matrix by value.
 *
 */
template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar);
 *
 * Summary:
 *
 *    Adds a scalar value to all elements in the matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function to that has friend privileges within the CustomMatrix class.
 *   Adds the scalar value to all elements in the matrix.
 *   Returns the new summed matrix by value.
 *
 */
template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar);

/*
 *
 * template <typename T>
 * CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar);
 *
 * Summary:
 *
 *    Subtracts a scalar value from all elements in the matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function to that has friend privileges within the CustomMatrix class.
 *   Subtracts the scalar value from all elements in the matrix.
 *   Returns the new resulting matrix by value.
 *
 */
template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar);

/*
 *
 * template <typename T>
 * CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar);
 *
 * Summary:
 *
 *    Multiplies all elements in the matrix by a scalar value.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Function to that has friend privileges within the CustomMatrix class.
 *   Multiplies all elements in the matrix by a scalar value.
 *   Returns the new resulting matrix by value.
 *
 */
template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B);
 *
 * Summary:
 *
 *    Binary + operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary + operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function add(const CustomMatrix<T>& A, const CustomMatrix<T>& B).
 *
 */
template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B);
 *
 * Summary:
 *
 *    Binary - operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary - operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B).
 *
 */
template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> A, const CustomMatrix<T> B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator*(const CustomMatrix<T> A, const CustomMatrix<T> B);
 *
 * Summary:
 *
 *    Binary * operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary * operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B).
 *
 */
template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> A, const CustomMatrix<T> B);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator+(const CustomMatrix<T> M, T scalar);
 *
 * Summary:
 *
 *    Binary + operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary + operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar).
 *
 */
template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> M, T scalar);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator-(const CustomMatrix<T> M, T scalar);
 *
 * Summary:
 *
 *    Binary - operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary - operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar).
 *
 */
template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> M, T scalar);

/*
 *
 * template <typename T>
 * CustomMatrix<T> operator*(const CustomMatrix<T> M, T scalar);
 *
 * Summary:
 *
 *    Binary * operator overload for a CustomMatrix matrix.
 *
 * Return Value: None
 *
 * Description:
 *
 *   Binary * operator overload that has friend privileges within the CustomMatrix class.
 *   Calls the friend function CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar).
 *
 */
template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> M, T scalar);

// Forward declaration of template friend functions ends here.

template <typename T>
class CustomMatrix
{
private:

    std::size_t m_rows{};
    std::size_t m_cols{};
    CustomArray<T> m_matrix{};

    /*
     *
     * std::ostream& display(std::ostream& out) const;
     *
     * Summary:
     *
     *   Sends the matrix data to the standard output.
     *
     * Parameters   : std::ostream& out
     *
     * Return Value : std::ostream& out
     *
     * Description:
     *
     *   Prints each item in the array m_matrix to the terminal.
     *   Called by the overloaded operator << friend function.
     *
     */
    std::ostream& display(std::ostream& out) const;

public:

    // CustomMatrix objects must be constructed with parameters.
    CustomMatrix() = delete;

    /*
     *
     * CustomMatrix(std::size_t rows, std::size_t cols) noexcept;
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
    CustomMatrix(std::size_t rows, std::size_t cols) noexcept;

    /*
     *
     * CustomMatrix(std::initializer_list<std::initializer_list<T>> lists) noexcept;
     *
     * Summary:
     *
     *   Initialises an array from a series of std::initializer_list lists.
     *
     * Parameters: std::initializer_list<std::initializer_list<T>> lists
     *
     * Description:
     *
     *   Copies the values of each std::initializer_list to m_matrix.
     *   m_rows equals the number of std::initializer_list lists
     *   m_cols equals the length of the largest std::initializer_list list.
     *   Note. Values skipped are treated as zero if at least one column is populated with values.
     *
     */
    CustomMatrix(std::initializer_list<std::initializer_list<T>> lists) noexcept;

    /*
     *
     * CustomMatrix(const CustomMatrix& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a matrix from another matrix.
     *
     * Parameters: CustomMatrix<T>& other
     *
     * Description:
     *
     *   Fundamental data type member variables are initialised with copy values.
     *   The CustomArray m_matrix is initialised using its copy constructor.
     *
     */
    CustomMatrix(const CustomMatrix& other) noexcept;

    /*
     *
     * CustomMatrix(CustomMatrix&& other) noexcept;
     *
     * Summary:
     *
     *   Initialises a matrix from another matrix.
     *
     * Parameters: CustomMatrix<T>&& other
     *
     * Description:
     *
     *   Fundamental data type member variables are initialised with copy values.
     *   The CustomArray m_matrix is initialised using its move constructor.
     *
     */
    CustomMatrix(CustomMatrix&& other) noexcept;

    // An overloaded destructor that writes a message to the standard output.
    ~CustomMatrix() noexcept;

    /*
     *
     * T& operator()(int row, int col);
     *
     * Summary:
     *
     *   Parenthesis operator overload.
     *
     * Return Value: T& m_matrix[row * m_cols + col]
     *
     * Description:
     *
     *   Returns the element of the matrix given a specified row and column.
     *
     */
    T& operator()(int row, int col);

    /*
     *
     * const T& operator()(int row, int col) const;
     *
     * Summary:
     *
     *   Parenthesis operator overload.
     *
     * Return Value: const T& m_matrix[row * static_cast<int>(m_cols) + col]
     *
     * Description:
     *
     *   Returns the element of the matrix given a specified row and column.
     *
     */
    const T& operator()(int row, int col) const;

    // CustomMatrix objects should be indexed with (), rather than [].
    T& operator[](int position) = delete;
    T operator[](int position) const = delete;

    /*
     *
     * CustomMatrix& operator=(const CustomMatrix<T>& other);
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
     *   The CustomArray m_matrix from other is copied using its own copy assignment overload.
     *
     */
    CustomMatrix& operator=(const CustomMatrix<T>& other);

    /*
     *
     * CustomMatrix& operator=(CustomMatrix<T>&& other);
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
     *   The CustomArray m_matrix from other is moved using its own move assignment overload.
     *
     */
    CustomMatrix& operator=(CustomMatrix<T>&& other);

    /*
     *
     * CustomMatrix& operator=(std::initializer_list<std::initializer_list<T>> lists);
     *
     * Summary:
     *
     *   Copy assignment operator overload from std::initializer_list lists.
     *
     * Return Value: *this
     *
     * Description:
     *
     *   Uses the copy and swap idiom.
     *   Creates a temporary matrix with the std::initializer_list lists.
     *   Switches pointer addresses and lengths with the temporary array.
     *
     */
    CustomMatrix& operator=(std::initializer_list<std::initializer_list<T>> lists);

    // Fully specialised template friend function declarations.
    friend std::ostream& operator<<<T>(std::ostream& out, const CustomMatrix<T>& M);
    friend CustomMatrix<T> add<T>(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
    friend CustomMatrix<T> subtract<T>(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
    friend CustomMatrix<T> multiply<T>(const CustomMatrix<T>& A, const CustomMatrix<T>& B);
    friend CustomMatrix<T> add<T>(const CustomMatrix<T>& M, T scalar);
    friend CustomMatrix<T> subtract<T>(const CustomMatrix<T>& M, T scalar);
    friend CustomMatrix<T> multiply<T>(const CustomMatrix<T>& M, T scalar);
    friend CustomMatrix<T> operator+<T>(const CustomMatrix<T> A, const CustomMatrix<T> B);
    friend CustomMatrix<T> operator-<T>(const CustomMatrix<T> A, const CustomMatrix<T> B);
    friend CustomMatrix<T> operator*<T>(const CustomMatrix<T> A, const CustomMatrix<T> B);
    friend CustomMatrix<T> operator+<T>(const CustomMatrix<T> M, T scalar);
    friend CustomMatrix<T> operator-<T>(const CustomMatrix<T> M, T scalar);
    friend CustomMatrix<T> operator*<T>(const CustomMatrix<T> M, T scalar);
};

// Private member function definitions begin here.

template<class T>
std::ostream& CustomMatrix<T>::display(std::ostream& out) const
{
    for (auto i{ 0 }; i < static_cast<int>(m_rows); ++i)
    {
        for (auto j{ 0 }; j < static_cast<int>(m_cols); ++j)
        {
            out << operator()(i,j) << " ";
        }
        out << "\n";
    }
    return out;
}

// Private member function definitions end here.

// Constructor and Destructor definitions begin here.

template <typename T>
CustomMatrix<T>::CustomMatrix(std::size_t rows, std::size_t cols) noexcept
    : m_rows{ rows }, m_cols{ cols }
{
    std::cout << "Parameterised CustomMatrix constructor called.\n";
    std::size_t elements{ rows * cols };
    m_matrix.resize(elements);
}

template <typename T>
CustomMatrix<T>::CustomMatrix(std::initializer_list<std::initializer_list<T>> lists) noexcept
    : m_rows{ lists.size() }, m_cols{ 1 }
{
    std::cout << "CustomMatrix list-initialised constructor called.\n";

    auto* lists_it{ lists.begin() };
    while (lists_it != lists.end())
    {
        if (lists_it->size() > m_cols)
        {
            m_cols = lists_it->size();
        }
        ++lists_it;
    }

    std::size_t elements{ m_rows * m_cols };
    m_matrix.resize(elements);

    lists_it = lists.begin();
    for (auto row{ 0 }; lists_it != lists.end(); ++lists_it, ++row)
    {
        auto* elem_it = lists_it->begin();
        for (auto col{ 0 }; elem_it != lists_it->end(); ++elem_it, ++col)
        {
            operator()(row,col) = *elem_it;
        }
    }
}

template <typename T>
CustomMatrix<T>::CustomMatrix(const CustomMatrix& other) noexcept
    : m_rows{ other.m_rows }, m_cols{ other.m_cols }, m_matrix{ other.m_matrix }
{
    std::cout << "CustomMatrix reference copy constructor called.\n";
}

template <typename T>
CustomMatrix<T>::CustomMatrix(CustomMatrix&& other) noexcept
    : m_rows { other.m_rows }
    , m_cols{ other.m_cols }
    , m_matrix{ static_cast<CustomArray<T>&&>(other.m_matrix) }
{
    std::cout << "CustomMatrix move constructor called.\n";
}

template <typename T>
CustomMatrix<T>::~CustomMatrix() noexcept
{
    std::cout << "CustomMatrix destructor called.\n";
}

// Constructor and Destructor definitions end here.

// Operator overload definitions begin here.

template<class T>
T& CustomMatrix<T>::operator()(int row, int col)
{
    return m_matrix[row * static_cast<int>(m_cols) + col];
}

template<class T>
const T& CustomMatrix<T>::operator()(int row, int col) const
{
    return m_matrix[row * static_cast<int>(m_cols) + col];
}

template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(const CustomMatrix<T>& other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = other.m_matrix;

    return *this;
}

template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(CustomMatrix<T>&& other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = static_cast<CustomArray<T>&&>(other.m_matrix);

    return *this;
}

template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(std::initializer_list<std::initializer_list<T>> lists)
{
    CustomMatrix<T> temp{ lists };
    std::swap(m_rows, temp.m_rows);
    std::swap(m_cols, temp.m_cols);
    m_matrix.swap(temp.m_matrix);
    return *this;
}

// Operator overload definitions end here.

// Public member functions definitions begin here.

// Public member functions definitions end here.

// Friend function definitions begin here.

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomMatrix<T>& M)
{
    return M.display(out);
}

template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_rows && A.m_cols == B.m_cols && "Matrices unsuitable for addition.");
    CustomMatrix<T> addMatrix { A.m_rows, A.m_cols };
    for (int i{ 0 }; i < static_cast<int>(A.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(A.m_cols); ++j)
        {
            addMatrix.operator()(i,j) = A.operator()(i,j) + B.operator()(i,j);
        }
    }
    return addMatrix;
}

template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_rows && A.m_cols == B.m_cols && "Matrices unsuitable for subtraction.");
    CustomMatrix<T> subtractMatrix { A.m_rows, A.m_cols };
    for (int i{ 0 }; i < static_cast<int>(A.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(A.m_cols); ++j)
        {
            subtractMatrix.operator()(i,j) = A.operator()(i,j) - B.operator()(i,j);
        }
    }
    return subtractMatrix;
}

template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_cols && "Matrices unsuitable for multiplication.");
    CustomMatrix<T> multiplyMatrix { A.m_rows, B.m_cols };
    for (int i{ 0 }; i < static_cast<int>(A.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(B.m_cols); ++j)
        {
            for (int k{ 0 }; k < static_cast<int>(A.m_cols); ++k)
            {
                multiplyMatrix.operator()(i,j) += A.operator()(i,k) * B.operator()(k,j);
            }
        }
    }
    return multiplyMatrix;
}

template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> addMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < static_cast<int>(M.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(M.m_cols); ++j)
        {
            addMatrix.operator()(i,j) = M.operator()(i,j) + scalar;
        }
    }
    return addMatrix;
}

template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> subtractMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < static_cast<int>(M.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(M.m_cols); ++j)
        {
            subtractMatrix.operator()(i,j) = M.operator()(i,j) - scalar;
        }
    }
    return subtractMatrix;
}

template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> multiplyMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < static_cast<int>(M.m_rows); ++i)
    {
        for (int j{ 0 }; j < static_cast<int>(M.m_cols); ++j)
        {
            multiplyMatrix.operator()(i,j) = M.operator()(i,j) * scalar;
        }
    }
    return multiplyMatrix;
}

template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return add(A,B);
}

template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return subtract(A,B);
}

template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return multiply(A,B);
}

template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> M, T scalar)
{
    return add(M,scalar);
}

template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> M, T scalar)
{
    return subtract(M,scalar);
}

template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> M, T scalar)
{
    return multiply(M,scalar);
}

// Friend functions definitions end here.

#endif // CUSTOMMATRIX_H_INCLUDED
