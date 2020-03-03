// project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

template <class DT>
class GLRow; //class prototype

template <class DT>
ostream& operator <<(ostream& s, GLRow<DT>& oneGLRow);

template <class DT>
class GLRow {
	friend ostream& operator<< <DT>(ostream& s, GLRow<DT>& oneGLRow);

protected:
	DT* _Info;
	int _Next;
	int _Down;

public:
	GLRow();
	GLRow(DT& newInfo);
	GLRow(GLRow<DT>& anotherOne);
	GLRow<DT>& operator= (GLRow<DT>& anotherOne); //Make sure I do a deep copy
	int getNext();
	int getDown();
	DT& getInfo();
	int setNext(int n);
	int setDown(int d);
	int setInfo(DT& x);
	~GLRow(); //destructor


};

template<class DT>
GLRow<DT>::GLRow()
{
	_Info = NULL;
	_Next = -1;
	_Down = -1;
}

template <class DT>
GLRow<DT>::GLRow(DT& newInfo) {
	_Info = newInfo;
	_Next = -1;
	_Down = -1;
}

template <class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne) {
	_Info = anotherOne.getInfo();
	_Next = anotherOne.getNext();
	_Down = anotherOne.getDown();
}

template <class DT>
ostream& operator << (ostream& s, GLRow<DT>& oneGLRow) {
	return s;
}

template<class DT>
GLRow<DT>& GLRow<DT>::operator=(GLRow<DT>& anotherOne)
{
	// TODO: insert return statement here
}

template<class DT>
int GLRow<DT>::getNext()
{
	return _Next;
}

template <class DT>
int GLRow<DT>::getDown() {
	return _Down;
}

template <class DT>
DT& GLRow<DT>::getInfo() {
	return _Info;
}

template <class DT>
int GLRow<DT>::setNext(int n) {
	_Next = n;
	return _Next;
}

template <class DT>
int GLRow<DT>::setDown(int d) {
	_Down = d;
	return _Down;
}

template <class DT>
int GLRow<DT>::setInfo(DT& x) {
	_Info = x;
	return _Info;
}

template <class DT>
GLRow<DT>::~GLRow() {
	//Implement destructor
}

template <class DT>
class ArrayGLL; //class prototype

template <class DT>
ostream& operator <<(ostream& s, ArrayGLL<DT>& oneGLL);

template <class DT>
class ArrayGLL {
	friend ostream& operator<< <DT>(ostream& s, ArrayGLL<DT>& oneGLL);
protected:
	GLRow<DT>* myGLL;
	int maxSize; //Maximum siz of the array of GLRows
	int firstElement;
	int firstFree;

public:
	ArrayGLL();
	ArrayGLL(int size);
	ArrayGLL(ArrayGLL<DT>& anotherOne);
	ArrayGLL<DT>& operator= (ArrayGLL<DT>& anotherOne);
	void display(); //display in parenthesis format 10% BONUS
	int find(DT& key); //return the index position where you find the element key; -1 if not found, use recursive search
	void findDisplayPath(DT& key); //as you travel through the tree, print values of nodes enountered.
	int noFree(); //return the number of free locations; you need to follow the _Next and get free locations
	int size(); //return the number of elements stored
	int parentPos(DT& key); //provide the location of the parent of the element key in the array 10% BONUS
	GLRow<DT>& operator [] (int pos); //return the GLRow that is in the position pos in the array
	int getFirstFree();
	int getFirstElement();
	void setFirstFree(int pos);
	void setFirstElement(int pos);
	~ArrayGLL(); //destructor
};




int main()
{
    std::cout << "Hello World!\n";
}


