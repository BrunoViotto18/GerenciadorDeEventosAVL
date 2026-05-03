#include <stdlib.h>
#include <string.h>
#include "event.h"

Event *event_new(size_t id, EventType type, EventSeverity severity, time_t timestamp, char *city_region, EventStatus status)
{
    Event *event = malloc(sizeof(Event));

    if (event == NULL)
    {
        return NULL;
    }

    event->id = id;
    event->type = type,
    event->severity = severity;
    event->timestamp = timestamp;
    strncpy(event->city_region, city_region, EVENT_CITY_REGION_SIZE);
    event->status = status;

    return event;
}

void event_free(Event *event)
{
    free(event);
}
