#include<iostream>
#include "LinkList.h"
#include <cmath>

using namespace std;


/*===========================================================
//===================== Notes =============================//
- Create a Template LinkList Class!
===========================================================*/


//===========================================================//
// Copy Constructor: 
// Copies and allocates spaces for a new list
//===========================================================//
LinkList::LinkList(LinkList &list)
{
	LNode *head = list.retHead();
	LNode *node = NULL;

	int index = 0;
	while (head)
	{
		node = list.indexNodePtr(index);
		index++;
		pushEnd(node->data_);
		head = head->next_;
	}
}
//===========================================================//
// Destructor: 
// Deletes nodes an frees up allocated memory
//===========================================================//
LinkList::~LinkList()
{
	int index = 0;
	int counter = 0;
	int size = size_;
	while (counter < size)
	{
		//removing the front index 
		//until the list empty 
		deleteIndex(index);
		counter++;
	}
}

//===========================================================//
// listSize: Returns the number of nodes in the list
// Receives: Nothing
// Returns: _size = Number of nodes
//===========================================================//
int LinkList::listSize()
{
	return size_;
}
//===========================================================//
// displayList: Displays the entire list of nodes
// Receives: Nothing
// Returns: Nothing
//===========================================================//
void LinkList::displayList()
{
	LNode *head = headPtr_;
	if (head == NULL || size_ == 0)
	{
		//cout << "List is currently Empty! " << endl;
		throw LLExceptions(EMPTY_LIST);
	}
	int count = 0;
	cout << "===== List Display =====" << endl;
	while (head)
	{
		cout << "[" << count << "]: " << head->data_ << endl;
		count++;
		head = head->next_;
	}
}
//===========================================================//
// pushFront: Adds a node to the front of ther list
// Receives: value = the data to insert into the list
// Returns: True if successful insertion, else false
//===========================================================//

void LinkList::pushFront(int value)
{
	//Create LNode
	LNode *newItem;

	newItem = new LNode;

	if (newItem == NULL)
	{
		throw LLExceptions(UNKOWN_ERROR);
	}

	//If headPtr is NULL the start of the list
	if (headPtr_ == NULL)
	{
		newItem->data_ = value;
		newItem->next_ = NULL;
		size_++;
		headPtr_ = newItem;


	}
	//else more one or more in the list.
	else
	{
		newItem->data_ = value;
		newItem->next_ = headPtr_;
		headPtr_ = newItem;
		size_++;
	}
}
//===========================================================//
// removeFront: Removes the node at the front of the list
// Receives: Nothing
// Returns: True if successful deletion, else false
//===========================================================//
void LinkList::removeFront()
{
	LNode *oldHead = headPtr_;
	//If the LinkList is empty return error message
	if (headPtr_ == NULL)
	{
		//cout << "The list is empty!" << endl;
		throw LLExceptions(EMPTY_LIST);
	}
	//Else one or more Node is in the LinkList
	//Advance the current headPtr  
	headPtr_ = headPtr_->next_;
	delete oldHead;
	size_--;
}
//===========================================================//
// pushEnd: Adds a value to the end of the list
// Receives: value = the data to insert into the list
// Returns: True if successful insertion, else false
//===========================================================//
void  LinkList::pushEnd(int value)
{
	LNode* head = headPtr_;
	//Create and Initialize a new node
	LNode *newItem = new LNode();
	newItem->next_ = NULL;
	newItem->data_ = value;
	if (newItem == NULL)
	{
		throw LLExceptions(UNKOWN_ERROR);
		//return false;
	}

	if (head == NULL)
	{
		return pushFront(value);
	}
	while (head->next_ != NULL)
	{
		head = head->next_;
	}
	//head is now the end on the list because it is pointing to null
	head->next_ = newItem;
	size_++;
	//return true;

}

