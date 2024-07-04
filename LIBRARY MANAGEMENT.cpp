#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Book {
public:
    string id, name, author;

    Book(string bookId, string bookName, string bookAuthor)
        : id(bookId), name(bookName), author(bookAuthor) {}
};

class Library {
private:
    vector<Book> books;

    void loadBooks();
    void saveBooks();

public:
    Library();
    void addBook();
    void showAll();
    void extractBook();
    void deleteBook();
    void searchByAuthor();
};

Library::Library() {
    loadBooks();
}

void Library::loadBooks() {
    ifstream file("bookData.txt");
    string id, name, author;

    while (getline(file, id, '*') && getline(file, name, '*') && getline(file, author, '\n')) {
        books.push_back(Book(id, name, author));
    }
    file.close();
}

void Library::saveBooks() {
    ofstream file("bookData.txt");
    for (const auto& book : books) {
        file << book.id << "*" << book.name << "*" << book.author << endl;
    }
    file.close();
}

void Library::addBook() {
    string id, name, author;
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Book's Author Name :: ";
    getline(cin, author);

    books.push_back(Book(id, name, author));
    saveBooks();
}

void Library::showAll() {
    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    for (const auto& book : books) {
        cout << "\t\t " << book.id << " \t\t\t " << book.name << " \t\t\t " << book.author << endl;
    }
}

void Library::extractBook() {
    string searchId;
    cout << "Enter Book Id :: ";
    getline(cin, searchId);

    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    auto it = find_if(books.begin(), books.end(), [&](const Book& book) { return book.id == searchId; });

    if (it != books.end()) {
        cout << "\t\t " << it->id << " \t\t\t " << it->name << " \t\t\t " << it->author << endl;
        cout << "Book Extracted Successfully...!" << endl;
    } else {
        cout << "Book Not Found...!" << endl;
    }
}

void Library::deleteBook() {
    string searchId;
    cout << "Enter Book Id to Delete :: ";
    getline(cin, searchId);

    auto it = remove_if(books.begin(), books.end(), [&](const Book& book) { return book.id == searchId; });

    if (it != books.end()) {
        books.erase(it, books.end());
        saveBooks();
        cout << "Book Deleted Successfully...!" << endl;
    } else {
        cout << "Book Not Found...!" << endl;
    }
}

void Library::searchByAuthor() {
    string searchAuthor;
    cout << "Enter Author's Name to Search :: ";
    getline(cin, searchAuthor);

    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    for (const auto& book : books) {
        if (book.author == searchAuthor) {
            cout << "\t\t " << book.id << " \t\t\t " << book.name << " \t\t\t " << book.author << endl;
        }
    }
}

int main() {
    Library library;
    char choice;

    while (true) {
        cout << "----------------------------------" << endl;
        cout << "1 - Show All Books" << endl;
        cout << "2 - Extract Book" << endl;
        cout << "3 - Add Book (ADMIN)" << endl;
        cout << "4 - Delete Book (ADMIN)" << endl;
        cout << "5 - Search by Author" << endl;
        cout << "6 - Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;
        cin.ignore(); // To consume the newline character left by cin

        switch (choice) {
            case '1':
                library.showAll();
                break;
            case '2':
                library.extractBook();
                break;
            case '3':
                library.addBook();
                break;
            case '4':
                library.deleteBook();
                break;
            case '5':
                library.searchByAuthor();
                break;
            case '6':
                return 0;
            default:
                cout << "Invalid Choice...!" << endl;
        }
    }

    return 0;
}
