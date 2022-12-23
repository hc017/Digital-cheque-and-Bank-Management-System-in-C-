#include<iostream>
#include<sstream>
#include<conio.h>
#include<mysql.h>
#include"Bank.cpp"
#include"User.cpp"
#include"Dropbox.cpp"

using namespace std;

// Global variable for login check
bool login;

// Structure for performing tasks on the selected bank
struct dbHelper
{
	// Attributes or properties of structure
	const char *server, *user, *password, *database;
	
	// To set attributes of a structure as per selected database
	void setDetails(const char *db)
	{
		server = "localhost";
		user = "root";
		password = "rish14";	
		database = db;
	}
	
	// To get all records from the table
	void getAllRecords(MYSQL *con)
	{
		struct user_details user;
		stringstream ss;
		ss<<"select * from user_details;";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row; 
		res = mysqlExecuteQuery(con, str.c_str());
		while((row = mysql_fetch_row(res)) != NULL)
		{
			user.setDetails(row[0], row[1], row[2], atoi(row[3]), atoi(row[4]), row[5], row[6]);
			user.printDetailsAll();
		}
		mysql_free_result(res);
	}
	
	// To get record of a particular user
	void getRecord(MYSQL *con, string username, string password)
	{
		struct user_details user;
		stringstream ss;
		ss<<"select * from user_details where username = '"<<username<<"' and password = '"<<password<<"';";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row;
		res = mysqlExecuteQuery(con, str.c_str());
		while((row = mysql_fetch_row(res)) != NULL)
		{
			user.setDetails(row[0], row[1], row[2], atoi(row[3]), atoi(row[4]), row[5], row[6]);
			user.printDetails();
		}
		mysql_free_result(res);
	}
	
	// To login the existing user
	struct user_details loginUser(MYSQL *con)
	{
		struct user_details user;
		string username, password;
		cout<<"Enter Username: ";
		cin>>username;
		cout<<"Enter Password: ";
		cin>>password;
		stringstream ss;
		ss<<"select * from user_details where username = '"<<username<<"' and password = '"<<password<<"';";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row;
		res = mysqlExecuteQuery(con, str.c_str());
		if((row = mysql_fetch_row(res)) != NULL)
		{
			user.setDetails(row[0], row[1], row[2], atoi(row[3]), atoi(row[4]), row[5], row[6]);
			cout<<"Verification Successful..."<<endl;
			login = true;
		}
		else
		{
			cout<<"Verification Failed..."<<endl;
			cout<<"con err: "<<mysql_errno(con)<<endl;
		}
		mysql_free_result(res);
		return user;
	}
	
	// To register the new user
	void registerUser(MYSQL *con)
	{
		struct user_details user;
		user.getDetails();
		user.capitalize(user.first_name);
		user.capitalize(user.last_name);
		if(uniquePass(con, user.password))
		{
			stringstream ss;
			string str;		
			ss<<"insert into user_details(first_name, last_name, gender, balance, username, password) values('"<<user.first_name<<"','"<<user.last_name<<"','"<<user.gender<<"',"<<user.balance<<",'"<<user.username<<"','"<<user.password<<"');";
			str = ss.str();
			system("cls");
			if(!(mysql_query(con, str.c_str())))
			{
				cout<<"User Registeration Successful."<<endl;
			}
			else
			{
				cout<<"User Registeration Failed."<<endl;
				cout<<"con err: "<<mysql_errno(con)<<endl;
			}
		}
		else
		{
			cout<<"Enter a unique password!!!"<<endl;
		}
	}
	
	// To change user's password
	void changePassword(MYSQL *con, struct user_details user)
	{
		string newpass;
		cout<<"Enter new password: ";
		cin>>newpass;
		stringstream ss;
		ss<<"update user_details set password = '"<<newpass<<"' where username = '"<<user.username<<"' and password = '"<<user.password<<"';";
		string str = ss.str();
		if(!(mysql_query(con, str.c_str())))
		{
			cout<<"Password Change Successful."<<endl;
		}
		else
		{
			cout<<"Password Change Failed."<<endl;
			cout<<"con err: "<<mysql_errno(con)<<endl;
		}
	}
	
