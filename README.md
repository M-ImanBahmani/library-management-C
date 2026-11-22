Library Management System in C (سیستم مدیریت کتابخانه)

A comprehensive, role-based console Library Management System built entirely in Standard C with file-based persistent storage. Originally developed as the Fundamentals of Computer & Programming project at the University of Kashan, this application implements multi-role authentication, automated fine calculation, an electronic wallet system, and sorted data reporting using only core C standard libraries.

✨ Key Features by Role

👑 1. Senior Admin (مدیر ارشد)

Secure Initial Setup: Prompts for the admin password twice on first launch and stores it encoded in admin_password.txt.

Librarian Management: Add new librarians (using National ID as username), edit existing profiles, and activate/deactivate accounts with confirmation prompts.

Credential Control: Reset forgotten librarian passwords and update the admin's own password securely.

Monitoring: View sorted lists of active and inactive librarians.

📚 2. Librarians (کتابداران)

Member Lifecycle: Register new members (Student, Professor, or General) with auto-generated unique membership codes, edit profiles, reset passwords, search members, and toggle active/inactive status.

Book Catalog Management: Add new books with auto-generated unique book codes, edit metadata (title, author, subject, publication year), list available books, and filter by subject.

Borrowing Workflow: Review pending borrow requests (approve/reject), register book returns, and inspect overdue books along with borrower details.

Financial & Wallet Operations: View member borrowing histories with calculated fines and top up members' electronic wallets.

Self-Service: Change own password securely.

👤 3. Library Members (اعضا)

Catalog Browsing & Borrowing: View available books and submit borrow requests (approval date is automatically recorded as the borrow date).

Borrowing History: Track all currently borrowed and previously returned books, including return dates and automatically calculated late fines.

E-Wallet Fine Payment: Pay accrued fines directly from the electronic wallet balance (members with unpaid fines are restricted from borrowing new books until settled).

Self-Service: Change own password.

📊 Borrowing & Late Fine Policy

Fines are automatically calculated upon book return based on the member's category:

Membership Type

Allowed Duration

Daily Late Fine

Professor (استاد)

1 Month (30 days)

500 Rials / day

Student (دانشجو)

2 Weeks (14 days)

1,000 Rials / day

General (متفرقه)

1 Week (7 days)

1,500 Rials / day

🛠️ Technical Highlights & Constraints

Pure Standard C Libraries Only: Built strictly using stdio.h, stdlib.h, string.h, time.h, and assert.h without any external third-party dependencies.

Modular Architecture: Every operation is encapsulated in dedicated, reusable functions.

Sorted Reporting: All book and member lists are displayed in sorted order.

User-Friendly Console UX: Includes step-by-step confirmation dialogs, clear success/error feedback messages, and full back-navigation across all menus.

Persistent File Storage: Structured .txt files maintain state across sessions.

📂 Project Structure

library-management-c/
├── Project.c                      # Main C source code
├── project_C.pdf                  # Official project specification & documentation
├── admin_password.txt             # Encoded admin credentials
├── books.txt                      # Books catalog database
├── librarians.txt                 # Librarians database
├── listofthebooks_m.txt           # Managed books records
├── listofthemembers.txt           # Registered members database
├── chargemember.txt               # Member e-wallet balances
├── MemberBorrowing.txt            # Active & historical borrowing records
├── MemberBorrowing_pay_fine.txt   # Fine payment records
├── .gitignore                     # Ignored compiled binaries & IDE files
└── README.md                      # Project documentation


🚀 How to Compile and Run

Prerequisites

Ensure you have a C compiler installed (such as GCC / MinGW, Dev-C++, or Code::Blocks).

Using GCC (Terminal / Command Prompt)

Clone the repository:

git clone https://github.com/M-ImanBahmani/library-management-c.git


Navigate to the project directory:

cd library-management-c


Compile the source code:

gcc Project.c -o library_app


Run the application:

Windows:

library_app.exe


Linux / macOS:

./library_app


Note: Keep the .txt data files in the same directory as the compiled executable so the program can properly read and update records.

👤 Author

Mohammad Iman Bahmani (محمد ایمان بهمنی)

GitHub: @M-ImanBahmani
Telegram: @M-ImanBahmani
