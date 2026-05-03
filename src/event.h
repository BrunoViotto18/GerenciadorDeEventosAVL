#ifndef EVENTS_H
#define EVENTS_H

#include <stddef.h>
#include <time.h>

/// @brief Max size for the Event.city_region.
#define EVENT_CITY_REGION_SIZE 64

/// @brief Represents an event.
typedef struct Event Event;

/// @brief Represents an event type.
typedef enum EventType EventType;

/// @brief Represents the severity of the event.
typedef enum EventSeverity EventSeverity;

/// @brief Represents the current status of an event.
typedef enum EventStatus EventStatus;

/// @brief Represents an event type.
enum EventType
{
    /// @brief Represents a traffic accident type of event.
    EVENT_TYPE_TRAFFIC_ACCIDENT,

    /// @brief Represents a traffic light malfunction type of event.
    EVENT_TYPE_TRAFFIC_LIGHT_MALFUNCTION,

    /// @brief Represents a power outage type of event.
    EVENT_TYPE_POWER_OUTAGE,

    /// @brief Represents a flood type of event.
    EVENT_TYPE_FLOOD,

    /// @brief Represents a wildfire type of event.
    EVENT_TYPE_WILDFIRE
};

/// @brief Represents the severity of the event.
enum EventSeverity
{
    /// @brief Represents a minimal severity.
    EVENT_SEVERITY_MINIMAL = 1,

    /// @brief Represents a low severity.
    EVENT_SEVERITY_LOW = 2,

    /// @brief Represents a medium severity.
    EVENT_SEVERITY_MEDIUM = 3,

    /// @brief Represents a high severity.
    EVENT_SEVERITY_HIGH = 4,

    /// @brief Represents a critical severity, action must be taken immediately.
    EVENT_SEVERITY_CRITICAL = 5,
};

/// @brief Represents the current status of an event.
enum EventStatus
{
    /// @brief The event is still active.
    EVENT_STATUS_ACTIVE,

    /// @brief The event was resolved.
    EVENT_STATUS_RESOLVED
};

/// @brief Represents an event.
struct Event
{
    /// @brief The event id.
    size_t id;

    /// @brief The event type.
    EventType type;

    /// @brief The current severity of the event.
    EventSeverity severity;

    /// @brief The event timestamp data.
    time_t timestamp;

    /// @brief The city region in which the event takes place.
    char city_region[EVENT_CITY_REGION_SIZE];

    /// @brief The current status of the event.
    EventStatus status;
};

/// @brief Creates a new event.
/// @param id The event id.
/// @param type The event type.
/// @param severity The severity of the event.
/// @param timestamp The timestamp of the event.
/// @param city_region The city region in which the event takes place.
/// @param status The event status.
/// @return Returns the created event, or NULL if the allocation failed.
Event *event_new(size_t id, EventType type, EventSeverity severity, time_t timestamp, char *city_region, EventStatus status);

/// @brief Frees an event.
/// @param event The event to be freed.
void event_free(Event *event);

#endif