	// To check if the password is unique
	bool uniquePass(MYSQL *con, string pass)
	{
		stringstream ss;
		ss<<"select * from user_details where password = '"<<pass<<"';";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row;
		bool unique = true;
		res = mysqlExecuteQuery(con, str.c_str());
		if((row = mysql_fetch_row(res)) != NULL)
		{
			unique = false;
		}
		return unique;
	}
	
	// To show the available balance in a bank account
	void showBalance(MYSQL *con, struct user_details user)
	{
		cout<<"Available Balance = "<<user.balance<<endl;
	}
	
	// To withdraw money from a bank account
	struct user_details withdraw(MYSQL *con, struct user_details user)
	{
		int amount;
		cout<<"Enter amount = ";
		cin>>amount;
		user.balance = user.balance - amount;
		stringstream ss;
		ss<<"update user_details set balance = '"<<user.balance<<"' where username = '"<<user.username<<"' and password = '"<<user.password<<"';";
		string str = ss.str();
		if(!(mysql_query(con, str.c_str())))
		{
			cout<<"Withdraw Successful."<<endl;
		}
		else
		{
			cout<<"Withdraw Failed."<<endl;
			cout<<"con err: "<<mysql_errno(con)<<endl;
		}
		return user;
	}
	
	// To deposit money to a bank account
	struct user_details deposit(MYSQL *con, struct user_details user)
	{
		int amount;
		cout<<"Enter amount = ";
		cin>>amount;
		user.balance = user.balance + amount;
		stringstream ss;
		ss<<"update user_details set balance = '"<<user.balance<<"' where username = '"<<user.username<<"' and password = '"<<user.password<<"';";
		string str = ss.str();
		if(!(mysql_query(con, str.c_str())))
		{
			cout<<"Deposit Successful."<<endl;
		}
		else
		{
			cout<<"Deposit Failed."<<endl;
			cout<<"con err: "<<mysql_errno(con)<<endl;
		}
		return user;
	}
	
	// To get all records from the table for a particular user
	void getDropBoxRecords(MYSQL *con, int acc)
	{
		struct dropbox dbox;
		stringstream ss;
		ss<<"select * from dropbox where receiver_acc_no = "<<acc<<";";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row; 
		res = mysqlExecuteQuery(con, str.c_str());
		while((row = mysql_fetch_row(res)) != NULL)
		{
			dbox.setDetails(row[0], atoi(row[1]), atoi(row[2]), atoi(row[3]));
			dbox.printDetailsAll();
		}
		mysql_free_result(res);
	}
	
	// To get all records from the table
	void getAllDropBoxRecords(MYSQL *con)
	{
		struct dropbox dbox;
		stringstream ss;
		ss<<"select * from dropbox;";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row; 
		res = mysqlExecuteQuery(con, str.c_str());
		while((row = mysql_fetch_row(res)) != NULL)
		{
			dbox.setDetails(row[0], atoi(row[1]), atoi(row[2]), atoi(row[3]));
			dbox.printDetailsAll();
		}
		mysql_free_result(res);
	}
	
	// To check if the user exists in the database or not
	bool userExists(MYSQL *con, int acc)
	{
		stringstream ss;
		ss<<"select * from user_details where account_no = "<<acc<<";";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row;
		bool exists = false;
		res = mysqlExecuteQuery(con, str.c_str());
		if((row = mysql_fetch_row(res)) != NULL)
		{
			exists = true;
		}
		mysql_free_result(res);
		return exists;
	}
	
	// To check if the cheque exists in the dropbox or not
	bool chequeExists(MYSQL *con, struct dropbox dbox)
	{
		stringstream ss;
		ss<<"select * from dropbox where sender_bank_name = '"<<dbox.sender_bank_name<<"' and sender_acc_no = "<<dbox.sender_acc_no<<" and receiver_acc_no = "<<dbox.receiver_acc_no<<" and amount = "<<dbox.amount<<";";
		string str = ss.str();
		MYSQL_RES *res;
		MYSQL_ROW row;
		bool exists = false;
		res = mysqlExecuteQuery(con, str.c_str());
		if((row = mysql_fetch_row(res)) != NULL)
		{
			exists = true;
		}
		mysql_free_result(res);
		return exists;
	}
	
