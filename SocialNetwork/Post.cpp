#include "stdafx.h"
#include "Post.h"

Post::Post(int id, int userId, string text, string date)
{
	m_nId = id;
	m_nUserId = userId;
	m_sText = text;
	m_sDate = date;
}

Post::~Post()
{
}