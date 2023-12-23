#ifndef MYSTACK_HPP
#define MYSTACK_HPP

#include<iostream>
#include<exception>

using namespace std;

//Define MyStack Class here
template<typename T>

class myStack{
private:
	//Private data member of the class.
	int  sizeStack;
	T* array_stack;
	int capacity;

public:
	//public methods of the class: including constructor and destructor
	myStack(int capacity = 50);
	~myStack();
	void push(T e);
	void pop();
	T top() const;
	int size() const;
	bool empty() const;
};

template<typename T>
myStack<T>::myStack(int capacity){
	this->capacity = capacity;
	array_stack = new T[capacity];
	sizeStack = 0;
}

template<typename T>
myStack<T>::~myStack(){
	delete[] array_stack;
}

template<typename T>
void myStack<T>::push(T e){
	if(sizeStack == capacity){
		throw runtime_error("The Stack is Full"); // throw an error in case the stack is full
	}else{
		array_stack[sizeStack] = e;
		sizeStack++;
	}
}

template<typename T>
void myStack<T>::pop(){
	if(empty()){
		throw runtime_error("The Stack is Empty"); // throw an error in case the stack is empty
	}else{
		sizeStack--;
	}
}

template<typename T>
T myStack<T>::top() const{
	if(empty()){
		throw runtime_error("The Stack is Empty"); // throw an error in case the stack is full
	}else{
		return array_stack[sizeStack - 1];
	}
}

template<typename T>
int myStack<T>::size() const{
	return sizeStack;
}

template<typename T>
bool myStack<T>::empty() const{
	return sizeStack == 0;
}


#endif