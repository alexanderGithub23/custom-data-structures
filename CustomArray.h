#ifndef CUSTOMARRAY_H_INCLUDED
#define CUSTOMARRAY_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <cassert>
#include <iterator>

// The following are forward declarations of friend functions required for C++ templates.

// The CustomArray class must be forward declared for template function declaration to be possible.
template <typename T>
class CustomArray;

template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomArray<T>& arr);

template <typename T>
CustomArray<T> mergeArrays(const CustomArray<T>& A, const CustomArray<T>& B);

template <typename T>
CustomArray<T> unionArrays(const CustomArray<T>& A, const CustomArray<T>& B);

template <typename T>
CustomArray<T> relComplimentArrays(const CustomArray<T>&A, const CustomArray<T>& B);

template <typename T>
CustomArray<T> intersectionArrays(const CustomArray<T>& A, const CustomArray<T>& B);

template <typename T>
CustomArray<T> operator+(CustomArray<T> A, CustomArray<T> B);

template <typename T>
CustomArray<T> operator-(CustomArray<T> A, CustomArray<T> B);

// Forward declaration of template friend functions ends here.

/*
   Full template class definition.
   The class defines a resizable array that is continguous in memory.
   Member functions to add, remove, reverse, search and order elements are available.
   Overloaded <<, + and - (binary), [] and = operators have been added.
   Set theory operations can also be used via friend functions.
*/
template <typename T>
class CustomArray
{
private:
    // Private variables.
    int m_arrayLength{};
    T* m_array{};

    // Private member function declarations.
    bool isNull() { return m_array == nullptr; } // Used as a check for dynamic memory deletion.
    void swapElements(T& elementOne, T& elementTwo);
    int linearSearch(T element);
    int binarySearch(T element);
    std::ostream& Display(std::ostream& out) const;
public:
    // Constructor and destructor declarations.
    CustomArray() noexcept;
    CustomArray(std::initializer_list<T> lst) noexcept;
    CustomArray(const CustomArray<T>& arr) noexcept;
    CustomArray(CustomArray<T>&& arr) noexcept;
    ~CustomArray();

    // Public member function declarations.
    int getLength() { return m_arrayLength; }
    void clearArray();
    void resizeArray(int newLength);
    void insertElement(T val, int idx);
    void removeElement(int idx);
    void appendElement(T val);
    void reverseArray();
    void bubbleSort();
    bool isSorted();
    int searchElement(T element);

    // Operator overload member function declarations.
    T& operator[](int idx);
    T operator[](int idx) const;
    CustomArray& operator=(const CustomArray<T>& arr);
    CustomArray& operator=(CustomArray<T>&& arr);
    CustomArray& operator=(std::initializer_list<T> lst);

    // Fully specialised template friend function declarations.
    friend std::ostream& operator<<<T>(std::ostream& out, const CustomArray<T>& arr);
    friend CustomArray<T> mergeArrays<T>(const CustomArray<T>& A, const CustomArray<T>& B);
    friend CustomArray<T> unionArrays<T>(const CustomArray<T>& A, const CustomArray<T>& B);
    friend CustomArray<T> relComplimentArrays<T>(const CustomArray<T>&A, const CustomArray<T>& B);
    friend CustomArray<T> intersectionArrays<T>(const CustomArray<T>& A, const CustomArray<T>& B);
    friend CustomArray<T> operator+<T>(CustomArray<T> A, CustomArray<T> B);
    friend CustomArray<T> operator-<T>(CustomArray<T> A, CustomArray<T> B);

    // Iterator class definition.
    class const_iterator : public std::iterator<std::input_iterator_tag, T, int, T*, T&>
    {
    private:
        T* m_ptr{};
    public:
        explicit const_iterator(T* ptr = nullptr) : m_ptr{ ptr } {}
        const_iterator(const const_iterator& it) : m_ptr{ it.m_ptr } {}
        const_iterator& operator++() { ++m_ptr; return *this; }
        const_iterator operator++(int) { const_iterator tmp{ *this }; operator++(); return tmp; }
        bool operator==(const_iterator other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const_iterator other) const { return m_ptr != other.m_ptr; }
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
    };

    // CustomArray iterator functions.
    const_iterator cbegin() const { return const_iterator{ m_array }; }
    const_iterator cend() const { return const_iterator{ m_array + m_arrayLength }; }
};

// Constructor definitions begin here.

/*
   Overloaded default constructor to print creation to the terminal.
*/
template <typename T>
CustomArray<T>::CustomArray() noexcept
{
    std::cout << "CustomArray default constructor called.\n";
}