//===========================================================//
// removeEnd: Removes the node at the end of the list
// Receives: Nothing
// Returns: True if successful deletion, else false
//===========================================================//
void LinkList::removeEnd()
{
	int count = 0;
	LNode* head = headPtr_;
	LNode* tailPtr = NULL;
	//If the LinkList is empty return error message
	if (size_ == 0 && headPtr_ == NULL)
	{
		//cout << "The list is empty!" << endl;
		//return false;
		throw LLExceptions(EMPTY_LIST);
	}
	//If there is only one item in the LinkList
	//Remove the front!
	if (size_ == 1)
	{
		 removeFront();
		 return;
	}
	while (head)
	{
		//save the second to last node address
		if (count == ((size_ - 1) - 1))
		{
			tailPtr = head;
		}
		count++;
		head = head->next_;
	}
	//Removing the last item in the list & releasing
	//heap memory
	tailPtr->next_ = NULL;
	delete head;
	size_--;
	//return true;
}
//===========================================================//
// InsertIndex: Allows the user to input a value in any index
// in the current list, including adding one to the end!
// Receives: 
//		value = the data to insert into the list
//		index = the index where the new value will be inputed
// Returns: True if successful insertion, else false
//===========================================================//
	void LinkList::InsertIndex(int index, int value)
{
	int counter = 0;
	LNode *tailPtr = NULL;
	LNode* head = headPtr_;
	//Create and initialize a new LNode
	LNode *newItem = new LNode();
	newItem->next_ = NULL;
	newItem->data_ = value;
	//Test if heap allocation was successful
	if (newItem == NULL)
	{
		//return false;
		throw LLExceptions(UNKOWN_ERROR);
	}
	//Testing if user index is out of bounds
	if (index > size_ || index < 0)
	{
		//cout << "Invalid Index! " << endl;
		//return false;
		throw LLExceptions(INVALID_INDEX);
	}
	//Front insertion
	if (index == 0)
	{
		pushFront(value);
		return;

	}
	//Insertion from index ([1] - [N-1])
	if (index < size_)
	{
		while (counter != index)
		{
			//Saves a pointer the [index -1]
			if (counter == index - 1)
			{
				tailPtr = head;
			}
			head = head->next_;
			counter++;
		}
		//inserts new item between [N-1] & [N]
		tailPtr->next_ = newItem;
		newItem->next_ = head;
		size_++;
		return;
	}
	//End insertion
	if (index == size_)
	{
		pushEnd(value);
		return;
	}
	//Returns False if no insertion occurs
	throw LLExceptions(UNKOWN_ERROR);
}
//===========================================================//
// deleteIndex: Allows the user to delete a value in any index
// in the current list
// Receives: index = the index where the value will be deleted
// Returns: True if successful deletion, else false
//===========================================================//
void LinkList::deleteIndex(int index)
{
	LNode *tailPtr = NULL;
	LNode *head = headPtr_;
	int count = 0;
	//If invalid index return false
	if (index < 0 || index >= size_)
	{
		//cout << "Invalid index!!" << endl;
		//return false;
		throw LLExceptions(INVALID_INDEX);
	}
	//Front removal
	if (index == 0)
	{
		removeFront();
		return;
	}
	//End removal
	if (index == size_-1)
	{
		removeEnd();
		return;
	}
	//Stores the address before (index-1)
	//and after (index+1) the index 
	while (count < index)
	{
		
		if (count == index-1 )
		{
			tailPtr = head;
		}
		count++;
		head = head->next_;
	}
	//Freeing heap memory and adjusting LinkList
	tailPtr->next_ = head->next_;
	delete head;
	size_--;
	return;


}
//==== This function can be used to overload the [] operator ====//
//===========================================================//
// indexNodePtr: Returns the address of the node at 
// the given index 
// Receives: index = the "index" the node is located
// Returns: a pointer the node at the "index"
//===========================================================//
LNode* LinkList::indexNodePtr(int index)
{
	LNode *returnNode = headPtr_;
	//Testing for empty list
	if (returnNode == NULL && size_ == 0)
	{
		cout << "The list is empty!" << endl;
		return returnNode;
	}
	//Testing index out of bounds
	if (index < 0 || index >= size_)
	{
		cout << "Invalid Index!" << endl;
		return NULL;
	}
	//At least one item in the list
	//Returns the first node at index [0]
	if (index == 0 || size_ == 1)
	{
		return returnNode;
	}

	for (int count = 0; count < index; count++)
	{
		returnNode = returnNode->next_;
	}
	
	return returnNode;
}
//===========================================================//
// nodePtrIndex: Returns the index of the node 
// Receives: node = pointer to a node whos index will be 
// returned
// Returns: index of the node, else -1 if index does not exist
//===========================================================//
int LinkList::nodePtrIndex(LNode * node)
{
	LNode *head = headPtr_;
	
	//Testing for empty list
	if (head == NULL && size_ == 0)
	{
		cout << "The list is empty!" << endl;
		return -1;
	}
	if (head == node)
	{
		return 0;
	}

	for (int count = 0; count < size_; count++)
	{
		if (head == node)
		{
			return count;
		}
		head = head->next_;
	}
	return -1;
}

//===========================================================//
// swapIndex: Switches the values of two indexies 
// Receives: index1 = the "index" of the node to swap data
//			 index2 = the "index" of the second node to swap
// RReturns: True if successful swap, else false
//===========================================================//

