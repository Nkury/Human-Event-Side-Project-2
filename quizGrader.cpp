#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

#define E 0
#define Dm .667
#define D 1
#define Dp 1.333
#define Cm 1.667
#define C 2
#define Cp 2.333
#define Bm 2.667
#define B 3
#define Bp 3.333
#define Am 3.667
#define A 4

struct Student{
	string name;
	vector<float> grades;
};

vector<Student> students;

int reference; // to reference the stopping position for filling in groups
int position = 1; // for counting the section
vector<string> sections; // list of sections
int sectionNum;

void main(){
	cout << "############################## QUIZ GRADER ##############################\n\n" << endl;
	cout << "Welcome to an application for grading students' quizzes." << endl;
	cout << "Please type the letter associated with the following operations.\nIt is case-sensitive." << endl;
	cout << "\n\n\t\t#################### MENU ####################" << endl;
	cout << "\t\tN- New Section" << endl;
	cout << "\t\tL- Load Section" << endl;
	cout << "\t\tA- Add Answer Key" << endl;
	cout << "\t\tQ= Quit Application" << endl;

	string input; // for input 
	string line; // for reading from file
	string fileName; // for storing the name of the file.

	while(input.compare("C") != 0){
		getline(cin, input, '\n');
		if(input.compare("N") == 0){
			students.clear(); // clearing students since we are making a new section
			cout << "\n\n\t\t################ NEW SECTION #################" << endl;
			cout << "\nWhat would you like to call the section?" << endl;
			cout << "You cannot use \":\", \"\\\", \"/\", \"?\", \"*\", \"<\", \">\", \"|\", or \"\"\"" << endl;
			getline(cin, input, '\n');
			fileName = input;
			ofstream sectionFile;
			sectionFile.open("sections.txt", fstream::app);
			if(sectionFile.is_open())
				sectionFile << input << "\n";
			else
				cout << "File is not open." << endl;
			sectionFile.close();
			cout << "\nGreat! Start adding students one by one by pressing ENTER per name." << endl;
			cout << "When you are finished, type \"DONE\"." << endl;
			cout << "If you made a mistake, type \"UNDO\" to take back your previous action." << endl;
			cout << "Okay, start entering names now: " << endl;
			while(input.compare("DONE") != 0){
				getline(cin, input, '\n');

				if(input.compare("UNDO") == 0){
					if(!students.empty()){
						ifstream inputFile;
						cout << students.back().name << " has been removed." << endl;
						inputFile.open(fileName + ".txt");
						ofstream temp("temp.txt");
						while(getline(inputFile, line)){
							if(line != students.back().name){
								temp << line << "\n";
							}
						}
						temp.close();
						inputFile.close();
						remove((fileName + ".txt").c_str());
						rename("temp.txt", (fileName + ".txt").c_str());
						students.pop_back();
					}
					else
						cout << "No students to undo. Add a student before using the UNDO function" << endl;
				}
				else if(input.compare("DONE") != 0){
					struct Student stud;
					stud.name = input;
					students.push_back(stud);
					ofstream newFile;
					newFile.open(fileName + ".txt", fstream::app);
					if(newFile.is_open())
						newFile << input << "\n";
					else
						cout << "File is not open." << endl;
					newFile.close();
				}
				else{
					if(students.empty()){
						cout << "You need to input students if you want this thing to work!" << endl;
						input = "NO";
					}
					else if(students.size() < 10){
						cout << "A class of students less than 10 won't work that well.\nEnter more than 10 students." << endl;
						input = "NO";
					}
				}
			}
			cout << "\n\n" << fileName << " successfully added!" << endl;
			cout << "Load the section to start group splitting!" << endl;
			cout << "\n\n\t\t#################### MENU ####################" << endl;
			cout << "\t\tN- New Section" << endl;
			cout << "\t\tL- Load Section" << endl;
			cout << "\t\tA- Add Answer Key" << endl;
			cout << "\t\tQ= Quit Application" << endl;
			
		}
		else if(input.compare("Q") ==0){
			exit(0);
		}
		else if(input.compare("B") ==0){
			cout << "\n\n\t\t#################### MENU ####################" << endl;
			cout << "\t\tN- New Section" << endl;
			cout << "\t\tL- Load Section" << endl;
			cout << "\t\tA- Add Answer Key" << endl;
			cout << "\t\tQ= Quit Application" << endl;
		}
		else if(input.compare("R") == 0){
			remove((sections[sectionNum-1] + ".txt").c_str());
			cout << sections[sectionNum-1] << " successfully removed." << endl;
			ifstream inputFile;
			inputFile.open("sections.txt");
			ofstream temp("temp.txt");
			while(getline(inputFile, line)){
				if(line != sections[sectionNum-1]){
					temp << line << "\n";
				}
			}
			temp.close();
			inputFile.close();
			remove("sections.txt");
			rename("temp.txt", "sections.txt");
			sections.erase(sections.begin() + sectionNum - 1);
			cout << "\n\n\t\t#################### MENU ####################" << endl;
			cout << "\t\tN- New Section" << endl;
			cout << "\t\tL- Load Section" << endl;
			cout << "\t\tA- Add Answer Key" << endl;
			cout << "\t\tQ= Quit Application" << endl;
		}
		else if(input.compare("L") == 0){
			cout << "\n\n\t\t############### LOAD SECTION #################" << endl;
			students.clear();
			bool fileExists = true;
			ifstream sectFile("sections.txt");
			if(sectFile){ // file exists
				if ( sectFile.peek() == std::ifstream::traits_type::eof()){
					// Empty File
					fileExists = false;
				}
				else{		
					cout << "\nHere are the sections you currently have stored. Type the number associated with the section you want to load:" << endl;
					if(sectFile.is_open()){
						position = 1;
						while (getline (sectFile, line, '\n')){
							cout << position << ": " << line << endl;
							sections.push_back(line);
							position++;	
						}
						sectFile.close();
					}
					else
						cout << "Unable to open file" << endl;
				}
			}
			else
				fileExists = false;
				

			if(fileExists){
				bool check4 = true;
				while(check4){
					cin >> sectionNum;
					if(sectionNum < 0 || sectionNum > sections.size()){
						cout << "Invalid choice. Please select a valid section number." << endl;
					}
					else
						check4 = false;
				}
				
				cout << "\n\n\t\t############### " << sections[sectionNum-1] << " ##################" << endl;
				cout << "\nGreat! Here are the students in " << sections[sectionNum-1] << ": " << endl;
				ifstream secFile(sections[sectionNum-1] + ".txt");
				if(secFile){ // file exists
					if(secFile.is_open()){
						while (getline (secFile, line, '\n')){
							cout << line << endl;
							struct Student stud;
							stud.name = line;
							students.push_back(stud);
						}
						secFile.close();
					}
					else
						cout << "Unable to open file";
				}

				cout << "\n\t\tC- Continue" << endl;
				cout << "\t\tR- Remove Section" << endl;
				cout << "\t\tB- Go Back" << endl;

				getline(cin, input, '\n');
			}
			else{
				cout << "No sections to load. Please add a new section before loading." << endl;
				cout << "\n\n\t\t#################### MENU ####################" << endl;
				cout << "\t\tN- New Section" << endl;
				cout << "\t\tL- Load Section" << endl;
				cout << "\t\tA- Add Answer Key" << endl;
				cout << "\t\tQ= Quit Application" << endl;
			}
		}
		else if(input.compare("A") == 0){
			cout << "\n\n\t\t############### ANSWER KEY #################" << endl;
			cout << "\t\tN- New Answer Key" << endl;
			cout << "\t\tB- Go Back" << endl;
		}
		else if(input.compare("C") != 0){
			cout << "Unrecognized input. Please try again." << endl;
		}
	}

	cout << "\n\nYou can continue to add students to the section by typing students' names" << endl;
	cout << "\tand pressing ENTER per name." << endl;
	cout << "If you make any mistakes, type \"UNDO\" to correct them" << endl;
	cout << "When you are finished, type \"DONE\" to move onto group splitting." << endl;
	cout << "Remember, input is case-sensitive." << endl;

	ofstream outputFile;
	ifstream inputFile;
	// keeps reading input until user types "DONE"
	while(input.compare("DONE") != 0){
		getline(cin, input, '\n');

		if(input.compare("UNDO") == 0){
			if(!students.empty()){
				cout << students.back().name << " has been removed." << endl;
				inputFile.open(sections[sectionNum-1] + ".txt");
				ofstream temp("temp.txt");
				while(getline(inputFile, line)){
					if(line != students.back().name){
						temp << line << "\n";
					}
				}
				temp.close();
				inputFile.close();
				remove((sections[sectionNum-1] + ".txt").c_str());
				rename("temp.txt", (sections[sectionNum-1] + ".txt").c_str());
				students.pop_back();
			}
			else
				cout << "No students to undo. Add a student before using the UNDO function" << endl;
		}
		else if(input.compare("DONE") != 0){
			struct Student stud;
			stud.name = input;
			students.push_back(stud);
			outputFile.open(sections[sectionNum-1] + ".txt", fstream::app);
			if(outputFile.is_open())
				outputFile << input << "\n";
			else
				cout << "File is not open." << endl;
			outputFile.close();
		}
		else{
			if(students.empty()){
				cout << "You need to input students if you want this thing to work!" << endl;
				input = "NO";
			}
			else if(students.size() < 10){
				cout << "A class of students less than 10 won't work that well.\nEnter more than 10 students." << endl;
				input = "NO";
			}
		}
	}


}