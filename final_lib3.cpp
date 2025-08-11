#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Book {
    string title, author, category;
    int copies, available;

    string serialize() {
        return title + "|" + author + "|" + category + "|" + to_string(copies) + "|" + to_string(available);
    }

    static Book deserialize(const string& line) {
        Book b;
        stringstream ss(line);
        getline(ss, b.title, '|');
        getline(ss, b.author, '|');
        getline(ss, b.category, '|');
        string copiesStr, availStr;
        getline(ss, copiesStr, '|');
        getline(ss, availStr, '|');
        b.copies = stoi(copiesStr);
        b.available = stoi(availStr);
        return b;
    }
};

struct Member {
    string name, email;

    string serialize() {
        return name + "|" + email;
    }

    static Member deserialize(const string& line) {
        Member m;
        stringstream ss(line);
        getline(ss, m.name, '|');
        getline(ss, m.email, '|');
        return m;
    }
};

struct IssueRecord {
    string memberEmail, bookTitle;

    string serialize() {
        return memberEmail + "|" + bookTitle;
    }

    static IssueRecord deserialize(const string& line) {
        IssueRecord r;
        stringstream ss(line);
        getline(ss, r.memberEmail, '|');
        getline(ss, r.bookTitle, '|');
        return r;
    }
};

struct User {
    string username, password, role;  // roles: admin, librarian, member

    string serialize() {
        return username + "|" + password + "|" + role;
    }

    static User deserialize(const string& line) {
        User u;
        stringstream ss(line);
        getline(ss, u.username, '|');
        getline(ss, u.password, '|');
        getline(ss, u.role, '|');
        return u;
    }
};

vector<Book> books;
vector<Member> members;
vector<IssueRecord> issued;
vector<User> users;

const string BOOKS_FILE = "books.txt";
const string MEMBERS_FILE = "members.txt";
const string ISSUED_FILE = "issued.txt";
const string USERS_FILE = "users.txt";

void loadBooks() {
    books.clear();
    ifstream fin(BOOKS_FILE);
    string line;
    while (getline(fin, line)) if (!line.empty()) books.push_back(Book::deserialize(line));
}

void saveBooks() {
    ofstream fout(BOOKS_FILE);
    for (auto& b : books) fout << b.serialize() << "\n";
}

void loadMembers() {
    members.clear();
    ifstream fin(MEMBERS_FILE);
    string line;
    while (getline(fin, line)) if (!line.empty()) members.push_back(Member::deserialize(line));
}

void saveMembers() {
    ofstream fout(MEMBERS_FILE);
    for (auto& m : members) fout << m.serialize() << "\n";
}

void loadIssued() {
    issued.clear();
    ifstream fin(ISSUED_FILE);
    string line;
    while (getline(fin, line)) if (!line.empty()) issued.push_back(IssueRecord::deserialize(line));
}

void saveIssued() {
    ofstream fout(ISSUED_FILE);
    for (auto& r : issued) fout << r.serialize() << "\n";
}

void loadUsers() {
    users.clear();
    ifstream fin(USERS_FILE);
    string line;
    while (getline(fin, line)) if (!line.empty()) users.push_back(User::deserialize(line));
}

void saveUsers() {
    ofstream fout(USERS_FILE);
    for (auto& u : users) fout << u.serialize() << "\n";
}

int findUserIndex(const string& username) {
    for (size_t i = 0; i < users.size(); i++)
        if (users[i].username == username) return i;
    return -1;
}

int findBookIndex(const string& title) {
    for (size_t i = 0; i < books.size(); i++)
        if (books[i].title == title) return i;
    return -1;
}

int findMemberIndex(const string& email) {
    for (size_t i = 0; i < members.size(); i++)
        if (members[i].email == email) return i;
    return -1;
}

bool isBookIssuedToMember(const string& email, const string& title) {
    for (auto& r : issued)
        if (r.memberEmail == email && r.bookTitle == title) return true;
    return false;
}