void LinkList::swapIndex(int index1, int index2)
{
	LNode *nodePtr1;
	LNode *nodePtr2;
	int temp;

	//Testing for empty list
	if (headPtr_ == NULL && size_ == 0)
	{
		//cout << "Empty List!" << endl;
		throw LLExceptions(EMPTY_LIST);
	}
	if (size_ == 1)
	{
		//cout << "Error their is only one item in the list" << endl;
		throw LLExceptions(ONE_ITEM);
	}
	if (index1 < 0 || index1 >= size_)
	{
		//cout << "Error the first index is invalid!" << endl;
		throw LLExceptions(INVALID_FIRST);
	}
	if (index2 < 0 || index2 >= size_)
	{
		//cout << "Error the second index is invalid!" << endl;
		throw LLExceptions(INVALID_SECOND);
	}
	//Switching the values of each node at the given idexies
	nodePtr1 = indexNodePtr(index1);
	nodePtr2 = indexNodePtr(index2);
	temp = nodePtr1->data_;
	nodePtr1->data_ = nodePtr2->data_;
	nodePtr2->data_ = temp;
}

//===========================================================//
// copyOverIndex: Copies a value at the given "index" 
// Receives: index = the "index" of the node
//			 value = the data to copy over 
// Returns: True if successful swap, else false
//===========================================================//
void LinkList::copyOverIndex(int index, int value)
{
	LNode *head = headPtr_;
	head = indexNodePtr(index);
	if (head == NULL && size_ == 0)
	{
		throw LLExceptions(EMPTY_LIST);
	}
	head->data_ = value;
}

//===========================================================//
// remCase: This function removes value off the list depending
// on what function is passed to it
// Receives: func = A function that takes in a value and 
// returns a boolean depending on the case.
// Returns: Nothing
//===========================================================//
void LinkList::remCase(bool(*func) (int))
{

	LNode *head = headPtr_;
	int currIndex = 0;
	//Testing for an empty list
	if (head == NULL && size_ == 0)
	{
		//cout << "List is currently Empty! " << endl;
		throw LLExceptions(EMPTY_LIST);
	}
	cout << "===== Removing Numbers =====" << endl;
	//Displays the data being deleted
	// at the current "index"
	while (currIndex != size_-1)
	{
		//Deletes Node at current index 
		if ((*func) (head->data_)) //<=== function goes here!
		{
			cout << (head)->data_ << " Deleted! " << endl;
			deleteIndex(currIndex);
			currIndex--;
		}
		currIndex++;
		head = indexNodePtr(currIndex);
	}
}

//===========================================================//
// isEven: Dtermines wether a value is even or not
// Receives: value = the value to test 
// Returns: True if even, else false
//===========================================================//

bool isEven(int value)
{
	if ((value) % 2 == 0)
	{
		return true;
	}
	return false;
}
//===========================================================//
// isOdd: Dtermines wether a value is odd
// Receives: value = the value to test 
// Returns: True if odd, else false
//===========================================================//
bool isOdd(int value)
{
	return !isEven(value);
}
//===========================================================//
// isPrime: Dtermines wether a value is Prime
// Receives: value = the value to test 
// Returns: True if Prime, else false
//===========================================================//

bool isPrime(int value)
{
	bool bVal = true;
	for (int i = 2; i <= value / 2; i++)
	{
		if (value % i == 0)
		{
			bVal = false;
			break;
		}
	}
	return bVal;
}


// A number is a fibonacci # if either (5*n^2+4) or (5*n^2-4)
// are perfect squares or both
//===========================================================//
// isFibonacci: Deyytermines wether a value is a fibbonacci #
// Receives: value = the value to test 
// Returns: True if in fibonacci sequence, else false
//===========================================================//

bool isFibonacci(int value)
{
	int S1 = 5 * (pow(value, 2)) + 4;
	int S2 = 5 * (pow(value, 2)) - 4;

	int s1 = sqrt(S1);
	int s2 = sqrt(S2);
	if (value < 0)
	{
		return false;
	}


	if ((s1*s1 == S1) || (s2*s2 == S2))
	{
		return true;
	}
	return false;

}
// -Find the fastest algorith that will work for a link list!
// -Figure out how to 

