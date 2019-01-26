#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <nan.h>
#include "board.h"
#include "component.h"
#include "and.h"
#include "link.h"
#include "clk.h"
#include "node.h"

const char* v8ToString(v8::Local<v8::Value> str) {
	return *v8::String::Utf8Value(str->ToString());
}

void init(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	if (args.Length() != 1 || !args[0]->IsObject()) {
		Nan::ThrowTypeError("Error: One object expected!");
		return;
	}

	unsigned int componentCount = 0;
	unsigned int linkCount = 0;
	Component** components;
	Link** links;

	v8::Local<v8::Object> obj = args[0]->ToObject();
	if (obj->Get(Nan::New("links").ToLocalChecked())->IsNumber()) {
		linkCount = obj->Get(Nan::New("links").ToLocalChecked())->Int32Value();
		links = new Link*[linkCount];
		for (unsigned int i = 0; i < linkCount; i++) {
			links[i] = new Link();
		}
	}

	if (obj->Get(Nan::New("components").ToLocalChecked())->IsArray()) {
		v8::Local<v8::Array> v8Components = v8::Local<v8::Array>::Cast(obj->Get(Nan::New("components").ToLocalChecked()));

		componentCount = v8Components->Length();
		components = new Component*[componentCount];
		for (unsigned int i = 0; i < componentCount; i++) {
			std::cout << "Processing Component " << i << " of " << componentCount << std::endl;
			v8::Local<v8::Object> v8Component = v8Components->Get(i)->ToObject();

			const char* componentType = v8ToString(v8Component->Get(Nan::New("type").ToLocalChecked()));
			v8::Local<v8::Array> v8ComponentInputs = v8::Local<v8::Array>::Cast(v8Component->Get(Nan::New("inputs").ToLocalChecked()));
			Link** componentInputs = new Link*[v8ComponentInputs->Length()];
			for (unsigned int j = 0; j < v8ComponentInputs->Length(); j++)
				componentInputs[j] = links[v8ComponentInputs->Get(j)->Int32Value()];

			v8::Local<v8::Array> v8ComponentOutputs = v8::Local<v8::Array>::Cast(v8Component->Get(Nan::New("outputs").ToLocalChecked()));
			Link** componentOutputs = new Link*[v8ComponentOutputs->Length()];
			for (unsigned int j = 0; j < v8ComponentOutputs->Length(); j++)
				componentOutputs[j] = links[v8ComponentOutputs->Get(j)->Int32Value()];

			if (componentType == "CLK")
				components[i] = new CLK(componentInputs, componentOutputs, v8Component->Get(Nan::New("CLK_Speed").ToLocalChecked())->Int32Value());
			else if(componentType == "AND")
				components[i] = new AND(componentInputs, componentOutputs);
			else
				Nan::ThrowTypeError((std::string("Error: Component '") + std::string(componentType) + std::string("' (") + std::to_string(i) + std::string(") is of no valid type!")).c_str());
		}
	}


	/*Link** links = new Link*[3]
	{
		new Link(),
		new Link(),
		new Link()
	};

	Component** components = new Component*[componentCount];

	components[0] = new CLK(new Link*[1]{ links[1] }, new Link*[1]{ links[0] });

	for (unsigned int i = 1; i < componentCount; i++) {
		components[i] = new AND(new Link*[2]{ links[0], links[1] }, new Link*[1]{ links[2] });
	}*/

	Board::init(components, componentCount, 1);
}

void start(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	Board::start();
}

void stop(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	Board::stop();
}

void getStatus(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = args.GetIsolate();
	v8::Local<v8::Object> obj = Nan::New<v8::Object>();
	
	obj->Set(Nan::New("currentSpeed").ToLocalChecked(), Nan::New((double)Board::currentSpeed));
	obj->Set(Nan::New("currentStatus").ToLocalChecked(), Nan::New(Board::getCurrentState()));
	obj->Set(Nan::New("threadCount").ToLocalChecked(), Nan::New(Board::getThreadCount()));
	obj->Set(Nan::New("componentCount").ToLocalChecked(), Nan::New((unsigned int)Board::componentCount));
	obj->Set(Nan::New("manualClock").ToLocalChecked(), Nan::New(Board::getManualClock()));
	obj->Set(Nan::New("tick").ToLocalChecked(), Nan::New((double)Board::getCurrentTick()));

	args.GetReturnValue().Set(obj);
}

void Initialize(v8::Local<v8::Object> exports) {
	exports->Set(Nan::New("init").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(init)->GetFunction());
	exports->Set(Nan::New("start").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(start)->GetFunction());
	exports->Set(Nan::New("stop").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(stop)->GetFunction());
	exports->Set(Nan::New("getStatus").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(getStatus)->GetFunction());
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)