#include<iostream>
#include<sstream>
#include<mysql.h>
#include"Interface.cpp"

using namespace std;

// A blueprint class for all banks
class Bank:public Interface
{
	// Attributes or properties of a bank
	private:
		string name, address, ifsc;
	
	// Member functions of a bank
	public:
		
		// To set attributes of a bank
		void setDetails(string name, string address, string ifsc)
		{
			Bank::name = name;
			Bank::address = address;
			Bank::ifsc = ifsc;
		}
		
		// To print details of the bank
		void getDetails()
		{
			cout<<"Bank Name = "<<Bank::name<<endl;
			cout<<"Bank Address = "<<Bank::address<<endl;
			cout<<"Bank IFSC Code = "<<Bank::ifsc<<endl;
			cout<<endl;
		}
		
		// To get name of the bank
		string getName()
		{
			return Bank::name;
		}
		
		// To get address of the bank
		string getAddress()
		{
			return Bank::address;
		}
		
		// To get ifsc code of the bank
		string getIfsc()
		{
			return Bank::ifsc;
		}
};
