#pragma once

class Component;
class Link;

class Output
{
public:
	Output(Component* component, Link* link);
	~Output();
	bool getPowered();
	void setPowered(bool state);
	Component* getComponent();
	Link* getLink();
private:
	Component* component;
	Link* link;
	bool powered;
};

