#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "List.h"
#include "Student.h"
#include <sstream>

using namespace std;

bool CreateStuList(const char *, List *);
bool DeleteStudent(List *, char *);
bool PrintList(List, int); 
bool InsertExamResult(const char *, List *);
bool PrintStatistic(List);
bool FilterStudent(List, List *, char *, int, int) ;
bool UpdateIDandPhone(List *);
bool FindPotentialFirstClass(List, List *, char *);
int menu();

using namespace std;


int main() {

	// create the needed list
	List studentList, filteredList, potentialList;
	const char* studentFileName = "student.txt";
	const char* examFileName = "exam.txt";

	int choice = 0;

	// loop the program
	while (true) {
	MENU:
		choice = menu();  // display menu and get user's choice

		// create student list
		if (choice == 1) {
			if (CreateStuList(studentFileName, &studentList)) {
				system("cls");

				cout << "\nStudent list is created successfully.\n" << endl;

				//PrintList(studentList, 1);  // for testing purpose only
				system("pause");
				system("cls");
			}
			else {
				system("cls");

				cout << "\nStudent list is not created successfully." << endl;

				system("pause");
				system("cls");
			}
		}

		// delete student
		else if (choice == 2) {
			char sid[12];  // student ID
			char conf;  // confirmation


			cout << "\n\nPlease enter the student ID (e.g:2300123) that you wish to delete: ";
			cin >> sid;

			cout << "\n\nDo you confirm to delete student " << sid << " from the list?" << endl;
			cout << "Choice (Y/N): ";
			cin >> conf;

			if (conf == 'Y' || conf == 'y') {
				system("cls");

				DeleteStudent(&studentList, sid);

				system("pause");
				system("cls");

			}

			else {
				system("cls");
				goto MENU;
			}
		}

		// print student list
		else if (choice == 3) {
			int source = 0;

			system("cls");

			cout << "\nPlease enter the source: " << endl;
			cout << "1. Print to the screen" << endl;
			cout << "2. Write in student_result.txt" << endl;
			cout << "\nSource (1/2): ";
			cin >> source;

			PrintList(studentList, source);

			system("pause");
			system("cls");
		}

		// insert exam result
		else if (choice == 4) {
			if (InsertExamResult(examFileName, &studentList)) {
				system("cls");

				cout << "\n\nExam results are inserted successfully from file." << endl;
				PrintList(studentList, 1);

				system("pause");
				system("cls");
			}
			else
				cout << "\n\nExam results are not inserted successfully from file." << endl;
		}

		// print exam statistic
		else if (choice == 5) {
			system("cls");

			if (PrintStatistic(studentList)) {
				cout << "\n\nExam statistic is printed successfully.\n\n" << endl;

				system("pause");
				system("cls");
			}
			else {
				cout << "\n\nExam statistic is not printed successfully." << endl;

				system("pause");
				system("cls");
			}
				
		}

		// filter student
		else if (choice == 6) {
			char course[3];
			int year;
			int totalCredit;
			char cont;

			system("cls");

			do {
				cout << "\nPlease enter the course(XX): ";
				cin >> course;

				cout << "\nPlease enter the year(XXXX) : ";
				cin >> year;

				cout << "\nPlease enter the total credit: ";
				cin >> totalCredit;

				filteredList = List();  // reset the filtered list before filtering

				if (FilterStudent(studentList, &filteredList, course, year, totalCredit))
					PrintList(filteredList, 1);
				else
					cout << "\nNo students found with the given conditions.\n" << endl;

				do {
					cout << "\nWould you like to continue filtering student?" << endl;
					cout << "\nEnter your choice (Y/N): ";
					cin >> cont;
				} while (toupper(cont) != 'Y' && toupper(cont) != 'N');

				system("cls");

			} while (toupper(cont) == 'Y');

			system("cls");
		}

		// update student ID and phone
		else if (choice == 7) {
			if (UpdateIDandPhone(&studentList)) {
				system("cls");

				PrintList(studentList, 1);

				cout << "\n\nThe student's ID and phone are updated successfully.\n\n" << endl;

				system("pause");
				system("cls");
			}
			else {
				system("cls");

				cout << "\nThe student's ID and phone are not updated successfully.\n" << endl;

				system("pause");
				system("cls");
			}
		}

		// find potential first class
		else if (choice == 8) {
			char course[3];

			system("cls");

			cout << "\n\nPlease enter the course(XX): ";
			cin >> course;

			FindPotentialFirstClass(studentList, &potentialList, course);
			PrintList(potentialList, 1);

			system("pause");
			system("cls");
		}

		// exit
		else if (choice == 9) {
			system("cls");

			cout << "********************************" << endl;
			cout << "\nThank you for using the system!" << endl;
			cout << "\n\tGoodbye :)\n\n" << endl;
			cout << "********************************\n" << endl;

			break;
		}
	}
	system("pause");
	return 0;
}

