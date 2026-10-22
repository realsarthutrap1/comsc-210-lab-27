// COMSC-210 | Lab 27 | Sarthak Pani
// adapted from the instructor map demo

#include <iostream>
#include <map>
#include <string>
#include <tuple>
using namespace std;

// each tuple stores friendship level, species, and catchphrase
using Villager = tuple<int, string, string>;
using VillagerMap = map<string, Villager>;

void print_villager(const string& name, const Villager& details);
void display_villagers(const VillagerMap& villagers);
void search_villager(const VillagerMap& villagers, const string& name);

int main() {
    VillagerMap villagers;
    villagers["Drago"] = {5, "Alligator", "Snap to It!"};
    villagers["Raymond"] = {8, "Cat", "Nice fit"};
    villagers.insert({"Kyle", {10, "Wolf", "Hubba hubba!"}});

    // exercise tuple output with a range loop and iterators
    display_villagers(villagers);
    cout << "\nVillager details using iterators:" << endl;
    for (VillagerMap::const_iterator it = villagers.begin(); it != villagers.end(); ++it)
        print_villager(it->first, it->second);

    // check a tuple field and search for existing and missing names
    cout << "\nDrago's friendship level: " << get<0>(villagers.at("Drago")) << endl;
    search_villager(villagers, "Drago");
    villagers.erase("Raymond");
    search_villager(villagers, "Raymond");
    display_villagers(villagers);

    // confirm that clearing removes all the tuples
    cout << "\nSize before clear: " << villagers.size() << endl;
    villagers.clear();
    cout << "Size after clear: " << villagers.size() << endl;
    display_villagers(villagers);

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
