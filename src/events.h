#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <functional>

namespace Events
{
	// Base class for emitter.
	class Emitter
	{
	public:
		virtual ~Emitter() {}
	};

	// Base class for arguments.
	class EventArgs
	{
	public:
		virtual ~EventArgs() {}
	};

	template <typename TEventArgs = EventArgs>
	class EventHandler : private std::function < void(Emitter* emitter, TEventArgs&) >
	{
	public:
		template <typename F>
		EventHandler(const F& f) : std::function<void(Emitter*, TEventArgs&)>(f) {}
	public:
		void operator ()(Emitter* emitter, TEventArgs& args) { return std::function<void(Emitter*, TEventArgs&)>::operator()(emitter, args); }
	};

	template <typename TEventArgs = EventArgs>
	class Event
	{
	public:
		// Subscribe to events.
		void operator +=(EventHandler<TEventArgs>* handler)
		{
			_Handlers.push_back(handler);
		}

		// Unsubscribe from events.
		void operator -=(EventHandler<TEventArgs>* handler)
		{
			// Find a handler that points to the same target and remove it.
			auto it = std::find_if(_Handlers.begin(), _Handlers.end(), [handler](EventHandler<TEventArgs>* other) {
				return other == handler;
			});
			if (it != _Handlers.end())
				_Handlers.erase(it);
		}

		// Emit an event.
		void emit(Emitter* emitter, TEventArgs&& args) // For passing an l or rvalue reference.
		{
			// Call each handler with args.
			std::for_each(_Handlers.begin(), _Handlers.end(), [emitter, &args](EventHandler<TEventArgs>* h) {
				(*h)(emitter, args);
			});
		}

	protected:
		std::vector<EventHandler<TEventArgs>*> _Handlers;
	};
}