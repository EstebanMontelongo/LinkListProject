#pragma once
#include <iostream>
using namespace std;


enum LLError { INVALID_INDEX, EMPTY_LIST, UNKOWN_ERROR,
				INVALID_FIRST, INVALID_SECOND, ONE_ITEM };


class LLExceptions
{
public:
	LLExceptions(LLError exVal) :m_exVal(exVal){}
	LLError GetExVal()const{ return m_exVal; }

private: 
	LLError m_exVal;


};


struct LNode
{
	int data_;
	LNode *next_;
	void operator=(int value);
};

class LinkList 
{
public:
	//ctor
	LinkList():headPtr_(NULL),size_(0){}
	LinkList(LinkList &list);
	~LinkList();

	//Functions
	int listSize(); //
	void displayList();//
	void pushFront(int value);//
	void pushEnd(int value);//
	void InsertIndex(int index, int value);//
	void removeFront();//
	void removeEnd();//
	void deleteIndex(int index);//
	void copyOverIndex(int index, int value);//
	void swapIndex(int index1, int index2);
	void remCase(bool(*func) (int));
	void reverseList();

	
	LNode& operator[] (int value);
	void sort(LNode *headPtr, bool(*func) (int, int));
	LNode* retHead();
	


private:
	LNode* indexNodePtr(int index);
	int nodePtrIndex(LNode * node);
	LNode *headPtr_; 
	int size_;
};

//Overloading the << operator
ostream& operator<< (ostream& os, const LNode& node);

//remCase passing functions
bool isEven(int value);
bool isOdd(int value);
bool isPrime(int value);
bool isFibonacci(int value);
//sort passing functions
bool Up(int val1, int val2);
bool Down(int val1, int val2);

void LLQuery(LLExceptions &error_message);
