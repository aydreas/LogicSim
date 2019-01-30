#include "input.h"
#include "component.h"
#include "link.h"

Input::Input(Component* component, Link* link) :
	component(component),
	link(link)
{
}

Input::~Input()
{
}

bool Input::getPowered()
{
	return link->powered > 0;
}

Component* Input::getComponent()
{
	return component;
}

Link* Input::getLink()
{
	return link;
}
