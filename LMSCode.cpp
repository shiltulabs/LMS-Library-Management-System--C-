#include <iostream> // For input and output (like cin, cout)
#include <iomanip>  // For formatting output nicely (like setting text width)
#include <cstdlib>  // For standard library functions (like exit(0))
#include <cstring>  // For working with text strings (like strcpy, strcmp)
#include <cstdio>   // For file operations like delete or rename
#include <fstream>  // For reading and writing data to files on the hard drive

using namespace std; // Use the standard namespace to avoid typing std:: every time

// --- UTILITY FUNCTIONS (Helper functions) ---

// Clears the text from the screen to make it look clean
void clearScreen() {
    cout << "\x1B[2J\x1B[H"; // Special code that clears the console screen
}

// Pauses the program until the user presses the 'Enter' key
void waitForEnter() {
    cout << "\n\nPress Enter to continue...";
    cin.clear(); // Clears any error flags in the input
    cin.ignore(10000, '\n'); // Ignores any leftover 'Enter' characters in the memory
    cin.get(); // Waits for the user to press 'Enter'
}

// --- DATA CLASSES ---

// A blueprint for storing Book details
class Book {
    char bookNo[6];       // To store the book number (max 5 letters/digits)
    char bookName[50];    // To store the name of the book
    char authorName[20];  // To store the author's name
public:
    // Function to take input for a new book
    void createBook() {
        cout << "\n--- NEW BOOK ENTRY ---\n";
        cout << "ENTER BOOK NO.: ";
        cin >> bookNo; // Takes book number from user
        cin.ignore();  // Clears the 'Enter' key from memory so the next input works fine
        cout << "ENTER BOOK NAME: ";
        cin.getline(bookName, 50); // Takes the book name (allows spaces)
        cout << "ENTER AUTHOR NAME: ";
        cin.getline(authorName, 20); // Takes the author's name (allows spaces)
        cout << "\n\n[Success] Book Record Created.";
    }

    // Function to show a single book's details on the screen
    void showBook() const {
        cout << "\nBook Number      : " << bookNo;
        cout << "\nBook Name        : " << bookName;
        cout << "\nBook Author Name : " << authorName;
    }

    // Function to change (update) the details of an existing book
    void modifyBook() {
        cout << "\nBook Number: " << bookNo; // Book number stays the same
        cin.ignore();
        cout << "\nModify Book Name: ";
        cin.getline(bookName, 50); // Takes the new book name
        cout << "\nModify Author's Name: ";
        cin.getline(authorName, 20); // Takes the new author's name
    }

    // Returns the book number so other parts of the program can use it
    const char* getBookNo() const { return bookNo; }

    // Shows the book details in a single straight line (used for lists)
    void report() const {
        cout << left << setw(15) << bookNo << setw(30) << bookName << setw(20) << authorName << endl;
    }
};

// A blueprint for storing Student details
class Student {
    char admNo[6];         // Student's Admission Number
    char name[20];         // Student's Name
    char studentBookNo[6]; // The number of the book the student has borrowed
    int token;             // Number of books the student has (0 or 1)
public:
    // Function to take input for a new student
    void createStudent() {
        cout << "\n--- NEW STUDENT ENTRY ---\n";
        cout << "Enter The Admission No.: ";
        cin >> admNo; // Takes admission number
        cin.ignore();
        cout << "Enter The Student Name: ";
        cin.getline(name, 20); // Takes student's name
        token = 0; // Starts with 0 because the student hasn't borrowed a book yet
        studentBookNo[0] = '\0'; // Leaves the borrowed book number empty
        cout << "\n\n[Success] Student Record Created.";
    }

    // Function to show a single student's details
    void showStudent() const {
        cout << "\nAdmission Number : " << admNo;
        cout << "\nStudent Name     : " << name;
        cout << "\nNo of Book Issued: " << token;
        if (token == 1) { // If the student has a book, show the book number
            cout << "\nIssued Book No.  : " << studentBookNo;
        }
    }

    // Function to update a student's name
    void modifyStudent() {
        cout << "\nAdmission No. " << admNo; // Admission number stays the same
        cin.ignore();
        cout << "\nModify Student Name: ";
        cin.getline(name, 20); // Takes the new name
    }

    // Functions to let other parts of the program access student data
    const char* getAdmNo() const { return admNo; }
    const char* getStudentBookNo() const { return studentBookNo; }
    int getToken() const { return token; }
    