/*
   Constructor to accept list initialisation.
   Member variables are initialised with default values, then copy assigned in the function body.
   Example: CustomArray A{ 1,2,3 }; creates an array A with length 3 and elements [1,2,3].
*/
template <typename T>
CustomArray<T>::CustomArray(std::initializer_list<T> lst) noexcept
{
    std::cout << "CustomArray list-initialised constructor called.\n";
    if (lst.size() > 0)
    {
        m_arrayLength = static_cast<int>(lst.size());
        m_array = new T[lst.size()];
        int counter{ 0 };
        for (auto element : lst)
        {
            m_array[counter++] = element;
        }
    }
}

/*
   Overloaded copy constructor.
   Member variables are initialised with default values, then copy assigned in the function body.
   Example: CustomArray A{ 1,2,3 };
            CustomArray B{ A };     creates an array B with length 3 and elements [1,2,3].
*/
template <typename T>
CustomArray<T>::CustomArray(const CustomArray<T>& arr) noexcept
{
    std::cout << "CustomArray reference copy constructor called.\n";
    if (arr.m_arrayLength > 0)
    {
        m_arrayLength = arr.m_arrayLength;
        m_array = new T[m_arrayLength];
        for (int idx{ 0 }; idx < m_arrayLength; ++idx)
        {
            m_array[idx] = arr.m_array[idx];
        }
    }
}

/*
   Overloaded move constructor.
   Member variables are initialised with default values.
   Member variables take the place of the r-value reference array in the function body.
*/
template <typename T>
CustomArray<T>::CustomArray(CustomArray<T>&& arr) noexcept
{
    std::cout << "CustomArray move constructor called.\n";
    if (arr.m_arrayLength > 0)
    {
        m_arrayLength = arr.m_arrayLength;
        m_array = arr.m_array;
        arr.m_arrayLength = 0;
        arr.m_array = nullptr;
    }
}

/*
   Overloaded destructor to delete the dynamically allocated array in memory.
*/
template <typename T>
CustomArray<T>::~CustomArray()
{
    std::cout << "CustomArray destructor called.\n";
    if (!isNull()) { delete[] m_array; }
}

/*
   Swap two elements in an array using move semantics.
*/
template <typename T>
void CustomArray<T>::swapElements(T& elementOne, T& elementTwo)
{
    T tmp { static_cast<T&&>(elementOne) };
    elementOne = static_cast<T&&>(elementTwo);
    elementTwo = static_cast<T&&>(tmp);
}

/*
   Default function for outputting an array.
   Display() is used by the overloaded << operator function.
*/
template <typename T>
std::ostream& CustomArray<T>::Display(std::ostream& out) const
{
    for (int i{ 0 }; i < m_arrayLength; ++i)
    {
        out << i << ". " << m_array[i] << "\n";
    }
    return out;
}

/*
   Specialised Display() function for char types.
   Example: CustomArray A{ 'a','b','c' };
*/
template<>
std::ostream& CustomArray<char>::Display(std::ostream& out) const
{
    for (int i{ 0 }; i < m_arrayLength; ++i)
    {
        out << m_array[i];
    }
    out << "\n";
    return out;
}

/*
   Specialised Display() function for const char* types.
   Example: CustomArray A{ "Hello World" };
*/
template<>
std::ostream& CustomArray<const char*>::Display(std::ostream& out) const
{
    for (int i{ 0 }; i < m_arrayLength; ++i)
    {
        out << m_array[i];
    }
    out << "\n";
    return out;
}

/*
   Quickly wipes the array.
   Results in length zero and a null array pointer.
*/
template <typename T>
void CustomArray<T>::clearArray()
{
    std::cout << "clearArray() function called.\n";
    m_arrayLength = 0;
    if (!isNull()) { delete[] m_array; }
    m_array = nullptr;
}

/*
   Slow resize function. All elements are kept in the array up to the new length.
   Warning! Elements at index greater than the new length will be dropped from the array.
*/
template <typename T>
void CustomArray<T>::resizeArray(int newLength)
{
    std::cout << "resizeArray(...) function called.\n";
    if (m_arrayLength == newLength) { return; }
    if (newLength <= 0)
    {
        clearArray();
        return;
    }
    int elementsToCopy{ (newLength > m_arrayLength)? m_arrayLength : newLength };
    T* newArray{ new T[newLength]{} };
    for (int idx{ 0 }; idx < elementsToCopy; ++idx)
    {
        newArray[idx] = m_array[idx];
    }
    delete[] m_array;
    m_array = newArray;
    m_arrayLength = newLength;
}

