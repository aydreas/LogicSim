#include <iostream>
#include <thread>
#include <chrono>
#include "board.h"
#include "component.h"
#include "and.h"
#include "link.h"
#include "clk.h"

int main() {
	const int componentCount = 1000;

	Link** links = new Link*[3]
	{
		new Link(),
		new Link(),
		new Link()
	};

	Component** components = new Component*[componentCount];

	components[0] = new CLK(new Link*[1]{ links[1] }, new Link*[1]{ links[0] });

	for (int i = 1; i < componentCount; i++) {
		components[i] = new AND(new Link*[2]{ links[0], links[1] }, new Link*[1]{ links[2] });
	}

	Board::init(components, componentCount, 8);

	Board::start();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	for (int i = 0; i < 10; i++) {
		std::cout << "Wird gestoppt.." << std::endl;
		Board::stop();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Wird gestartet.." << std::endl;
		Board::start();
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	std::this_thread::sleep_for(std::chrono::seconds(30));
}
