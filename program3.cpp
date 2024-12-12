#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    std::string title;
    std::string author;
    bool isAvailable;

    Book(std::string t, std::string a) : title(t), author(a), isAvailable(true) {}
};

class Borrower {
public:
    std::string name;
    std::vector<Book*> borrowedBooks;

    Borrower(std::string n) : name(n) {}
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Borrower> borrowers;

public:
    void addBook(std::string title, std::string author) {
        books.emplace_back(title, author);
    }

    void registerBorrower(std::string name) {
        borrowers.emplace_back(name);
    }

    void borrowBook(std::string borrowerName, std::string bookTitle) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                for (auto& book : books) {
                    if (book.title == bookTitle && book.isAvailable) {
                        book.isAvailable = false;
                        borrower.borrowedBooks.push_back(&book);
                        std::cout << borrowerName << " borrowed " << bookTitle << std::endl;
                        return;
                    }
                }
            }
        }
        std::cout << "Book not available or borrower not found." << std::endl;
    }

    void returnBook(std::string borrowerName, std::string bookTitle) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                for (auto it = borrower.borrowedBooks.begin(); it != borrower.borrowedBooks.end(); ++it) {
                    if ((*it)->title == bookTitle) {
                        (*it)->isAvailable = true;
                        borrower.borrowedBooks.erase(it);
                        std::cout << borrowerName << " returned " << bookTitle << std::endl;
                        return;
                    }
                }
            }
        }
        std::cout << "Book not found in borrower's records." << std::endl;
    }
};

int main() {
    Library library;
    library.addBook("1984", "George Orwell");
    library.addBook("To Kill a Mockingbird", "Harper Lee");

    library.registerBorrower("Alice");
    library.registerBorrower("Bob");

    library.borrowBook("Alice", "1984");
    library.returnBook("Alice", "1984");

    return 0;
}