	// To send and reflect cheque to the designated bank
	void sendCheque(MYSQL *con, struct dropbox dbox)
	{
		stringstream ss;
		ss<<"insert into dropbox values('"<<dbox.sender_bank_name<<"',"<<dbox.sender_acc_no<<","<<dbox.receiver_acc_no<<","<<dbox.amount<<");";
		string str = ss.str();
		if(!(mysql_query(con, str.c_str())))
		{
			cout<<"Cheque Sent Successfully."<<endl;
		}
		else
		{
			cout<<"Cheque Failed."<<endl;
			cout<<"con err: "<<mysql_errno(con)<<endl;
		}
	}
	
	// To claim the cheque from the dropbox
	struct user_details claimCheque(MYSQL *con, struct user_details user, struct dropbox dbox, MYSQL *conn)
	{
		int balance;
		stringstream ss1;
		ss1<<"select balance from user_details where account_no = "<<dbox.sender_acc_no<<";";
		string str1 = ss1.str();
		MYSQL_RES *res1;
		MYSQL_ROW row;
		res1 = mysqlExecuteQuery(conn, str1.c_str());
		if((row = mysql_fetch_row(res1)) != NULL)
		{
			balance = atoi(row[0]);
		}
		mysql_free_result(res1);
		if(balance < dbox.amount)
		{
			cout<<"Cheque Bounced!"<<endl;
		}
		else
		{
			stringstream ss2;
			ss2<<"update user_details set balance = "<<(balance - dbox.amount)<<" where account_no = "<<dbox.sender_acc_no<<";";
			string str2 = ss2.str();
			if(!(mysql_query(conn, str2.c_str())))
			{
				user.balance = user.balance + dbox.amount;
				stringstream ss3;
				ss3<<"update user_details set balance = "<<user.balance<<" where account_no = "<<user.account_no<<";";
				string str3 = ss3.str();
				if(!(mysql_query(con, str3.c_str())))
				{
					stringstream ss4;
					ss4<<"delete from dropbox where sender_bank_name = '"<<dbox.sender_bank_name<<"' and sender_acc_no = "<<dbox.sender_acc_no<<" and receiver_acc_no = "<<dbox.receiver_acc_no<<" and amount = "<<dbox.amount<<";";
					string str4 = ss4.str();
					if(!(mysql_query(con, str4.c_str())))
					{
						cout<<"Cheque Claimed Successfully."<<endl;
					}
					else
					{
						cout<<"con err: "<<mysql_errno(con)<<endl;
					}
				}
				else
				{
					cout<<"con err: "<<mysql_errno(con)<<endl;
				}
			}
			else
			{
				cout<<"con err: "<<mysql_errno(conn)<<endl;
			}
		}
		return user;
	}
	
	// To run queries on the database
	MYSQL_RES* mysqlExecuteQuery(MYSQL *connection, const char *sqlQuery)
	{
		if(mysql_query(connection, sqlQuery))
		{
			cout<<"MySQL Query Error: "<<mysql_error(connection)<<endl;
			exit(1);
		}
		return mysql_use_result(connection);
	}
};

// To generate connection to the database
MYSQL* setupConnection(struct dbHelper details)
{
	MYSQL *con = mysql_init(0);
	con = mysql_real_connect(con, details.server, details.user, details.password, details.database, 0, NULL, 0);
	if(!con)
	{
		cout<<"Connection Error Number: "<<mysql_errno(con)<<endl;
		exit(1);
	}
	return con;
}

// To clear console screen
void clearScreen()
{
	cout<<"Press any key to continue..."<<endl;
	getch();
	system("cls");
}

