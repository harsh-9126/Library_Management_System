# 📚 Library Management System

A console-based **Library Management System** developed in **C++** that allows administrators, librarians, and members to manage library operations efficiently through a role-based interface. The application uses **file handling** to provide persistent storage without requiring a database.

---

## 🚀 Features

### 👨‍💼 User Authentication
- Role-based Login and Signup
- Three user roles:
  - Admin
  - Librarian
  - Member
- Default Admin account creation on first execution

### 📖 Book Management
- Add new books
- View available books
- Search books by title or author
- Track total and available copies

### 👥 Member Management
- Register new members
- View registered members

### 📚 Book Issue & Return
- Issue books to members
- Return issued books
- Prevent duplicate book issuance
- Automatically update available book copies

### 💾 Persistent Storage
The project stores data using text files:
- `books.txt`
- `members.txt`
- `issued.txt`
- `users.txt`

All records are automatically loaded when the program starts and saved after every modification.

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:**
  - Object-Oriented Programming (Structures)
  - File Handling
  - STL (`vector`, `string`, `algorithm`)
  - Role-Based Access Control
  - Data Serialization & Deserialization

---

## 📂 Project Structure

```
Library-Management-System/
│
├── main.cpp
├── books.txt
├── members.txt
├── issued.txt
├── users.txt
└── README.md
```

---

## ⚙️ How to Run

### Clone the repository

```bash
git clone https://github.com/harsh-9126/Library_Management_System
```

### Navigate to the project directory

```bash
cd library-management-system
```

### Compile

```bash
g++ main.cpp -o library
```

### Run

```bash
./library
```

---

## 🔑 Default Admin Credentials

When the application is executed for the first time, a default administrator account is created automatically.

```
Username: admin
Password: admin123
```

---

## 📸 Functionalities

- User Login & Signup
- Role-Based Access
- Add Book
- View Books
- Search Books
- Add Member
- View Members
- Issue Book
- Return Book
- Persistent File Storage

---

## 📚 Concepts Demonstrated

- File Handling
- CRUD Operations
- Data Serialization
- Data Persistence
- Authentication
- Role-Based Authorization
- Search Algorithms
- Standard Template Library (STL)

---

## 🔮 Future Enhancements

- Replace text files with MySQL or PostgreSQL
- GUI using Qt or C++
- Fine calculation for overdue books
- Book reservation system
- Password encryption
- Admin dashboard
- Report generation
- Due date management

---

## 👨‍💻 Author

**Harsh Jani**

B.Tech Information Technology  
Dharmsinh Desai University