// create student list
bool CreateStuList(const char* filename, List* list) {
	ifstream infile;
	infile.open(filename);

	Student temp;  // store the data of each student
	string line;

	if (!infile.is_open()) {
		cout << "\n\nError: Cannot open the file " << filename << " successfully\n";
		return false;
	}
	else
		cout << "\n\nSuccessfully open the file " << filename << "." << endl;

	while (getline(infile, line)) {
		if (line.find("Student Id") != string::npos) {  // string::npos - to indicate that a search for a substring was unsuccessful
			string id = line.substr(line.find("=") + 2);  // add 2 index after the '='
			strcpy(temp.id, id.c_str());
		}
		else if (line.find("Name") != string::npos) {
			string name = line.substr(line.find("=") + 2);
			strcpy(temp.name, name.c_str());
		}
		else if (line.find("course") != string::npos) {
			string course = line.substr(line.find("=") + 2);
			strcpy(temp.course, course.c_str());
		}
		else if (line.find("Phone Number") != string::npos) {
			string phone_no = line.substr(line.find("=") + 2);
			strcpy(temp.phone_no, phone_no.c_str());

			// Check for duplicate records
			bool duplicate = false;  // 1 duplicate data is stored in the text file to try out the function is working or not

			for (int i = 1; i <= list->size(); i++) {
				Student existing;

				list->get(i, existing);

				if (temp.compareID(existing)) {  // compare using ID
					duplicate = true;
					break;  // if there is duplication of data, break the program
				}
			}

			if (!duplicate)
				list->insert(temp);

			// Reset temporary student object
			temp = Student();
		}
	}
	infile.close();
	return true;
}

// delete the student selected
bool DeleteStudent(List* list, char* id) {
	Student temp;

	for (int i = 1; i <= list->size(); i++) {
		list->get(i, temp);
		if (strcmp(temp.id, id) == 0) {
			list->remove(i);
			cout << "Student ID " << id << " has been deleted." << endl;
			return true;
		}
	}

	cout << "\nStudent ID " << id << " is not found." << endl;
	return false;
}

// print student list
bool PrintList(List list, int source) {
	// check if the list is empty
	if (list.empty()) {
		cout << "Cannot print from empty list!" << endl;
		return false;
	}

	if (source == 1) { // print to screen
		// create a cur pointer
		// assign the head to cur
		Node* cur = list.head;

		while (cur != NULL) {
			cur->item.print(cout);  // print student info
			if (cur->item.exam_cnt == 0) {  // trimester exam == 0
				cout << "THIS STUDENT HAVEN'T TAKEN ANY EXAM YET" << endl;
			}
			else {
				for (int i = 0; i < cur->item.exam_cnt; i++) {  // print exam info
					cur->item.exam[i].print(cout);
				}
			}

			// move to the next node
			cur = cur->next;
		}
		return true;
	}
	else if (source == 2) { // write to file
		ofstream outFile("student_result.txt");

		if (!outFile.is_open()) {
			cout << "Error: Cannot open the file " << "student_result.txt." << endl;
			return false;
		}

		Node* cur = list.head;
		while (cur != NULL) {
			cur->item.print(outFile);
			if (cur->item.exam_cnt == 0)
				outFile << "THIS STUDENT HAVEN'T TAKEN ANY EXAM YET" << endl;
			else {
				for (int i = 0; i < cur->item.exam_cnt; i++) {
					cur->item.exam[i].print(outFile);
				}
			}
			cur = cur->next;
		}

		cout << "\n\nThe result has been written to the file student_result.txt." << endl;
		outFile.close();
		return true;
	}
	else {
		cout << "Invalid source." << endl;  // if the source is not 1 or 2
		return false;
	}

	return true;
}