    // Sets token to 1 when a student borrows a book
    void issueToken() { token = 1; }
    // Sets token back to 0 when the student returns the book
    void resetToken() { token = 0; }
    
    // Saves the number of the book the student just borrowed
    void setStudentBookNo(const char t[]) {
        strcpy(studentBookNo, t); // Copies the text (t) into studentBookNo
    }

    // Shows the student details in a single straight line (used for lists)
    void report() const {
        cout << left << setw(20) << admNo << setw(25) << name << setw(15) << token << endl;
    }
};

// --- SYSTEM MANAGER CLASS ---
// This class handles all the logic, saving files, and loading files

class LibraryManager {
private:
    fstream file, file1;   // Variables used to read and write files
    Book currentBook;      // An object to hold a book's data temporarily
    Student currentStudent;// An object to hold a student's data temporarily

    // Function to check the admin password
    bool verifyAdmin() {
        string password;
        cout << "\n\t[SECURITY] Enter Administrator Password: ";
        cin >> password;
        if (password == "admin123") { // If the password is correct
            return true; // Allow access
        }
        cout << "\n\t[ERROR] Incorrect Password! Access Denied.\n";
        waitForEnter();
        return false; // Deny access
    }

public:
    // Function to permanently save a new book to the computer
    void writeBook() {
        char ch;
        // Opens 'book.dat' to add new data at the end (app = append)
        file.open("book.dat", ios::out | ios::app | ios::binary);
        do {
            clearScreen();
            currentBook.createBook(); // Ask user for book details
            // Save the book details into the file
            file.write(reinterpret_cast<char*>(&currentBook), sizeof(Book));
            cout << "\n\nDo you want to add another record? (y/n): ";
            cin >> ch; // Ask if they want to add more
        } while (ch == 'y' || ch == 'Y'); // Loop if they press 'y'
        file.close(); // Close the file when done
    }

