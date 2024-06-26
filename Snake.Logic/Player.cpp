#include "pch.h"
#include "Player.h"

Player::Player()
{
	head = { 0, 10 };
	direction = { 1, 0 };
	length = 5;
	removed = { -1, -1 };
}

Player::Player(int hx, int hy, int dx, int dy, int l)
{
	head = { hx, hy };
	direction = { dx, dy };
	length = l;
	removed = { -1, -1 };
}

point Player::Head()
{
	return head;
}

point Player::Direction()
{
	return direction;
}

void Player::setDirection(point d)
{
	if ((d * -1) != lastDirection)
		direction = d;
}

int Player::Length()
{
	return length;
}

void Player::setLength(int l)
{
	length = l;
}

void Player::setLocation(int x, int y)
{
	head = { x, y };
}

std::vector<point> Player::TailSegments()
{
	return segments;
}

void Player::setTailSegments(std::vector<point> s)
{
	segments = s;
}

point Player::TailRemoved()
{
	return removed;
}

void Player::Step()
{
	removed = { -1, -1 };
	segments.push_back(head);
	if (segments.size() > length) {
		removed = segments[0];
		segments.erase(segments.begin() + 0);
	}
	lastDirection = direction;
	head = head + direction;
}

void Player::AteFood()
{
	length++;
}