//===========================================================//
// sort: Sorts the link list depending on the user choice
// Receives: headPtr = Pointer to the head of the list
//			 func = a function determining the direction of 
//					the sorting algorithm.
// Returns: Nothing
//===========================================================//
void LinkList::sort(LNode * headPtr, bool(*func)(int, int))
{
	LNode *tempNode = headPtr;
	//base case returns when its at the end of the list
	if (headPtr->next_ == NULL)
	{
		return;
	}
	else
	{
		tempNode = headPtr->next_;
		sort(tempNode, func);
	}
	//compares head node value with each node value 
	//swaps every time condition matches after each swap
	//check entire list again to make sure it is in order
	//if it isnt continue swaps
	if ((func)((tempNode->data_), (headPtr->data_)))
	{
		swapIndex(nodePtrIndex(tempNode), nodePtrIndex(headPtr));
		sort(headPtr, func);
		return;
	}
	return;


} 

LNode* LinkList::retHead()
{
	return headPtr_;
}
	

bool Up(int val1, int val2)
{
	if (val1 < val2)
	{
		return true;
	}
	return false;
}

bool Down(int val1, int val2)
{
	if (val1 > val2)
	{
		return true;
	}
	return false;
}
//===========================================================//
// Overloaded operator []
// Receives: index = the "index" of the node
// Returns: A Refrence to a LNode
//===========================================================//
LNode& LinkList::operator[](int index)
{
	LNode* returnNode = indexNodePtr(index);
	if (returnNode)
	{
		return *returnNode;
	}
	else
	{
		cout << "Error index invalid!" << endl;
		return *returnNode;
	}
}

//===========================================================//
// reverseList: Reverses the order of the entire linkList
// Receives: Nothing
// Returns: true if successful reversal of list, else false
//===========================================================//
void LinkList::reverseList()
{
	int currIndex = size_ - 1;
	LNode * node = NULL;
	//the last memeber of the linklist will be the new head!
	LNode *newHead = indexNodePtr(currIndex);

	for (int x = 0; x < size_ ; x++)
	{
		//When iteration with full list is done set
		//the new last node's next(NULL) 
		//and set the new head pinter!
		if (x == size_ - 1)
		{
			//set new end of list
			node = indexNodePtr(currIndex);
			node->next_ = NULL;
			//set new head pointer
			headPtr_ = newHead;
			return;
		}
		node = indexNodePtr(currIndex);
		//if the current node is not null set its next 
		//next pointer to its previous in the list
		if (node)
		{
			node->next_ = indexNodePtr(currIndex - 1);
		}
		currIndex--;
	}
	//if loop exits error has occured
	//cout << "Error could not reverse list!" << endl;
	throw LLExceptions(UNKOWN_ERROR);
}


//===========================================================//
// Overloaded operator <<
// Receives: os = putstream
//			 node = node data you want to display
// Returns: A Refrence to a LNode
//===========================================================//
ostream& operator<<(ostream& os, const LNode& node)
{
	os << node.data_;
	return os;
}
//===========================================================//
// Overloaded operator =
// Receives: value = the desired value to assigned the member
// Returns: Nothing
//===========================================================//
void LNode::operator=(int value)
{
	if (this != NULL)
	{
		data_ = value;
	}
}

//===========================================================//
// LLQuery: Handles exceptions when thrown
// Receives: error_message - an exception error
// Returns: Nothing
//===========================================================//

void LLQuery(LLExceptions & error_message)
{
	switch (error_message.GetExVal())
	{
	case INVALID_INDEX:
		cout << "INVALID_INDEX has been thrown" << endl << endl;
		break;
	case EMPTY_LIST:
		cout << "EMPTY_LIST has been thrown" << endl << endl;
		break;
	case INVALID_FIRST:
		cout << "INVALID_FIRST has been thrown" << endl << endl;
		break;
	case INVALID_SECOND:
		cout << "INVALID_SECOND has been thrown" << endl << endl;
		break;
	case ONE_ITEM:
		cout << "ONE_ITEM error has been thrown" << endl << endl;
		break;
	case  UNKOWN_ERROR:
		cout << "UNKOWN_ERROR has been thrown" << endl << endl;
		break;

	}
}