int main()
{	
	MYSQL *con;
	Bank b;
	struct user_details user;
	struct dbHelper mysqlD, db;
	struct dropbox dbox;
	int option, dOption;
	bool loginScreen;
	
	while(1)
	{
		b.displayBanks();
		cin>>option;
		if(option == 0)
		{
			system("cls");
			cout<<"Program terminated.....";
			exit(0);
		}
		if(option > 5)
		{
			system("cls");
			cout<<"Invalid option!!!"<<endl;
			clearScreen();
			continue;
		}
		system("cls");
		loginScreen = true;
		mysqlD.setDetails(b.getConstValue(b.getBanks(), option));
		b.setDetails(b.getValue(b.getBanks(), option), b.getValue(b.getBankAddress(), option), b.getValue(b.getBankIfsc(), option));
		while(loginScreen)
		{
			b.displayLogin();
			cin>>option;
			system("cls");
			con = setupConnection(mysqlD);

			
			switch(option)
			{
				case 1:{
					user = mysqlD.loginUser(con);
					clearScreen();
					while(login)
					{
						b.displayFunctions();
						cin>>option;
						system("cls");
						switch(option)
						{
							case 1:{
								mysqlD.showBalance(con, user);
								clearScreen();
								break;
							}
							case 2:{
								user = mysqlD.withdraw(con, user);
								clearScreen();
								break;
							}
							case 3:{
								user = mysqlD.deposit(con, user);
								clearScreen();
								break;
							}
							case 4:{
								user.printDetails();
								clearScreen();
								break;
							}
							case 5:{
								mysqlD.changePassword(con, user);
								clearScreen();
								break;
							}
							case 6:{
								b.getDetails();
								clearScreen();
								break;
							}
							case 0:{
								cout<<"Moving to main screen."<<endl;
								clearScreen();
								login = false;
								break;
							}
						}
					}
					break;
				}
				case 2:{
					mysqlD.registerUser(con);
					clearScreen();
					break;
				}
				case 3:{
					user = mysqlD.loginUser(con);
					clearScreen();
					if(login)
					{
						cout<<"Select the bank to which you want to send the Digital Cheque."<<endl<<endl;
						b.displayBanks();
						cin>>dOption;
						if(dOption == 0)
						{
							system("cls");
							continue;
						}
						if(dOption > 5)
						{
							system("cls");
							cout<<"Invalid option!!!"<<endl;
							clearScreen();
							continue;
						}
						system("cls");
						db.setDetails(b.getConstValue(b.getBanks(), dOption));
						con = NULL;
						con = setupConnection(db);
						cout<<db.database<<endl;
						int acc, amt;
						cout<<"Enter Receiver's account number: ";
						cin>>acc;
						if(db.userExists(con, acc))
						{
							cout<<"Enter Amount: ";
							cin>>amt;
							if(amt > user.balance)
							{
								cout<<"Insufficient Balance."<<endl;
								clearScreen();
								continue;
							}
							dbox.setDetails(b.getName(), user.account_no, acc, amt);
							db.sendCheque(con, dbox);
						}
						else
						{
							cout<<"The Account Number Entered Does Not Exist..."<<endl;
						}
						clearScreen();
					}
					login = false;
					break;
				}
				case 4:{
					user = mysqlD.loginUser(con);
					clearScreen();
					if(login)
					{
						MYSQL *conn;
						string bankName;
						int amt, acc;
						cout<<"Enter Sender's Bank: ";
						cin>>bankName;
						cout<<"Enter Sender's Account Number: ";
						cin>>acc;
						cout<<"Enter Amount: ";
						cin>>amt;
						dbox.setDetails(bankName, acc, user.account_no, amt);
						if(mysqlD.chequeExists(con, dbox))
						{
							db.setDetails(bankName.c_str());
							conn = setupConnection(db);
							user = mysqlD.claimCheque(con, user, dbox, conn);
						}
						else
						{
							cout<<"No Such Cheque Exists In Dropbox."<<endl;
						}
						clearScreen();
					}
					break;
				}
				case 5:{
					user = mysqlD.loginUser(con);
					clearScreen();
					if(login)
					{
						mysqlD.getDropBoxRecords(con, user.account_no);
						cout<<endl;
						clearScreen();
					}
					login = false;
					break;
				}
				case 0:{
					cout<<"Moving to bank select screen."<<endl;
					clearScreen();
					loginScreen = false;
					break;
				}
				default:{
					cout<<"Invalid option!!!"<<endl;
					clearScreen();
					break;
				}
			}
		}
	}
	
	mysql_close(con);
	
	return 0;
}