bool loginUser(string& loggedInUser, string& loggedInRole) {
    cout << "Select Role:\n1. Admin\n2. Librarian\n3. Member\nEnter choice: ";
    string roleChoice; getline(cin, roleChoice);
    string role;
    if (roleChoice == "1") role = "admin";
    else if (roleChoice == "2") role = "librarian";
    else if (roleChoice == "3") role = "member";
    else {
        cout << "Invalid role choice.\n";
        return false;
    }

    cout << "Enter username: ";
    string username; getline(cin, username);
    cout << "Enter password: ";
    string password; getline(cin, password);

    for (auto& u : users) {
        if (u.username == username && u.password == password && u.role == role) {
            loggedInUser = username;
            loggedInRole = role;
            cout << "Login successful as " << role << "!\n";
            return true;
        }
    }
    cout << "Invalid credentials or role mismatch.\n";
    return false;
}

bool signupUser() {
    cout << "Select Role for Signup:\n1. Admin\n2. Librarian\n3. Member\nEnter choice: ";
    string roleChoice; getline(cin, roleChoice);
    string role;
    if (roleChoice == "1") role = "admin";
    else if (roleChoice == "2") role = "librarian";
    else if (roleChoice == "3") role = "member";
    else {
        cout << "Invalid role choice.\n";
        return false;
    }

    cout << "Enter new username: ";
    string username; getline(cin, username);
    if (username.empty()) {
        cout << "Username cannot be empty.\n";
        return false;
    }
    if (findUserIndex(username) != -1) {
        cout << "Username already exists.\n";
        return false;
    }
    cout << "Enter password: ";
    string password; getline(cin, password);
    if (password.empty()) {
        cout << "Password cannot be empty.\n";
        return false;
    }

    users.push_back({username, password, role});
    saveUsers();
    cout << "User created successfully. You can now login.\n";
    return true;
}

// Admin, Librarian, Member Menus (same as before, simplified)

void addBook() {
    string title, author, category;
    int copies;
    cout << "Enter book title: ";
    getline(cin, title);
    if (title.empty()) { cout << "Title cannot be empty.\n"; return; }
    if (findBookIndex(title) != -1) {
        cout << "Book already exists.\n";
        return;
    }
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter category: ";
    getline(cin, category);
    cout << "Enter number of copies: ";
    cin >> copies;
    cin.ignore();
    if (copies < 1) {
        cout << "Invalid copies number.\n";
        return;
    }
    books.push_back({title, author, category, copies, copies});
    saveBooks();
    cout << "Book added successfully.\n";
}

void viewBooks() {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }
    cout << "\nBooks List:\n";
    for (size_t i = 0; i < books.size(); i++) {
        cout << i + 1 << ". " << books[i].title << " by " << books[i].author
            << " | Category: " << books[i].category
            << " | Available: " << books[i].available << "/" << books[i].copies << "\n";
    }
}