/*
   Inserts a new element into the array.
   The array length is also increased by one.
*/
template <typename T>
void CustomArray<T>::insertElement(T val, int idx)
{
    std::cout << "insertElement(...) function called.\n";
    assert(idx >= 0 && idx <= m_arrayLength && "Index is out of range.");
    T* newArray{ new T[m_arrayLength + 1] };
    if (!isNull())
    {
        for (int before{ 0 }; before < idx; ++before)
        {
            newArray[before] = m_array[before];
        }
        for (int after{ idx }; after < m_arrayLength; ++after)
        {
            newArray[after + 1] = m_array[after];
        }
        delete[] m_array;
    }
    newArray[idx] = val;
    m_array = newArray;
    ++m_arrayLength;
}

/*
   Removes an element at specified index from the array.
   The length of the array is also reduced by one.
*/
template <typename T>
void CustomArray<T>::removeElement(int idx)
{
    std::cout << "removeElement(...) function called.\n";
    if (m_arrayLength == 0 && isNull()) { return; }
    assert(idx >= 0 && idx < m_arrayLength && "Index is out of range.");
    if (m_arrayLength == 1)
    {
        clearArray();
        return;
    }
    T* newArray{ new T[m_arrayLength - 1] };
    for (int before{ 0 }; before < idx; ++before)
    {
        newArray[before] = m_array[before];
    }
    for (int after{ idx + 1 }; after < m_arrayLength; ++after)
    {
        newArray[after - 1] = m_array[after];
    }
    delete[] m_array;
    m_array = newArray;
    --m_arrayLength;
}

/*
   Adds an element to the end of the array.
   The length of the array is also increased by one.
*/
template <typename T>
void CustomArray<T>::appendElement(T val)
{
    std::cout << "appendElement(...) function called.\n";
    insertElement(val,m_arrayLength);
}

/*
   Flips the order of elements in the array.
   This results in a permanent change to the array.
   Example: CustomArray A{ 1,2,3 }; becomes CustomArray A{ 3,2,1 };
*/
template <typename T>
void CustomArray<T>::reverseArray()
{
    std::cout << "reverseArray(...) function called.\n";
    for (int i{ 0 }, j{ m_arrayLength - 1 }; i < j; ++i, --j)
    {
        swapElements(m_array[i],m_array[j]);
    }
}

/*
   Sorts the array in ascending order using the famous bubble sort algorithm.
   Example: CustomArray A{ 4,2,3,1 } becomes CustomArray A{ 1,2,3,4 };
   This results in a permanent change to the array.
*/
template <typename T>
void CustomArray<T>::bubbleSort()
{
    std::cout << "bubbleSort(...) function called.\n";
    for (int i{ 0 }; i < m_arrayLength - 1; ++i)
    {
        for (int j{ 0 }; j < m_arrayLength - 1 - i; ++j)
        {
            if (m_array[j] > m_array[j + 1])
            {
                swapElements(m_array[j],m_array[j + 1]);
            }
        }
    }
}

