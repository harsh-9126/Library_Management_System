# Library_Management_System

Project Description : 
This Library Management System is a console-based C++ application designed to help manage library operations efficiently. It supports multiple user roles with specific privileges:
Admin: Can manage books, members, issue/return books, update/delete records, and manage users.
Librarian: Can manage books, members, issue/return books, and view issued books.
Member: Can view available books, search for books, view their issued books, and change their password.
The system uses file-based storage to persist data between sessions, storing information about books, members, issued books, and users in separate text files.

Features : 
User Authentication: Login and signup with role-based access control (admin, librarian, member).
Book Management:
Add, update, delete, view, and search books.
Track the number of copies and availability.
Member Management:
Add, update, delete, and view library members.
Issue and Return Books:
Issue books to members if available.
Return books and update availability.
Track issue date and calculate overdue fines.
Issued Books Tracking:
View currently issued books by a particular member.
Display overdue status and fine if applicable.
Password Management:
Users can change their passwords securely.
Fine System:
Automatic fine calculation for books returned after the allowed loan period (14 days).
File Persistence:
All data is saved in text files (books.txt, members.txt, issued.txt, and users.txt) to maintain state between program runs.
