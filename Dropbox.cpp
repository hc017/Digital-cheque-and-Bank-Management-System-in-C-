#include<iostream>

using namespace std;

// A blueprint structure for a dropbox
struct dropbox
{
	// Attributes or properties of a dropbox
	string sender_bank_name;
	int sender_acc_no;
	int receiver_acc_no;
	int amount;
	
	// To get the amount
	int getAmount()
	{
		return amount;
	}
	
	// To set details of a dropbox object with reference to the database
	void setDetails(string sbn, int san, int ran, int amt)
	{
		sender_bank_name = sbn;
		sender_acc_no = san;
		receiver_acc_no = ran;
		amount = amt;
	}
	
	// To print details of a particular dropbox object
	void printDetails()
	{
		cout<<"Sender's Bank Name = "<<sender_bank_name<<endl;
		cout<<"Sender's Account Number = "<<sender_acc_no<<endl;
		cout<<"Receiver's Account Number = "<<receiver_acc_no<<endl;
		cout<<"Amount = "<<amount<<endl;
		cout<<endl;
	}
	
	// To print details of multiple dropbox objects as a row
	void printDetailsAll()
	{
		cout<<sender_bank_name<<" | "<<sender_acc_no<<" | "<<receiver_acc_no<<" | "<<amount<<endl;
	}
};