// insert exam result
bool InsertExamResult(const char* filename, List* list) {
	ifstream infile;
	infile.open(filename);

	Student tempStudent;
	Exam tempExam;
	char buffer[256];
	int pos;
	
	string line;

	if (!infile.is_open()) {
		cout << "\n\nError: Cannot open the file " << filename << " successfully\n";
		return false;
	}
	else
		cout << "\n\nSuccessfully open the file " << filename << "." << endl;



	while (infile) {
		// read student ID
		infile >> tempStudent.id;

		if (!infile)
			break;

		// read exam tri, yr, no of subjects
		infile >> tempExam.trimester >> tempExam.year >> tempExam.numOfSubjects;

		// read subjects info
		for (int i = 0; i < tempExam.numOfSubjects; i++) {
			infile >> tempExam.sub[i].subject_code;
			infile.get();
			infile.getline(tempExam.sub[i].subject_name, 256, '\t');
			infile >> tempExam.sub[i].credit_hours >> tempExam.sub[i].marks;
		}

		// calculate GPA
		tempExam.calculateGPA();

		// Find the correct student based on ID and insert the exam struct variable
		for (pos = 1; pos <= list->size(); pos++) {
			Student currentStudent;
			list->get(pos, currentStudent);

			if (currentStudent.compareID(tempStudent)) {
				currentStudent.exam[currentStudent.exam_cnt++] = tempExam;
				currentStudent.calculateCurrentCGPA();
				list->set(pos, currentStudent);
				break;
			}
		}
	}
	infile.close();
	return true;
}

// print statistic for the student list
bool PrintStatistic(List list) {
	int total_stu = list.size();
	int cs_stu = 0, ia_stu = 0, ib_stu = 0, cn_stu = 0, ct_stu = 0;
	double total_cgpa = 0;
	int total_subjects = 0;
	int total_credits = 0;

	if (list.empty()) {
		cout << "\n\nThe list is empty" << endl;
		return false;
	}

	for (int i = 1; i <= total_stu; i++) {
		Student current_stu;
		list.get(i, current_stu);
		total_cgpa += current_stu.current_cgpa;

		if (strcmp(current_stu.course, "CS") == 0) {
			cs_stu++;
		}
		else if (strcmp(current_stu.course, "IA") == 0) {
			ia_stu++;
		}
		else if (strcmp(current_stu.course, "IB") == 0) {
			ib_stu++;
		}
		else if (strcmp(current_stu.course, "CN") == 0) {
			cn_stu++;
		}
		else if (strcmp(current_stu.course, "CT") == 0) {
			ct_stu++;
		}

		for (int j = 0; j < current_stu.exam_cnt; j++) {
			total_subjects += current_stu.exam[j].numOfSubjects;

			for (int k = 0; k < current_stu.exam[j].numOfSubjects; k++) {
				total_credits += current_stu.exam[j].sub[k].credit_hours;
			}
		}
	}

	double avg_cgpa = total_cgpa / total_stu;
	double avg_subj_per_semester = static_cast<double>(total_subjects) / total_stu;
	double avg_credits_per_semester = static_cast<double>(total_credits) / total_stu;

	cout << "\n\n";

	cout << "Total Students: " << total_stu << endl;
	cout << "  CS Students : " << cs_stu << endl;
	cout << "  IA Students : " << ia_stu << endl;
	cout << "  IB Students : " << ib_stu << endl;
	cout << "  CN Students : " << cn_stu << endl;
	cout << "  CT Students : " << ct_stu << endl;

	cout << "\n";

	cout << "Average CGPA: " << fixed << setprecision(5) << avg_cgpa << endl;
	cout << "Average Subjects Taken Per Semester: " << fixed << setprecision(2) << avg_subj_per_semester << endl;
	cout << "Average Credits Earned Per Semester: " << fixed << setprecision(2) << avg_credits_per_semester << endl;

	return true;
}

