#include "stdafx.h"
#include "Comment.h"

Comment::Comment(string text, string name, string surname, int postId)
{
	m_sText = text;
	m_sName = name;
	m_sSurname = surname;
	m_nPostId = postId;
}

Comment::~Comment()
{
}