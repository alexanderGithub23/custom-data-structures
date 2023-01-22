#ifndef CUSTOMMATRIX_H_INCLUDED
#define CUSTOMMATRIX_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <cassert>
#include "CustomArray.h"

// The following are forward declarations of friend functions required for C++ templates.

// The CustomMatrix class must be forward declared for template function declaration to be possible.
template <typename T>
class CustomMatrix;

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomMatrix<T>& mat);

template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B);

template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar);

template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar);

template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar);

template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B);

template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> A, const CustomMatrix<T> B);

template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> A, const CustomMatrix<T> B);

template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> M, T scalar);

template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> M, T scalar);

template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> M, T scalar);

// Forward declaration of template friend functions ends here.

/*
   Full template class definition.
   This class defines a two dimensional matrix.
   Overloaded <<, + and - (binary), () and = operators have been added.
   Indexing the matrix is done via operator()(row,column).
*/
template <typename T>
class CustomMatrix
{
private:
    // Private variables.
    int m_rows{};
    int m_cols{};
    CustomArray<T> m_matrix{};

    // Private member function declarations.
    std::ostream& Display(std::ostream& out) const;
public:
    // Constructor and destructor declarations.
    CustomMatrix() = delete; // CustomMatrix must be constructed with parameters.
    CustomMatrix(int rows, int cols) noexcept;
    CustomMatrix(std::initializer_list<std::initializer_list<T>> lsts) noexcept;
    CustomMatrix(const CustomMatrix& other) noexcept;
    CustomMatrix(CustomMatrix&& other) noexcept;
    ~CustomMatrix();

