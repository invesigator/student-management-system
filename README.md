# Student Management System (FICT)

A C++ console application for managing student records and exam results using linked lists data structure.

## 📋 Overview

This project implements a comprehensive student management system for the Faculty of Information and Communication Technology (FICT). The system manages student information, exam results, and provides various analytical features using custom linked list implementation.

## 🏗️ Project Structure

### Core Data Structures

- **Student**: Contains personal information and academic records
- **Exam**: Stores trimester exam results and subjects
- **Subject**: Individual subject details with grades and credit hours
- **List**: Custom linked list implementation for data management
- **Node**: Linked list node structure

### Key Files

```
├── app.cpp               # Main application logic
├── Student.h/.cpp        # Student class implementation
├── Exam.h/.cpp           # Exam class implementation
├── Subject.h/.cpp        # Subject class implementation
├── List.h/.cpp           # Custom linked list implementation
├── Node.h/.cpp           # Node structure for linked list
├── student.txt           # Sample student data file
├── exam.txt              # Sample exam results file
└── student_result.txt    # Output file for student records
```

## ✨ Features

### 1. Student Management
- **Create Student List**: Import student records from text file
- **Delete Student**: Remove student by ID with confirmation
- **Print Student List**: Display to screen or export to file
- **Duplicate Detection**: Prevents duplicate student records

### 2. Exam Management
- **Insert Exam Results**: Import exam data and calculate GPAs
- **Automatic CGPA Calculation**: Real-time cumulative GPA updates
- **Multiple Trimester Support**: January, May, October trimesters

### 3. Analytics & Reporting
- **Print Statistics**: 
  - Total students by course (CS, IA, IB, CN, CT)
  - Average CGPA across all students
  - Average subjects per semester
  - Average credits per semester

### 4. Advanced Filtering
- **Filter Students**: Search by course, enrollment year, and credit hours
- **Potential First Class**: Identify students likely to achieve first-class honors
- **Course-based Analysis**: Filter by specific academic programs

### 5. Data Management
- **Update Student Information**: Modify IDs and phone numbers
- **Phone Number Standardization**: Convert 7-digit to 9-digit format
- **ID Prefix Addition**: Add course prefixes (BCS, BIA, BIB, BCN, BCT)

## 🎓 Academic Grading System

| Grade | Marks | Points |
|-------|-------|--------|
| A+    | 90-100| 4.0000 |
| A     | 80-89 | 4.0000 |
| A-    | 75-79 | 3.6700 |
| B+    | 70-74 | 3.3300 |
| B     | 65-69 | 3.0000 |
| B-    | 60-64 | 2.6700 |
| C+    | 55-59 | 2.3300 |
| C     | 50-54 | 2.0000 |
| F     | 0-49  | 0.0000 |

## 📊 Sample Data Format

### Student Data (student.txt)
```
Student Id = 1200233
Name = Matt Damon
course = CS
Phone Number = 790-3233

Student Id = 1201237
Name = Ben Affleck
course = IA
Phone Number = 432-4579
```

### Exam Data (exam.txt)
```
1200233  1  2013  3 UCCD1004 PROGRAMMING_CONCEPTS_AND_DESIGN 4 70 UCCD1024 DATA_STRUCTURES_AND_ALGORITHMIC_PROBLEM_SOLVING 4 80 UCCD2502 INTRODUCTION_TO_INVENTIVE_PROBLEM_SOLVING_AND_PROPOSAL_WRITING 3 78
```

## 🚀 Getting Started

### Prerequisites
- Microsoft Visual Studio 2022
- C++ compiler with C++11 support
- Windows operating system (uses system calls)

### Compilation & Execution
1. Open the project in Visual Studio 2022
2. Build the solution (Ctrl+Shift+B)
3. Run the executable
4. Follow the interactive menu system

### Menu Options
```
1. Create student list
2. Delete Student
3. Print student list
4. Insert exam result
5. Print Exam Statistic
6. Filter Student
7. Update Student's ID and Phone
8. Find Potential First Class Student
9. Exit
```

## 🎯 Key Algorithms

### CGPA Calculation
```cpp
current_cgpa = sum_of_all_grade_points / total_credit_hours
```

### First Class Potential Criteria
- Minimum 3 trimesters completed
- GPA ≥ 3.75 for at least 3 trimesters
- Minimum 12 credit hours per high-GPA trimester
- All other trimesters must have GPA ≥ 3.50

### Year Extraction from Student ID
```cpp
year_enrolled = (id[0] - '0') * 10 + (id[1] - '0') + 2000
```

## 🔧 Technical Implementation

### Data Structures Used
- **Singly Linked List**: For dynamic student record management
- **Arrays**: For storing multiple exams and subjects per student
- **Structs**: Organized data representation

### Memory Management
- Dynamic memory allocation for linked list nodes
- Proper cleanup and deallocation
- Efficient insertion and deletion operations

### File I/O Operations
- Text file parsing for student and exam data
- Output formatting for reports and lists
- Error handling for file operations

## 📈 Performance Features

- **O(n)** search operations for student lookup
- **O(1)** insertion at list head
- **Sorted insertion** by student name for better organization
- **Memory efficient** dynamic allocation

## 🛡️ Error Handling

- File not found protection
- Duplicate record detection and prevention
- Input validation for menu choices
- Empty list handling for all operations
- Graceful recovery from errors

## 👥 Course Information

**Course Codes Supported:**
- **CS**: Computer Science
- **IA**: Information Systems Engineering  
- **IB**: Business Information Systems
- **CN**: Communication and Networking
- **CT**: Computer Engineering

## 📝 Assignment Context

This project was developed as Assignment 1 for UCCD1024 - Data Structures and Algorithmic Problem Solving. The assignment focuses on:

- Understanding and implementing linked lists
- Dynamic data structure manipulation
- File I/O operations
- Object-oriented programming in C++
- Complex data relationships and calculations

## 🔍 Testing

The system has been tested with various scenarios including:
- Empty lists and files
- Large datasets
- Edge cases for GPA calculations
- Various course combinations
- Different trimester patterns

## 📄 License

This project is for educational purposes as part of university coursework.

---

*Developed for UCCD1024 Data Structures and Algorithmic Problem Solving*
