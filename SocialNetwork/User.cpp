#include "stdafx.h"
#include "User.h"

User::User(int id, string name, string surname, string username, string password)
{
	m_nId = id;
	m_sName = name;
	m_sSurname = surname;
	m_sUsername = username;
	m_sPassword = password;
}

User::~User()
{
}