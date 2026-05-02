#include <stdio.h>
#include <string.h>
#include "avltree.h"
#include "event.h"
#include "terminal.h"

typedef enum
{
    MENU_EXIT = 0,
    MENU_CREATE_EVENT,
    MENU_REMOVE_EVENT,
    MENU_GET_EVENT,
    MENU_GET_SEVERITY_RANGE,
    MENU_GET_REGION_EVENTS,
    MENU_GET_ID_RANGE,
    MENU_UPDATE_STATUS,
    MENU_UPDATE_SEVERITY,
    MENU_DISPLAY_TREE_HEIGHT,
    MENU_DISPLAY_TREE_COUNT,
    MENU_DISPLAY_ACTIVE_COUNT,
    MENU_DISPLAY_TREE_BALANCING_FACTOR,
    MENU_DISPLAY_TREE_ROTATION_COUNT,
} MenuOption;

MenuOption menu();
void create_event(AvlTree *tree);
void remove_event(AvlTree *tree);
void get_event_by_id(AvlTree *tree);
void get_severity_range(AvlTree *tree);
void get_region_events(AvlTree *tree);
void get_id_range(AvlTree *tree);
void update_event_status(AvlTree *tree);
void update_event_severity(AvlTree *tree);
void display_tree_height(AvlTree *tree);
void display_tree_count(AvlTree *tree);
void display_active_event_count(AvlTree *tree);
void display_tree_balancing_factor(AvlTree *tree);
void display_tree_rotation_count(AvlTree *tree);

void display_event(Event *event);
void take_until_new_line(char *str);

const void *get_event_id(const void *value);
int compare_event_ids(const void *value1, const void *value2);
void free_event(void *value);

int main(void)
{
    AvlTree *tree;
    avltree_new(&tree, sizeof(Event *), true, compare_event_ids, get_event_id);

    MenuOption option;
    do
    {
        option = menu();

        clear_terminal();

        switch (option)
        {
        case MENU_CREATE_EVENT:
            create_event(tree);
            break;
        case MENU_REMOVE_EVENT:
            remove_event(tree);
            break;
        case MENU_GET_EVENT:
            get_event_by_id(tree);
            break;

        case MENU_GET_SEVERITY_RANGE:
            get_severity_range(tree);
            break;
        case MENU_GET_REGION_EVENTS:
            get_region_events(tree);
            break;
        case MENU_GET_ID_RANGE:
            get_id_range(tree);
            break;

        case MENU_UPDATE_STATUS:
            update_event_status(tree);
            break;
        case MENU_UPDATE_SEVERITY:
            update_event_severity(tree);
            break;

        case MENU_DISPLAY_TREE_HEIGHT:
            display_tree_height(tree);
            break;
        case MENU_DISPLAY_TREE_COUNT:
            display_tree_count(tree);
            break;
        case MENU_DISPLAY_ACTIVE_COUNT:
            display_active_event_count(tree);
            break;
        case MENU_DISPLAY_TREE_BALANCING_FACTOR:
            display_tree_balancing_factor(tree);
            break;
        case MENU_DISPLAY_TREE_ROTATION_COUNT:
            display_tree_rotation_count(tree);
            break;
        case MENU_EXIT:
            break;
        }

        if (option != MENU_EXIT)
        {
            wait_for_enter();
            clear_terminal();
        }
    } while (option != MENU_EXIT);

    avltree_free(tree, free_event);

    return 0;
}

