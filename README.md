# Library Management System (C++)

A robust, console-based application designed for efficient library administration. This system utilizes Object-Oriented Programming (OOP) and binary file handling to manage student records and book catalogs with high reliability.

---

## 🚀 System Overview

This project automates daily library tasks by storing data permanently on your hard drive using `book.dat` and `student.dat` files. It eliminates the need for external databases, providing a lightweight, high-performance solution for managing library assets.

## 🛠 Key Features

* **Book Management:** Add, search, modify, or delete book entries.
* **Student Management:** Maintain detailed student records, including tracking borrowed books.
* **Transaction Processing:** * **Book Issuance:** Automatically validates student status and enforces a one-book-per-student policy.
* **Book Returns:** Calculates late-return fines (Rs 15/day after a 15-day grace period).


* **Administrative Security:** Password-protected admin access for system maintenance.
* **Data Integrity:** Permanent storage via binary file streams (`<fstream>`) ensuring data persists after application closure.

## 📋 Operation Modes

1. **Main Menu:** Open to all users for routine borrowing and depositing of books.
2. **Administrator Menu:** Restricted access for system management, record modification, and data resets.

## ⚙️ Technical Specifications

* **Language:** C++
* **Architecture:** Object-Oriented Programming (OOP)
* **Storage:** Binary File Handling (`.dat`)
* **Error Handling:** Built-in validation for invalid entries, access denial for unauthorized attempts, and confirmation prompts for destructive actions.

---

## 🛡 Security Note

Access to the **Administrator Menu** is strictly controlled by a security password (`admin123`). Please ensure this is kept confidential to maintain database integrity.

---

*Developed as a core C++ project for efficient record-keeping and administrative automation.*
