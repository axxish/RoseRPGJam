#pragma once

enum class EventType
{
    Error = 0,
    EntityMove,
    PlayerMove,
    EntityAttack,
    InventoryOpen
};

struct Event
{
    EventType type;

    Event(EventType type) : type(type)
    {
    }
};

struct PlayerMovedEvent : Event
{
    PlayerMovedEvent() : Event(EventType::PlayerMove)
    {
    }
};