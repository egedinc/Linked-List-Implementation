//*****************************************************************************
// Ege Toker Dinç CS204 hw2     This code makes 5 operations on 4 linked lists
//21.10.2018 Sabanci University    Istanbul
//*****************************************************************************
#include <iostream>
#include <string>

using namespace std;

#define SIZE 4

struct complexNode { //node that can point to 4 next nodes

	int num;
	string type; // Can be "S"(standard) or "M"(merged)
	complexNode* nexts[SIZE];

	complexNode(int n = 0)
		: num(n) {
		for(int i = 0; i < SIZE; i++)
			nexts[i] = nullptr;
		type = "S";
	}
};

complexNode* heads[SIZE];



void Message() // print out the menu
{
	cout << "\n1 - Insert a new node\n" << 
			"2 - Merge lists\n" << 
			"3 - Print list\n" << 
			"4 - Print all lists\n" <<
			"5 - Delete node\n" <<
			"6 - Exit\n\n" <<
			"Enter your choice:";
}

void Insert() //insert a given value to a list
{
	int listNum, element;

	cout << "Please enter which list you want to add to: ";
	cin >> listNum;
	
	if(listNum < 0 || listNum > 3){
		cout << "Selection out of range." << endl;
	}
	else{
		cout << "Please enter the element you want to add: ";
		cin >> element;

		if(heads[listNum] == nullptr){
			heads[listNum] = new complexNode(element);
			for(int i = 0; i < SIZE; i++){
				heads[listNum]->nexts[i] = nullptr;	
			}
		}
		else{
			complexNode * ptr = heads[listNum];
			complexNode * tmp = new complexNode(element);
			while(ptr->nexts[listNum] != nullptr)
			{
				ptr = ptr->nexts[listNum];
			}
			ptr->nexts[listNum] = tmp;
		}
	}
}

void Merge() // squeeze the lists together by using the common nodes as one and deleting the unnnecessary ones
{
	for (int i=0; i<SIZE-1; i++){
		complexNode * ptr1 = heads[i];
		for (int j=i+1; j<SIZE; j++){   // 2 for loops to iterate between binary comparisons in 4 lists
			complexNode * ptr2 = heads[j];
			complexNode * prev = ptr2;
			if(ptr1 != nullptr && ptr2 != nullptr){ // as long as there is a next node
				while(ptr1 != nullptr && ptr2 != nullptr)  // for all values in the ith list
				{
					if(ptr1->num == ptr2->num){ // examine the first element seperately
						if(ptr1->type == "S") 
							ptr1->type = "M" + to_string(i); // no need to change to merged if already merged
						ptr1->nexts[j] = ptr2->nexts[j];
						ptr2 = ptr2->nexts[j];
						delete prev;
						prev = ptr1;
						heads[j] = ptr1;
					}
					else{
						ptr2 = ptr2->nexts[j];
					}
					while(ptr2 != nullptr){  // for all values in the jth list
						if(ptr1->num == ptr2->num){
							if(ptr1->type == "S")
								ptr1->type = "M" + to_string(i);
							ptr1->nexts[j] = ptr2->nexts[j];
							ptr2 = ptr2->nexts[j];
							if(ptr1->type == "S")
								delete prev->nexts[j];
							prev->nexts[j] = ptr1;
							prev = ptr1;
						}
						else{
							prev = ptr2;
							ptr2 = ptr2->nexts[j];
						}
					}
					ptr1 = ptr1->nexts[i];
					if(ptr1 == nullptr){
						ptr1 = heads[i];
						break;
					}
					ptr2 = heads[j];
					prev = ptr2;
					
				}
			}
		}
	}
}

void Print() // prints the desired linked list
{
	int listNum;
	cout << "Please enter which list you want to print: ";
	cin >> listNum;

	if(listNum < 0 || listNum > 3){
		cout << "Selection out of range." << endl;
	}
	else{
		complexNode * ptr = heads[listNum];
		//List is empty
		if(heads[listNum] == nullptr)
		{
			cout << "The list is empty" << endl;
		}
		else
		{
			while(ptr != nullptr)
			{
				cout << ptr->type << "-" << ptr->num << " ";
				ptr = ptr->nexts[listNum];
			}
			cout << endl;
		}
	}
}

void PrintAll() // prints all 4 linked lists
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << "***** LIST " << i << " *****" << endl;
		complexNode * ptr = heads[i];
		//List is empty
		if(heads[i] == nullptr)
		{
			cout << "The list is empty" << endl;
		}
		else
		{
			while(ptr != nullptr)
			{
				cout << ptr->type << "-" << ptr->num << " ";
				ptr = ptr->nexts[i];
			}
			cout << endl;
		}
	}
}

void Delete() // deletes a desired value from a list
{
	int listNum, toBeDeleted;
	cout << "Please enter which list you want delete from: ";
	cin >> listNum;

	if(listNum < 0 || listNum > 3){
		cout << "Selection out of range." << endl;
	}
	else{
		cout << "Please enter the number to be deleted: ";
		cin >> toBeDeleted;
		
		complexNode* ptr = heads[listNum];
		complexNode* prev = ptr;
		bool flag = false; // in case the value is not in the list
		if(ptr != nullptr){
			if(ptr->num == toBeDeleted){ //if it's the first element
				if(ptr->type == "S"){
					heads[listNum] = ptr->nexts[listNum];
					delete ptr;
				}
				else{ // if it's a mnerged node
					heads[listNum] = ptr->nexts[listNum];
					ptr->nexts[listNum] = nullptr;
					int count = 0;
					for (int i = 0; i < SIZE; i++){  //check if it became a standard node after deletion
						if(ptr->nexts[i] != nullptr)
							count++;
					}
					if(count < 2)
						ptr->type = "S";
				}
				flag = true;
			}
			else{  // if not the first element
				ptr = ptr->nexts[listNum];
				while(ptr != nullptr){
					if(ptr->num == toBeDeleted){
						if(ptr->type == "S"){
							prev->nexts[listNum] = ptr->nexts[listNum];
							delete ptr;
						}
						else{
							prev->nexts[listNum] = ptr->nexts[listNum];
							ptr->nexts[listNum] = nullptr;
							int count = 0;
							for (int i = 0; i < SIZE; i++){
								if(ptr->nexts[i] != nullptr)
									count++;
							}
							if(count < 2)
								ptr->type = "S";
						}
						flag = true;
						break;
					}
					prev = ptr;
					ptr =  ptr->nexts[listNum];
				}
			}
		}
		if(ptr == nullptr)
			cout << "The list is empty" << endl;
		else if(!flag)
			cout << "That number does not exist in the list " << listNum << endl;
	}
}

int main()
{
	for(int i = 0; i < SIZE; i++){ //create head pointers
		heads[i] = nullptr;		
	}
	
	int choice;
	while (true)  // keep showing the menu until user exits
	{
		Message();
		cin >>  choice;
		if (choice == 1) {
			Insert();
		}
		else if(choice == 2) {
			Merge();
		}
		else if(choice == 3) {
			Print();
		}
		else if(choice == 4) {
			PrintAll();
		}
		else if(choice == 5) {
			Delete();
		}
		else if(choice == 6) {
			return 0;
		}
		else {
			cout << "Invalid choice! Enter again: ";
		}
	}
	return 0;
}