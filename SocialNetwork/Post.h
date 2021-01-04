#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Comment.h"
using namespace std;
class Post
{
public:
	int m_nId;
	int m_nUserId;
	string m_sText;
	string m_sDate;
	Post(int id, int userId, string text, string date);
	~Post();
};