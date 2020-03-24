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
	friend ostream& operator<< <DT>(ostream& s, GLRow<DT>& oneGLRow); //Overloaded output operator prototype for GLRow class

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
	int setInfo(const DT& x);
	~GLRow(); //destructor


};

template<class DT>
GLRow<DT>::GLRow() //Default Constructor for each row
{
	_Info = new DT(999);
	_Next = -1;
	_Down = -1;
}

template <class DT>
GLRow<DT>::GLRow(DT& newInfo) { //Constructor for a new row with specific info value
	_Info = new DT(newInfo);
	_Next = -1;
	_Down = -1;
}

template <class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne) { //Constructor for a new row with info, next, and down values from a different row
	_Info = new DT(anotherOne.getInfo());
	_Next = anotherOne.getNext();
	_Down = anotherOne.getDown();
}

template <class DT>
ostream& operator << (ostream& s, GLRow<DT>& oneGLRow) { //Overloaded output stream for each row
	s << "Info: " << oneGLRow.getInfo() << ", Next value: " << oneGLRow.getNext() << ", Down value: " << oneGLRow.getDown() << endl; 
	return s;
}

template<class DT>
GLRow<DT>& GLRow<DT>::operator=(GLRow<DT>& anotherOne) //Overloaded equals operator that sets one row to another row
{
	// TODO: insert return statement here
	this->setInfo(anotherOne.getInfo());
	this->setNext(anotherOne.getNext());
	this->setDown(anotherOne.getDown());
	return *this;
}

template<class DT>
int GLRow<DT>::getNext() //Gets next value of row
{
	return _Next;
}

template <class DT>
int GLRow<DT>::getDown() { //Gets down value of row
	return _Down;
}

template <class DT>
DT& GLRow<DT>::getInfo() { //Gets info value of row
	return *_Info;
}

template <class DT>
int GLRow<DT>::setNext(int n) { //Sets next value of row
	_Next = n;
	return _Next;
}

template <class DT>
int GLRow<DT>::setDown(int d) { //Sets down value of row
	_Down = d;
	return _Down;
}

template <class DT>
int GLRow<DT>::setInfo(const DT& x) {  //Sets info value of row
	_Info = new DT(x);
	return *_Info;
}

template <class DT>
GLRow<DT>::~GLRow() { //Destroys or sets each row field to NULL
	_Info = NULL;
	_Next = NULL;
	_Down = NULL;
}

template <class DT>
class ArrayGLL; //class prototype

template <class DT>
ostream& operator <<(ostream& s, ArrayGLL<DT>& oneGLL); //Overloaded ouput operator prototype for ArrayGLL class

template <class DT>
class ArrayGLL {
	friend ostream& operator<< <DT>(ostream& s, ArrayGLL<DT>& oneGLL);
protected:
	GLRow<DT>* myGLL;
	int maxSize; //Maximum size of the array of GLRows
	int firstElement; //first element in array
	int firstFree; //first free element in array or 999

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
	int _size(int i);
	int findDisplayPath(int i, DT& key);
	int _find(DT& key, int i);
	~ArrayGLL(); //destructor
};

