#include "psql_admin.h"

// /////////////////////////////
// ADMIN FUNCTIONS
// /////////////////////////////

void Admin_BookRoom(PSQLconnect* connection, int adminID)
{
    int sessionID;
    int roomID;

    printf("--- Room Booking ---\n");

    printf("Enter PT sessionID to change: ");
    scanf("%d", &sessionID);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter roomID to assign: ");
    scanf("%d", &roomID);
    while ((c = getchar()) != '\n' && c != EOF);

    char sessionIDbuff[10];
    char roomIDbuff[10];

    snprintf(sessionIDbuff, sizeof(sessionIDbuff), "%d", sessionID);
    snprintf(roomIDbuff, sizeof(roomIDbuff), "%d", roomID);

    const char* params[2] =
    {
        sessionIDbuff,
        roomIDbuff
    };

    const char* getSessionTimeQ =
    "SELECT sessionTime FROM ptSession WHERE sessionID = $1;";

    PGresult* result = PSQL_ExecuteParams(connection, getSessionTimeQ, 1, params);

    if (PQntuples(result) == 0)
    {
        printf("No such PT session\n");
        PSQL_ClearResult(result);
        return;
    }

    char sessionTime[50];
    snprintf(sessionTime, sizeof(sessionTime), "%s", PQgetvalue(result, 0, 0));

    PSQL_ClearResult(result);

    const char* checkRoomQ =
    "SELECT 1 FROM ptSession "
    "WHERE roomID = $2 AND sessionTime = $1;";

    const char* checkParams[2] =
    {
        sessionTime,
        roomIDbuff
    };

    result = PSQL_ExecuteParams(connection, checkRoomQ, 2, checkParams);

    if (PQntuples(result) > 0)
    {
        printf("Room is already booked for that time\n");
        PSQL_ClearResult(result);
        return;
    }

    PSQL_ClearResult(result);

    const char* updateQ =
    "UPDATE ptSession SET roomID = $2 WHERE sessionID = $1";

    result = PSQL_ExecuteParams(connection, updateQ, 2, params);

    if (result != NULL)
    {
        printf("Room successfully assigned\n");
    }
    else
    {
        printf("Error assigning room: %s\n", PQerrorMessage(connection->conn));
    }

    PSQL_ClearResult(result);
}

void Admin_EquipmentMaintenanceLog(PSQLconnect* connection, int adminID)
{
    int choice;

    printf("--- Equipment Maintenance Logging ---\n");

    printf("What do you want to do?\n");
    printf("1. Log New Maintenance Issue:\n");
    printf("2. Resolve an issue:\n");

    printf("Choice: ");
    scanf("%d", &choice);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (choice == 1)
    {
        int equipmentID;
        char description[200];

        printf("Enter equipmentID: ");
        scanf("%d", &equipmentID);
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Enter issue with equipment: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0';

        char equipmentIDbuff[10];
        snprintf(equipmentIDbuff, sizeof(equipmentIDbuff), "%d", equipmentID);

        const char* params[2] =
        {
            equipmentIDbuff,
            description
        };

        const char* insertQ =
        "INSERT INTO maintenanceRecord(equipmentID, issueDescription) "
        "VALUES ($1, $2);";

        PGresult* result = PSQL_ExecuteParams(connection, insertQ, 2, params);

        if (result != NULL)
        {
            printf("Maintenance issue logged\n");
        }
        else
        {
            printf("Error logging the issue: %s", PQerrorMessage(connection->conn));
        }

        PSQL_ClearResult(result);

    }
    else if (choice == 2)
    {
        int recordID;

        printf("Enter recordID to resolve: ");
        scanf("%d", &recordID);
        while ((c = getchar()) != '\n' && c != EOF);

        char recordIDbuff[10];
        snprintf(recordIDbuff, sizeof(recordIDbuff), "%d", recordID);

        const char* params[1] =
        {
            recordIDbuff
        };

        const char* updateQ =
        "UPDATE maintenanceRecord SET status = 'closed' "
        "WHERE recordID = $1 AND status = 'open';";

        PGresult* result = PSQL_ExecuteParams(connection, updateQ, 1, params);

        if (result != NULL)
        {
            if (strcmp(PQcmdTuples(result), "0") == 0)
            {
                printf("No open issues found with recordID: %d", recordID);
            }
            else
            {
                printf("Maintenance issue resolved\n");
            }
        }
        else
        {
            printf("Error updating maintenance record: %s\n", PQerrorMessage(connection->conn));
        }

        PSQL_ClearResult(result);

    }
    else
    {
        printf("Invalid choice\n");
    }
}

// /////////////////////////////
// 
// /////////////////////////////