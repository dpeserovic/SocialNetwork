#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Friend
{
public:
	int m_nMyId;
	int m_nFriendsId;
	Friend(int myId, int friendsId);
	~Friend();
};