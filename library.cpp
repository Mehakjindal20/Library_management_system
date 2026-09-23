#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

/* ---------- Utility ---------- */
bool equalsIgnoreCase(const char* a, const char* b) {
    return strcasecmp(a, b) == 0;
}

/* ---------- BOOK CLASS ---------- */
class Book {
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void create() {
        cout << "\nEnter Book No: ";
        cin >> bno;
        cin.ignore();
        cout << "Enter Book Name: ";
        cin.getline(bname, 50);
        cout << "Enter Author Name: ";
        cin.getline(aname, 20);
    }

    void show() const {
        cout << "\nBook No: " << bno
             << "\nBook Name: " << bname
             << "\nAuthor: " << aname << endl;
    }

    char* getNo() { return bno; }

    void report() const {
        cout << left << setw(10) << bno
             << setw(30) << bname
             << setw(20) << aname << endl;
    }
};

/* ---------- STUDENT CLASS ---------- */
class Student {
    char admno[6];
    char name[20];
    char bookno[6];
    int token;

public:
    void create() {
        cout << "\nEnter Admission No: ";
        cin >> admno;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 20);
        token = 0;
        bookno[0] = '\0';
    }

    void show() const {
        cout << "\nAdmission No: " << admno
             << "\nName: " << name
             << "\nBooks Issued: " << token;
        if (token)
            cout << "\nBook No: " << bookno;
        cout << endl;
    }

    char* getAdmNo() { return admno; }
    char* getBookNo() { return bookno; }
    int getToken() const { return token; }

    void issueBook(const char* bno) {
        strcpy(bookno, bno);
        token = 1;
    }

    void returnBook() {
        token = 0;
        bookno[0] = '\0';
    }

    void report() const {
        cout << left << setw(10) << admno
             << setw(20) << name
             << setw(5) << token << endl;
    }
};

/* ---------- GLOBAL OBJECTS ---------- */
fstream fp;
Book bk;
Student st;

/* ---------- FUNCTIONS ---------- */
void addBook() {
    fp.open("book.dat", ios::out | ios::app | ios::binary);
    bk.create();
    fp.write((char*)&bk, sizeof(Book));
    fp.close();
}

void addStudent() {
    fp.open("student.dat", ios::out | ios::app | ios::binary);
    st.create();
    fp.write((char*)&st, sizeof(Student));
    fp.close();
}

void showAllBooks() {
    fp.open("book.dat", ios::in | ios::binary);
    cout << "\nBOOK LIST\n";
    while (fp.read((char*)&bk, sizeof(Book)))
        bk.report();
    fp.close();
}

void showAllStudents() {
    fp.open("student.dat", ios::in | ios::binary);
    cout << "\nSTUDENT LIST\n";
    while (fp.read((char*)&st, sizeof(Student)))
        st.report();
    fp.close();
}

/* ---------- MAIN ---------- */
int main() {
    int choice;
    do {
        cout << "\n\nLIBRARY MANAGEMENT SYSTEM";
        cout << "\n1. Add Book";
        cout << "\n2. Add Student";
        cout << "\n3. Show All Books";
        cout << "\n4. Show All Students";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: addStudent(); break;
            case 3: showAllBooks(); break;
            case 4: showAllStudents(); break;
            case 5: exit(0);
            default: cout << "Invalid choice";
        }
    } while (choice != 5);

    return 0;
}
