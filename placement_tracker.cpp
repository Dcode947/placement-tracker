#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Topic {
    string subject;
    string topicName;
    string status;  // Not Started / In Progress / Completed
};

vector<Topic> topics;

// Load data from file
void loadData() {
    ifstream file("tracker.txt");
    if (!file) return;

    Topic t;
    while (file >> t.subject >> t.topicName >> t.status) {
        topics.push_back(t);
    }
    file.close();
}

// Save data to file
void saveData() {
    ofstream file("tracker.txt");
    for (auto &t : topics) {
        file << t.subject << " "
             << t.topicName << " "
             << t.status << endl;
    }
    file.close();
}

// Add new topic
void addTopic() {
    Topic t;
    cout << "Enter Subject (DSA/OS/DBMS/etc): ";
    cin >> t.subject;
    cout << "Enter Topic Name: ";
    cin >> t.topicName;
    t.status = "NotStarted";

    topics.push_back(t);
    saveData();
    cout << "Topic added successfully!\n";
}

// Update topic status
void updateStatus() {
    int index;
    cout << "Enter topic number to update: ";
    cin >> index;

    if (index < 1 || index > topics.size()) {
        cout << "Invalid index\n";
        return;
    }

    cout << "1. Not Started\n2. In Progress\n3. Completed\nChoose status: ";
    int choice;
    cin >> choice;

    if (choice == 1) topics[index - 1].status = "NotStarted";
    else if (choice == 2) topics[index - 1].status = "InProgress";
    else if (choice == 3) topics[index - 1].status = "Completed";
    else {
        cout << "Invalid choice\n";
        return;
    }

    saveData();
    cout << "Status updated!\n";
}

// View all topics
void viewTopics() {
    if (topics.empty()) {
        cout << "No topics added yet.\n";
        return;
    }

    cout << "\n Placement Preparation Tracker\n";
    for (int i = 0; i < topics.size(); i++) {
        cout << i + 1 << ". "
             << topics[i].subject << " - "
             << topics[i].topicName << " ["
             << topics[i].status << "]\n";
    }
}

// Main menu
int main() {
    loadData();
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Topic\n";
        cout << "2. Update Topic Status\n";
        cout << "3. View Topics\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTopic(); break;
            case 2: updateStatus(); break;
            case 3: viewTopics(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}