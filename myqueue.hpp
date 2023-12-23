#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP



#include<iostream>
#include<exception>
	 
using namespace std;

#define QUEUE_SIZE 10   //Default Queue Size

//=========== Queue Class =========================
template <typename T>
class Queue
{
	private:
		T *array;
		int capacity;	//Max Capacity of the Queue
		int size;		//current number of elements in the Queue
		int front;		//front of the Queue
		int rear;		//index where a new element will be added
	public:
		Queue();
		~Queue();
		void enqueue(T); 
		T dequeue();
		T getFront();
		bool isEmpty();
		bool isFull();
};

template<typename T> Queue<T>::Queue()
{
	// Inititalise the private attribute of the queue
	this->size = 0;
	this->capacity = QUEUE_SIZE;
	this->front = 0;
	this->rear = 0;

	// Allocate memory for the dynamic array
	array = new T[QUEUE_SIZE];

}
//===========================================
template<typename T> Queue<T>::~Queue()
{
	// Deallocate the memory of the dynamic array
	delete[] array;
}
//===========================================
template<typename T> void Queue<T>::enqueue(T element)
{
	// Check if the queue is full
	if(isFull()){
		// Throw an error in case the queue is full
		throw overflow_error("The Queue is Full! ");
	}

	array[rear] = element;

	// Move the rear of the front of the queue one place
	rear = (rear + 1)%capacity;

	// Update the size
	size++;
}
//===========================================
template<typename T> T Queue<T>::dequeue()
{
	// Check if the queue is empty
	if(isEmpty()){
		// throw an error in case the queue is empty
		throw underflow_error("The Queue is Empty! ");
	}


	T element = array[front];

	// Move the front of the queue one place
	front = (front + 1)%capacity;

	// Update the size
	size--;

	// Return the the element at the front of the queue
	return element;
}
//===========================================
template<typename T> T Queue<T>::getFront()
{
	// Check if the queue is empty
	if(isEmpty()){
		// In case it is empty throw an error
		throw underflow_error("The Queue is Empty! ");
	}

	// Return the element in the front of the queue
	return array[front];
}
//===========================================
template<typename T> bool Queue<T>::isEmpty()
{
	// Check whether "size" is equal to 0: return true if they are equal, false otherwise
	return size == 0;
}
//===========================================
template<typename T> bool Queue<T>::isFull()
{
	// Check whether "size" is equal to "capacity": return true if they are equal, false otherwise
	return size == capacity;
}
//=============================================




#endif