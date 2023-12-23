#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

// Include necessary C++ standard libraries
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <sstream>

using namespace std;

// Define a template class for MyVector
template <typename T>
class MyVector {
private:
    T *data;            // Pointer to int (array) to store elements
    int v_size;         // Current size of vector (number of elements in the vector)
    int v_capacity;     // Capacity of the vector

public:
    MyVector(int cap = 0);  // Constructor
    ~MyVector();           // Destructor
    int size() const;      // Return current size of vector
    int capacity() const;  // Return capacity of vector
    bool empty() const;    // Return true if the vector is empty, false otherwise
    const T& front();      // Returns a reference to the first element in the vector
    const T& back();       // Returns a reference to the last element in the vector
    void push_back(T element);   // Add an element at the end of the vector
    void insert(int index, T element);  // Add an element at a specific index
    void erase(int index);  // Removes an element from a specific index
    T& operator[](int index);  // Returns a reference to an element at a given index
    T& at(int index);         // Return a reference to an element at a given index
    void shrink_to_fit();      // Reduce vector capacity to fit its size
    void reserve(int N);       // Reserve a new capacity for the vector
};

// Constructor for MyVector
template <typename T>
MyVector<T>::MyVector(int cap) {
	// Initialise the private attibute of the vector
    this->v_capacity = cap;
    this->v_size = 0;

    // Allocate memory for the dynamic array of size "v_capacity"
    data = new T[v_capacity];
}

// Destructor for MyVector
template <typename T>
MyVector<T>::~MyVector() {
	// Deallocate the memory of the dynamic array
    delete[] data;
}

// Return the current size of the vector
template <typename T>
int MyVector<T>::size() const {
    return v_size;
}

// Return the capacity of the vector
template <typename T>
int MyVector<T>::capacity() const {
    return v_capacity;
}

// Check if the vector is empty
template <typename T>
bool MyVector<T>::empty() const {
    return v_size == 0;
}

// Return a reference to the first element in the vector
template <typename T>
const T& MyVector<T>::front() {
	// Check if the vector is empty
	if(empty()){
		// If the vector is empty, throw an error
		throw logic_error("The MyVector is empty");
	}

	// If the vector is not
    return data[0];
}

// Return a reference to the last element in the vector
template <typename T>
const T& MyVector<T>::back() {
    return data[v_size - 1];
}

// Add an element at the end of the vector
template <typename T>
void MyVector<T>::push_back(T element) {
	// resize the vector in case it is full
    if (v_size == v_capacity) {
        reserve(max(1, 2 * v_capacity));
    }

    // set the lest element of the vector to "element" ans then increment the size
    data[v_size++] = element;
}

// Add an element at a specific index
template <typename T>
void MyVector<T>::insert(int index, T element) {
	// resize the vector in case it is full
    if (v_size == v_capacity) {
        reserve(max(1, 2 * v_capacity));
    }

    // throw an error in case the index passed is out of range
    if (index < 0 || index >= v_size) {
        throw range_error("Index out of bounds");
        return;
    }
    // shifitng to the right
	for (int i = v_size - 1; i >= index; i--) {
        data[i + 1] = data[i];
    }
    // sign the element to the element of index "index"
    data[index] = element;

    //update the size
    v_size++;

}

// Remove an element from a specific index
template <typename T>
void MyVector<T>::erase(int index) {
	// throw an error in case the index passed is out of range
    if (index < 0 || index >= v_size) {
        throw range_error("Index out of bounds");
    }

    // shifting tp the left
    for (int i = index + 1; i < v_size; i++) {
        data[i - 1] = data[i];
    }

    //update the size
    v_size--;
}

// Return a reference to an element at a given index
template <typename T>
T& MyVector<T>::operator[](int index) {
    if (index < 0 || index >= v_size) {
        throw range_error("Index out of bounds");
    }
    return data[index];
}

// Return a reference to an element at a given index
template <typename T>
T& MyVector<T>::at(int index) {
    if (index < 0 || index >= v_size) {
        throw range_error("Index out of bounds");
    }
    return data[index];
}

// Reduce vector capacity to fit its size
template <typename T>
void MyVector<T>::shrink_to_fit() {
	// If the capacity was greater than the size, then assign size to the capacity
    if (v_capacity > v_size) {
        v_capacity = v_size;
    }
}

// Reserve a new capacity for the vector
template <typename T>
void MyVector<T>::reserve(int N) {
	// Create a dynamic array of size N
    T* newData = new T[N];

    // Assign capacity to N
    this->v_capacity = N;

    // Copy all the element of the old array in the new array
    for (int i = 0; i < v_size; i++) {
        newData[i] = data[i];
    }

    // deallocate the memory of the first dynamic array
    delete[] data;

    // Assign data to the newly created dynamic array
    data = newData;
}

#endif