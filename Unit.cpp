
#define _WINDOWS

#include "Unit.h"
#include <iostream>
#include "Tools.h"

Unit::Unit(Sprite* sprite, double x, double y, double width, double height)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

double Unit::getCenterX()
{
	return x + getWidth() / 2;
}

double Unit::getCenterY()
{
	return y + height / 2;
}

void Unit::setWidth(double width) {
	this->width = width;
}

double Unit::getWidth()
{
	return width;
}

void Unit::move(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Unit::moveRelative(double xRelative, double yRelative)
{
	this->x += xRelative;
	this->y += yRelative;
}

bool Unit::intersects(Unit* other)
{
		return !(this->x + this->getWidth() - 1 < other->x ||
		this->x > other->x + other->getWidth() - 1 ||
		this->y > other->y + other->height - 1 ||
		this->y + this->height - 1 < other->y
		);
}
Side Unit::collides(Unit* other)
{
	if (linesIntersects(other->getCenterX(), other->getCenterY(), getCenterX(), getCenterY(), x, y, x + getWidth(), y))
	{
		return Side::TOP;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), getCenterX(), getCenterY(), x, y + height, x + getWidth(), y + height))
	{
		return Side::BOTTOM;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), getCenterX(), getCenterY(), x, y, x, y + height))
	{
		return Side::LEFT;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), getCenterX(), getCenterY(), x + getWidth(), y, x + getWidth(), y + height))
	{
		return Side::RIGHT;
	}
}

void Unit::draw()
{
	setSpriteSize(sprite, getWidth(), height);
	drawSprite(sprite, x, y);
}