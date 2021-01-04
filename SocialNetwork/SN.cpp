#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "stdafx.h"
#include "tinyxml2.h"
#include "SN.h"
#include "User.h"
#include "Friend.h"
#include "Post.h"
#include "Comment.h"

using namespace std;
using namespace tinyxml2;


SN::SN()
{
}

void SN::GetAllUsers()
{
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("users.xml");
	XMLElement* pSocialNetwork = oXmlDocument.FirstChildElement("root");
	XMLElement* pUsers = pSocialNetwork->FirstChildElement("users");
	XMLElement* pUser;
	for (pUser = pUsers->FirstChildElement("user"); pUser != NULL; pUser = pUser->NextSiblingElement())
	{
		int nId = stoi(pUser->Attribute("id"));
		string sName = pUser->Attribute("name");
		string sSurname = pUser->Attribute("surname");
		string sUsername = pUser->Attribute("username");
		string sPassword = pUser->Attribute("password");
		m_vUsers.push_back(new User(nId, sName, sSurname, sUsername, sPassword));
	}
	XMLElement* pFriends = pSocialNetwork->FirstChildElement("friends");
	XMLElement* pFriend;
	for (pFriend = pFriends->FirstChildElement("friend"); pFriend != NULL; pFriend = pFriend->NextSiblingElement())
	{
		int nMyId = stoi(pFriend->Attribute("my_id"));
		int nFriendsId = stoi(pFriend->Attribute("friends_id"));
		m_vFriends.push_back(new Friend(nMyId, nFriendsId));
	}

}

void SN::GetAllPosts()
{
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("posts.xml");
	XMLElement* pSocialNetwork = oXmlDocument.FirstChildElement("root");
	XMLElement* pPosts = pSocialNetwork->FirstChildElement("posts");
	XMLElement* pPost;
	for (pPost = pPosts->FirstChildElement("post"); pPost != NULL; pPost = pPost->NextSiblingElement())
	{
		int nId = stoi(pPost->Attribute("id"));
		int nUserId = stoi(pPost->Attribute("user_id"));
		string sText = pPost->Attribute("text");
		string sDate = pPost->Attribute("date");
		m_vPosts.push_back(new Post(nId, nUserId, sText, sDate));
	}
	XMLElement* pComments = pSocialNetwork->FirstChildElement("comments");
	XMLElement* pComment;
	for (pComment = pComments->FirstChildElement("comment"); pComment != NULL; pComment = pComment->NextSiblingElement())
	{
		string sText = pComment->Attribute("text");
		string sName = pComment->Attribute("name");
		string sSurname = pComment->Attribute("surname");
		int nPostId = stoi(pComment->Attribute("post_id"));
		m_vComments.push_back(new Comment(sText, sName, sSurname, nPostId));
	}
}

void SN::LogIn()
{
	int id;
	string username, password;
	bool isLoggedIn = false;
	cout << "Enter username:" << endl;
	cin >> username;
	cout << "Enter password:" << endl;
	cin >> password;
	for (int i = 0; i < m_vUsers.size(); i++)
	{
		if (username == m_vUsers[i]->m_sUsername && password == m_vUsers[i]->m_sPassword)
		{
			cout << "Welcome " << m_vUsers[i]->m_sName << " " << m_vUsers[i]->m_sSurname << endl;
			id = m_vUsers[i]->m_nId;
			GetMenu(id);
			isLoggedIn = true;
		}
	}
	if (isLoggedIn == false)
	{
		cout << "Wrong credentials, try again!" << endl;
		LogIn();
	}
stop:
	cout << endl;
}

void SN::GetMenu(int id)
{
	cout << "1 - View my friends posts" << endl;
	cout << "2 - Add a comment to the post" << endl;
	cout << "3 - My posts" << endl;
	cout << "4 - Add post" << endl;
	cout << "5 - Delete post (under construction)" << endl;
	cout << "6 - Follow user (under construction)" << endl;
	cout << "7 - Sign out" << endl;
	int n;
	cin >> n;
	switch (n)
	{
	case 1:
		ShowAllMyFriendsPosts(id);
		GetMenu(id);
		break;
	case 2:
		AddComment(id);
		GetMenu(id);
		break;
	case 3:
		ShowAllMyPosts(id);
		GetMenu(id);
		break;
	case 4:
		AddPost(id);
		GetMenu(id);
		break;
	case 5:
		DeletePost(id);
		GetMenu(id);
		break;
	case 6:
		FollowUser(id);
		GetMenu(id);
		break;
	case 7:
		SignOut(id);
		break;
	default:
		cout << "Wrong number, try again!" << endl;
		GetMenu(id);
		break;
	}
}