    // Operator overload member function declarations.
    T& operator()(int row, int col);
    T operator()(int row, int col) const;
    T& operator[](int idx) const = delete;
    CustomMatrix& operator=(const CustomMatrix<T>& other);
    CustomMatrix& operator=(CustomMatrix<T>&& other);
    CustomMatrix& operator=(std::initializer_list<std::initializer_list<T>> lsts);

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

// Constructor definitions begin here.

/*
   Parameterised constructor that takes matrix dimensions as input.
   Creates a matrix of zeroes of specified dimension.
*/
template <typename T>
CustomMatrix<T>::CustomMatrix(int rows, int cols) noexcept
    : m_rows{ rows }, m_cols{ cols }
{
    std::cout << "Parameterised CustomMatrix constructor called.\n";
    assert(rows > 0 && cols > 0 && "Matrix must have positive dimensions.");
    int matrixElements{ rows * cols };
    m_matrix.resizeArray(matrixElements);
}

/*
   Overloaded destructor to print destruction call to the terminal.
*/
template <typename T>
CustomMatrix<T>::~CustomMatrix()
{
    std::cout << "CustomMatrix destructor called.\n";
}

/*
   Constructor to accept list initialisation.
   Member variables are initialised with default values, then copy assigned in the function body.
   Example: CustomMatrix I{ {1,0},{0,1} }; creates a two by two identity matrix.
   Note. Values skipped are treated as zeroes if at least one column is populated with values.
   Example: CustomMatrix I{ {1},{0,1,0},{0,0,1} }; creates a three by three identity matrix.
*/
template <typename T>
CustomMatrix<T>::CustomMatrix(std::initializer_list<std::initializer_list<T>> lsts) noexcept
{
    std::cout << "CustomMatrix list-initialised constructor called.\n";
    assert(lsts.size() > 1 && "Matrix must have two dimensions.");
    m_rows = static_cast<int>(lsts.size());
    auto* lst_it{ lsts.begin() };
    m_cols = ((lst_it->size() >= 1) ? lst_it->size() : 1);
    while (lst_it != lsts.end())
    {
        if (static_cast<int>(lst_it->size()) > m_cols)
        {
            m_cols = static_cast<int>(lst_it->size());
        }
        ++lst_it;
    }
    lst_it = lsts.begin();
    int matrixElements{ m_rows * m_cols };
    m_matrix.resizeArray(matrixElements);
    for (int row{ 0 }; lst_it != lsts.end(); ++lst_it, ++row)
    {
        auto* elem_it = lst_it->begin();
        for (int col{ 0 }; elem_it != lst_it->end(); ++elem_it, ++col)
        {
            this->operator()(row,col) = *elem_it;
        }
    }
}

/*
   Overloaded copy constructor.
   Member variables are initialised with copy values.
   Example: CustomMatrix I{ {1,0},{0,1} };
            CustomMatrix M{ I }; creates a matrix M that is a copy of the two by two identity matrix I.
*/
template <typename T>
CustomMatrix<T>::CustomMatrix(const CustomMatrix& other) noexcept
    : m_rows{ other.m_rows }, m_cols{ other.m_cols }, m_matrix{ other.m_matrix }
{
    std::cout << "CustomMatrix reference copy constructor called.\n";
}

/*
   Overloaded move constructor.
   Fundamental data type member variables are initialised with copy values.
   The CustomArray m_matrix is initialised using its move constructor.
*/
template <typename T>
CustomMatrix<T>::CustomMatrix(CustomMatrix&& other) noexcept
    : m_rows { other.m_cols }
    , m_cols{ other.m_cols }
    , m_matrix{ static_cast<CustomArray<T>&&>(other.m_matrix) }
{
    std::cout << "CustomMatrix move constructor called.\n";
}

/*
   Member function to overload the parenthesis operator.
   Used for indexing the array to retrieve elements.
*/
template<class T>
T& CustomMatrix<T>::operator()(int row, int col)
{
    return m_matrix[row * m_cols + col];
}

/*
   Member function to overload the parenthesis operator.
   Used for indexing the array to retrieve elements.
*/
template<class T>
T CustomMatrix<T>::operator()(int row, int col) const
{
    return m_matrix[row * m_cols + col];
}

/*
   Member function to overload the assignment operator from an l-value reference.
   Copy assigns the CustomMatrix reference.
   Example: CustomMatrix I{ {1,0},{0,1} };, M{ 2,2 };
            M = I;
   This example copies the matrix rows, columns, and elements from CustomMatrix I to M.
*/
template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(const CustomMatrix<T>& other)
{
    std::cout << "CustomMatrix overloaded assignment operator (l-value reference CustomMatrix argument).\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = other.m_matrix;

    return *this;
}

/*
   Member function to overload the assignment operator from an r-value reference.
   Move assigns the CustomMatrix reference.
   Example: CustomMatrix I{ {1,0},{0,1} }; M{ 2,2 };
            M = I;
   This example copies the matrix rows, columns, and elements from CustomMatrix I to M.
*/
template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(CustomMatrix<T>&& other)
{
    std::cout << "CustomMatrix overloaded assignment operator (r-value reference CustomMatrix argument).\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = static_cast<CustomArray<T>&&>(other.m_matrix);

    return *this;
}

/*
   Member function to overload the assignment operator from a list of initializer_list lists.
   Copy assigns the CustomMatrix reference.
   Example: CustomMatrix I{ 2,2 };
            I = { {1,0},{0,1} };
   This example creates a two by two matrix of zeroes I, then copies a two by two identity matrix into it.
   Note. Values skipped are treated as zeroes if at least one column is populated with values.
   Example CustomMatrix I = { {1},{0,1,0},{0,0,1} }; copy assigns a three by three identity matrix.
*/
template <typename T>
CustomMatrix<T>& CustomMatrix<T>::operator=(std::initializer_list<std::initializer_list<T>> lsts)
{
    std::cout << "CustomMatrix overloaded assignment operator (initializer_list argument).\n";
    assert(lsts.size() > 1 && "Matrix must have two dimensions.");
    m_rows = static_cast<int>(lsts.size());
    auto* lst_it{ lsts.begin() };
    m_cols = ((lst_it->size() >= 1) ? static_cast<int>(lst_it->size()) : 1);
    while (lst_it != lsts.end())
    {
        if (static_cast<int>(lst_it->size()) > m_cols)
        {
            m_cols = static_cast<int>(lst_it->size());
        }
        ++lst_it;
    }
    lst_it = lsts.begin();
    int matrixElements{ m_rows * m_cols };
    m_matrix.clearArray();
    m_matrix.resizeArray(matrixElements);
    for (int row{ 0 }; lst_it != lsts.end(); ++lst_it, ++row)
    {
        auto* elem_it = lst_it->begin();
        for (int col{ 0 }; elem_it != lst_it->end(); ++elem_it, ++col)
        {
            this->operator()(row,col) = *elem_it;
        }
    }
    return *this;
}

/*
   Default function for outputting a matrix.
   Display() is used by the overloaded << operator function.
*/
template<class T>
std::ostream& CustomMatrix<T>::Display(std::ostream& out) const
{
    for (int i{ 0 }; i < m_rows; ++i)
    {
        for (int j{ 0 }; j < m_cols; ++j)
        {
            std::cout << this->operator()(i,j) << " ";
        }
        std::cout << "\n";
    }
    return out;
}

/*
   Friend function to overload the ostream operator.
   Calls the Display member function.
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomMatrix<T>& M)
{
    return M.Display(out);
}

/*
   Friend function to add two matrices together.
   Can be called by the overloaded operator+ (binary) function.
   The function takes references to two matrices, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded + operator.
*/
template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_rows && A.m_cols == B.m_cols && "Matrices unsuitable for addition.");
    CustomMatrix<T> addMatrix { A.m_rows, A.m_cols };
    for (int i{ 0 }; i < A.m_rows; ++i)
    {
        for (int j{ 0 }; j < A.m_cols; ++j)
        {
            addMatrix.operator()(i,j) = A.operator()(i,j) + B.operator()(i,j);
        }
    }
    return addMatrix;
}

