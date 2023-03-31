#include <iostream>
//fstream for file input and output
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
//stdlib.h for changing colour of terminal and text (purely cosmetic)
#include <stdlib.h>
using namespace std;

//simple class for testing purposes -> probably needs to be expanded with more data fields, functions, and expanded into more inherited classes
void MainLoop();
class Employee {
	string id;
	string password;
	string name;
	string role;
public:
	//constructor for data fields
	Employee(string id, string password, string name, string role) {
		this->id = id;
		this->password = password;
		this->name = name;
		this->role = role;
	}
	//default constructor with blank datafields
	Employee() {
		id = "";
		password = "";
		name = "";
		role = "";
	}

	//setters and getters for data fields
	void setID(string id) {
		this->id = id;
	}

	void setName(string name) {
		this->name = name;
	}

	void setRole(string role) {
		this->role = role;
	}

	void setPassword(string password) {
		this->password = password;
	}

	string getID() {
		return id;
	}

	string getName() {
		return name;
	}

	string getRole() {
		return role;
	}

	string getPassword() {
		return password;
	}
};

//Method used to save new employee into file. Only used when adding an employee, not when editing or erasing current employees. 
//This method just appends to the end of existing file the new employee, rather than rewriting whole file
void SaveEmployeeToFile(Employee employee) {
	//fstream is object for outputting and inputting
	fstream output;
	//ios::app opens the file without overwriting, and appends the data to the end of the file
	output.open("EmployeeData.txt", ios::app);
	//write to the file employee password, name, and role
	output << employee.getID() << " " << employee.getPassword() << " " << employee.getName() << " " << employee.getRole() << endl;
	output.close();
}

//Other method used for saving. This one is used for when editing or deleting current employees. This method rewrites the entire file from scratch.
void OverwriteSaveFile(vector<Employee> employees) {
	fstream output;
	output.open("EmployeeData.txt", ios::out);
	for (int i = 0; i < employees.size(); i++) {
		output << employees[i].getID() << " " << employees[i].getPassword() << " " << employees[i].getName() << " " << employees[i].getRole() << endl;
	}
	output.close();
}

//Method to add new employees. Needs to be changed to only be accessible to managers
Employee AddEmployee() {
	string id;
	string password;
	string name;
	//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
	string firstName;
	string lastName;
	string role;
	//ask user for new employees password, name, and role. Then make new employee object from these inputs, and return it. Also save to the file this new employee
	cout << "Set employee id" << endl;
	cin >> id;
	cout << "Set employee password: " << endl;
	cin >> password;
	cout << "Enter employee name:" << endl;
	cin >> firstName >> lastName;
	name += firstName + " " + lastName;
	cout << "Enter the employees role: " << endl;
	cin >> role;
	cout << name << endl << password << endl << role << endl;
	Employee employeeToAdd(id, password, name, role);
	SaveEmployeeToFile(employeeToAdd);
	return employeeToAdd;
}

//Loop through the employee array, and print out each employee and their datafields
void ViewEmployees(vector<Employee> employees) {
	for (int i = 0; i < employees.size(); i++) {
		cout << employees[i].getID() << " " << employees[i].getName() << " " << employees[i].getPassword() << " " << employees[i].getRole() << endl;
	}
}

