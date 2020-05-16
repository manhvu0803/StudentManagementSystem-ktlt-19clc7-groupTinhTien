#ifndef COURSE_INCLUDE_H_
#define COURSE_INCLUDE_H_
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "utility.h"
#include <ctime>
#include <algorithm>
#include <cmath>
//#include "class.h"
#include <cstdio>
#include "dataStructure.h"
using namespace std;
void courseMenu(int year, string semester);
void loadCsvFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void loadDatFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void loadCourseStudentFile(tt::course& Course, tt::vector<int>& classStudents, string filePath);
void saveCourseList(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void saveCourseStudentFile(tt::course& Course, tt::vector<int>& classStudent, string filePath);
void importCsvFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void output1Course(tt::course& Course, tt::vector<int>& classStudents);
void outputCourseList(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students);
void output1CourseData(tt::course& Course);
void outputSchedule(tt::vector<tt::course>& list);
int  inputTime(tt::time& courseTime);
int  inputDate(tt::date& Date);
void input1Course(tt::course& newCourse, tt::vector<int>& classStudents);
void inputCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void editCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void deleteCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath);
void remove1Student(tt::vector<int>& classStudent);
void add1Student(tt::course& Course, tt::vector<int>& classStudents);
void addStudent(tt::course& Course, tt::vector<int>& classStudents);
void viewStudentList(tt::vector<int>& classStudent);
void sortList(tt::vector<tt::course>& List, tt::vector<tt::vector<int>>& students);
int maxdayinmonth(int month, int year);
void swap(tt::vector<int>& list1, tt::vector<int>& list2);
tt::course searchCourse(string filePath, string Id);

#endif