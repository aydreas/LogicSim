#pragma once

class Component;
class Link;

class Input
{
public:
	Input(Component* component, Link* link);
	~Input();
	bool getPowered();
	Component* getComponent();
	Link* getLink();
private:
	Component* component;
	Link* link;
};