void searchBooks() {
    cout << "Enter keyword to search (title or author): ";
    string keyword; getline(cin, keyword);
    if (keyword.empty()) {
        cout << "Keyword cannot be empty.\n";
        return;
    }
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    bool found = false;
    for (auto& b : books) {
        string titleLower = b.title, authorLower = b.author;
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
        if (titleLower.find(keyword) != string::npos || authorLower.find(keyword) != string::npos) {
            cout << b.title << " by " << b.author << " | Category: " << b.category << " | Available: " << b.available << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matching books found.\n";
}

void addMember() {
    string name, email;
    cout << "Enter member name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }
    cout << "Enter member email: ";
    getline(cin, email);
    if (email.empty()) {
        cout << "Email cannot be empty.\n";
        return;
    }
    if (findMemberIndex(email) != -1) {
        cout << "Member already registered.\n";
        return;
    }
    members.push_back({name, email});
    saveMembers();
    cout << "Member added successfully.\n";
}

void viewMembers() {
    if (members.empty()) {
        cout << "No members registered.\n";
        return;
    }
    cout << "\nMembers List:\n";
    for (size_t i = 0; i < members.size(); i++) {
        cout << i + 1 << ". " << members[i].name << " | " << members[i].email << "\n";
    }
}

void issueBook() {
    string email, title;
    cout << "Enter member email: ";
    getline(cin, email);
    if (findMemberIndex(email) == -1) {
        cout << "Member not found.\n";
        return;
    }
    cout << "Enter book title to issue: ";
    getline(cin, title);
    int bIndex = findBookIndex(title);
    if (bIndex == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[bIndex].available < 1) {
        cout << "No copies available.\n";
        return;
    }
    if (isBookIssuedToMember(email, title)) {
        cout << "Book already issued to this member.\n";
        return;
    }
    issued.push_back({email, title});
    books[bIndex].available--;
    saveIssued();
    saveBooks();
    cout << "Book issued successfully.\n";
}

void returnBook() {
    string email, title;
    cout << "Enter member email: ";
    getline(cin, email);
    cout << "Enter book title to return: ";
    getline(cin, title);
    auto it = find_if(issued.begin(), issued.end(), [&](IssueRecord& r) {
        return r.memberEmail == email && r.bookTitle == title;
    });
    if (it == issued.end()) {
        cout << "No such issued record found.\n";
        return;
    }
    int bIndex = findBookIndex(title);
    if (bIndex != -1) books[bIndex].available++;
    issued.erase(it);
    saveIssued();
    saveBooks();
    cout << "Book returned successfully.\n";
}

void adminMenu() {
    while (true) {
        cout << "\nAdmin Menu:\n"
            << "1. Add Book\n2. View Books\n3. Search Books\n"
            << "4. Add Member\n5. View Members\n6. Issue Book\n7. Return Book\n8. Logout\n"
            << "Enter choice: ";
        string choice; getline(cin, choice);

        if (choice == "1") addBook();
        else if (choice == "2") viewBooks();
        else if (choice == "3") searchBooks();
        else if (choice == "4") addMember();
        else if (choice == "5") viewMembers();
        else if (choice == "6") issueBook();
        else if (choice == "7") returnBook();
        else if (choice == "8") break;
        else cout << "Invalid choice.\n";
    }
}

void librarianMenu() {
    while (true) {
        cout << "\nLibrarian Menu:\n"
            << "1. Add Book\n2. View Books\n3. Search Books\n"
            << "4. View Members\n5. Issue Book\n6. Return Book\n7. Logout\n"
            << "Enter choice: ";
        string choice; getline(cin, choice);

        if (choice == "1") addBook();
        else if (choice == "2") viewBooks();
        else if (choice == "3") searchBooks();
        else if (choice == "4") viewMembers();
        else if (choice == "5") issueBook();
        else if (choice == "6") returnBook();
        else if (choice == "7") break;
        else cout << "Invalid choice.\n";
    }
}

void memberMenu() {
    while (true) {
        cout << "\nMember Menu:\n"
            << "1. View Books\n2. Search Books\n3. Logout\n"
            << "Enter choice: ";
        string choice; getline(cin, choice);

        if (choice == "1") viewBooks();
        else if (choice == "2") searchBooks();
        else if (choice == "3") break;
        else cout << "Invalid choice.\n";
    }
}

int main() {
    loadBooks();
    loadMembers();
    loadIssued();
    loadUsers();

    // If no users exist, create default admin
    if (users.empty()) {
        users.push_back({"admin", "admin123", "admin"});
        saveUsers();
        cout << "Default admin created: username=admin password=admin123\n";
    }

    while (true) {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Login\n2. Signup\n3. Quit\nEnter choice: ";
        string mainChoice; getline(cin, mainChoice);

        if (mainChoice == "1") {
            string loggedInUser, loggedInRole;
            if (loginUser(loggedInUser, loggedInRole)) {
                if (loggedInRole == "admin") adminMenu();
                else if (loggedInRole == "librarian") librarianMenu();
                else if (loggedInRole == "member") memberMenu();
            }
        }
        else if (mainChoice == "2") {
            signupUser();
        }
        else if (mainChoice == "3") {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