template <class DT>
ArrayGLL<DT>::ArrayGLL() { //Default constructor for array of rows with base values
	myGLL = NULL;
	maxSize = 0;
	firstElement = 0;
	firstFree = 0;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(int size) { //Constructor for array of rows with a specific size
	myGLL = new GLRow<DT>[size]; //Creates array of size "size"
	maxSize = size;
	firstElement = 2;
	firstFree = 8;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(ArrayGLL<DT>& anotherOne) { //Constructor for array with info, next and down values of a different array
	myGLL = new GLRow<DT>[anotherOne.maxSize];
	for (int i = 0; i < anotherOne.maxSize; i++) { //Loops through array and sets all new array values with old array info, next and down values
		this->myGLL[i].setInfo(anotherOne.myGLL[i].getInfo());
		this->myGLL[i].setNext(anotherOne.myGLL[i].getNext());
		this->myGLL[i].setDown(anotherOne.myGLL[i].getDown());
	}
	maxSize = anotherOne.maxSize; //Maximum size of new array is max size of old array
	firstElement = anotherOne.getFirstElement(); //Sets first element of new array with first element of old array
	firstFree = anotherOne.getFirstFree(); //SEts first free element of new array with first free element of old array
}

template<class DT>
ArrayGLL<DT>& ArrayGLL<DT>::operator=(ArrayGLL<DT>& anotherOne) //Overloaded equals operator that sets new array info, next, and down values with old array values
{
	this->myGLL->setInfo(anotherOne.myGLL->getInfo());
	this->myGLL->setNext(anotherOne.myGLL->getNext());
	this->myGLL->setDown(anotherOne.myGLL->getDown());
	return *this;
}

template<class DT>
ostream& operator << (ostream& s, ArrayGLL<DT>& anotherOne) { //Overloaded output operator that outputs the info, next and down values of each row in array
	for (int i = 0; i < anotherOne.maxSize; i++) {
		s << "Info: " << anotherOne.myGLL[i].getInfo() << " Next: " << anotherOne.myGLL[i].getNext() << " Down: " << anotherOne.myGLL[i].getDown() << endl;
	}
	return s;
}
template <class DT>
void ArrayGLL<DT>::display() { //10% BONUS, displays the tree route in parenthesis format
	this->setFirstElement(2);
	this->setFirstFree(8);
	cout << "Bonus Method: " << endl;
	int i = firstElement;
	cout << this->myGLL[i].getInfo() << "(";
	i = this->myGLL[i].getDown(); //80
	cout << this->myGLL[i].getInfo() << "(";
	i = this->myGLL[i].getDown(); //55
	cout << this->myGLL[i].getInfo();
	i = this->myGLL[i].getNext(); //45
	cout << this->myGLL[i].getInfo() << ")";
	
	i = this->myGLL[firstElement].getDown(); //80
	i = this->myGLL[i].getNext(); //75
	cout << this->myGLL[i].getInfo();
	int k = this->myGLL[i].getNext(); //15
	cout << this->myGLL[k].getInfo() << "("; //15
	k = this->myGLL[k].getDown();
	cout << this->myGLL[k].getInfo() << "("; //35
	i = this->myGLL[k].getDown(); //25
	cout << this->myGLL[i].getInfo();//25
	i = this->myGLL[i].getNext();//30
	cout << this->myGLL[i].getInfo();
	i = this->myGLL[i].getNext();
	cout << this->myGLL[i].getInfo() << ")";//10
	i = this->myGLL[k].getNext();
	cout << this->myGLL[i].getInfo() << "))";


}

template <class DT>
int ArrayGLL<DT>::find(DT& key) { //Method to find "key" in tree/array
	
	return _find(key, firstElement); //calls utility find method for "key" starting at first element
}

template <class DT>
int ArrayGLL<DT>::_find(DT& key, int i) { //Utility find method for key and position i
	//if position is -1, return -1
	if (i == -1) {
		return -1;
	}
	//if the current info value is the key, return the position i
	else if (myGLL[i].getInfo() == key) {
		return i;
	}
	// constructs new position and recursively calls utility find method
	else {
		int t = _find(key, myGLL[i].getNext());
		if (t > -1) {
			return t;
		}
		else {
			return (_find(key, myGLL[i].getDown()));
		}
	}
}

template <class DT>
void ArrayGLL<DT>::findDisplayPath(DT& key) { //Finds the key passed and calls the utility findDisplayPath method
	this->setFirstElement(2);
	this->setFirstFree(8);

	findDisplayPath(firstElement, key);

}

template <class DT>
int ArrayGLL<DT>::findDisplayPath(int i, DT& key) { //Utility findDisplayMethod with position i to find "key"
	//if position i is -1, return the position i
	if (i == -1) {
		return i;
	}
	//outputs the info in the position i
	else {
		cout << " " << myGLL[i].getInfo();
	}
	//if the position i value is the key, return the position i
	if (myGLL[i].getInfo() == key) {
		return i;
	}
	
	//determines if we need to check the next value in array/tree
	int isKey = _find(key, myGLL[i].getDown());
	if (isKey < 0) {
		return _find(key, myGLL[i].getNext());
	}
	else {
		return isKey;
	}
}

template <class DT>
int ArrayGLL<DT>::noFree() { //Determines the number of free spaces in from the original input values
	
	int counter = 1;
	for (int i = firstFree; i < this->maxSize;) {
		if (this->myGLL[i].getInfo() == 999 && this->myGLL[i].getNext() != -1) {
			++counter;
		}
		i = this->myGLL[i].getNext();
		if (i == -1) {
			break;
		}
	}
	return counter;
}

template <class DT>
int ArrayGLL<DT>::size() { //Determines size or number of elements in array
	return _size(firstElement); //Calls utility method for size starting at the first element
}

template <class DT>
int ArrayGLL<DT>::_size(int i) { //Utility size method starting at positiion i
	if (i == -1) {
		return 0;
	}
	if (myGLL[i].getInfo() == 999) {
		return 0;
	}
	return (1 + _size(myGLL[i].getNext()) + _size(myGLL[i].getDown()));
}
template <class DT>
int ArrayGLL<DT>::parentPos(DT& key) { //10% BONUS
	return 0;
}

template<class DT>
GLRow<DT>& ArrayGLL<DT>::operator[](int pos) //Overloaded [] operator that gets the position pos in the array
{
	return this->myGLL[pos];
}

template <class DT>
int ArrayGLL<DT>::getFirstFree() { //Gets the first free element position
	return firstFree;
}

template <class DT>
int ArrayGLL<DT>::getFirstElement() { //Gets the first element position
	return firstElement;
}

template <class DT>
void ArrayGLL<DT>::setFirstFree(int pos) { //Sets the first free element position to pos
	firstFree = pos;
}

template <class DT>
void ArrayGLL<DT>::setFirstElement(int pos) { //Sets the first free element position to pos
	firstElement = pos;
}

template <class DT>
ArrayGLL<DT>::~ArrayGLL() { //Destructor method that sets all info, next and down values in the array in each row to NULL
	this->myGLL->setInfo(NULL);
	this->myGLL->setNext(NULL);
	this->myGLL->setDown(NULL);
}
int main()
{
	ArrayGLL<int> firstGLL(20);
	int noElements, value, next, down, parentPos;
	int pos = -1;
	int keyValue;
	int tempValue = 0;
	GLRow<int> oneRow;

	//first line of input contains the number of segments
	cin >> noElements;
	for (int i = 0; i < noElements; i++) {
		cin >> value >> next >> down;
		oneRow.setInfo(value);
		oneRow.setNext(next);
		oneRow.setDown(down);
		firstGLL[i] = oneRow;
	}

	firstGLL.setFirstFree(noElements);
	firstGLL.setFirstElement(0);
	cout << firstGLL << endl;
	firstGLL.display();
	cout << "\n" << endl;
	ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);

	(*secondGLL)[1].setInfo(600);
	(*secondGLL)[2].setInfo(700);

	cout << *secondGLL << endl;
	(*secondGLL).display();

	cout << "\n" << endl;

	keyValue = 700;
	pos = (*secondGLL).find(keyValue);
	if (pos != -1) {
		cout << (*secondGLL)[pos] << endl;
		(*secondGLL).findDisplayPath(keyValue);
		cout << "\n" << endl;
	}
	else {
		cout << "key not found" << endl;
	}
	/*parentPos = (*secondGLL).parentPos(keyValue);
	if (parentPos != -1) {
		cout << (*secondGLL)[parentPos] << endl;
	}*/
	cout << (*secondGLL).size() << endl;
	cout << (*secondGLL).noFree() << endl;
	delete secondGLL;

	return 0;
}