    // Function to permanently save a new student to the computer
    void writeStudent() {
        char ch;
        file.open("student.dat", ios::out | ios::app | ios::binary);
        do {
            clearScreen();
            currentStudent.createStudent(); // Ask user for student details
            file.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student)); // Save it
            cout << "\n\nDo you want to add another record? (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
        file.close();
    }

    // Function to find and display one specific book
    void displaySpecificBook(const char n[]) {
        cout << "\n--- BOOK DETAILS ---\n";
        bool found = false;
        file.open("book.dat", ios::in | ios::binary); // Open file to read data
        // Read books one by one from the file
        while (file.read(reinterpret_cast<char*>(&currentBook), sizeof(Book))) {
            // If the book number matches the one we are looking for
            if (strcmp(currentBook.getBookNo(), n) == 0) {
                currentBook.showBook(); // Show it on screen
                found = true;
            }
        }
        file.close();
        if (!found) cout << "\n\n[Error] Book does not exist in the database.";
        waitForEnter();
    }

    // Function to find and display one specific student
    void displaySpecificStudent(const char n[]) {
        cout << "\n--- STUDENT DETAILS ---\n";
        bool found = false;
        file.open("student.dat", ios::in | ios::binary);
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
            if (strcmp(currentStudent.getAdmNo(), n) == 0) {
                currentStudent.showStudent();
                found = true;
            }
        }
        file.close();
        if (!found) cout << "\n\n[Error] Student does not exist in the database.";
        waitForEnter();
    }

    // Function to find a book and update its details
    void modifyBook() {
        char n[6];
        bool found = false;
        clearScreen();
        cout << "\n--- MODIFY BOOK RECORD ---\n";
        cout << "\nEnter the Book No.: ";
        cin >> n;
        // Open file for reading AND writing
        file.open("book.dat", ios::in | ios::out | ios::binary);
        while (file.read(reinterpret_cast<char*>(&currentBook), sizeof(Book)) && !found) {
            if (strcmp(currentBook.getBookNo(), n) == 0) { // If book is found
                currentBook.showBook();
                cout << "\n\n--- Enter the new details ---";
                currentBook.modifyBook(); // Ask for new details
                // Move the file pointer back by one book size to overwrite the old data
                std::streamoff pos = -1 * static_cast<std::streamoff>(sizeof(Book));
                file.seekp(pos, ios::cur);
                file.write(reinterpret_cast<char*>(&currentBook), sizeof(Book)); // Save new data
                cout << "\n\n[Success] Record Updated";
                found = true;
            }
        }
        file.close();
        if (!found) cout << "\n\n[Error] Record Not Found";
        waitForEnter();
    }

    // Function to find a student and update their details (same logic as modifyBook)
    void modifyStudent() {
        char n[6];
        bool found = false;
        clearScreen();
        cout << "\n--- MODIFY STUDENT RECORD ---\n";
        cout << "\nEnter the Admission No.: ";
        cin >> n;
        file.open("student.dat", ios::in | ios::out | ios::binary);
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student)) && !found) {
            if (strcmp(currentStudent.getAdmNo(), n) == 0) {
                currentStudent.showStudent();
                cout << "\n\n--- Enter the new details ---";
                currentStudent.modifyStudent();
                std::streamoff pos = -1 * static_cast<std::streamoff>(sizeof(Student));
                file.seekp(pos, ios::cur);
                file.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
                cout << "\n\n[Success] Record Updated";
                found = true;
            }
        }
        file.close();
        if (!found) cout << "\n\n[Error] Record Not Found";
        waitForEnter();
    }

    // Function to permanently delete a student from the file
    void deleteStudent() {
        char n[6];
        bool found = false;
        clearScreen();
        cout << "\n--- DELETE STUDENT ---\n";
        cout << "\nEnter the Admission No.: ";
        cin >> n;
        
        file.open("student.dat", ios::in | ios::binary); // Open original file
        fstream tempFile;
        tempFile.open("temp.dat", ios::out | ios::binary); // Create a temporary file
        
        // Read every student from the original file
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
            // If this is NOT the student we want to delete, save them to the temp file
            if (strcmp(currentStudent.getAdmNo(), n) != 0) {
                tempFile.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
            } else {
                found = true; // We found and skipped the student we wanted to delete
            }
        }
        tempFile.close();
        file.close();
        remove("student.dat"); // Delete the old file completely
        rename("temp.dat", "student.dat"); // Rename temp file to act as the new original file
        
        if (found) cout << "\n\n[Success] Record Deleted.";
        else cout << "\n\n[Error] Record not Found.";
        waitForEnter();
    }

    // Function to delete a book (uses the same temp file logic as deleteStudent)
    void deleteBook() {
        char n[6];
        bool found = false;
        clearScreen();
        cout << "\n--- DELETE BOOK ---\n";
        cout << "\nEnter the Book No.: ";
        cin >> n;
        file.open("book.dat", ios::in | ios::binary);
        fstream tempFile;
        tempFile.open("temp.dat", ios::out | ios::binary);
        
        while (file.read(reinterpret_cast<char*>(&currentBook), sizeof(Book))) {
            if (strcmp(currentBook.getBookNo(), n) != 0) {
                tempFile.write(reinterpret_cast<char*>(&currentBook), sizeof(Book));
            } else {
                found = true;
            }
        }
        tempFile.close();
        file.close();
        remove("book.dat");
        rename("temp.dat", "book.dat");
        
        if (found) cout << "\n\n[Success] Record Deleted.";
        else cout << "\n\n[Error] Record not Found.";
        waitForEnter();
    }

    // Function to wipe out all student and book files completely (Factory Reset)
    void clearAllData() {
        char confirm;
        clearScreen();
        cout << "\n--- WARNING: FACTORY RESET ---\n";
        cout << "\nAre you sure you want to delete ALL Students and Books data?";
        cout << "\nThis cannot be undone! Type (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            remove("student.dat"); // Deletes student file directly from hard disk
            remove("book.dat");    // Deletes book file directly from hard disk
            cout << "\n\n[Success] All data has been permanently deleted. System is empty now.";
        } else {
            cout << "\n\n[Cancelled] Action stopped. Your data is safe.";
        }
        waitForEnter();
    }

    // Function to show a list of all students
    void displayAllStudents() {
        clearScreen();
        file.open("student.dat", ios::in | ios::binary);
        if (!file) { // If the file doesn't exist yet
            cout << "[Error] File Could Not Be Opened. Maybe no records exist yet.";
            waitForEnter();
            return;
        }
        cout << "\n\n\t\tSTUDENT LIST\n\n";
        cout << "==============================================================\n";
        cout << left << setw(20) << "Admission No." << setw(25) << "Name" << setw(15) << "Book Issued\n";
        cout << "==============================================================\n";
        // Print every student line by line
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
            currentStudent.report(); 
        }
        file.close();
        waitForEnter();
    }

    // Function to show a list of all books
    void displayAllBooks() {
        clearScreen();
        file.open("book.dat", ios::in | ios::binary);
        if (!file) {
            cout << "[Error] File Could Not Be Opened. Maybe no records exist yet.";
            waitForEnter();
            return;
        }
        cout << "\n\n\t\tBOOK LIST\n\n";
        cout << "=================================================================\n";
        cout << left << setw(15) << "Book No." << setw(30) << "Book Name" << setw(20) << "Author\n";
        cout << "=================================================================\n";
        while (file.read(reinterpret_cast<char*>(&currentBook), sizeof(Book))) {
            currentBook.report();
        }
        file.close();
        waitForEnter();
    }

    // Function to let a student borrow a book
    void bookIssue() {
        char sn[6], bn[6];
        bool found = false, flag = false;
        clearScreen();
        cout << "\n--- BOOK ISSUE MODULE ---\n";
        cout << "\nEnter Student Admission No.: ";
        cin >> sn;
        
        file.open("student.dat", ios::in | ios::out | ios::binary); // Open student file
        file1.open("book.dat", ios::in | ios::out | ios::binary);   // Open book file
        
        // Search for the student
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student)) && !found) {
            if (strcmp(currentStudent.getAdmNo(), sn) == 0) { // If student is found
                found = true;
                if (currentStudent.getToken() == 0) { // Check if they don't already have a book
                    cout << "\nEnter The Book No.: ";
                    cin >> bn;
                    // Search for the book
                    while (file1.read(reinterpret_cast<char*>(&currentBook), sizeof(Book)) && !flag) {
                        if (strcmp(currentBook.getBookNo(), bn) == 0) { // If book is found
                            flag = true;
                            currentStudent.issueToken(); // Mark that student has borrowed a book
                            currentStudent.setStudentBookNo(currentBook.getBookNo()); // Save book number to student
                            
                            // Overwrite the student's data in the file to save changes
                            std::streamoff pos = -1 * static_cast<std::streamoff>(sizeof(Student));
                            file.seekp(pos, ios::cur);
                            file.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
                            
                            cout << "\n\n[Success] Book Issued Successfully!";
                            cout << "\nNote: Return the book within 15 days, otherwise a fine of Rs 15 per day applies.";
                        }
                    }
                    if (!flag) cout << "\n[Error] Book No. Does Not Exist!";
                } else {
                    cout << "\n[Notice] You Have Not Returned Your Previously Issued Book!";
                }
            }
        }
        if (!found) cout << "\n[Error] Student Record Does Not Exist!";
        
        file.close();
        file1.close();
        waitForEnter();
    }

    // Function to let a student return a book
    void bookDeposit() {
        char sn[6];
        bool found = false, flag = false;
        int day, fine;
        
        clearScreen();
        cout << "\n--- BOOK DEPOSIT MODULE ---\n";
        cout << "\nEnter Admission No. Of Student: ";
        cin >> sn;
        
        file.open("student.dat", ios::in | ios::out | ios::binary);
        file1.open("book.dat", ios::in | ios::out | ios::binary);
        
        while (file.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student)) && !found) {
            if (strcmp(currentStudent.getAdmNo(), sn) == 0) {
                found = true;
                if (currentStudent.getToken() == 1) { // Check if they actually have a book to return
                    while (file1.read(reinterpret_cast<char*>(&currentBook), sizeof(Book)) && !flag) {
                        // Find the specific book the student borrowed
                        if (strcmp(currentBook.getBookNo(), currentStudent.getStudentBookNo()) == 0) {
                            flag = true;
                            currentBook.showBook();
                            cout << "\n\nBook Deposited In No. Of Days: ";
                            cin >> day; // Ask how many days they kept the book
                            if (day > 15) { // If they kept it for more than 15 days
                                fine = (day - 15) * 15; // Calculate fine (Rs 15 per extra day)
                                cout << "\n\n[Penalty] Fine to be paid = Rs " << fine;
                            }
                            currentStudent.resetToken(); // Reset token to 0 (book returned)
                            
                            // Update the student's data in the file
                            std::streamoff pos = -1 * static_cast<std::streamoff>(sizeof(Student));
                            file.seekp(pos, ios::cur);
                            file.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
                            cout << "\n\n[Success] Book Deposited Successfully.";
                        }
                    }
                    if (!flag) cout << "\n[Error] Book does not exist in the database.";
                } else {
                    cout << "\n[Notice] No Book is Currently Issued to this Student.";
                }
            }
        }
        if (!found) cout << "\n[Error] Student Record Does Not Exist.";
        
        file.close();
        file1.close();
        waitForEnter();
    }

    // Hidden menu for the Librarian / Admin
    void adminMenu() {
        if (!verifyAdmin()) return; // Checks password, exits if wrong
        
        int choice;
        do {
            clearScreen();
            cout << "\n\n\t==============================";
            cout << "\n\t      ADMINISTRATOR MENU";
            cout << "\n\t==============================";
            cout << "\n\n\t1. CREATE STUDENT RECORD";
            cout << "\n\t2. DISPLAY ALL STUDENT RECORDS";
            cout << "\n\t3. DISPLAY SPECIFIC STUDENT";
            cout << "\n\t4. MODIFY STUDENT RECORD";
            cout << "\n\t5. DELETE STUDENT RECORD";
            cout << "\n\t6. CREATE BOOK RECORD";
            cout << "\n\t7. DISPLAY ALL BOOKS";
            cout << "\n\t8. DISPLAY SPECIFIC BOOK";
            cout << "\n\t9. MODIFY BOOK RECORD";
            cout << "\n\t10. DELETE BOOK RECORD";
            cout << "\n\t11. CLEAR ALL DATA (Factory Reset)"; // Option 11 to reset database
            cout << "\n\t12. LOGOUT (Back To Main Menu)";     // Changed to option 12
            cout << "\n\n\tEnter Your Choice (1-12): ";
            cin >> choice; 
            
            // Run the function based on what the admin chose
            switch (choice) {
                case 1: writeStudent(); break;
                case 2: displayAllStudents(); break;
                case 3: {
                    char num[6];
                    cout << "\n\n\tEnter Admission No.: ";
                    cin >> num;
                    displaySpecificStudent(num);
                    break;
                }
                case 4: modifyStudent(); break;
                case 5: deleteStudent(); break;
                case 6: writeBook(); break;
                case 7: displayAllBooks(); break;
                case 8: {
                    char num[6];
                    cout << "\n\n\tEnter Book No.: ";
                    cin >> num;
                    displaySpecificBook(num);
                    break;
                }
                case 9: modifyBook(); break;
                case 10: deleteBook(); break;
                case 11: clearAllData(); break; // Triggers the factory reset
                case 12: return; // Exits the admin menu and goes back to the main menu
                default: cout << "\n[Error] Invalid Choice. Please try again."; waitForEnter();
            }
        } while (choice != 12);
    }
};

