// COMSC-210 | Lab 27 | Sarthak Pani
// adapted from the instructor map demo

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
using namespace std;

// each tuple stores friendship level, species, and catchphrase
using Villager = tuple<int, string, string>;
using VillagerMap = map<string, Villager>;

void print_villager(const string& name, const Villager& details);
void display_villagers(const VillagerMap& villagers);
void search_villager(const VillagerMap& villagers, const string& name);

int main_menu();
void change_friendship(VillagerMap& villagers, const string& name, int change);

int main() {
    VillagerMap villagers;
    villagers["Drago"] = {5, "Alligator", "Snap to It!"};
    villagers["Raymond"] = {8, "Cat", "Nice fit"};
    villagers.insert({"Kyle", {10, "Wolf", "Hubba hubba!"}});

    display_villagers(villagers);
    while (true) {
        int choice = main_menu();
        if (choice == 4)
            break;

        cout << "Villager name: ";
        string name;
        if (!getline(cin, name))
            break;

        if (choice == 1)
            change_friendship(villagers, name, 1);
        else if (choice == 2)
            change_friendship(villagers, name, -1);
        else
            search_villager(villagers, name);
        display_villagers(villagers);
    }
    cout << "Goodbye!" << endl;

    return 0;
}

void print_villager(const string& name, const Villager& details) {
    cout << name << " [" << get<0>(details) << ", " << get<1>(details)
         << ", " << get<2>(details) << "]" << endl;
}

void display_villagers(const VillagerMap& villagers) {
    cout << "Villager details:" << endl;
    if (villagers.empty()) {
        cout << "No villagers yet." << endl;
        return;
    }
    for (const auto& villager : villagers)
        print_villager(villager.first, villager.second);
}

void search_villager(const VillagerMap& villagers, const string& name) {
    // find does not add a new entry when the name is missing
    auto it = villagers.find(name);
    if (it != villagers.end())
        print_villager(it->first, it->second);
    else
        cout << name << " not found." << endl;
}

int main_menu() {
    cout << "\n1. Increase Friendship\n"
         << "2. Decrease Friendship\n"
         << "3. Search for Villager\n"
         << "4. Exit\n";
    while (true) {
        cout << "Enter choice: ";
        string input;
        if (!getline(cin, input))
            return 4;

        // accept a whole integer without trailing input
        istringstream entry(input);
        int choice;
        char extra;
        if (entry >> choice && !(entry >> extra) && choice >= 1 && choice <= 4)
            return choice;
        cout << "Please enter a number from 1 to 4." << endl;
    }
}

void change_friendship(VillagerMap& villagers, const string& name, int change) {
    auto it = villagers.find(name);
    if (it == villagers.end()) {
        cout << name << " not found." << endl;
        return;
    }

    // keep friendship within the allowed range
    int& level = get<0>(it->second);
    int updated = level + change;
    if (updated < 0 || updated > 10) {
        cout << name << " is already at friendship level " << level << "." << endl;
        return;
    }
    level = updated;
    cout << name << " now has friendship level " << level << "." << endl;
}
