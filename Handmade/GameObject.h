#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <utility>
#include "Vector.h"




class GameObject 
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}
	
public:

	bool IsAlive() const;
	bool IsActive() const;
	bool IsVisible() const;

	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);

public:

	float GetAngle() const;
	int GetPriority() const;

	const std::string& GetTag() const;
	const Vector<int>& GetPosition() const;
	const Vector<int>& GetDimension() const;

	void SetPosition(int x, int y);
	void SetDimension(int x, int y);
	void SetTag(const std::string& tag);

public:

	virtual void Update(int deltaTime) = 0;
	virtual bool Draw() = 0;

protected:

	float m_angle;
	int m_priority;
	
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;

	std::string m_tag;
	Vector<int> m_position;
	Vector<int> m_dimension;

};

#endif