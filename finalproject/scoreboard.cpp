#include <iostream>
#include <ctime>
#include "scoreboard.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void ViewStudentScoreBoard(vector<score> B) {
	cout << "\n\n\t\t=====YOUR SCOREBOARD=====\n";
	for (int i = 0; i < 87; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << "ID" << left << setw(7) << "Class" << left << setw(30) << "Name" << left << setw(10) << "Midterm"
		<< left << setw(10) << "Final" << left << setw(10) << "Total" << left << setw(10) << "Bonus" << endl;
	for (int i = 0; i < 87; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < B.size(); i++) {
		cout << left << setw(10) << B[i].id << left << setw(7) << B[i].cls << left << setw(30) << B[i].studentName
			<< left << setw(10) << B[i].mid << left << setw(10) << B[i].final << left << setw(10) << B[i].total
			<< left << setw(10) << B[i].bonus << endl;
		for (int i = 0; i < 87; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void FindStudent(student &A, int ID) {
	ifstream fin;
	string inputpath;
	string classname;
	string choose;
	vector<student> list;
	int a;
	int check = 0;
	fin.open("./data/classes/class.dat");
	if (!fin.is_open()) {
		cout << "Error" << endl;
	}
	else {
		while (fin >> classname) {
			list.clear();
			inputpath = "./data/classes/" + classname + ".dat";
			LoadClass(list, inputpath);
			for (int i = 0; i < list.size(); i++) {
				if (list[i].id == ID) {
					A = list[i];
					check = 1;
					break;
				}
			}
		}
		fin.close();
	}
	if (check == 0) {
		cout << "Student can't be found" << endl;
	}
}
void LoadClass(vector<student>& list, string inputpath){
	ifstream fin;
	fin.open(inputpath);
	if (!fin.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		LoadStudent(fin, list);
		fin.close();
	}
}
void LoadStudent(ifstream& fin, vector<student>& list)
{
	student A;
	string temp, line;
	while (fin >> A.number)
	{
		fin >> A.id;
		fin.ignore(1);
		getline(fin, A.lastName);
		getline(fin, A.firstName);
		getline(fin, temp);
		A.gender = temp[0];
		getline(fin, temp, ' ');
		A.DoB.y = stoi(temp);
		getline(fin, temp, ' ');
		A.DoB.m = stoi(temp);
		getline(fin, temp);
		A.DoB.d = stoi(temp);
		list.push_back(A);
	}
}
void LoadStudentCourse(ifstream& file, vector<string>& course, string inputpath) {
	file.open(inputpath);
	string tmp;
	int n = 0;
	if (!file.is_open()) {
		cout << "Error";
	}
	else {
		while (getline(file, tmp)) {
			course[n] = tmp;
			n++;
		}

	}
}
void SearchCourse(string &Year,string &Semester ,string &Course) {
	ifstream file;
	int choice1, choice2, choice3, choice4;
	vector<string> year;
	vector<string> semester;
	vector<course> course;
	string inputpath;

	inputpath = "./data/course/year.dat";
	LoadYearFile(inputpath, year);
	cout << " Year(s):\n";
	for (int i = 0; i < year.size(); i++) {
		cout << "(" << i << ") " << year[i] << endl;
	}
	cout << "Choose a year: ";
	cin >> choice1;
	while (choice1 < 0 || choice1 >= year.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a year: ";
		cin >> choice1;
	}

	inputpath = "./data/course/" + year[choice1] + "/semester.dat";
	LoadFile(inputpath, semester);
	cout << "Semester(s):\n";
	for (int i = 0; i < semester.size(); i++) {
		cout << "(" << i << ") " << semester[i] << endl;
	}
	cout << "Choose a semester: ";
	cin >> choice2;
	while (choice2 < 0 || choice2 >= year.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a semester: ";
		cin >> choice2;
	}

	inputpath = "./data/course/" + year[choice1] +"/"+ semester[choice2] + "/course.dat";
	LoadCourseFile(course, inputpath);
	cout << "Course(s):\n";
	for (int i = 0; i < course.size(); i++) {
		cout << "(" << i << ") " << course[i].id << endl;
	}
	cout << "Choose a course: ";
	cin >> choice3;
	while (choice3 < 0 || choice3 >= course.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a course: ";
		cin >> choice3;
	}

	Year = year[choice1];
	Semester = semester[choice2];
	Course = course[choice3].id;

}
void LoadFile(string inputpath, vector<string> &A) {
	ifstream fin;
	string tmp;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "File cannot be found";
	}
	else {
		while (getline(fin, tmp)) {
			A.push_back(tmp);
		}
		fin.close();
	}
}
void PrintStudentScore(string inputpath, int choice,string year,string semester,string course) {
	ifstream fin,fin1;
	vector<student>Student;
	vector<score> Score;
	string scoreboard;
	vector<int>ID;
	vector<int>Select;
	int id,number,number1,decide;
	student A;
	score tmp;
	date tmp1;
	Time tmp2;
	string line, last, middle, first;
	if (choice == 0) {
		fin.open(inputpath);
		if (!fin.is_open()) {
			cout << "Can't open file course " << endl;
		}
		else {
			while (fin >> id) {
				/*FindStudent(A, id);
				Student.push_back(A);*/
				scoreboard = "./data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(id) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Student " << id << " can't be found" << endl;
				}
				else {
					tmp.id = id;
					getline(fin1, line);
					tmp.cls = line;
					getline(fin1, line);
					tmp.studentName = line;
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					fin1.ignore(1);
					while (fin1 >> tmp1.y) {
						fin1.ignore(1);
						fin1 >> tmp1.m;
						fin1.ignore(1);
						fin1 >> tmp1.d;
						fin1.ignore(1);
						tmp.checkedDate.push_back(tmp1);
						fin1 >> tmp2.h;
						fin1.ignore(1);
						fin1 >> tmp2.m;
						fin1.ignore(1);
						fin1 >> tmp2.s;
						fin1.ignore(1);
						tmp.checkedTime.push_back(tmp2);
					}
					Score.push_back(tmp);
				}
				fin1.close();
			}
			ViewStudentScoreBoard(Score);
			ExportCsv(Score);
		}
		fin.close();
	}
	else if (choice == 1) {
		fin.open(inputpath);
		if (!fin.is_open()) {
			cout << "Can't open file " << endl;
		}
		else {
			while (fin >> id) {
				ID.push_back(id);
			}
			cout << "Students of this course: " << endl;
			for (int i = 0; i < ID.size(); i++) {
				cout << "(" << i << ") : " << ID[i] << endl;
			}
			cout << "How many students you want to view score ? : ";
			cin >> number;
			cin.ignore();
			for (int j = 0; j < number; j++) {
				cout << "Enter ordinal number of the student : ";
				cin >> number1;
				cin.ignore();
				Select.push_back(ID[number1]);
				cout << endl;
			}
			do{
				cout << "Do you want to add someone else ? " << endl;
				cout << "(1) YES " << endl << "(2) NO" << endl;
				cout << "Your choice : ";
				cin >> decide;
				cin.ignore();
				if (decide == 1) {
					cout << "How many students you want to add more ? : ";
					cin >> number;
					cin.ignore();
					for (int j = 0; j < number; j++) {
						cout << "Enter ordinal number of the student : ";
						cin >> number1;
						cin.ignore();
						Select.push_back(ID[number1]);
						cout << endl;
					}
				}
			} while (decide == 1);
			for (int i = 0; i < Select.size();i++) {
				scoreboard = "./data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(Select[i]) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Can't open file score" << endl;
				}
				else {
					tmp.id = id;
					getline(fin1, line);
					tmp.cls = line;
					getline(fin1, line);
					tmp.studentName = line;
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					fin1.ignore(1);
					while (fin1 >> tmp1.y) {
						fin1.ignore(1);
						fin1 >> tmp1.m;
						fin1.ignore(1);
						fin1 >> tmp1.d;
						fin1.ignore(1);
						tmp.checkedDate.push_back(tmp1);
						fin1 >> tmp2.h;
						fin1.ignore(1);
						fin1 >> tmp2.m;
						fin1.ignore(1);
						fin1 >> tmp2.s;
						fin1.ignore(1);
						tmp.checkedTime.push_back(tmp2);
					}
					Score.push_back(tmp);
				}
				fin1.close();
			}
			ViewStudentScoreBoard(Score);
			ExportCsv(Score);
		}
	}
	else {
		cout << "Fail";
	}
}
void LoadCourseFile(vector<course>& list, string filePath)
{
	ifstream myFile(filePath);
	string line;
	course temp;
	int number;
	if (myFile.is_open())
	{
		while (myFile >> number)
		{
			temp.number = number;
			myFile.ignore(1);
			getline(myFile, temp.id);
			getline(myFile, temp.name);
			getline(myFile, temp.className);
			getline(myFile, temp.lecturer);
			myFile >> temp.startDate.y;
			myFile >> temp.startDate.m;
			myFile >> temp.startDate.d;
			myFile >> temp.endDate.y;
			myFile >> temp.endDate.m;
			myFile >> temp.endDate.d;
			myFile >> temp.DoW;
			myFile >> temp.startTime.h;
			myFile >> temp.startTime.m;
			temp.startTime.s = 0;
			myFile >> temp.endTime.h;
			myFile >> temp.endTime.m;
			temp.endTime.s = 0;
			myFile.ignore(1);
			getline(myFile, temp.room);
			list.push_back(temp);
		}

	}
	else
	{
		cout << "courses.dat not found" << endl;
		return;
	}
	myFile.close();
}
void ExportCsv(vector<score>B) {
	ofstream fout;
	fout.open("./export/scoreboard.csv");
	if (!fout.is_open()) {
		cout << "Can't open file export" << endl;
	}
	else {
		fout << "ID," << "Class," << "StudentName," << "Midterm," << "Final," << "Total," << "Bonus" << endl;
		for (int i = 0; i < B.size(); i++) {
			fout << B[i].id << "," << B[i].cls << "," << B[i].studentName << ","  << B[i].mid << "," << B[i].final << "," << B[i].total << "," << B[i].bonus << endl;
		}
	}
	fout.close();
}
void ImportCsv(string importpath,vector<score>&B) {
	ifstream fin;
	string trash,tmp;
	score tmp2;
	fin.open(importpath);
	if (!fin.is_open()) {
		cout << "Can't open file import" << endl;
	}
	else {
		getline(fin, trash);
		while (getline(fin, tmp, ',')) {
			tmp2.id = stoi(tmp);
			getline(fin, tmp, ',');
			tmp2.cls = tmp;
			getline(fin, tmp, ',');
			tmp2.studentName = tmp;
			getline(fin, tmp, ',');
			tmp2.mid = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.final = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.total = stof(tmp);
			getline(fin, tmp);
			tmp2.bonus = stof(tmp);
			B.push_back(tmp2);
		}
	}
	fin.close();
}
void LoadYearFile(string inputpath, vector<string>& A) {
	ifstream fin;
	string tmp;
	string year1, year2;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "File cannot be found";
	}
	else {
		while (getline(fin, year1,' ')) {
			getline(fin, year2);
			tmp = year1 + "-" + year2;
			A.push_back(tmp);
		}
		fin.close();
	}
}
void DecideToView(string year , string semester, string course) {
	int choice;
	string inputpath;
	cout << "Do you want to view scoreboard of the whole course or only some students ?" << endl;
	cout << "(0) Whole course" << endl;
	cout << "(1) Selected Students" << endl;
	cout << "Your choice: ";
	cin >> choice;
	while (choice < 0 || choice > 1 || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Your choice: ";
		cin >> choice;
	}
	inputpath = "./data/course/" + year + "/" + semester + "/" + course + ".dat";
	PrintStudentScore(inputpath, choice, year, semester, course);

}
void EditScore(string inputpath, string year, string semester , string course) {
	ifstream fin, fin1;
	int id,number,choice,choice1 = 0;
	vector<int>ID;
	string studentfile, line;
	vector<score>Score;
	score tmp;
	date tmp1;
	Time tmp2;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "Can't edit score" << endl;
	}
	else {
		while (fin >> id) {
			ID.push_back(id);
		}
		cout << "Student(s) of this course: " << endl;
		for (int i = 0; i < ID.size(); i++) {
			cout << "(" << i << ") : " << ID[i] << endl;
		}
		cout << "Enter the ordinal number of the student you want to edit score: ";
		cin >> number;
		cin.ignore(1);
		studentfile = "./data/course/" + year + "/" + semester + "/" + course + "/" + to_string(ID[number])+ ".dat";
		fin1.open(studentfile);
		if (!fin1.is_open()) {
			cout << "Can't open student file to edit" << endl;
		}
		else {
			tmp.id = id;
			getline(fin1, line);
			tmp.cls = line;
			getline(fin1, line);
			tmp.studentName = line;
			fin1 >> tmp.mid;
			fin1.ignore(1);
			fin1 >> tmp.final;
			fin1.ignore(1);
			fin1 >> tmp.total;
			fin1.ignore(1);
			fin1 >> tmp.bonus;
			fin1.ignore(1);
			while (fin1 >> tmp1.y ) {
				fin1.ignore(1);
				fin1 >> tmp1.m;
				fin1.ignore(1);
				fin1 >> tmp1.d;
				fin1.ignore(1);
				tmp.checkedDate.push_back(tmp1);
				fin1 >> tmp2.h;
				fin1.ignore(1);
				fin1 >> tmp2.m;
				fin1.ignore(1);
				fin1 >> tmp2.s;
				fin1.ignore(1);
				tmp.checkedTime.push_back(tmp2);
			}
			Score.push_back(tmp);
		}
		fin1.close();
		ViewStudentScoreBoard(Score);
		cout << "\n\nDo you want to edit this student's score ?" << endl;
		cout << "(1) Yes" << endl << "(2) No" << endl;
		cout << "Your choice : ";
		cin >> choice;
		while (choice != 1 && choice != 2 || cin.fail()) {
			cin.clear();
			cout << "Error , try again" << endl;
			cout << "Your choice : ";
			cin >> choice;
		}
		do{
			if (choice == 1) {
				cout << "\nEnter the new score: " << endl;
				cout << "Midterm score : ";
				cin >> Score[0].mid;
				cin.ignore(1);
				cout << "Final score : ";
				cin >> Score[0].final;
				cin.ignore(1);
				cout << "Total score : ";
				cin >> Score[0].total;
				cin.ignore(1);
				cout << "Bonus : ";
				cin >> Score[0].bonus;
				cin.ignore(1);
				ViewStudentScoreBoard(Score);
				cout << "\nDo you want to edit again ?" << endl;
				cout << "(1) Yes " << endl << "(2) No" << endl;
				cout << "Your choice: ";
				cin >> choice1;
				cin.ignore(1);
				while (choice1 != 1 && choice1 != 2 || cin.fail()) {
					cin.clear();
					cout << "Error , try again" << endl;
					cout << "Your choice : ";
					cin >> choice1;
				}
			}
		} while (choice1 == 1);
		SaveFileScore(studentfile, Score[0]);
		fin1.close();
	}
	fin.close();
}
void SaveFileScore(string outputpath, score student) {
	ofstream fout;
	fout.open(outputpath);
	if (!fout.is_open()) {
		cout << "Can't open file to save" << endl;
	}
	else {
		fout << student.cls << endl;
		fout << student.studentName << endl;
		fout << student.mid << " " << student.final << " " << student.total << " " << student.bonus << endl;
		for (int i = 0; i < student.checkedDate.size(); i++) {
			fout << student.checkedDate[i].y << " " << student.checkedDate[i].m << " " << student.checkedDate[i].d << " " << 
				student.checkedTime[i].h << " " << student.checkedTime[i].m << " " << student.checkedTime[i].s << endl;
		}
	}
	fout.close();
}