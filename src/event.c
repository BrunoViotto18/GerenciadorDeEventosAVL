#include <stdlib.h>
#include <string.h>
#include "event.h"

static size_t id = 0;

Event *event_new(EventType type, EventSeverity severity, time_t timestamp, char *cityRegion, EventStatus status)
{
    Event *event = malloc(sizeof(Event));

    if (event == NULL)
    {
        return NULL;
    }

    id++;
    event->id = id;
    event->type = type,
    event->severity = severity;
    event->timestamp = timestamp; // TODO: Check implemenation later
    strncpy(event->cityRegion, cityRegion, EVENT_CITY_REGION_SIZE);
    event->status = status;

    return event;
}

void event_free(Event *event)
{
    // TODO: May need to free cityRegion later
    free(event);
}

EventError event_get_id(const Event *event, size_t *id)
{
    if (event == NULL || id == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    *id = event->id;

    return EVENT_OK;
}

EventError event_set_type(Event *event, EventType type)
{
    if (event == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    event->type = type;

    return EVENT_OK;
}

EventError event_set_severity(Event *event, EventSeverity severity)
{
    if (event == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    event->severity = severity;

    return EVENT_OK;
}

EventError event_set_datetime(Event *event, time_t timestamp)
{
    if (event == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    event->timestamp = timestamp;

    return EVENT_OK;
}

EventError event_set_cityregion(Event *event, char *cityRegion)
{
    if (event == NULL || cityRegion == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    strncpy(event->cityRegion, cityRegion, EVENT_CITY_REGION_SIZE);

    return EVENT_OK;
}

EventError event_set_status(Event *event, EventStatus status)
{
    if (event == NULL)
    {
        return EVENT_NULL_POINTER_ARGUMENT;
    }

    event->status = status;

    return EVENT_OK;
}
