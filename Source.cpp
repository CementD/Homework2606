#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int MAX_ENTRIES = 100;

class DirectoryEntry {
public:
    string companyName;
    string owner;
    string phone;
    string address;
    string activity;

    DirectoryEntry() {}
    DirectoryEntry(string cName, string own, string ph, string addr, string act)
        : companyName(cName), owner(own), phone(ph), address(addr), activity(act) {}
};

class Directory {
private:
    DirectoryEntry entries[MAX_ENTRIES];
    int entryCount;
    const string fileName = "directory.txt";

    void loadFromFile() {
        ifstream file(fileName);
        string line;
        entryCount = 0;
        while (getline(file, line) && entryCount < MAX_ENTRIES) {
            stringstream ss(line);
            string companyName, owner, phone, address, activity;
            getline(ss, companyName, ',');
            getline(ss, owner, ',');
            getline(ss, phone, ',');
            getline(ss, address, ',');
            getline(ss, activity, ',');
            entries[entryCount++] = DirectoryEntry(companyName, owner, phone, address, activity);
        }
    }

    void saveToFile() {
        ofstream file(fileName);
        for (int i = 0; i < entryCount; i++) {
            file << entries[i].companyName << "," << entries[i].owner << "," << entries[i].phone << ","
                << entries[i].address << "," << entries[i].activity << "\n";
        }
        file.close();
    }

public:
    Directory() : entryCount(0) {
        loadFromFile();
    }

    ~Directory() {
        saveToFile();
    }

    void addEntry(const DirectoryEntry& entry) {
        if (entryCount < MAX_ENTRIES) {
            entries[entryCount++] = entry;
        }
        else {
            cerr << "Error: Directory is full, cannot add more entries.\n";
        }
    }

    void searchByCompanyName(string name) const {
        for (int i = 0; i < entryCount; i++) {
            if (entries[i].companyName == name) {
                printEntry(entries[i]);
            }
        }
    }

    void searchByOwner(string owner) const {
        for (int i = 0; i < entryCount; i++) {
            if (entries[i].owner == owner) {
                printEntry(entries[i]);
            }
        }
    }

    void searchByPhone(string phone) const {
        for (int i = 0; i < entryCount; i++) {
            if (entries[i].phone == phone) {
                printEntry(entries[i]);
            }
        }
    }

    void searchByActivity(string activity) const {
        for (int i = 0; i < entryCount; i++) {
            if (entries[i].activity == activity) {
                printEntry(entries[i]);
            }
        }
    }

    void printAllEntries() const {
        for (int i = 0; i < entryCount; i++) {
            printEntry(entries[i]);
        }
    }

    void printEntry(const DirectoryEntry& entry) const {
        cout << "Company Name: " << entry.companyName << "\n"
            << "Owner: " << entry.owner << "\n"
            << "Phone: " << entry.phone << "\n"
            << "Address: " << entry.address << "\n"
            << "Activity: " << entry.activity << "\n"
            << "-------------------------\n";
    }
};

int main() {
    Directory directory;

    directory.addEntry(DirectoryEntry("Company A", "Name A", "123456789", "Street A", "Activity A"));
    directory.addEntry(DirectoryEntry("Company B", "Name B", "987654321", "Street B", "Activity B"));

    cout << "Search by company name 'Company A':\n";
    directory.searchByCompanyName("Company A");

    cout << "\nSearch by owner 'Name B':\n";
    directory.searchByOwner("Name B");

    cout << "\nSearch by phone '123456789':\n";
    directory.searchByPhone("123456789");

    cout << "\nSearch by activity 'Activity B':\n";
    directory.searchByActivity("Activity B");

    cout << "\nAll entries:\n";
    directory.printAllEntries();

    return 0;
}
