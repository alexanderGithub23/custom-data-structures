#ifndef CUSTOMSPARSEMATRIX_H_INCLUDED
#define CUSTOMSPARSEMATRIX_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <cassert>
#include "CustomArray.h"

/*
   Element object that contains row, column and value information.
   Will be entered into a CustomArray<T> object to generate the CustomSparseMatrix.
*/
template <typename T>
struct element
{
    int row{};
    int col{};
    T value{};
};

// The following are forward declarations of friend functions required for C++ templates.

// The CustomSparseMatrix class must be forward declared for template function declaration to be possible.
template <typename T>
class CustomSparseMatrix;

template <typename T>
std::ostream& operator<<(std::ostream& out, CustomSparseMatrix<T>& M);

// Forward declaration of template friend functions ends here.

template <typename T>
class CustomSparseMatrix
{
private:
    // Private variables.
    int m_rows{};
    int m_cols{};
    CustomArray<element<T>> m_matrix{};

    // Private member function declarations.
    std::ostream& Display(std::ostream& out) const;
public:
    // Constructor and destructor declarations.
    CustomSparseMatrix() = delete;
    CustomSparseMatrix(int rows, int cols) noexcept;
    CustomSparseMatrix(const CustomSparseMatrix<T>& other) noexcept;
    CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept;
    ~CustomSparseMatrix();

    // Public member function declarations.
    void insertElement(element<T> e, int idx);
    void appendElement(element<T> e);
    void removeElement(int idx);
    void sortElements();
    bool isSorted();

    // Operator overload member function declarations.
    T operator()(int row, int col) const;
    element<T>& operator[](int idx);
    element<T> operator[](int idx) const;
    CustomSparseMatrix& operator=(const CustomSparseMatrix<T>& other);
    CustomSparseMatrix& operator=(CustomSparseMatrix<T>&& other);

    // Fully specialised template friend function declarations.
    friend std::ostream& operator<<<T>(std::ostream& out, CustomSparseMatrix<T>& M);
};

/*
   Overloaded Parameterised constructor.
   Creates an empty CustomSparseMatrix of specified row and column dimensions.
*/
template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(int rows, int cols) noexcept
    : m_rows{ rows }, m_cols{ cols }
{
    std::cout << "Parameterised CustomSparseMatrix constructor called.\n";
}

/*
   Overloaded copy constructor.
   Member variables are initialised with copy values.
   Example: CustomSparseMatrix A{ 5,5 };
            CustomSparseMatrix B{ A }; creates a sparse matrix B that is a copy of A.
*/
template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(const CustomSparseMatrix<T>& other) noexcept
    : m_rows{ other.m_rows }, m_cols{ other.m_cols }, m_matrix{ other.m_matrix }
{
    std::cout << "CustomSparseMatrix copy constructor called.\n";

}

/*
   Overloaded move constructor.
   Fundamental data type member variables are initialised with copy values.
   The CustomArray m_matrix is initialised using its move constructor.
*/
template <typename T>
CustomSparseMatrix<T>::CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept
    : m_rows { other.m_rows }
    , m_cols{ other.m_cols }
    , m_matrix{ static_cast<CustomArray<element<T>>&&>(other.m_matrix)}
{
    std::cout << "CustomSparseMatrix move constructor called.\n";
}

/*
   Overloaded destructor to print destruction call to the standard output.
*/
template <typename T>
CustomSparseMatrix<T>::~CustomSparseMatrix()
{
    std::cout << "CustomSparseMatrix destructor called.\n";
}

/*
   Inserts a new element at a specified index into the CustomArray by calling the insertElement member function.
*/
template <typename T>
void CustomSparseMatrix<T>::insertElement(element<T> e, int idx)
{
    std::cout << "CustomSparseMatrix insertElement(...) function called.\n";
    m_matrix.insertElement(e,idx);
}


/*
   Inserts a new element at the end of the the CustomArray by calling its appendElement member function.
*/
template <typename T>
void CustomSparseMatrix<T>::appendElement(element<T> e)
{
    std::cout << "CustomSparseMatrix appendElement(...) function called.\n";
    m_matrix.appendElement(e);
}

/*
   Removes an element from the CustomArray m_matrix by calling its removeElement member function.
*/
template <typename T>
void CustomSparseMatrix<T>::removeElement(int idx)
{
    std::cout << "CustomSparseMatrix removeElement(...) function called.\n";
    m_matrix.removeElement(idx);
}