// filter student in list 1 and insert into list 2
bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {
	// Check if list1 is empty or list2 is not empty
	if (list1.empty() || !list2->empty())
		return false;

	// Traverse list1
	for (int i = 1; i <= list1.size(); i++) {
		Student student;

		int year_enrolled = 0;
		list1.get(i, student);

		// Extract year enrolled from student id
		year_enrolled = (student.id[0] - '0') * 10 + (student.id[1] - '0') + 2000;

		// Check if student fulfills all conditions
		if (strcmp(student.course, course) == 0 && year_enrolled == year && student.totalCreditsEarned >= totalcredit) {
			// Insert the student into list2
			list2->insert(student);
		}
	}
	
	return true;
}

// update student ID and phone number
bool UpdateIDandPhone(List* list) {
	if (list->empty())
		return false;

	Node* cur;
	cur = list->head;

	while (cur != NULL) {
		Student& student = cur->item;

		// Update ID
		char newID[13];
		switch (student.course[0]) {
		case 'C':
			if (student.course[1] == 'S')
				strcpy(newID, "BCS");
			else if (student.course[1] == 'N')
				strcpy(newID, "BCN");
			else if (student.course[1] == 'T')
				strcpy(newID, "BCT");
			break;
		case 'I':
			if (student.course[1] == 'A')
				strcpy(newID, "BIA");
			else if (student.course[1] == 'B')
				strcpy(newID, "BIB");
			break;
		}

		strcat(newID, student.id);
		strcpy(student.id, newID);

		// Update phone number
		char newPhone[11];

		if (student.phone_no[0] % 2 == 0)
			strcpy(newPhone, "02");
		else
			strcpy(newPhone, "01");

		strncat(newPhone, student.phone_no, 3);
		strncat(newPhone, student.phone_no + 4, 4);
		strcpy(student.phone_no, newPhone);

		cur = cur->next;
	}

	return true;
}

// find potential first class student
bool FindPotentialFirstClass(List list1, List* list2, char* course) {
	bool foundPotentialFirstClass = false;
	Student tempStudent;
	int firstClassCounter;
	int otherCounter;
	
	if (list1.empty() || !list2->empty())
		return false;

	for (int i = 1; i <= list1.size(); i++) {
		list1.get(i, tempStudent);

		if (strcmp(tempStudent.course, course) == 0 && tempStudent.exam_cnt >= 3) {
			firstClassCounter = 0;
			otherCounter = 0;  // other trimesters GPA cannot be < 3.50000

			for (int j = 0; j < tempStudent.exam_cnt; j++) {
				if (tempStudent.exam[j].gpa >= 3.75000 && tempStudent.totalCreditsEarned >= 12)  // check student have potential to get first class
					firstClassCounter++;
				else if (tempStudent.exam[j].gpa >= 3.50000)  // cannot be < 3.50000, so it will be >= 3.50000
					otherCounter++;
			}

			// if there are at least 3 trimesters with a GPA of 3.75 or higher and if the remaining trimesters have a GPA of at least 3.5
			if (firstClassCounter >= 3 && otherCounter == tempStudent.exam_cnt - firstClassCounter) {
				list2->insert(tempStudent);
				foundPotentialFirstClass = true;
			}
		}
	}

	// if there is no student in the course that has potential to get first class
	if (!foundPotentialFirstClass)
		cout << "\nThere is no student in " << course << " that has potential to get first class.\n" << endl;
	
	return true;
}

// menu
int menu() {
	int choice;

	while (true) {
		cout << "\n----------------------------------------------------" << endl;
		cout << "\tStudent FICT Management System Menu" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "\t1. Create student list" << endl;
		cout << "\t2. Delete Student" << endl;
		cout << "\t3. Print student list" << endl;
		cout << "\t4. Insert exam result" << endl;
		cout << "\t5. Print Exam Statistic" << endl;
		cout << "\t6. Filter Student" << endl;
		cout << "\t7. Update Student's ID and Phone" << endl;
		cout << "\t8. Find Potential First Class Student" << endl;
		cout << "\t9. Exit" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Please enter your choice in number: ";
		cin >> choice;

		if (choice >= 1 && choice <= 9)
			break;
		else {
			cout << "\n\nInvalid choice, please try again." << endl;
			
			system("pause");
			system("cls");
		}
	}

	return choice;
}