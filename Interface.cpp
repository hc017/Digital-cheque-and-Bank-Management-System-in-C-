#include<iostream>
#include<list>

using namespace std;

class Interface
{
	// List variables holding bank details
	private:
		list<string> banks = {"BOI","ICICI","SBI","UBOI","UCO"};
		list<string> bankAddress = {"Head Office, Star House, C-5, G-Block, Bandra Kurla Complex, Bandra (East), Mumbai-400 051",
									"Grd Flr, Plot No. C-53, G - Block, Bandra Kurla Complex, Bandra (East) Mumbai, Maharashtra, 400051",
									"Central Office, State Bank Bhavan, Madam Cama Road, Mumbai-400 021",
									"Head Office, 239, Vidhan Bhavan Marg, Nariman Point, Mumbai-400 021.",
									"Head Office, 10, B.T.M. Sarani, Brabourn Road, Calcutta-700 001."};
		list<string> ifsc = {"BKID0006400","ICIC0003449","SBIN0001817","UBIN0535532","UCBA0000190"};
	
	public:
		void displayBanks()
		{
			cout<<"Enter 1 for BANK OF INDIA."<<endl;
			cout<<"Enter 2 for ICICI BANK."<<endl;
			cout<<"Enter 3 for STATE BANK OF INDIA."<<endl;
			cout<<"Enter 4 for UNION BANK OF INDIA."<<endl;
			cout<<"Enter 5 for UCO BANK."<<endl;
			cout<<"Enter 0 to EXIT."<<endl<<endl;
			cout<<"Enter option: ";
		}
		
		void displayLogin()
		{
			cout<<"Enter 1 to Visit Your Account."<<endl;
			cout<<"Enter 2 to Register New User."<<endl;
			cout<<"Enter 3 to Send A Digital Cheque."<<endl;
			cout<<"Enter 4 to Claim A Cheque."<<endl;
			cout<<"Enter 5 to Check Dropbox."<<endl;
			cout<<"Enter 0 to Move Back"<<endl<<endl;
			cout<<"Enter option: ";
		}
		
		void displayFunctions()
		{
			cout<<"Enter 1 to Show Available Balance."<<endl;
			cout<<"Enter 2 to Withdraw Money."<<endl;
			cout<<"Enter 3 to Deposit Money."<<endl;
			cout<<"Enter 4 to Show User Details."<<endl;
			cout<<"Enter 5 to Change Password."<<endl;
			cout<<"Enter 6 to Display Bank Details."<<endl;
			cout<<"Enter 0 to Move Back."<<endl<<endl;
			cout<<"Enter option: ";
		}
		
		list<string> getBanks()
		{
			return banks;
		}
		
		list<string> getBankAddress()
		{
			return bankAddress;
		}
		
		list<string> getBankIfsc()
		{
			return ifsc;
		}
		
		const char* getConstValue(list<string> l, int index)
		{
			list<string>::iterator itr = l.begin();
			advance(itr, index-1);
			string s = *itr;
			return s.c_str();
		}
		
		string getValue(list<string> l, int index)
		{
			list<string>::iterator itr = l.begin();
			advance(itr, index-1);
			return *itr;
		}
};