//===========================================================//
// Menu: Disdplays a Menu for every function available in 
// LinkList class
// Receives: A refereance to a list
// Returns: None
//===========================================================//
void Menu(LinkList* List)
{	

	int size = 0;
	bool menuActive = true;
	bool caseBool = true;
	bool(*func)(int, int) = NULL;
	bool(*remFunc)(int) = NULL;
	int userChoice = -1;
	int index1 = 0;
	int index2 = 0;
	int value = 0;

	while (menuActive)
	{
		cout << "1: pushFront " << endl
			<< "2: pushEnd " << endl
			<< "3: removeFront " << endl
			<< "4: removeEnd " << endl
			<< "5: InsertIndex " << endl
			<< "6: copyOverIndex " << endl
			<< "7: displayList " << endl
			<< "8: listSize " << endl
			<< "9: deleteIndex " << endl
			<< "10: reverseList " << endl
			<< "11: sort" << endl
			<< "12 Remove Case" << endl
			<< "-1: EXIT! " << endl
			<< endl << endl << "Choice:	";


		cin >> userChoice;

		while (cin.fail()) {
			cout << "Error please enter a valid integer! " << endl << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Choice:	";
			cin >> userChoice;
		}
		cout << endl;
		switch (userChoice)
		{
		case -1:
			menuActive = false;
			break;

		case 1:
			try
			{
				cout << "Please enter a value to be pushed in the front of the LinkList! " << endl;
				cin >> value;

				List->pushFront(value);
				cout << endl << endl;
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;
		case 2:
			try
			{
				cout << "Please enter a value to be pushed in the end of the LinkList! " << endl;
				cin >> value;
				List->pushEnd(value);
				cout << endl << endl;
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 3:
			try
			{
				List->removeFront();
				cout << "The first node in the link list has been removed!" << endl << endl;

			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;
		case 4:
			try
			{
				List->removeEnd();
				cout << "The last node in the link list has been removed!" << endl << endl;
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;
		case 5:
			try
			{
				cout << "Please enter an value and an index to place it into the list!" << endl;
				cout << "Value: ";
				cin >> value;
				cout << endl;
				cout << "index: ";
				cin >> index1;
				cout << endl << endl;

				List->InsertIndex(index1, value);
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 6:
			try
			{
				cout << "Please enter an value and an index to replace in the list!" << endl;
				cout << "Value: ";
				cin >> value;
				cout << endl;
				cout << "index: ";
				cin >> index1;
				cout << endl << endl;
				List->copyOverIndex(index1, value);
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;
		case 7:
			try
			{
				List->displayList();
				cout << endl << endl;

			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 8:
			try
			{
				size = List->listSize();
				cout << "The LinkList size is " << size << endl << endl;
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 9:
			try
			{
				cout << "Please enter index to delete its value from the list!" << endl;
				cout << "index: ";
				cin >> index1;
				cout << endl << endl;
				List->deleteIndex(index1);
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 10:
			try
			{
				List->reverseList();
				cout << "The LinkList order has been reversed!" << endl << endl;

			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		case 11:


			try
			{
				while (caseBool)
				{
					cout << "Choose (0) for upwards and (1) for downwards! " << endl;
					cout << "Choice: ";
					cin >> value;
					while (cin.fail())
					{
						cout << "Error please enter a valid integer! " << endl << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Choice: ";
						cin >> value;
					}
					if (value == 0)
					{
						func = Up;
						caseBool = false;
					}
					else if (value == 1)
					{
						func = Down;
						caseBool = false;

					}
					else
					{
						cout << "Error please enter a valid integer! " << endl << endl;
					}
				}
				caseBool = true;
				List->sort(List->retHead(), func);
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;
		case 12:


			try
			{
				while (caseBool)
				{
					cout << "Choose what values you would like to remove " << endl
						<< " (0) Even (1) Odd (2) More Options" << endl;
					cout << "Choice: ";
					cin >> value;
					while (cin.fail())
					{
						cout << "Error please enter a valid integer! " << endl << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Choice: ";
						cin >> value;
					}
					if (value == 0)
					{
						remFunc = isEven;
						caseBool = false;
					}
					else if (value == 1)
					{
						remFunc = isOdd;
						caseBool = false;
					}
					else if (value == 2)

					{
						cout << "(0) Prime (1) Fibbanacci " << endl;
						cout << "Choice: ";
						cin >> value;


						while (cin.fail())
						{
							cout << "Error please enter a valid integer! " << endl << endl;
							cin.clear();
							cin.ignore(256, '\n');
							cout << "Choice: ";
							cin >> value;
						}
						if (value == 0)
						{
							remFunc = isPrime;
							caseBool = false;
						}
						else if (value == 1)
						{
							remFunc = isFibonacci;
							caseBool = false;
						}

					}
					else
					{
						cout << "Error please enter a valid integer! " << endl << endl;
					}
				}
				caseBool = true;
				List->remCase(remFunc);
				cout << endl;
			}
			catch (LLExceptions & error_message)
			{
				LLQuery(error_message);
			}
			break;

		default:
			cout << "Error please enter a valid integer! " << endl;

			break;

		}

	}
}

