#include "recipients.h"
#include"blood_data.h"
#include "ArrayStack.h"
#include<iostream>
#include<vector>
#include<fstream>
#include <string>
using namespace std;
int getRecipientID()
{
	ifstream recipientFile;
	recipientFile.open("RecipientRegister.txt");
	int recipient_id = 0;
	string fname, lname, mail, password, gender, blood_type, hospital_name, doctor_fname, doctor_lname;
	int age, ID;
	ArrayStack stack;
	string line;
	while (recipientFile >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctor_fname >> doctor_lname, getline(recipientFile, hospital_name, '\n'))
	{
		stack.push(ID);

	}
	recipient_id = stack.pop() + 1;
	recipientFile.close();
	return recipient_id;
}
void getDatafile(vector<blood_data>& vecupdate)
{
	fstream file;
	file.open("bloodData.txt");
	int quantity;
	string bloodType;
	string received_date, expired_date;
	while (file >> quantity >> bloodType >> received_date >> expired_date)
	{
		blood_data newData(quantity, bloodType, received_date, expired_date);
		vecupdate.push_back(newData);
	}

}
void creatvector(vector<blood_data>& newDatavector) 
{
	bool found = false;
	int quantity = 0;
	vector<blood_data>temp;

	for (int i = 0; i < newDatavector.size(); i++) 
	{
		blood_data newdata(newDatavector[i].getQuantity(), newDatavector[i].getType(), newDatavector[i].getDate(), newDatavector[i].getExDate());
		temp.push_back(newdata);
	}
	for (int i = 0; i < temp.size(); i++) {
		for (int j = i + 1; j < newDatavector.size(); j++)
			if ((temp[i].getType() == newDatavector[j].getType()) && (temp[i].getDate() == newDatavector[j].getDate())) {
				quantity = newDatavector[j].getQuantity() + temp[i].getQuantity();
				newDatavector[j].setQuantity(quantity);
				newDatavector.erase(newDatavector.begin() + i);
				temp.clear();
			}
	}


}
void saveData(vector<blood_data>& data) 
{
	fstream file;
	file.open("bloodData.txt", ios::out);
	for (int i = 0; i < data.size(); i++) {
		file << data[i].getQuantity() << ' ';
		file << data[i].getType() << ' ';
		file << data[i].getDate() << ' ';
		file << data[i].getExDate() << '\n';
	}
	file.close();
	string getcontent;
	file.open("bloodData.txt", ios::in);
	while (!file.eof())
	{
		getline(file, getcontent);
		cout << getcontent << endl;
	}
	file.close();
}
void savenewData(vector<blood_data>& data)
{
	fstream file;
	file.open("bloodData.txt", ios::out);
	for (int i = 0; i < data.size(); i++) {
		file << data[i].getQuantity() << ' ';
		file << data[i].getType() << ' ';
		file << data[i].getDate() << ' ';
		file << data[i].getExDate() << '\n';
	}
	file.close();
	
}
bool searchforBlood(vector<string>availableBlood, vector<blood_data>& vecupdate)
{

	bool found = false;
	for (auto x : availableBlood)
	{

		for (auto c : vecupdate)
		{

			if (x == c.getType())
			{
				cout << "available :" << endl;
				cout << c.getQuantity() << " " << c.getType() << " " << c.getDate() << " " << c.getExDate() << endl;
				found = true;

			}
		}
	}
	if (found) {
		return true;
	}
	else {
		return false;
	}

}
bool checkrequestedblood(vector<string>availableBlood, vector<blood_data>& vecupdate)
{
	string btype;
	cout << "Enter the blood type that available to you : ";
	cin >> btype;
	int quantity;
	cout << "Enter the quantity you want : " << endl;
	cin >> quantity;
	for (string x : availableBlood) {

		for (int i = 0; i < vecupdate.size(); i++) {
			if (btype == x && x == vecupdate[i].getType()) {

				if (quantity <= vecupdate[i].getQuantity()) {
					int newquantity = vecupdate[i].getQuantity() - quantity;
					vecupdate[i].setQuantity(newquantity);
					if (vecupdate[i].getQuantity() == 0) {
						vecupdate.erase(vecupdate.begin() + i);
					}
					return true;
				}
			}

		}
	}


}
void recipients::recipient_menu()
{
	cout << "1-Register " << endl;
	cout << "2-login " << endl;
	cout << "3-exit" << endl;
	while (true)
	{
		int choice;
		cout << "Choose the number that meets your need:" << endl;
		cin >> choice;
		if (choice == 1)
		{
			Register();
			break;
		}
		else if (choice == 2)
		{
			login();
			break;
		}
		else if (choice == 3)
		{
			exit(0);
			break;
		}
		else
			cout << "wrong choice! please try again" << endl;
		continue;
	}
}
void recipients::sub_menu(int id)
{
	while (true)
	{
		cout << "1-update your Data " << endl;
		cout << "2-Delete your account " << endl;
		cout << "3-search for the availability of blood type " << endl;
		cout << "4-Display blood data " << endl;
		cout << "5-Request donation " << endl;
		cout << "6-Back" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			update(id);
			system("pause");
			system("cls");

		}
		else if (choice == 2)
		{
			Delete(id);
			system("pause");
			system("cls");
		}
		else if (choice == 3)
		{
			search();
			system("pause");
			system("cls");
		}
		else if (choice == 4)
		{
			display();
			system("pause");
			system("cls");
		}
		else if (choice == 5)
		{
			requestDonation(id);
			system("pause");
			system("cls");
		}
		else if (choice == 6)
		{
			recipient_menu();
			system("pause");
			system("cls");
		}
		else
			cout << "wrong choice ! try again" << endl;
		continue;
	}

	system("pause");
	system("cls");
}
void recipients::Register()
{
	cout << "Enter your  First Name : " << endl;
	cin >> fname;
	cout << "Enter your  Last Name : " << endl;
	cin >> lname;
	cout << "Enter your mail : " << endl;
	cin >> mail;
	cout << "Enter your passwrod : " << endl;
	cin >> password;
	cout << "Enter your age : " << endl;
	cin >> age;
	cout << "Enter your gender : " << endl;
	cin >> gender;
	cout << "Enter your blood type : " << endl;
	cin >> blood_type;
	cout << "Enter doctor first name : " << endl;
	cin >> doctorFname;
	cout << "Enter doctor last name : " << endl;
	cin >> doctorLname;
	cout << "Enter the hospital name : " << endl;
	cin.ignore();
	getline(cin, hospital_name);
	cout << "account is created successfully " << endl;
	ID = getRecipientID();
	cout << "Your ID is : ";
	cout << ID << endl;
	fstream RegFile;
	recipients newRecipient(ID, fname, lname, mail, password, age, gender, blood_type, doctorFname, doctorLname, hospital_name);
	vector<recipients> recipientVec;
	recipientVec.push_back(newRecipient);
	RegFile.open("RecipientRegister.txt", ios::app);
	for (int i = 0; i < recipientVec.size(); i++) {
		RegFile << recipientVec[i].ID << " ";
		RegFile << recipientVec[i].fname << " ";
		RegFile << recipientVec[i].lname << " ";
		RegFile << recipientVec[i].mail << " ";
		RegFile << recipientVec[i].password << " ";
		RegFile << recipientVec[i].age << " ";
		RegFile << recipientVec[i].gender << " ";
		RegFile << recipientVec[i].blood_type << " ";
		RegFile << recipientVec[i].doctorFname << " ";
		RegFile << recipientVec[i].doctorLname << " ";
		RegFile << recipientVec[i].hospital_name << endl;

	}
	RegFile.close();
	system("pause");
	system("cls");
	sub_menu(ID);
}
void recipients::update(int id)

