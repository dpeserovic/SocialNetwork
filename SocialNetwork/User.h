#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class User
{
public:
	int m_nId;
	string m_sName;
	string m_sSurname;
	string m_sUsername;
	string m_sPassword;
	User(int id, string name, string surname, string username, string password);
	~User();
};