/*
   Function to declare whether the array elements are in ascending order or not.
*/
template <typename T>
bool CustomArray<T>::isSorted()
{
    std::cout << "isSorted() function called.\n";
    for (int i{ 0 }; i < m_arrayLength - 1; ++i)
    {
        if (m_array[i] > m_array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

/*
   Private linear search member function.
   Searches for an element in the array from front to back.
   Returns the index of the element, or -1 if the element is not found.
   This is the algorithm used for searching through unsorted arrays in the searchElement member function.
*/
template <typename T>
int CustomArray<T>::linearSearch(T element)
{
    std::cout << "linearSearch(...) function called.\n";
    for (int idx{ 0 }; idx < m_arrayLength; ++idx)
    {
        if (element == m_array[idx])
        {
            return idx;
        }
    }
    return -1;
}

/*
   Private binary search member function.
   Searches through the array using the famous binary search algorithm.
   Returns the index of the element, or -1 if the element is not found.
   This is the algorithm used for searching through sorted arrays in the searchElement member function.
*/
template <typename T>
int CustomArray<T>::binarySearch(T element)
{
    std::cout << "binarySearch(...) function called.\n";
    int idx{};
    int low{};
    int high{ m_arrayLength - 1 };
    while (low <= high)
    {
        idx = (low + high ) / 2;
        if (element == m_array[idx])
        {
            return idx;
        }
        else if (element < m_array[idx])
        {
            high = idx - 1;
        }
        else
        {
            low = idx + 1;
        }
    }
    return -1;
}

/*
   Public search member function.
   Determines whether the array elements are in ascending order.
   Searches linearly if the elements are not in ascending order.
   Searches using a binary search algorithm if elements are in ascending order.
*/
template <typename T>
int CustomArray<T>::searchElement(T element)
{
    std::cout << "searchElement(...) function called.\n";
    if (isSorted())
    {
        return binarySearch(element);
    }
    return linearSearch(element);
}

/*
   Member function to overload the subscript operator.
   Returns a reference to the element of the array at the specified index.
*/
template <typename T>
T& CustomArray<T>::operator[](int idx)
{
    assert(idx >= 0 && idx < m_arrayLength && "Index is out of range.");
    return m_array[idx];
}

/*
   Member function to overload the subscript operator.
   Returns a copy of the element of the array at the specified index.
*/
template <typename T>
T CustomArray<T>::operator[](int idx) const
{
    assert(idx >= 0 && idx < m_arrayLength && "Index is out of range.");
    return m_array[idx];
}

/*
   Member function to overload the assignment operator from an l-value reference.
   Copy assigns the array reference to the array.
   Example: CustomArray A{ 1,2,3 }, B{};
            B = A;
   This example copies the array length and elements from CustomArray A to B.
*/
template <typename T>
CustomArray<T>& CustomArray<T>::operator=(const CustomArray<T>& arr)
{
    std::cout << "CustomArray overloaded assignment operator (l-value reference CustomArray argument).\n";
    if (&arr == this) { return *this; };

    if (arr.m_arrayLength > 0)
    {
        m_arrayLength = arr.m_arrayLength;
        if (!isNull()) { delete[] m_array; }
        m_array = new T[m_arrayLength];

        for (int idx{ 0 }; idx < m_arrayLength; ++idx)
        {
            m_array[idx] = arr.m_array[idx];
        }
    }
    else if (arr.m_arrayLength == 0)
    {
        m_arrayLength = 0;
        if (!isNull()) { delete[] m_array; }
        m_array = nullptr;
    }

    return *this;
}

/*
   Member function to overload the assignment operator from an r-value reference.
   Move assigns the array reference to the array.
   Example: CustomArray A{ 1,2,3 }, B{ 4,5,6 }, C{};
            C = unionArray(A,B);
   This example creates an anonymous temporary CustomArray from the unionArray(A,B) friend function.
   CustomArray C then takes the array length and elements from unionArray(A,B) using move assignment.
*/
template <typename T>
CustomArray<T>& CustomArray<T>::operator=(CustomArray<T>&& arr)
{
    std::cout << "CustomArray overloaded assignment operator (r-value reference CustomArray argument).\n";
    if (arr.m_arrayLength > 0)
    {
        m_arrayLength = arr.m_arrayLength;
        m_array = arr.m_array;
        arr.m_array = nullptr;
    }

    return *this;
}

/*
   Member function to overload the assignment operator from a list of elements.
   Copy assigns the array reference to the array.
   Example: CustomArray A{};
            A = { 1,2,3 };
   This example copies the array length and elements from the list to A.
*/
template <typename T>
CustomArray<T>& CustomArray<T>::operator=(std::initializer_list<T> lst)
{
    std::cout << "CustomArray overloaded assignment operator (initializer_list argument).\n";
    int newLength{ static_cast<int>(lst.size()) };
    if (newLength == 0)
    {
        clearArray();
        return *this;
    }
    if (m_arrayLength != newLength)
    {
        delete[] m_array;
        m_arrayLength = newLength;
        m_array = new T[newLength];
    }
    int counter{ 0 };
    for (auto element : lst)
    {
        m_array[counter++] = element;
    }

    return *this;
}

/*
   Friend function to overload the ostream operator.
   Calls the Display member function that is most suited to the CustomArray template type.
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const CustomArray<T>& arr)
{
    return arr.Display(out);
}

/*
   Friend function to combine two arrays.
   Outputs a temporary CustomArray to allow for chaining via the overloaded + operator.
   The function takes references to two arrays, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded + operator.
*/
template <typename T>
CustomArray<T> mergeArrays(const CustomArray<T>& A, const CustomArray<T>& B)
{
    std::cout << "mergeArrays(...) function called.\n";
    int i{};
    int j{};
    CustomArray<T> mergedArray{};
    while (i < A.m_arrayLength && j < B.m_arrayLength)
    {
        if (A[i] < B[j])
        {
            mergedArray.appendElement(A[i++]);
        }
        else
        {
            mergedArray.appendElement(B[j++]);
        }
    }
    for (; i < A.m_arrayLength; ++i)
    {
        mergedArray.appendElement(A[i]);
    }
    for (; j < B.m_arrayLength; ++j)
    {
        mergedArray.appendElement(B[j]);
    }
    return mergedArray;
}

/*
   Friend function to output the union of two arrays, as if they were sets.
   The function takes references to two arrays, rather than copying by value.
   Example: CustomArray A{ 1,2,3 }, B { 3,4,5 }, C{};
            C = unionArray(A,B);
   This example copy assigns CustomArray C with length 5 and elements [1,2,3,4,5].
*/
template <typename T>
CustomArray<T> unionArrays(const CustomArray<T>& A, const CustomArray<T>& B)
{
    std::cout << "unionArrays(...) function called.\n";
    int i{};
    int j{};
    CustomArray<T> unionArray{};
    while (i < A.m_arrayLength && j < B.m_arrayLength)
    {
        if (A[i] < B[j])
        {
            unionArray.appendElement(A[i++]);
        }
        else if (A[i] > B[j])
        {
            unionArray.appendElement(B[j++]);
        }
        else if (A[i] == B[j])
        {
            unionArray.appendElement(A[i++]);
            ++j;
        }
    }
    for (; i < A.m_arrayLength; ++i)
    {
        unionArray.appendElement(A[i]);
    }
    for (; j < B.m_arrayLength; ++j)
    {
        unionArray.appendElement(B[j]);
    }
    return unionArray;
}

/*
   Friend function to output the relative compliment of two arrays, as if they were sets.
   Outputs a temporary CustomArray, to allow for chaining via the overloaded - operator.
   The function takes references to two arrays, rather than copying by value.
   As such, using this function directly (where appropriate) is faster than calling the overloaded - operator.
   Example: CustomArray A{ 1,2,3 }, B { 3,4,5 }, C{};
            C = relComplimentArrays(A,B);
   This example copy assigns CustomArray C with length 2 and elements [1,2].
*/
template <typename T>
CustomArray<T> relComplimentArrays(const CustomArray<T>& A, const CustomArray<T>& B)
{
    std::cout << "relComplimentArrays(...) function called.\n";
    int i{};
    int j{};
    CustomArray<T> relComplimentArray{};
    while (i < A.m_arrayLength && j < B.m_arrayLength)
    {
        if (A[i] < B[j])
        {
            relComplimentArray.appendElement(A[i++]);
        }
        else if (A[i] > B[j]) { ++j; }
        else if (A[i] == B[j])
        {
            ++i;
            ++j;
        }
    }
    for (; i < A.m_arrayLength; ++i)
    {
        relComplimentArray.appendElement(A[i]);
    }
    return relComplimentArray;
}

/*
   Friend function to output the intersection of two arrays, as if they were sets.
   The function takes references to two arrays, rather than copying by value.
   Example: CustomArray A{ 1,2,3 }, B { 3,4,5 }, C{};
            C = intersectionArrays(A,B);
   This example copy assigns CustomArray C with length 1 and element [3].
*/
template <typename T>
CustomArray<T> intersectionArrays(const CustomArray<T>& A, const CustomArray<T>& B)
{
    std::cout << "intersectionArrays(...) function called.\n";
    int i{};
    int j{};
    CustomArray<T> intersectionArray{};
    while (i < A.m_arrayLength && j < B.m_arrayLength)
    {
        if (A[i] < B[j]) { ++i; }
        else if (A[i] > B[j]) { ++j; }
        else if (A[i] == B[j])
        {
            intersectionArray.appendElement(A[i++]);
            ++j;
        }
    }
    return intersectionArray;
}

/*
   Friend function to overload the + operator.
   Calls the mergeArrays function, copying the arrays into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomArray<T> operator+(CustomArray<T> A, CustomArray<T> B)
{
    return mergeArrays(A,B);
}

/*
   Friend function to overload the - operator.
   Calls the relComplimentArrays function, copying the arrays into the function scope first.
   This operator can be chained as required.
*/
template <typename T>
CustomArray<T> operator-(CustomArray<T> A, CustomArray<T> B)
{
    return relComplimentArrays(A,B);
}

#endif // CUSTOMARRAY_H_INCLUDED
