#pragma once
#include "Event.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

class EventManager
{
  public:
    static EventManager& Instance();
    typedef std::function<void(std::shared_ptr<Event>)> EventCallback;

    // Subscribe a listener to a specific event type
    void Subscribe(EventType type, EventCallback listener);
    // Publish an event to all listeners of its type
    void Publish(std::shared_ptr<Event> event);

  private:
    EventManager(){};                                               // Private constructor to enforce singleton
    EventManager(const EventManager &) = delete;            // Delete copy constructor
    EventManager &operator=(const EventManager &) = delete; // Delete assignment operator
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};