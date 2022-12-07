

//-------------------------------------------------------

//if you use this Vector class, remember to change the name
//push_back and pop_back to something else. Because this is
//class is not really a Vector. Can change to addElement etc

//---------------------------------------------------------

#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>

using namespace std;

/**
 * @class Vector template class
 * @brief Represent the vector
 *
 * This Vector template class contains 3 member variables.
 * The data type depends on the type passed in by the user.
 * m_pointer is the pointer of the dynamic array. m_counter is the allocation. m_size
 * is the size of array.
 * This class also contain necessary vector method like push, pop, etc.
 *
 * @author Tee Yee Kang
 * @version 01
 * @date 10/09/2021 Tee Yee Kang, Started
 *
 *
 * @bug Some check in push function might not sufficient
 */

template <class T>
class Vector
{

public:

    /**
     * @brief Create Vector class object with default value
     *
     * This is the default constructor. Inside the constructor will set the
     * member variables to default value by using the Clear() method.
     */
    Vector();

    /**
     * @brief Vector class constructor with parameters
     *
     * This is the constructor for Vector class. Which will takes
     * in 1 parameter which is the size of array. The constructor will then set the array size.
     *
     * @param newSize - Size of array
     */
    Vector(int newSize);

    /**
     * @brief Vector destructor
     *
     * Inside the destructor will clean up the memory heap
     */
    ~Vector();

    /**
     * @brief Display the elements in the Vector object
     *
     * This constant function is used to print out the value of vector.
     * No input parameter is required.
     *
     * @return void
     */
    void Display() const;

    /**
     * @brief Resize the dynamic array
     *
     * This function is used to resize the vector. The function will double
     * the size of dynamic array and paste the existing elements into the
     * new array. The pointer will then pointer to the new dynamic array.
     *
     * @return void
     */
    void Resize();

    /**
     * @brief Add item into the Vector array
     *
     * This function is used to add new item into the array of Vector. Size of the
     * array will take care by the program itself.
     *
     * @param item - item to add
     * @return bool
     */
    bool PushBack(const T &item);

    /**
     * @brief Remove item from the Vector array
     *
     * This function is used to remove item into the array of Vector.
     *
     * @param item - variable to store the removed item
     * @return bool
     */
    bool PopBack(T &item);

    /**
     * @brief Get the size of vector array
     *
     * This constant function is used to return the size of Vector array.
     *
     * @return int
     */
    int GetVecSize() const;

    /**
     * @brief Get the counter/allocation of vector
     *
     * This constant function is used to return the allocation/counter of Vector.
     *
     * @return int
     */
    int GetCounter() const;

    /**
     * @brief Get the element in specific position/index
     *
     * This function is used to return the element based on the passed in position/index.
     *
     * @param index - Position to return
     * @return T - Based on the data type passed in by user
     */
    T Get(int index) const;

    //copy function
    void Copy(const Vector& otherVector);

    //copy constructor
    Vector (Vector &otherVector);

    //overload assignment operator
    Vector& operator = (const Vector& otherVector)
    {
        Copy(otherVector);
    }

private:
    T* m_pointer;
    int m_counter;
    int m_size;
};

template <class T>
Vector<T>::Vector()
{
    m_size=10;
    m_pointer = new T[m_size];
    m_counter = 0;
}

template <class T>
Vector<T>::Vector(int newSize)
{
    m_size=newSize;
    m_pointer = new T[m_size];
    m_counter = 0;
}

template <class T>
Vector<T>::~Vector()
{
   delete[] m_pointer; //clean memory heap
}

template <class T>
void Vector<T>::Resize()
{
    T* temp;
    m_size *= 2;
    temp = new T[m_size];

    for(int idx=0; idx < m_counter; idx++)
    {
        temp[idx] = m_pointer[idx]; //copy and paste elements
    }

    delete [] m_pointer;
    m_pointer = temp;
}

template <class T>
bool Vector<T>::PushBack(const T& item)
{
    if(m_counter >= m_size/2)
    {
        Resize();
    }

    if(m_counter < m_size)
    {
        m_pointer[m_counter] = item; //add item
        m_counter++;

        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool Vector<T>::PopBack(T &item)
{
    if(m_pointer == 0)
    {
        cout<<"No element inside"<<endl;
        return false;
    }
    else
    {
        item = m_pointer[m_counter-1];
        m_counter--;
        return true;
    }
}

template <class T>
int Vector<T>::GetVecSize() const
{
    return m_size;
}

template <class T>
int Vector<T>::GetCounter() const
{
    return m_counter;
}

template <class T>
T Vector<T>::Get(int index) const
{
    try
    {
        if(index > m_size-1)
        {
            throw(index);
        }
    }
    catch(int invalidIndex)
    {
        cout<<"Index out of bound"<<endl;
    }

    if(index >= 0 && index < m_counter)
    {
        return m_pointer[index];
    }
}

template <class T>
void Vector<T>::Display() const
{
    for(int idx=0; idx < m_counter; idx++)
    {
        cout << m_pointer[idx] << endl;
    }
}

template <class T>
void Vector<T>::Copy(const Vector& otherVector)
{
    m_size = otherVector.GetVecSize();
    m_counter = otherVector.GetCounter();
    T* newPointer;
    newPointer = new T[m_size];

    for(int idx=0; idx < otherVector.GetCounter(); idx++)
    {
        newPointer[idx] = otherVector.Get(idx);//copy and paste elements
    }

    delete[] m_pointer;
    m_pointer = newPointer;
}

template <class T>
Vector<T>:: Vector (Vector &otherVector)
{
    Copy(otherVector);
}



#endif // VECTOR_H

