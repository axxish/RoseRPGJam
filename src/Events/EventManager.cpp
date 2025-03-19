#include "EventManager.h"

EventManager& EventManager::Instance()
{
    static EventManager instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

void EventManager::Subscribe(EventType type, EventCallback listener)
{
    listeners[type].push_back(listener);
}

void EventManager::Publish(std::shared_ptr<Event> event)
{
    auto &eventListeners = listeners[event->type];
    for (const auto &listener : eventListeners)
    {
        listener(event); // Call each listener with the event data
    }
}