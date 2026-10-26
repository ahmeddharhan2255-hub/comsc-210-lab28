// COMSC-210 | Lab 28 | Ahmad Dharhan

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void find_goat(list<Goat> trip, string name);
void size(list<Goat> trip);
void reverseGoat(list<Goat> &trip);
void oldestGoat(list<Goat> &trip);
void youngestGoat(list<Goat> &trip);
    
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name;
    string color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 7) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Enter Goat Name.\n";
                cin >> name;
                find_goat(trip, name);
                break;
            case 5:
                cout << "The size of your list is: ";
                size(trip);
                break;
            case 6:
                reverseGoat(trip);
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] See if Goat exists\n";
    cout << "[5] Find Size of List\n";
    cout << "[6] Reverse Goats\n";
    cout << "[7] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 8) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void find_goat(list<Goat> trip, string name){
    bool found = false;

    for (auto gt: trip){
        if (gt.get_name() == name){
            found = true;
            break; 
        }

    }

    if (found){
        cout << name <<  " exists!" << endl;
    }
    else{
        cout << name << " doesn't exist" << endl;
    }
}

void size(list<Goat> trp){
    int size = accumulate(trp.begin(),trp.end(),0,[](int total, const Goat gt){
        return total + 1;
    });

    cout<<size;
}
        
void reverseGoat(list<Goat> &trip){
    reverse(trip.begin(),trip.end()); 
}

void oldestGoat(list<Goat> &trip){
    if (trip.empty()){
        cout << "No goats in list" << endl;
        return;
    }

    auto it = max_element(trip.begin(),trip.end(), 
        [](const Goat& a, const Goat& b){

        return a.get_age() < b.get_age()

    )};
}

void youngestGoat(list<Goat> &trip){

}