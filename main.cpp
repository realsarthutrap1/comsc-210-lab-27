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
bool read_number(const string& prompt, int minimum, int maximum, int& value);
bool read_text(const string& prompt, string& value);
bool add_villager(VillagerMap& villagers);
void delete_villager(VillagerMap& villagers, const string& name);
void change_friendship(VillagerMap& villagers, const string& name, int change);

int main() {
    VillagerMap villagers;
    villagers["Drago"] = {5, "Alligator", "Snap to It!"};
    villagers["Raymond"] = {8, "Cat", "Nice fit"};
    villagers.insert({"Kyle", {10, "Wolf", "Hubba hubba!"}});

    display_villagers(villagers);
    while (true) {
        int choice = main_menu();
        if (choice == 6)
            break;

        if (choice == 1) {
            if (!add_villager(villagers))
                break;
        } else {
            string name;
            if (!read_text("Villager name: ", name))
                break;
            if (choice == 2)
                delete_villager(villagers, name);
            else if (choice == 3)
                change_friendship(villagers, name, 1);
            else if (choice == 4)
                change_friendship(villagers, name, -1);
            else
                search_villager(villagers, name);
        }
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
    cout << "\n1. Add Villager\n"
         << "2. Delete Villager\n"
         << "3. Increase Friendship\n"
         << "4. Decrease Friendship\n"
         << "5. Search for Villager\n"
         << "6. Exit\n";
    int choice;
    if (!read_number("Enter choice: ", 1, 6, choice))
        return 6;
    return choice;
}

bool read_number(const string& prompt, int minimum, int maximum, int& value) {
    while (true) {
        cout << prompt;
        string input;
        if (!getline(cin, input))
            return false;

        // accept a whole integer without trailing input
        istringstream entry(input);
        int number;
        char extra;
        if (entry >> number && !(entry >> extra) && number >= minimum && number <= maximum) {
            value = number;
            return true;
        }
        cout << "Please enter a number from " << minimum << " to " << maximum << "." << endl;
    }
}

bool read_text(const string& prompt, string& value) {
    while (true) {
        cout << prompt;
        string input;
        if (!getline(cin, input))
            return false;
        if (input.find_first_not_of(" \t\r\n\v\f") != string::npos) {
            value = input;
            return true;
        }
        cout << "Please enter a nonempty value." << endl;
    }
}

bool add_villager(VillagerMap& villagers) {
    string name, species, catchphrase;
    int friendship;
    if (!read_text("Villager name: ", name))
        return false;
    if (villagers.find(name) != villagers.end()) {
        cout << name << " already exists." << endl;
        return true;
    }

    // finish all input before changing the map
    if (!read_number("Friendship level: ", 0, 10, friendship) ||
        !read_text("Species: ", species) || !read_text("Catchphrase: ", catchphrase)) {
        cout << "Addition canceled: input ended." << endl;
        return false;
    }
    villagers.insert({name, {friendship, species, catchphrase}});
    cout << name << " added." << endl;
    return true;
}

void delete_villager(VillagerMap& villagers, const string& name) {
    if (villagers.erase(name) != 0)
        cout << name << " deleted." << endl;
    else
        cout << name << " not found." << endl;
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
