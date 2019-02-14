#include "component.h"
#include "input.h"
#include "output.h"
#include "link.h"
#include "board.h"
#include <memory>

Component::Component(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount) :
	board(board),
	inputs(inputs),
	outputs(outputs),
	inputCount(inputCount),
	outputCount(outputCount)
{
	componentIndex = board->getNextComponentIndex();
}

Component::Component(Board* board, Link** inputs, Link** outputs, int inputCount, int outputCount) :
	board(board),
	inputCount(inputCount),
	outputCount(outputCount)
{
	this->inputs = new Input*[inputCount];
	for (int i = 0; i < inputCount; i++) {
		this->inputs[i] = new Input(this, inputs[i]);
	}

	this->outputs = new Output*[outputCount];
	for (int i = 0; i < outputCount; i++) {
		this->outputs[i] = new Output(this, outputs[i]);
	}

	for (int i = 0; i < inputCount; i++) {
		Input** newInputs = new Input*[inputs[i]->inputCount + 1];
		std::memcpy(newInputs, inputs[i]->inputs, inputs[i]->inputCount * sizeof(Input*));
		newInputs[inputs[i]->inputCount] = this->inputs[i];
		delete[] inputs[i]->inputs;
		inputs[i]->inputs = newInputs;
		inputs[i]->inputCount++;
	}

	for (int i = 0; i < outputCount; i++) {
		Output** newOutputs = new Output*[outputs[i]->outputCount + 1];
		std::memcpy(newOutputs, outputs[i]->outputs, outputs[i]->outputCount * sizeof(Output*));
		newOutputs[outputs[i]->outputCount] = this->outputs[i];
		delete[] outputs[i]->outputs;
		outputs[i]->outputs = newOutputs;
		outputs[i]->outputCount++;
	}

	componentIndex = board->getNextComponentIndex();
}

Component::~Component() {
	for (int i = 0; i < inputCount; i++) {
		Input** newInputs = new Input*[inputs[i]->getLink()->inputCount - 1];
		for (int j = 0, k = 0; j < inputs[i]->getLink()->inputCount - 1; j++, k++) {
			if (inputs[i]->getLink()->inputs[k] == inputs[i])
				k++;
			newInputs[j] = inputs[i]->getLink()->inputs[k];
		}
		delete[] inputs[i]->getLink()->inputs;
		inputs[i]->getLink()->inputCount--;
		std::memcpy(newInputs, inputs[i]->getLink()->inputs, inputs[i]->getLink()->inputCount * sizeof(Input*));

		delete inputs[i];
	}
	delete[] inputs;

	for (int i = 0; i < outputCount; i++) {
		Output** newOutputs = new Output*[outputs[i]->getLink()->outputCount - 1];
		for (int j = 0, k = 0; j < outputs[i]->getLink()->outputCount - 1; j++, k++) {
			if (outputs[i]->getLink()->outputs[k] == outputs[i])
				k++;
			newOutputs[j] = outputs[i]->getLink()->outputs[k];
		}
		delete[] outputs[i]->getLink()->outputs;
		outputs[i]->getLink()->outputCount--;
		std::memcpy(newOutputs, outputs[i]->getLink()->outputs, outputs[i]->getLink()->outputCount * sizeof(Output*));

		delete outputs[i];
	}
	delete[] outputs;
}
