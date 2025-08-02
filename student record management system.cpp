#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
};

vector<Student> students;

void loadFromFile() {
    ifstream infile("students.txt");
    students.clear();
    Student s;
    while (infile >> s.id) {
        infile.ignore(); // Ignore leftover newline
        getline(infile, s.name);
        infile >> s.age;
        infile.ignore();
        getline(infile, s.course);

        // Make sure all fields are read properly
        if (!infile.fail())
            students.push_back(s);
    }
    infile.close();
}

void saveToFile() {
    ofstream outfile("students.txt");
    for (const auto& s : students) {
        outfile << s.id << endl << s.name << endl << s.age << endl << s.course << endl;
    }
    outfile.close();
}

void addStudent() {
    Student s;
    cout << "Enter ID: ";
    cin >> s.id;
    cin.ignore(); // Remove the leftover newline
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();
    cout << "Enter Course: ";
    getline(cin, s.course);

    students.push_back(s);
    saveToFile();
    cout << "Student added successfully.\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }
    for (const auto& s : students) {
        cout << "\nID: " << s.id
             << "\nName: " << s.name
             << "\nAge: " << s.age
             << "\nCourse: " << s.course << "\n";
    }
}

void searchStudent() {
    int id;
    cout << "Enter student ID to search: ";
    cin >> id;
    for (const auto& s : students) {
        if (s.id == id) {
            cout << "\nFound Student:\n"
                 << "Name: " << s.name << "\nAge: " << s.age
                 << "\nCourse: " << s.course << "\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void updateStudent() {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;
    bool found = false;
    for (auto& s : students) {
        if (s.id == id) {
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, s.name);
            cout << "Enter new age: ";
            cin >> s.age;
            cin.ignore();
            cout << "Enter new course: ";
            getline(cin, s.course);
            saveToFile();
            cout << "Student updated.\n";
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            saveToFile();
            cout << "Student deleted.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n2. Display All Students\n3. Search Student\n";
        cout << "4. Update Student\n5. Delete Student\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
