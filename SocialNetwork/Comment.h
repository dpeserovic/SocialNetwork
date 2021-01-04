#pragma once
#include <iostream>
#include <string>
using namespace std;
class Comment
{
public:
	string m_sText;
	string m_sName;
	string m_sSurname;
	int m_nPostId;
	Comment(string text, string name, string surname, int postId);
	~Comment();
};