//Used for both editing and deleting employees. Whether editing or removing is decided from the 'editOrRemove' parameter
void EditEmployees(vector<Employee> employees, string editOrRemove) {
	string id;
	int index;
	bool found = false;
	//change colour of output window and text depending on if editing or removing
	if (editOrRemove == "edit") {
		system("Color E0");
	}
	else if (editOrRemove == "remove") {
		system("Color C0");
	}
	//Ask for employee id
	cout << "Enter employees ID: " << endl;
	cin >> id;



	//Search array for employee id, if found return index of employee
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getID() == id) {
			index = i;
			found = true;
			break;
		}
	}

	//if the employee was found, ask for futher input
	if (found == true) {
		string input;
		//if editing, ask what the user wants to edit
		if (editOrRemove == "edit") {

			cout << "Employee to edit: " << employees[index].getName() << endl;
			cout << "What to edit? " << endl;
			cout << "1. Name" << endl;
			cout << "2. Password" << endl;
			cout << "3. Job" << endl;
			cout << "4. ID" << endl;

			cin >> input;
			if (input == "1") {
				//Change the name of the index of the account the user wants to change
				string firstName;
				string lastName;
				string name;
				cout << "Enter the new name: " << endl;
				cin >> firstName >> lastName;
				name = firstName + " " + lastName;
				employees[index].setName(name);
			}
			else if (input == "2") {
				//Change the password of the account of index the user wants to change 
				string password;
				cout << "Enter the new password: " << endl;
				cin >> password;
				employees[index].setPassword(password);
			}
			else if (input == "3") {
				//Change the job [or role] of the account of index chosen by user
				string job;
				cout << "Enter the new job: " << endl;
				cin >> job;
				employees[index].setRole(job);
			}
			else if (input == "4") {
				string id;
				cout << "Enter the new id: " << endl;
				cin >> id;
				employees[index].setID(id);
			}
			else {
				//if user chooses other invalid input, let them know, and break out of method
				cout << "Invalid input." << endl;
				return;
			}
		}
		else if (editOrRemove == "remove") {
			//Alternatively, if not editing but removing employees
			string removeInput;
			//Ask for confirmation they want to remove an employee
			cout << "Employee to remove: " << employees[index].getName() << endl;
			cout << "Are you sure you want to remove them? (y/n)" << endl;
			cin >> removeInput;
			if (removeInput == "y" or removeInput == "Y") {
				cout << "Removed " << employees[index].getName() << endl;
				//erase the employee at index found. vector.erase() method takes in a pointer value, so have to use vector.begin() then add the index
				employees.erase(employees.begin() + index);
			}
			else if (removeInput == "n" or removeInput == "N") {
				cout << "Cancelled remove." << endl;
				return;
			}
			else {
				cout << "Invalid input. Noone was removed." << endl;
				return;
			}
		}
		//Once employee is edited or removed, rewrite the file with new data
		OverwriteSaveFile(employees);
	}
	else {
		cout << "Could not find that id." << endl;
	}
}

void Loading() {
	cout << "\n\n\n\n\n\t\t\t\t\t Loading Please wait..." << endl;
	char loading = 220;
	cout << "\t\t\t";
	for (int i = 0; i <= 50; i++) {
		Sleep(100);
		cout << loading;
	}
	cout << "\n" << endl;
	system("CLS");


}

//Load employee vector from the file, if the file exists
vector<Employee> LoadEmployees() {
	vector<Employee> employees;
	fstream input;
	input.open("EmployeeData.txt");
	if (input.fail() || input.peek() == ifstream::traits_type::eof()) {
		//cout << "Could not open save file." << endl;
		cout << "This is your first time setting up! Welcome!" << endl;
		string id;
		string password;
		//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
		string role;
		string firstName;
		string lastName;
		string name;
		cout << "What is your name?" << endl;
		cin >> firstName >> lastName;
		name += firstName + " " + lastName;
		system("CLS");
		cout << "I assume that you are the manager of this corporation, please create a password" << endl;
		role = "Manager";
		cin >> password;
		system("CLS");
		cout << "Perfect!, What will be your ID?" << endl;
		cin >> id;
		system("CLS");
		srand(time(0));

		Employee firstEmployee(id, password, name, role);
		employees.push_back(firstEmployee);
		SaveEmployeeToFile(firstEmployee);

	}
	else {
		//Keep looping until end of file, and read the data from file one word at a time. Create the employee objects from this file data, and pushback to employee vector each object
		while (!input.eof()) {
			string id;
			string name;
			string firstName;
			string lastName;
			string role;
			string password;
			input >> id;
			input >> password;
			input >> firstName;
			input >> lastName;
			input >> role;
			name = firstName + " " + lastName;
			Employee employee(id, password, name, role);
			employees.push_back(employee);
		}
	}
	//close file
	input.close();
	return employees;
}

Employee login(vector<Employee> employees) {
	string id;
	string password;
	int index;
	bool found = false;
	cout << "Login" << endl;
	cout << "ID: ";
	cin >> id;
	for (int i = 0; i < employees.size(); i++) {
		if (id == employees[i].getID()) {
			index = i;
			found = true;
			break;
		}
	}

	if (found == true) {
		cout << "Enter password for user " << employees[index].getName() << " " << endl;
		cout << "Password: ";
		cin >> password;
		if (password == employees[index].getPassword()) {
			cout << "Logged in!" << endl;
			return employees[index];
		}
		else {
			cout << "Invalid password. Try again." << endl;
			login(employees);
		}
	}
	else {
		cout << "Invalid ID. Try again." << endl;
		login(employees);
	}
}