void SN::ShowAllMyFriendsPosts(int id)
{
	for (int i = 0; i < m_vFriends.size(); i++)
	{
		if (m_vFriends[i]->m_nMyId == id)
		{
			for (int j = 0; j < m_vUsers.size(); j++)
			{
				if (m_vUsers[j]->m_nId == m_vFriends[i]->m_nFriendsId)
				{
					cout << "POST BY: " << m_vUsers[j]->m_sName << " " << m_vUsers[j]->m_sSurname << endl;
					for (int z = 0; z < m_vPosts.size(); z++)
					{
						if (m_vPosts[z]->m_nUserId == m_vUsers[j]->m_nId)
						{
							cout << "POST ID: " << m_vPosts[z]->m_nId << " USER ID: " << m_vPosts[z]->m_nUserId << " TEXT: " << m_vPosts[z]->m_sText << " DATE: " << m_vPosts[z]->m_sDate << endl;
							for (int y = 0; y < m_vComments.size(); y++)
							{
								if (m_vComments[y]->m_nPostId == m_vPosts[z]->m_nId)
								{
									cout << "COMMENT BY: " << m_vComments[y]->m_sName << " " << m_vComments[y]->m_sSurname << endl;
									cout << "POST ID: " << m_vComments[y]->m_nPostId << " TEXT: " << m_vComments[y]->m_sText << endl;
								}
							}
						}
					}
				}
			}
		}
		cout << endl;
	}
}

void SN::AddComment(int id)
{
	int nPostId;
	string sText, sName, sSurname;
	bool isValidId = false;
	for (int i = 0; i < m_vUsers.size(); i++)
	{
		if (m_vUsers[i]->m_nId == id)
		{
			sName = m_vUsers[i]->m_sName;
			sSurname = m_vUsers[i]->m_sSurname;
		}
	}
	cout << "Enter the post id you want to comment: " << endl;
	cin >> nPostId;
	for (int i = 0; i < m_vPosts.size(); i++)
	{
		if (m_vPosts[i]->m_nId == nPostId)
		{
			cout << "Enter the comment: " << endl;
			cin >> sText;
			XMLDocument oXmlDocument;
			oXmlDocument.LoadFile("posts.xml");
			XMLElement* pSocialNetwork = oXmlDocument.FirstChildElement("root");
			XMLElement* pComments = pSocialNetwork->FirstChildElement("comments");
			XMLElement* pComment = oXmlDocument.NewElement("comment");
			pComment->SetAttribute("text", (sText).c_str());
			pComment->SetAttribute("name", (sName).c_str());
			pComment->SetAttribute("surname", (sSurname).c_str());
			pComment->SetAttribute("post_id", (nPostId));
			pComments->LinkEndChild(pComment);
			oXmlDocument.SaveFile("posts.xml");
			m_vComments.push_back(new Comment(sText, sName, sSurname, nPostId));
			cout << "Success, comment added!" << endl;
			isValidId = true;
		}
	}
	if (isValidId == false)
		cout << "Post id doesn't exist!" << endl;
}

void SN::ShowAllMyPosts(int id)
{
	for (int i = 0; i < m_vPosts.size(); i++)
	{
		if (m_vPosts[i]->m_nUserId == id)
		{
			cout << "POST ID: " << m_vPosts[i]->m_nId << " USER ID: " << m_vPosts[i]->m_nUserId << " TEXT: " << m_vPosts[i]->m_sText << " DATE: " << m_vPosts[i]->m_sDate << endl;
			for (int j = 0; j < m_vComments.size(); j++)
			{
				if (m_vComments[j]->m_nPostId == m_vPosts[i]->m_nId)
				{
					cout << "COMMENT BY " << m_vComments[j]->m_sName << " " << m_vComments[j]->m_sSurname << endl;
					cout << "POST ID: " << m_vComments[j]->m_nPostId << " TEXT: " << m_vComments[j]->m_sText << endl;
				}
			}
			cout << endl;
		}
	}
}

void SN::AddPost(int id)
{
	string sText;
	cout << "Insert post text: " << endl;
	cin >> sText;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("posts.xml");
	XMLElement* pSocialNetwork = oXmlDocument.FirstChildElement("root");
	XMLElement* pPosts = pSocialNetwork->FirstChildElement("posts");
	XMLElement* pPost = oXmlDocument.NewElement("post");
	pPost->SetAttribute("id", (m_vPosts.size() + 1));
	pPost->SetAttribute("user_id", (id));
	pPost->SetAttribute("text", (sText).c_str());
	char s[80];
	time_t t = time(0);
	strftime(s, 80, "%d/%m/%Y", localtime(&t));
	pPost->SetAttribute("date", (s));
	pPosts->LinkEndChild(pPost);
	oXmlDocument.SaveFile("posts.xml");
	m_vPosts.push_back(new Post(m_vPosts.size() + 1, id, sText, s));
	cout << "Success, post added!" << endl;
}

void SN::DeletePost(int id)
{
}

void SN::FollowUser(int id)
{
}

int SN::SignOut(int id)
{
	return 0;
}

SN::~SN()
{
}