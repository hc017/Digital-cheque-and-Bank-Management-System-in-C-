#include<iostream>

using namespace std;

// A blueprint structure of a bank account user
struct user_details
{
	// Attributes or properties of a user
	string first_name;
	string last_name;
	string gender;
	int account_no;
	int balance;
	string username;
	string password;
	
	// To get details of a user object as input from the console
	void getDetails()
	{
		cout<<"Enter First Name: ";
		cin>>first_name;
		cout<<"Enter Last Name: ";
		cin>>last_name;
		cout<<"Enter Gender(Male, Female, Others): ";
		cin>>gender;
		cout<<"Enter Balance: ";
		cin>>balance;
		cout<<"Enter Username: ";
		cin>>username;
		cout<<"Enter Password: ";
		cin>>password;
	}
	
	// To set details of a user object with reference to the database
	void setDetails(string first, string last, string gen, int acc, int bal, string user, string pass)
	{
		first_name = first;
		last_name = last;
		gender = gen;
		account_no = acc;
		balance = bal;
		username = user;
		password = pass;
	}
	
	// To print details of a particular user
	void printDetails()
	{
		cout<<"First Name = "<<first_name<<endl;
		cout<<"Last Name = "<<last_name<<endl;
		cout<<"Gender = "<<gender<<endl;
		cout<<"Account Number = "<<account_no<<endl;
		cout<<"Balance = "<<balance<<endl;
		cout<<"Username = "<<username<<endl;
		cout<<"Password = "<<password<<endl;
		cout<<endl;
	}
	
	// To print details of multiple users as a row
	void printDetailsAll()
	{
		cout<<first_name<<" | "<<last_name<<" | "<<gender<<" | "<<account_no<<" | "<<balance<<" | "<<username<<" | "<<password<<endl;
	}
	
	void capitalize(string &str)
	{
		if (str.length() == 0) {
			return;
		}
		str[0] = std::toupper(str[0]);
	}
};
