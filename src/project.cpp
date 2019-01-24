#include <iostream>
#include <thread>
#include <chrono>
#include "board.h"
#include "component.h"
#include "and.h"
#include "link.h"
#include "clk.h"
#include "node.h"

void init(const v8::FunctionCallbackInfo<v8::Value>& args) {
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

	Board::init(components, componentCount, 4);
}

void start(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Board::start();
}

void stop(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Board::stop();
}

void getStatus(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = args.GetIsolate();
	v8::Local<v8::Object> obj = v8::Object::New(isolate);

	obj->Set(v8::String::NewFromUtf8(isolate, "currentSpeed"),
		v8::Number::New(isolate, Board::currentSpeed));

	obj->Set(v8::String::NewFromUtf8(isolate, "currentStatus"),
		v8::Number::New(isolate, Board::getCurrentState()));

	obj->Set(v8::String::NewFromUtf8(isolate, "threadCount"),
		v8::Number::New(isolate, Board::getThreadCount()));

	obj->Set(v8::String::NewFromUtf8(isolate, "componentCount"),
		v8::Number::New(isolate, Board::componentCount));

	obj->Set(v8::String::NewFromUtf8(isolate, "manualClock"),
		v8::Boolean::New(isolate, Board::getManualClock()));

	obj->Set(v8::String::NewFromUtf8(isolate, "tick"),
		v8::Number::New(isolate, Board::getCurrentTick()));

	args.GetReturnValue().Set(obj);
}

void Initialize(v8::Local<v8::Object> exports) {
	NODE_SET_METHOD(exports, "init", init);
	NODE_SET_METHOD(exports, "start", start);
	NODE_SET_METHOD(exports, "stop", stop);
	NODE_SET_METHOD(exports, "getStatus", getStatus);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)