MenuOption menu()
{
    while (true)
    {
        printf("[Operações Básicas]\n");
        printf("[ 1 ] Criar evento\n");
        printf("[ 2 ] Remover evento\n");
        printf("[ 3 ] Buscar evento\n");

        printf("\n[Consultas Avançadas]\n");
        printf("[ 4 ] Buscar intervalo de severidade\n");
        printf("[ 5 ] Buscar por região\n");
        printf("[ 6 ] Buscar intervalo de IDs\n");

        printf("\n[Operações de Atualização]\n");
        printf("[ 7 ] Alterar status de evento ativo\n");
        printf("[ 8 ] Alterar severidade de evento ativo\n");

        printf("\n[Métricas da Árvore]\n");
        printf("[ 9 ] Altura da árvore\n");
        printf("[ 10 ] Quantidade de nós\n");
        printf("[ 11 ] Número de eventos ativos\n");
        printf("[ 12 ] Fator de balanceamento\n");
        printf("[ 13 ] Quantidade total de rotações\n");

        printf("\n[ 0 ] Sair\n");

        char buffer[32];
        printf("Selecione uma opção: ");
        fgets(buffer, sizeof buffer, stdin);

        int option;
        if (sscanf(buffer, "%d", &option) == 1 && option >= 0 && option <= 13)
        {
            return option;
        }

        clear_terminal();
        printf("Opção inválida, tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    }
}

void create_event(AvlTree *tree)
{
    char buffer[64];

    EventType type;
    while (true)
    {
        printf("[ 1 ] Acidente de Trânsito\n");
        printf("[ 2 ] Falha em semáforo\n");
        printf("[ 3 ] Interrupção de energia\n");
        printf("[ 4 ] Alagamento\n");
        printf("[ 5 ] Incêndio\n");
        printf("Selecione o tipo do evento: ");
        fgets(buffer, sizeof buffer, stdin);
        if (sscanf(buffer, "%d", (int *)&type) == 1 && type >= 1 && type <= 5)
        {
            type--;
            break;
        }

        printf("Tipo de evento inválido! Tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    };

    clear_terminal();

    EventSeverity severity;
    while (true)
    {
        printf("Digite a severidade do evento [1~5]: ");
        fgets(buffer, sizeof buffer, stdin);
        if (sscanf(buffer, "%d", (int *)&severity) == 1 && severity >= 1 && severity <= 5)
        {
            break;
        }

        printf("Severidade inválida! Tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    };

    clear_terminal();

    time_t timestamp;
    while (true)
    {
        int year, month, day, hour, minute, second;
        printf("Digite a data do evento [dd/MM/YYYY HH:mm:ss]: ");
        fgets(buffer, sizeof buffer, stdin);
        if (sscanf(buffer, "%d/%d/%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second) == 6 && year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31 && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
        {
            struct tm tm = {0};

            tm.tm_year = year - 1900;
            tm.tm_mon = month - 1;
            tm.tm_mday = day;
            tm.tm_hour = hour;
            tm.tm_min = minute;
            tm.tm_sec = second;
            tm.tm_isdst = -1;

            timestamp = mktime(&tm);

            if (timestamp != -1)
            {
                break;
            }
        }

        printf("Data e/ou hora inválida! Tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    };

    clear_terminal();

    char city_region[EVENT_CITY_REGION_SIZE] = {0};
    while (true)
    {
        printf("Digite a região da cidade: ");
        fgets(city_region, sizeof city_region, stdin);
        take_until_new_line(city_region);
        if (strlen(city_region) != 0)
        {
            break;
        }

        printf("Região da cidade inválida! Tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    };

    clear_terminal();

    EventStatus status;
    while (true)
    {
        printf("[ 1 ] Ativo\n");
        printf("[ 2 ] Resolvido\n");
        printf("Selecione o status do evento: ");
        fgets(buffer, sizeof buffer, stdin);
        if (sscanf(buffer, "%d", (int *)&status) == 1 && status >= 1 && status <= 2)
        {
            status--;
            break;
        }

        printf("Status inválido! Tente novamente...\n");
        wait_for_enter();
        clear_terminal();
    };

    clear_terminal();

    Event *event = event_new(type, severity, timestamp, city_region, status);

    if (event == NULL)
    {
        printf("Falta de memória para criar evento!\n");
        return;
    }

    AvlTreeStatus add_status = avltree_add(tree, &event);

    if (add_status == AVLTREE_OUT_OF_MEMORY)
    {
        event_free(event);
        printf("Falta de memória para armazenar evento!\n");
        return;
    }

    printf("Evento criado com sucesso!\n");

    display_event(event);
}

void remove_event(AvlTree *tree)
{
    (void)tree;
}

void get_event_by_id(AvlTree *tree)
{
    (void)tree;
}

void get_severity_range(AvlTree *tree)
{
    (void)tree;
}

void get_region_events(AvlTree *tree)
{
    (void)tree;
}

void get_id_range(AvlTree *tree)
{
    (void)tree;
}

void update_event_status(AvlTree *tree)
{
    (void)tree;
}

void update_event_severity(AvlTree *tree)
{
    (void)tree;
}

void display_tree_height(AvlTree *tree)
{
    (void)tree;
}

void display_tree_count(AvlTree *tree)
{
    (void)tree;
}

void display_active_event_count(AvlTree *tree)
{
    (void)tree;
}

void display_tree_balancing_factor(AvlTree *tree)
{
    (void)tree;
}

void display_tree_rotation_count(AvlTree *tree)
{
    (void)tree;
}

void display_event(Event *event)
{
    printf("Id: %ld\n", event->id);

    printf("Tipo: ");
    switch (event->type)
    {
    case EVENTTYPE_TRAFFIC_ACCIDENT:
        printf("Acidente de Trânsito");
        break;
    case EVENTTYPE_TRAFFIC_LIGHT_MALFUNCTION:
        printf("Falhas em Semáforos");
        break;
    case EVENTTYPE_POWER_OUTAGE:
        printf("Iterrupção de Energia");
        break;
    case EVENTTYPE_FLOOD:
        printf("Alagamento");
        break;
    case EVENTTYPE_WILDFIRE:
        printf("Incêndio");
        break;
    }
    printf("\n");

    printf("Severidade: %d\n", event->severity);

    struct tm *tm = localtime(&event->timestamp);
    char buffer[32] = {0};
    strftime(buffer, sizeof buffer, "%d/%m/%Y %H:%M:%S", tm);
    printf("Data/Hora: %s\n", buffer);

    printf("Região: %s\n", event->cityRegion);

    printf("Status: ");
    switch (event->status)
    {
    case EVENT_STATUS_ACTIVE:
        printf("Ativo");
        break;
    case EVENT_STATUS_RESOLVED:
        printf("Resolvido");
        break;
    }
    printf("\n");
}

void take_until_new_line(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

const void *get_event_id(const void *value)
{
    const Event *event = value;

    return &event->id;
}

int compare_event_ids(const void *value1, const void *value2)
{
    const int *key1 = value1;
    const int *key2 = value2;

    if (*key1 > *key2)
    {
        return 1;
    }

    if (*key1 < *key2)
    {
        return -1;
    }

    return 0;
}

void free_event(void *value)
{
    Event *event = value;
    event_free(event);
}