/*
   Sorts elements in the CustomSparseMatrix by ascending row and column order using the bubble sort algorithm.
   Used when outputting the array via the overloaded >> operator.
*/
template <typename T>
void CustomSparseMatrix<T>::sortElements()
{
    std::cout << "CustomSparseMatrix sortElements(...) function called.\n";
    for (int i{ 0 }; i < m_matrix.getLength() - 1; ++i)
    {
        for (int j{ 0 }; j < m_matrix.getLength() - 1 - i; ++j)
        {
            if (m_matrix[j].row > m_matrix[j + 1].row)
            {
                m_matrix.swapElements(m_matrix[j],m_matrix[j + 1]);
            }
            else if ((m_matrix[j].row == m_matrix[j + 1].row) && (m_matrix[j].col > m_matrix[j + 1].col))
            {
                m_matrix.swapElements(m_matrix[j],m_matrix[j + 1]);
            }
        }
    }
}

/*
   Function to declare whether the CustomSparseMatrix elements are in ascending order or not.
*/
template <typename T>
bool CustomSparseMatrix<T>::isSorted()
{
    for (int i{ 0 }; i < m_matrix.getLength() - 1; ++i)
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

/*
   Default function for outputting a matrix.
   Display() is used by the overloaded << operator function.
*/
template <typename T>
std::ostream& CustomSparseMatrix<T>::Display(std::ostream& out) const
{
    auto elem_it{ m_matrix.cbegin() };
    for (int i{ 0 }; i < m_rows; ++i)
    {
        for (int j{ 0 }; j < m_cols; ++j)
        {
            if ((i == elem_it->row) && (j == elem_it->col))
            {
                out << elem_it->value << " ";
                if (elem_it != m_matrix.cend())
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
    return out;
}

/*
   Member function to overload the parenthesis operator.
   Used for indexing the CustomSparseMatrix to retrieve element values.
   Only returns by value and should be used to retrieve data, not edit it.
   To edit, use the overloaded subscript operator functions.
*/
template <typename T>
T CustomSparseMatrix<T>::operator()(int row, int col) const
{
    for (auto elem_it{ m_matrix.cbegin() }; elem_it != m_matrix.cend(); ++elem_it)
    {
        if ((elem_it->row == row) && (elem_it->col = col))
        {
            return elem_it->value;
        }
    }
    return static_cast<T>(0);
}

/*
   Member function to overload the subscript operator.
   Returns a reference to the element of the array at the specified index.
   Element member variables can be accessed via dot notation and can be amended.
   Example: CustomSparseMatrix<int> A{ 5,5 };
            element<int> e{ 1,1,10 }; // creates an element of value 10.
            A.appendElement(e); // adds element e to A at index 0.
            A[0].value = 5; // amends the value of A at position 1,1 to 5.
*/
template <typename T>
element<T>& CustomSparseMatrix<T>::operator[](int idx)
{
    return m_matrix[idx];
}

/*
   Member function to overload the subscript operator.
   Returns a copy of the element of the array at the specified index.
*/
template <typename T>
element<T> CustomSparseMatrix<T>::operator[](int idx) const
{
    return m_matrix[idx];
}

/*
   Member function to overload the assignment operator from an l-value reference.
   Copy assigns the CustomSparseMatrix reference.
*/
template <typename T>
CustomSparseMatrix<T>& CustomSparseMatrix<T>::operator=(const CustomSparseMatrix<T>& other)
{
    std::cout << "CustomSparseMatrix overloaded assignment operator (l-value reference argument).\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = other.m_matrix;
    return *this;
}

/*
   Member function to overload the assignment operator from an l-value reference.
   Copy assigns the CustomSparseMatrix fundamental data types.
   Move assigns the CustomArray<element<T>> object.
*/
template <typename T>
CustomSparseMatrix<T>& CustomSparseMatrix<T>::operator=(CustomSparseMatrix<T>&& other)
{
    std::cout << "CustomSparseMatrix overloaded assignment operator (r-value reference argument).\n";
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = static_cast<CustomArray<element<T>>&&>(other.m_matrix);
    return *this;
}

/*
   Friend function to overload the ostream operator.
   Sorts the CustomSparseMatrix if required and calls the Display member function.
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, CustomSparseMatrix<T>& M)
{
    if (!M.isSorted())
    {
        M.sortElements();
    }
    return M.Display(out);
}

#endif // CUSTOMSPARSEMATRIX_H_INCLUDED
