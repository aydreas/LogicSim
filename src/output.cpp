#include "output.h"
#include "link.h"
#include "input.h"
#include "board.h"
#include "component.h"

Output::Output(Component* component, Link* link)
{
	this->component = component;
	this->link = link;
	this->powered = false;
}

Output::~Output()
{
}

bool Output::getPowered()
{
	return powered;
}

void Output::setPowered(bool state) {
	if (state != powered) {
		powered = state;

		for (int i = 0; i < link->inputCount; i++)
			link->board->writeBuffer[link->inputs[i]->getComponent()->componentIndex] = true;
	}
}

Component* Output::getComponent()
{
	return component;
}

Link* Output::getLink()
{
	return link;
}