/*
   Friend function to subtract one matrix from another.
   Can be called by the overloaded operator- (binary) function.
   The function takes references to two matrices, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded - operator.
*/
template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_rows && A.m_cols == B.m_cols && "Matrices unsuitable for subtraction.");
    CustomMatrix<T> subtractMatrix { A.m_rows, A.m_cols };
    for (int i{ 0 }; i < A.m_rows; ++i)
    {
        for (int j{ 0 }; j < A.m_cols; ++j)
        {
            subtractMatrix.operator()(i,j) = A.operator()(i,j) - B.operator()(i,j);
        }
    }
    return subtractMatrix;
}

/*
   Friend function to multiply two matrices together.
   Can be called by the overloaded operator* function.
   The function takes references to two matrices, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded * operator.
*/
template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& A, const CustomMatrix<T>& B)
{
    assert(A.m_rows == B.m_cols && "Matrices unsuitable for multiplication.");
    CustomMatrix<T> multiplyMatrix { A.m_rows, B.m_cols };
    for (int i{ 0 }; i < A.m_rows; ++i)
    {
        for (int j{ 0 }; j < B.m_cols; ++j)
        {
            for (int k{ 0 }; k < A.m_cols; ++k)
            {
                multiplyMatrix.operator()(i,j) += A.operator()(i,k) * B.operator()(k,j);
            }
        }
    }
    return multiplyMatrix;
}

/*
   Friend function to add a scalar value to a matrix.
   Can be called by the overloaded operator+ (binary) function.
   The function takes a matrix by l-value reference, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded + operator.
*/
template <typename T>
CustomMatrix<T> add(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> addMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < M.m_rows; ++i)
    {
        for (int j{ 0 }; j < M.m_cols; ++j)
        {
            addMatrix.operator()(i,j) = M.operator()(i,j) + scalar;
        }
    }
    return addMatrix;
}

/*
   Friend function to subtract a scalar value from a matrix.
   Can be called by the overloaded operator- (binary) function.
   The function takes a matrix by l-value reference, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded - operator.
*/
template <typename T>
CustomMatrix<T> subtract(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> subtractMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < M.m_rows; ++i)
    {
        for (int j{ 0 }; j < M.m_cols; ++j)
        {
            subtractMatrix.operator()(i,j) = M.operator()(i,j) - scalar;
        }
    }
    return subtractMatrix;
}

/*
   Friend function to multiply a matrix by a scalar value.
   Can be called by the overloaded operator* function.
   The function takes a matrix by l-value reference, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded * operator.
*/
template <typename T>
CustomMatrix<T> multiply(const CustomMatrix<T>& M, T scalar)
{
    CustomMatrix<T> multiplyMatrix { M.m_rows, M.m_cols };
    for (int i{ 0 }; i < M.m_rows; ++i)
    {
        for (int j{ 0 }; j < M.m_cols; ++j)
        {
            multiplyMatrix.operator()(i,j) = M.operator()(i,j) * scalar;
        }
    }
    return multiplyMatrix;
}

/*
   Friend function to overload the operator+ (binary) function.
   Calls the add(...) function, copying the matrices into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return add(A,B);
}

/*
   Friend function to overload the operator- (binary) function.
   Calls the subtract(...) function, copying the matrices into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return subtract(A,B);
}

/*
   Friend function to overload the operator* function.
   Calls the multiply(...) function, copying the matrices into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> A, const CustomMatrix<T> B)
{
    return multiply(A,B);
}

/*
   Friend function to overload the operator+ (binary) function.
   Calls the add(...) function, copying the matrix into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator+(const CustomMatrix<T> M, T scalar)
{
    return add(M,scalar);
}

/*
   Friend function to overload the operator- (binary) function.
   Calls the subtract(...) function, copying the matrix into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator-(const CustomMatrix<T> M, T scalar)
{
    return subtract(M,scalar);
}

/*
   Friend function to overload the operator* function.
   Calls the multiply(...) function, copying the matrix into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomMatrix<T> operator*(const CustomMatrix<T> M, T scalar)
{
    return multiply(M,scalar);
}

#endif // CUSTOMMATRIX_H_INCLUDED
