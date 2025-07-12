#include<iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

class Item//superclass
{
public:
	string name;
	int quantity;
	bool stackable;
	Item(string n, int q, bool s) {//constructor for when i make the items.
		name = n;
		quantity = q;
		stackable = s;
	}
	Item() {//default constructor
		name = "empty";
		quantity = 0;
		stackable = false;
	}
	void display()//prints details of items.
	{
		cout << name << ", Qty: " << quantity << endl;
	}
	

};
class Stackable : public Item //items such as apples or arrows.
{
public:
	Stackable(string n, int q, bool s) : Item(n, q, s) { s = true; }

	
};
class NonStackable :public Item //items such as swords or axes.
{
public:
	NonStackable(string n, int q, bool s) : Item(n, q, s) { s = false; }
	
};

bool compareMyObjects(const Item& a, const Item& b) {//used in the sort function to specify sorting by what
	return a.name < b.name; // ascending order sorted by name
}
int main()
{
	cout << "your inventory has 3 spaces\n"; 
	
	int size = 3;
	
	//Item* Inventory = new Item[size];
	std::vector<Item> inventory;
	int decision;
	for (int i = 0; i < size; i++)
	{
		std::cout << "\n1.add a stackable \n2.add a nonstackable \n3.remove an item \n4.display inventory\n";
		cin >> decision;
		if (decision == 1)//add stackable
		{
			cout << "what item would you like to add?";
			string newName;
			
			
			
			cin >> newName;
			cout << "how many?";
			int qty;
			cin >> qty;
			bool repeat=false;
			int low = 0;//start of binary search
			int high = i-1;
			while (low <= high) {
				int mid = low + (high - low) / 2; // get midpoint as an integer
				int result1 = inventory[mid].name.compare(newName);
				if (result1 == 0) {
					cout << "same item detected\n";
					inventory[mid].quantity = inventory[mid].quantity + qty;
					
					repeat = true;
					--i;
					
					break;

				}
				else if (result1 > 0) {
					low = mid + 1; // Search in the right half
				}
				else {
					high = mid - 1; // Search in the left half
				}
			}//end of binary search
			if (!repeat) {//if its not repeated item.  
				inventory.push_back(Stackable(newName, qty, true));//record in the txt file.  
				ofstream file("record.txt", ios::app);
				if (file.is_open()) {
					file << newName << " " << qty << " has been added." << endl;
					file.close();
				}
			}
			cout << qty<<" " << newName << "s" << " have been added." << endl;
				

		}
		else if (decision == 2)//add nonstackable
		{
			cout << "what item would you like to add?";
			string newName;
			cin >> newName;

			int qty = 1;
			ofstream file("record.txt", ios::app);
			if (file.is_open()) {
				file << "The " << newName << " has been added." << endl;
				file.close();
			}
			inventory.push_back(NonStackable(newName, qty, false));
			cout <<"The " << newName << " has been added." << endl;

		}
		else if (decision == 3)//remove item
		{
			
			if (inventory.size() > 0) {
				cout << "which slot is the item you want to remove in?\n";
				int removedSlot;
				cin >> removedSlot;
				removedSlot = removedSlot - 1;
				ofstream file("record.txt", ios::app);
				if (file.is_open()) {
					file << inventory[removedSlot].name << " has been removed." << endl;
					file.close();
				}
				cout << inventory[removedSlot].name<< " has been removed\n";
				inventory.erase(inventory.begin() + removedSlot);

				
				--i;
			}
				
			else
			{
				cout << "your inventory is already empty.\n";
				i--;
			}

		}
		else if (decision == 4)//display inventory
		{
			for (int i = 0; i < inventory.size(); i++)
			{
				inventory[i].display();
				cout << "\n";

				
			}
			cout << "inventory size: "<<inventory.size() << endl;
			i--;
		}

	}
	cout << "your items will now be sorted alphabetically.\n";
	std::sort(inventory.begin(), inventory.end(), compareMyObjects);//vector must be sorted for binary search
	for (int i = 0; i < inventory.size(); i++)
	{
		inventory[i].display();
		cout << "\n";
	}
	cout << "what item would you like to select? (type in the correct name to find which slot your item is in)";
	string desiredItem;
	cin >> desiredItem;
	
	int low = 0;
	int high = inventory.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2; // calc midpoint 
		int result1 = inventory[mid].name.compare(desiredItem);
		if (result1 == 0) {
			cout<< "Your item is in slot "<<mid + 1; // found item
			return mid;
		}
		else if (result1<0) {
			low = mid + 1; // search right half
		}
		else {
			high = mid - 1; // search left half
		}
	}
	cout<<"your item does not exist"; // Target not found

	return 0;
}
//inventory management with consumables, use binary search for selecting items
//use text files for keeping track of what has happened
//