int Reset(vector<Employee> employees) {

	string opt;
	cout << "Do you want to reset the system? (Y/N)" << endl;
	cin >> opt;
	//Get line for the employee data
	if (opt == "Y" || opt == "y") {
		//Opens the file in which the employees are stored in
		fstream input;
		input.open("EmployeeData.txt", ofstream::out | ofstream::trunc);
		input.close();
		LoadEmployees();
		//Failsafe, if somehow the user resets this
		if (input.fail()) {
			LoadEmployees();
			return 1;
		}
	}
	else if (opt == "N" || opt == "n") {
		LoadEmployees();
	}
	else if (opt == "...") {
		ofstream reset("song.txt");
		reset << "I want you all to think more about the future of AI and feel a little saddened by the confusion and ethical dilemmas that will arise in the age of AI. Humansongs is about Po-UTA, who has an artificial brain and loves me, Porter, like a father. I am not immortal and Po-UTA is immortal. Therefore, we will be parted forever, and as a result Po-UTA will have to accept grief. In other words, this is the story of a child who has lost a parent. Of course, I am not sure if there is any reality in this AI since it is portrayed through human emotions and eyes, but since this is art, I made it so that it still resonates with the human heart.";
		bool played = PlaySound(TEXT("Song.wav"), NULL, SND_ASYNC);
		cout << "" << endl;
		string loading = " ";
		cout << "\t\t\t";
		for (int i = 0; i <= 120; i++) {
			Sleep(100);
			cout << loading;
		}
		cout << ":)" << endl;
		cout << "\n" << endl;
		for (int i = 0; i <= 380; i++) {
			Sleep(100);
			cout << loading;
		}
		cout << ":(" << endl;
		cout << "\n" << endl;
		system("pause");


	}


}

void Messaging(vector<Employee> employees) {
	string id;
	string opt;
	string name;
	string date;
	ofstream input;
	input.open("EmployeeMessages.txt");
	string message;
	cout << "Do you want to message the manager?" << endl;
	cin >> opt;
	cout << "Your alias?" << endl;
	getline(cin >> ws, name);
	cout << "Your ID?" << endl;
	cin >> id;
	cout << "Date?" << endl;
	getline(cin >> ws, date);
	cout << "Please state your message here!" << endl;
	getline(cin >> ws, message);
	if (opt == "Y" || "y") {
		if (input.is_open()) {
			input << name << " " << id << " " << date << " " << message << endl;
			input.close();
		}
	}
	else if (opt == "N" || "n") {

		MainLoop();

	}
}

//main loop that all other functions are childed to
void MainLoop() {
	while (true) {
		Employee user;
		system("Color 9F");
		//vector of all employees. Filled by the file, if the file exists
		vector<Employee> employees = LoadEmployees();
		user = login(employees);
		//prompt user for input
		if (user.getRole() == "Manager") {

			cout << "1: Add Employee" << endl;
			cout << "2: Remove Employee" << endl;
			cout << "3: Edit Employee" << endl;
			cout << "4: View Employees" << endl;
			cout << "5: Logout" << endl;
			cout << "9: Reset Everything" << endl;
			string input;
			cin >> input;
			if (input == "1") {
				employees.push_back(AddEmployee());
			}
			else if (input == "2") {
				EditEmployees(employees, "remove");
			}
			else if (input == "3") {
				EditEmployees(employees, "edit");
			}
			else if (input == "4") {
				ViewEmployees(employees);
			}
			else if (input == "5") {
				cout << "Logged out!" << endl;
				MainLoop();
			}
			else if (input == "9") {
				system("CLS");
				Reset(employees);
			}
		}
		else {
			cout << "User: " << user.getName() << endl;
			cout << "1: View Schedule" << endl;
			cout << "2: View Salary" << endl;
			cout << "3: Messaging" << endl;
			cout << "4: Logout" << endl;

			string input;
			cin >> input;
			if (input == "1") {
				MainLoop();
			}
			if (input == "3") {

				Messaging(employees);

			}
			if (input == "3") {
				cout << "Logged out!" << endl;
				MainLoop();
			}
		}
	}

}

int main() {
	//Changes colour of output background and text, respectively
	/* 1-blue 2-green 3-aqua 4-red 5-purple 6-yellow 7-white 8-gray 9-lightblue 0-black A-lightgreen B-lightaqua C-lightred D-lightpurple E-lightYellow F-brightwhite
	*/
	//3F is nice home menu colouring
	//9F is also nice home colouring
	//C is nice background colour for remove employee
	//E is relatively nice colour for viewing things
	MainLoop();
	/*
	fstream employeeData;
	employeeData.open("EmployeeData.txt");
	employeeData.close();
	*/
}