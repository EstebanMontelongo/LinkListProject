#include "LinkList.h"

#include <iostream>

using namespace std;
void Menu(LinkList* List);

int main()
{

	int size = 0;
	LinkList List;
	LinkList *listPtr = &List;
	
	
	
	
	//===========================================================//
	/*--------------------Debugging Tests!!----------------------*/
	//===========================================================//
	//List.displayList();
	List[0] = 55; // List is empty so invalid index

	List.pushFront(5);
	List[0] = 55;
	List.pushFront(4);
	List.pushFront(3);
	List.pushFront(2);
	List.pushFront(1);
	List.displayList();
	cout << List[2] << endl; 
	List.displayList();
	List.deleteIndex(1);
	List.displayList();
	List.copyOverIndex(1, 100);
	List.displayList();
	size = List.listSize();

	cout << "List size is "<< size << endl;
	List.displayList();
	List.swapIndex(1,2);
	List.displayList();
	List.pushFront(2);
	List.pushEnd(65);
	List.pushEnd(23);
	List.pushEnd(9);
	List.pushEnd(13);
	List.pushEnd(45689);
	List.pushEnd(3214);

	List.displayList();
	
	List.remCase(isFibonacci);
	List.displayList();
	//first arguement head pointer, second arguement sort up or down
	List.sort(List.retHead(), Up);
	List.displayList();
	List.sort(List.retHead(), Down);
	List.displayList();
	List.reverseList();
	List.displayList();
	


	//Create a looping menu, allow them to choose what function to use on the link list
	//display proper output!
	
	Menu(listPtr);


	

	return 0;
}



