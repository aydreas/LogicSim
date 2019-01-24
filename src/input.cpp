#include "input.h"
#include "component.h"
#include "link.h"

Input::Input(Component* component, Link* link)
{
	this->component = component;
	this->link = link;
}

Input::~Input()
{
}

bool Input::getPowered()
{
	return link->getPowered();
}

Component* Input::getComponent()
{
	return component;
}

Link* Input::getLink()
{
	return link;
}
