#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class Book {

public:
    string ISBN;
    string title;
    string author;

    Book(string isbn, string t, string a)
    {
        ISBN = isbn;
        title = t;
        author = a;
    }

};

class BookItem{

public: 
    string barcode;
    Book* book;
    bool isIssued;

    BookItem(string code, Book* b)
    {
        barcode = code;
        book = b;
        isIssued = false;
    } 

};

class User{

public:
    string userId;
    string name;

    User(string id, string n)
    {
        userId = id;
        name = n;
    }

    virtual string getRole() = 0;

};

class Member : public User {

public:

    unordered_set<string> borrowedBooks;

    Member(string id, string n) : User(id,n) {}

    string getRole() override {
        return "Member";
    }


};

class Librarian : public User {
public:
    Librarian(string id, string n) : User(id, n) {}

    string getRole() override {
        return "Librarian";
    }
};

class Transaction {
public:
    string memberId;
    string barcode;
    string borrowDate;
    string returnDate;
    bool isReturned;

    Transaction(string mId, string bcode, string bDate) {
        memberId = mId;
        barcode = bcode;
        borrowDate = bDate;
        returnDate = "";
        isReturned = false;
    }

    void markReturned(string rDate) {
        returnDate = rDate;
        isReturned = true;
    }
};

//code library class

class Library {

private: 
    const int MAX_BORROW_DAYS = 14;
    const int FINE_PER_DAY = 2;
    unordered_map<string, Book*> books; // ISBN -> books
    unordered_map<string, vector<BookItem*>> bookitems; // ISBN -> copies
    unordered_map<string, BookItem*> barcodeMap; // barcode -> bookItem
    unordered_map<string, Member*> members; //userid -> Member
    vector<Transaction*> transactions;  // tracks all transactions

public: 
    void addBook(string isbn, string title, string author)
    {
        if(books.find(isbn)==books.end())
        {
            books[isbn] = new Book(isbn,title,author);
        }
    }

    void addBookItem(string isbn, string barcode)
    {
        if(books.find(isbn) == books.end())
        {
            cout << "Book does not exist. please add book first\n";
            return;
        }

        BookItem* item = new BookItem(barcode, books[isbn]);
        bookitems[isbn].push_back(item);
        barcodeMap[barcode] = item;
    }

    void registerMember(string id, string name)
    {
        if(members.find(id) == members.end())
        {
            members[id] = new Member(id,name);
        }
    }

    int calculateFine(string borrowDate, string returnDate) {
        int borrow = stoi(borrowDate); // e.g., "20240501" → 20240501
        int ret = stoi(returnDate);
        int days = ret - borrow;

        if (days > MAX_BORROW_DAYS) {
            return (days - MAX_BORROW_DAYS) * FINE_PER_DAY;
        }
        return 0;
    }

    void borrowBook(string memberId, string barcode, string borrowDate) {
        if (members.find(memberId) == members.end()) {
            cout << "Member not found\n";
            return;
        }
        if (barcodeMap.find(barcode) == barcodeMap.end()) {
            cout << "Book copy not found\n";
            return;
        }

        BookItem* item = barcodeMap[barcode];
        if (item->isIssued) {
            cout << "Book already issued\n";
            return;
        }

        item->isIssued = true;
        members[memberId]->borrowedBooks.insert(barcode);

        Transaction* t = new Transaction(memberId, barcode, borrowDate);
        transactions.push_back(t);

        cout << "Book issued successfully\n";
    }

    void returnBook(string memberId, string barcode, string returnDate) {
        if (members.find(memberId) == members.end()) {
            cout << "Member not found\n";
            return;
        }
        if (barcodeMap.find(barcode) == barcodeMap.end()) {
            cout << "Book copy not found\n";
            return;
        }

        BookItem* item = barcodeMap[barcode];
        if (!item->isIssued) {
            cout << "Book was not issued\n";
            return;
        }

        item->isIssued = false;
        members[memberId]->borrowedBooks.erase(barcode);

        for (Transaction* t : transactions) {
            if (t->barcode == barcode && t->memberId == memberId && !t->isReturned) {
                t->markReturned(returnDate);
                int fine = calculateFine(t->borrowDate, returnDate);
                if (fine > 0) {
                    cout << "Book returned with fine: $" << fine << "\n";
                } else {
                    cout << "Book returned on time\n";
                }
                return;
            }
        }

        cout << "No matching transaction found\n";
    }

    void searchByTitle(string title) {
        for (auto& [isbn, book] : books) {
            if (book->title == title) {
                cout << "Found: " << book->title << " by " << book->author << " (ISBN: " << isbn << ")\n";
            }
        }
    }
};

int main() {
    Library lib;

    lib.registerMember("M1", "Nikhil");
    lib.addBook("456", "Design Patterns", "GOF");
    lib.addBookItem("456", "DP1");

    // Borrow on 20240501 (May 1, 2024)
    lib.borrowBook("M1", "DP1", "20240501");

    // Return on 20240520 (May 20, 2024)
    lib.returnBook("M1", "DP1", "20240520");

    return 0;
}