// --- MAIN FUNCTION ---

// Shows a welcome banner when the program starts
void displayIntro() {
    clearScreen();
    cout << "\n\n\n\n";
    cout << "\t\t==========================================\n";
    cout << "\t\t||      LIBRARY MANAGEMENT SYSTEM       ||\n";
    cout << "\t\t||         (OOP Architecture)           ||\n";
    cout << "\t\t==========================================\n";
    cout << "\n\t\t     Developed as a core C++ Project    \n";
    waitForEnter();
}

// The starting point of the C++ program
int main() {
    char choice;
    LibraryManager librarySystem; // Creates the main manager object to run everything
    
    displayIntro(); // Show the welcome screen
    do {
        clearScreen();
        // The normal menu for regular users
        cout << "\n\n\t==============================";
        cout << "\n\t         MAIN MENU";
        cout << "\n\t==============================";
        cout << "\n\n\t1. BOOK ISSUE";           // Borrow a book
        cout << "\n\t2. BOOK DEPOSIT";         // Return a book
        cout << "\n\t3. ADMINISTRATOR LOGIN";  // Go to admin tools
        cout << "\n\t4. EXIT APPLICATION";     // Close the program
        cout << "\n\n\tEnter Your Choice (1-4): ";
        cin >> choice;
        
        switch (choice) {
            case '1': librarySystem.bookIssue(); break;
            case '2': librarySystem.bookDeposit(); break;
            case '3': librarySystem.adminMenu(); break;
            case '4': 
                clearScreen();
                cout << "\n\n\tExiting Application. Have a great day!\n\n";
                exit(0); // Closes the program safely
                break;
            default: 
                cout << "\n[Error] Invalid Choice."; 
                waitForEnter();
        }
    } while (choice != '4'); // Keep showing this menu until the user presses 4
    
    return 0; // Standard signal that the program ended perfectly
}