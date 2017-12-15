/**
	@file login.cpp
	
	@brief This is the implementation for Excersise number 1 for this project (project 8)
	
	@author Pedram Safaei
	
	@version VERSION 1.0
	
	@date 11/07/2017
	
	@bug no known bugs, it was tested multiple times using online compilers, G++ and GCC in Linux and NoMachine, and it has passed the test cases on the submit website. 

*/

#include "HashTable.cpp"
#include <iostream>
#include <fstream>


class TestData 
{
  public:
  
    TestData();
	
    void setKey(const string& newKey);
	void setPwd(const string& newPwd);
	
    std::string getKey() const;
    std::string getPwd() const;
	
    static unsigned int hash(const string& str);

  private:
  
    std::string key; 
    std::string pwd; 
    static int count;
};

int TestData::count = 0;

/**
	@brief default constructor
	
	@param none
	
	@return none
*/
TestData::TestData()
{
	
}

/**
	@brief setKey, sets the username
	
	@param newkey, which is just the username
	
	@return none
*/
void TestData::setKey(const string& newKey) 
{
    key = newKey;
}

/**
	@brief setPwd, which sets the password
	
	@param newPwd, which is just he password
	
	@return none
*/
void TestData::setPwd(const string& newPwd) 
{
	pwd = newPwd;
}
/**
	@brief getKey, it is a getter for the key or username
	
	@param none
	
	@return returns the key or the username
*/
std::string TestData::getKey() const 
{
    return key;
}

/**
	@brief getPwd, it is a getter for the PWd oor password
	
	@param none
	
	@return returns the password
*/
std::string TestData::getPwd() const 
{
    return pwd;
}

/**
	@brief calculates the size 
	
	@param string
	
	@return unsigned int, whatever the size of the string is (ascii table value of each char)
*/
unsigned int TestData::hash(const string& str) 
{
    unsigned int val = 0;

    for (int i = 0; i < str.length(); ++i) 
	{
		val += str[i];
    }

    return val;
	
}



int main()
{
	
	HashTable<TestData, string> table(8);
	
	std::ifstream passwordFile("password.dat");
	
	TestData data;
	std::string tmp;
	
	while(passwordFile >> tmp)
	{
		
		data.setKey(tmp);
		passwordFile >> tmp;
		data.setPwd(tmp);
		table.insert(data);
		
	}
	
	table.showStructure();
	
	
	std::cout << "Login: ";
	
	while(std::cin >> tmp)
	{
		
		table.retrieve(tmp, data);
		std::cout << "Password: ";
		std::cin >> tmp;
		
		if(data.getPwd() == tmp)
		{
			std::cout << "Authentication successful";
		}
		
		else
		{
			std::cout << "Authentication failure";
		}
		
		std::cout << std::endl << "Login: ";
		
	}
}




































