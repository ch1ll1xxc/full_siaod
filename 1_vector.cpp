#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Student
{
	unsigned zachotka;
	std::string full_name;
	char group[10];
	unsigned marks[5];
};

float averageMarkOfStudent(Student& student)
{
	float res = 0;
	for (unsigned i = 0; i < 5; i++)
	{
		res += student.marks[i];
	}
	res /= 5.f;

	return res;
}

bool isGoodStudent(Student& student)
{
	if (averageMarkOfStudent(student) > 4.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void inputStudent(Student& student)
{
	std::cout << "Enter student's number: ";
	std::cin >> student.zachotka;
	std::cout << "Enter student's name: ";
	std::cin >> student.full_name;
	std::cout << "Enter student's group (10 symbols): ";
	for (unsigned i = 0; i < 10; i++)
	{
		std::cin >> student.group[i];
	}
	std::cout << "Enter student's marks: ";
	for (unsigned i = 0; i < 5; i++)
	{
		std::cin >> student.marks[i];
	}
}

void inputStudentTXT(Student& student, std::ifstream& in)
{
	in >> student.zachotka;
	in >> student.full_name;
	for (unsigned i = 0; i < 10; i++)
	{
		in >> student.group[i];
	}
	for (unsigned i = 0; i < 5; i++)
	{
		in >> student.marks[i];
	}
}

void outputStudent(Student& student)
{
	std::cout << student.zachotka << ' ';
	std::cout << student.full_name << ' ';
	for (unsigned i = 0; i < 10; i++)
	{
		std::cout << student.group[i];
	}
	std::cout << ' ';
	for (unsigned i = 0; i < 5; i++)
	{
		std::cout << student.marks[i] << ' ';
	}
	std::cout << averageMarkOfStudent(student) << std::endl;
}

struct Table
{
	size_t n = 0;
	std::vector<Student>students;
};

void addStudentsToTableTXT(Table& table, std::ifstream& in)
{
	int ch = 0;
	while (!in.eof())
	{
		Student tmp_student;
		inputStudentTXT(tmp_student, in);
		table.students.push_back(tmp_student);
		ch++;
		table.n++;
	}
	std::cout << "Introduced: " << ch << " note(-s)." << std::endl;
}

void addOneStudentToTable(Table& table)
{
	Student student;
	inputStudent(student);
	table.students.push_back(student);
	table.n++;
}

void addStudentsToTable(Table& table)
{
	int value_of_students;
	std::cout << "Enter the value of students: ";
	std::cin >> value_of_students;

	for (unsigned i = 0; i < value_of_students; i++)
	{
		addOneStudentToTable(table);
	}
}

void removeStudentFromTable(Table& table, float average)
{
	for (int i = 0; i < table.n; i++) {
		if (averageMarkOfStudent(table.students[i]) < average) {
			table.students.erase(table.students.begin() + i);
			table.n--;
		}
	}
}

void Insert(Table& table, Student& student, unsigned index)
{
	table.students.insert(table.students.begin() + index, student);
}

Table makeGoodTable(Table& table)
{
	Table goodTable;

	for (unsigned i = 0; i < table.n; i++)
	{
		if (averageMarkOfStudent(table.students[i]) > 4.f)
		{
			bool flag = false;
			for (unsigned index = 0; index < goodTable.n; index++)
			{
				if (averageMarkOfStudent(goodTable.students[index]) < averageMarkOfStudent(table.students[i]))
				{
					flag = true;
					Insert(goodTable, table.students[i], index);
					goodTable.n++;
					break;
				}
			}
			if (!flag)
			{
				goodTable.students.push_back(table.students[i]);
				goodTable.n++;
			}
		}
	}

	return goodTable;
}

void outputTable(Table table)
{
	for (unsigned i = 0; i < table.students.size(); i++)
	{
		outputStudent(table.students[i]);
	}
}

void outputStudentZach(Student& student)
{
	std::cout << student.zachotka;
}

void outputTableZach(Table table)
{
	for (unsigned i = 0; i < table.n; i++)
	{
		outputStudentZach(table.students[i]);
		std::cout << '\n';
	}
}

void Act(Table& studentTable)
{
	while (true)
	{
		std::cout << "Enter the code of action that you want" << std::endl;
		std::cout << "1 - Fill table by keyboard" << std::endl;
		std::cout << "2 - Fill table by .txt file" << std::endl;
		std::cout << "3 - Add note to table" << std::endl;
		std::cout << "4 - Make list of students (their numbers) which average mark more than 4.0" << std::endl;
		std::cout << "5 - Remove notes about students which average mark lower than given" << std::endl;
		std::cout << "6 - Write a table" << std::endl;
		std::cout << "0 - Finish" << std::endl;

		std::ifstream in("input.txt");
		unsigned ans;
		std::cin >> ans;

		if (ans == 1)
		{
			addStudentsToTable(studentTable);
		}
		if (ans == 2)
		{
			addStudentsToTableTXT(studentTable, in);
		}
		if (ans == 3)
		{
			addOneStudentToTable(studentTable);
		}
		if (ans == 4)
		{
			outputTableZach(makeGoodTable(studentTable));
		}
		if (ans == 5)
		{
			float avg;
			std::cout << "Enter average mark: ";
			std::cin >> avg;
			removeStudentFromTable(studentTable, avg);
		}
		if (ans == 6)
		{
			outputTable(studentTable);
		}
		if (ans == 0)
		{
			return;
		}
	}
}

int main()
{
	Table studentTable;
	Act(studentTable);
	return 0;
}
