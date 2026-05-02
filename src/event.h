#ifndef EVENTS_H
#define EVENTS_H

#include <stddef.h>
#include <time.h>

#define EVENT_CITY_REGION_SIZE 64

typedef struct Event Event;

typedef enum EventError EventError;

typedef enum EventType EventType;

typedef enum EventSeverity EventSeverity;

typedef enum EventStatus EventStatus;

enum EventError
{
    EVENT_OK,
    EVENT_NULL_POINTER_ARGUMENT
};

enum EventType
{
    EVENTTYPE_TRAFFIC_ACCIDENT,
    EVENTTYPE_TRAFFIC_LIGHT_MALFUNCTION,
    EVENTTYPE_POWER_OUTAGE,
    EVENTTYPE_FLOOD,
    EVENTTYPE_WILDFIRE
};

enum EventSeverity
{
    EVENTSEVERITY_1 = 1,
    EVENTSEVERITY_2 = 2,
    EVENTSEVERITY_3 = 3,
    EVENTSEVERITY_4 = 4,
    EVENTSEVERITY_5 = 5,
};

enum EventStatus
{
    EVENT_STATUS_ACTIVE,
    EVENT_STATUS_RESOLVED
};

struct Event
{
    size_t id;
    EventType type;
    EventSeverity severity;
    time_t timestamp;
    char city_region[EVENT_CITY_REGION_SIZE];
    EventStatus status;
};

Event *event_new(size_t id, EventType type, EventSeverity severity, time_t timestamp, char *city_region, EventStatus status);
void event_free(Event *event);

EventError event_set_type(Event *event, EventType type);
EventError event_set_severity(Event *event, EventSeverity severity);
EventError event_set_datetime(Event *event, time_t timestamp);
EventError event_set_cityregion(Event *event, char *city_region);
EventError event_set_status(Event *event, EventStatus status);

#endif
