#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Friend.h"
#include "Post.h"
#include "Comment.h"
using namespace std;
class SN
{
public:
	vector<User*> m_vUsers;
	vector<Friend*> m_vFriends;
	vector<Post*> m_vPosts;
	vector<Comment*> m_vComments;

	void GetAllUsers();
	void GetAllPosts();
	void LogIn();

	void GetMenu(int id);
	void ShowAllMyFriendsPosts(int id);
	void AddComment(int id);
	void ShowAllMyPosts(int id);
	void AddPost(int id);
	void DeletePost(int id);
	void FollowUser(int id);
	int SignOut(int id);

	SN();
	~SN();
};