{
	fstream RegFile;
	fstream temp;
	int input;
	RegFile.open("RecipientRegister.txt", ios::in);
	temp.open("temp.txt", ios::out);
	int choice;
	while (RegFile >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctorFname >> doctorLname, getline(RegFile, hospital_name, '\n'))
	{
		hospital_name.erase(0, 1);
		if (id == ID)
		{
			cout << "Press 1 to edit name : \n Press 2 to edit mail : \n Press 3 to edit password : \n press 4 to edit age : \n press 5 to edit Doctor_name: \n";
			cin >> choice;
			switch (choice)
			{

			case 1:
				cout << "Enter the new name" << endl;
				cout << "Enter first name : ";
				cin >> fname;
				cout << "Enter last name : ";
				cin >> lname;
				cout << "name is updated successfully" << endl;
				break;
			case 2:
				cout << "Enter the new mail" << endl;
				cin >> mail;
				cout << "mail is updated successfully" << endl;
				break;
			case 3:
				cout << "Enter the new password " << endl;
				cin >> password;
				cout << "password is updated successfully" << endl;
				break;

			case 4:
				cout << "Enter the new age " << endl;
				cin >> age;
				cout << "age is updated successfully" << endl;
				break;
			case 5:
				cout << "enter the new Doctor_of_the_case" << endl;
				cout << "Enter first name : ";
				cin >> doctorFname;
				cout << "Enter last name : ";
				cin >> doctorLname;
				cout << "doctor name is updated successfully" << endl;
				break;
			default:
				cout << "invalid number" << endl;
			}

			temp << ID << " " << fname << " " << lname << " " << mail << " " << password << " " << age << " " << gender << " " << blood_type << " " << doctorFname << " " << doctorLname << " " << hospital_name << endl;
		}

		else
		{
			temp << ID << " " << fname << " " << lname << " " << mail << " " << password << " " << age << " " << gender << " " << blood_type << " " << doctorFname << " " << doctorLname << " " << hospital_name << endl;
		}

	}
	temp.close();
	RegFile.close();
	remove("RecipientRegister.txt");
	rename("temp.txt", "RecipientRegister.txt");
	system("pause");
	system("cls");
	sub_menu(id);

}
recipients::recipients()
{
	ID = 0;
	fname = "";
	lname = "";
	mail = "";
	password = "";
	age = 0;
	gender = "";
	blood_type = "";
	doctorFname = "";
	doctorLname = "";
	hospital_name = "";

}
recipients::recipients(int id, string fristname, string lastname, string email, string pass, int recip_age, string recip_gender, string typeOfblood, string docFirstname, string docLastname, string nameOfhospital)
{
	ID = id;
	fname = fristname;
	lname = lastname;
	mail = email;
	password = pass;
	age = recip_age;
	gender = recip_gender;
	blood_type = typeOfblood;
	doctorFname = docFirstname;
	doctorLname = docLastname;
	hospital_name = nameOfhospital;

}
void recipients::Delete(int id)
{
	fstream RegFile;
	fstream temp;
	RegFile.open("RecipientRegister.txt", ios::in);
	temp.open("temp.txt", ios::out);
	string fname, lname, mail, password, gender, blood_type, hospital_name, doctor_fname, doctor_lname;
	int age, ID;
	int n;
	/*cout << "enter ID" << endl;
	cin >> n;*/
	while (RegFile >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctor_fname >> doctor_lname, getline(RegFile, hospital_name, '\n'))
	{
		hospital_name.erase(0, 1);
		if (ID == id)
		{
			continue;
		}
		else
		{
			temp << ID << " " << fname << " " << lname << " " << mail << " " << password << " " << age << " " << gender << " " << blood_type << " " << doctor_fname << " " << doctor_lname << " " << hospital_name << endl;
		}

	}
	RegFile.close();
	temp.close();
	RegFile.open("RecipientRegister.txt", ios::out);
	temp.open("temp.txt", ios::in);
	while (temp >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctor_fname >> doctor_lname, getline(temp, hospital_name, '\n'))
	{
		hospital_name.erase(0, 1);
		RegFile << ID << " " << fname << " " << lname << " " << mail << " " << password << " " << age << " " << gender << " " << blood_type << " " << doctor_fname << " " << doctor_lname << " " << hospital_name << endl;
	}
	temp.close();
	RegFile.close();
	remove("temp.txt");
	cout << "account deleted successfully" << endl;
	system("pause");
	system("cls");
	recipient_menu();
}
void recipients::display()
{
	vector<blood_data>dataOfblood;
	getDatafile(dataOfblood);
	creatvector(dataOfblood);
	saveData(dataOfblood);
}
void recipients::login()
{
	while (true)
	{
		fstream RegFile;
		int userID;
		RegFile.open("RecipientRegister.txt", ios::in);
		if (RegFile.fail())
		{
			cout << "Recipient Register file opening failed";
			exit(1);
		}
		string userPassword;
		cout << "Enter your ID :" << endl;
		cin >> userID;
		cout << "enter password :" << endl;
		cin >> userPassword;
		bool isFound = 0;
		int id;
		while (RegFile >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctorFname >> doctorLname, getline(RegFile, hospital_name, '\n'))
		{
			id = ID;
			if ((userID == ID) && (userPassword == password))
			{
				isFound = 1;
				break;
			}

		}
		if (isFound)
		{
			cout << "login successfully" << endl;
			system("pause");
			system("cls");
		}

		if ((!isFound))
		{
			cout << "login failed! try again" << endl;
			continue;
		}
		RegFile.close();
		while (true)
		{
			if (isFound)
			{
				int choice;
				cout << "1-update your Data " << endl;
				cout << "2-Delete your account " << endl;
				cout << "3-search for the availability of blood type " << endl;
				cout << "4-Display blood data " << endl;
				cout << "5-Request donation " << endl;
				cout << "6-Back" << endl;
				cout << "Choose the number that meets your need:" << endl;
				cin >> choice;
				if (choice == 1)
				{
					update(id);
					system("pause");
					system("cls");
				}
				else if (choice == 2)
				{
					Delete(id);
					system("pause");
					system("cls");
				}
				else if (choice == 3)
				{
					search();
					system("pause");
					system("cls");
				}
				else if (choice == 4)
				{
					display();
					system("pause");
					system("cls");
				}
				else if (choice == 5)
				{
					requestDonation(id);
					system("pause");
					system("cls");
				}
				else if (choice == 6)
				{
					recipient_menu();
					system("pause");
					system("cls");

				}
				else
					cout << "wrong choice ! try again" << endl;
				continue;

			}
		}
	}
	system("pause");
	system("cls");
}
void recipients::requestDonation(int id)
{
	vector<blood_data>dataOfblood;
	getDatafile(dataOfblood);
	//A PLUS
	vector<string>Aplus;
	Aplus.push_back("A+");
	Aplus.push_back("A-");
	Aplus.push_back("O+");
	Aplus.push_back("O-");
	//A MINUS
	vector<string>Aminus;
	Aminus.push_back("A-");
	Aminus.push_back("O-");

	//AB PLUS 
	vector<string>ABplus;
	ABplus.push_back("A+");
	ABplus.push_back("A-");
	ABplus.push_back("B+");
	ABplus.push_back("B-");
	ABplus.push_back("AB+");
	ABplus.push_back("AB-");
	ABplus.push_back("O+");
	ABplus.push_back("O-");

	//AB MINUS
	vector<string>ABminus;
	ABminus.push_back("B-");
	ABminus.push_back("A-");
	ABminus.push_back("AB-");
	ABminus.push_back("O-");

	//B PLUS
	vector<string>Bplus;
	Bplus.push_back("B+");
	Bplus.push_back("B-");
	Bplus.push_back("O+");
	Bplus.push_back("O-");

	//B MINUS 
	vector<string>Bmius;
	Bmius.push_back("B-");
	Bmius.push_back("O-");

	// O PLUS
	vector<string>Oplus;
	Oplus.push_back("O+");
	Oplus.push_back("O-");

	//O MINUS
	vector<string>Ominus;
	Ominus.push_back("O-");

	fstream RegFile;
	string bloodtype, hospitalname;
	int quantity;
	recipients r;
	RegFile.open("RecipientRegister.txt", ios::in);
	string nameOfhospital;
	while (RegFile >> ID >> fname >> lname >> mail >> password >> age >> gender >> blood_type >> doctorFname >> doctorLname, getline(RegFile, hospital_name))
	{

		if (id == ID)
		{
			cout << "Enter the hospital name where you will be available : ";
			cin.ignore();
			getline(cin, nameOfhospital);
			if (blood_type == "A+")
			{
				if (searchforBlood(Aplus, dataOfblood) == false) {
					cout << "Not Available" << endl;
				}
				else {
					if (checkrequestedblood(Aplus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}

				}
			}
			else if (blood_type == "A-")
			{
				if (searchforBlood(Aminus, dataOfblood) == false) {
					cout << "Not Available" << endl;
				}
				else {
					if (checkrequestedblood(Aminus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}

				}
			}
			else if (blood_type == "AB+")
			{
				if (searchforBlood(ABplus, dataOfblood) == false) {
					cout << "Not Available" << endl;
				}
				else {
					if (checkrequestedblood(ABplus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else if (blood_type == "AB-")
			{
				if (searchforBlood(ABminus, dataOfblood) == false) {

					cout << "Not Available" << endl;
				}

				else
				{
					if (checkrequestedblood(ABminus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else if (blood_type == "B+")
			{
				if (searchforBlood(Bplus, dataOfblood) == false) {
					cout << "Not Available" << endl;
				}
				else
				{
					if (checkrequestedblood(Bplus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else if (blood_type == "B-")
			{
				if (searchforBlood(Bmius, dataOfblood) == false) {
					cout << "Not Available" << endl;
				}
				else
				{
					if (checkrequestedblood(Bmius, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else if (blood_type == "O+")
			{
				if (searchforBlood(Oplus, dataOfblood) == false)
				{
					cout << "Not Available" << endl;
				}
				else
				{
					if (checkrequestedblood(Oplus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else if (blood_type == "O-")
			{
				if (searchforBlood(Ominus, dataOfblood) == false) {

					cout << "Not Available" << endl;
				}
				else
				{
					if (checkrequestedblood(Ominus, dataOfblood)) {
						savenewData(dataOfblood);
						cout << "Your Request is Confirmed" << endl;
					}
					else {
						cout << "Your Resquest not confirmed" << endl;

					}
				}
			}
			else
				cout << "wrong choice" << endl;


		}

	}
	RegFile.close();

}
void recipients::search()
{
	vector<blood_data>dataOfblood;
	getDatafile(dataOfblood);
	//A PLUS
	vector<string>Aplus;
	Aplus.push_back("A+");
	Aplus.push_back("A-");
	Aplus.push_back("O+");
	Aplus.push_back("O-");
	//A MINUS
	vector<string>Aminus;
	Aminus.push_back("A-");
	Aminus.push_back("O-");

	//AB PLUS 
	vector<string>ABplus;
	ABplus.push_back("A+");
	ABplus.push_back("A-");
	ABplus.push_back("B+");
	ABplus.push_back("B-");
	ABplus.push_back("AB+");
	ABplus.push_back("AB-");
	ABplus.push_back("O+");
	ABplus.push_back("O-");

	//AB MINUS
	vector<string>ABminus;
	ABminus.push_back("B-");
	ABminus.push_back("A-");
	ABminus.push_back("AB-");
	ABminus.push_back("O-");

	//B PLUS
	vector<string>Bplus;
	Bplus.push_back("B+");
	Bplus.push_back("B-");
	Bplus.push_back("O+");
	Bplus.push_back("O-");

	//B MINUS 
	vector<string>Bmius;
	Bmius.push_back("B-");
	Bmius.push_back("O-");

	// O PLUS
	vector<string>Oplus;
	Oplus.push_back("O+");
	Oplus.push_back("O-");

	//O MINUS
	vector<string>Ominus;
	Ominus.push_back("O-");

	int search_input;
	cout << "Enter the blood type " << endl;;
	cout << "1) A+" << "\n" << "2) A-" << "\n" << "3) B+" << "\n" << "4) B-" << "\n" << "5) AB+" << "\n" << "6) AB-" << "\n" << "7) O+" << "\n" << "8) O-" << endl;
	cin >> search_input;

	switch (search_input)
	{
	case 1:
		if (searchforBlood(Aplus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 2:
		if (searchforBlood(Aminus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 3:
		if (searchforBlood(Bplus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 4:
		if (searchforBlood(Bmius, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 5:
		if (searchforBlood(ABplus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 6:
		if (searchforBlood(ABminus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 7:
		if (searchforBlood(Oplus, dataOfblood) == false) {
			cout << "Not Available" << endl;
		};
		break;
	case 8:
		if (searchforBlood(Ominus, dataOfblood) == false) {

			cout << "Not Available" << endl;
		};
		break;
	default:
		cout << "Wrong Choice ! Try Again" << endl;
	}


}




