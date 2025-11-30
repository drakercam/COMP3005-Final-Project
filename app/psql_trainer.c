#include "psql_trainer.h"

// /////////////////////////////
// TRAINER FUNCTIONS
// /////////////////////////////

void Trainer_SetAvailability(PSQLconnect* connection, int trainerID)
{
    char startTime[50];
    char endTime[50];

    printf("--- Set Trainer Availability ---\n");

    printf("Enter start time [YYYY-MM-DD HH:MM:SS]: ");
    fgets(startTime, sizeof(startTime), stdin);
    startTime[strcspn(startTime, "\n")] = '\0';

    printf("Enter end time [YYYY-MM-DD HH:MM:SS]: ");
    fgets(endTime, sizeof(endTime), stdin);
    endTime[strcspn(endTime, "\n")] = '\0';

    const char* checkQ =
    "SELECT * FROM availability "
    "WHERE trainerID = $1 AND startTime < $3 AND endTime > $2;";

    char trainerIDbuff[10];
    snprintf(trainerIDbuff, sizeof(trainerIDbuff), "%d", trainerID);

    const char* params[3] =
    {
        trainerIDbuff,
        startTime,
        endTime
    };

    PGresult* result = PSQL_ExecuteParams(connection, checkQ, 3, params);

    if (PQntuples(result) > 0)
    {
        printf("This time window overlaps an existing one.\n");
        PSQL_ClearResult(result);
        return;
    }

    PSQL_ClearResult(result);
    
    const char* insertQ =
    "INSERT INTO availability(trainerID, startTime, endTime) "
    "VALUES ($1, $2, $3);";

    result = PSQL_ExecuteParams(connection, insertQ, 3, params);

    if (result != NULL)
    {
        printf("Availability set successfully.\n");
    }
    else
    {
        printf("Error setting availability: %s\n", PQerrorMessage(connection->conn));
    }

    PSQL_ClearResult(result);
}

void Trainer_ViewSchedule(PSQLconnect* connection, int trainerID)
{
    printf("--- View Trainer Schedule ---\n");

    char trainerIDbuff[10];
    snprintf(trainerIDbuff, sizeof(trainerIDbuff), "%d", trainerID);

    const char* params[1] =
    {
        trainerIDbuff
    };

    const char* Q =
    "SELECT pt.sessionTime, m.memberName, r.roomName "
    "FROM ptSession pt "
    "JOIN member m ON pt.memberID = m.memberID "
    "JOIN room r on pt.roomID = r.roomID "
    "WHERE pt.trainerID = $1 "
    "ORDER BY pt.sessionTime ASC;";

    PGresult* result = PSQL_ExecuteParams(connection, Q, 1, params);

    int rows = PQntuples(result);
    if (rows == 0)
    {
        printf("No sessions are scheduled\n");
    }
    else
    {
        printf("Trainer Schedule:\n");
        for (int i = 0; i < rows; ++i)
        {
            printf("%s | Member: %s | Room: %s\n", PQgetvalue(result, i, 0),
                                                   PQgetvalue(result, i, 1),
                                                   PQgetvalue(result, i, 2));
        }
    }

    PSQL_ClearResult(result);
}

// /////////////////////////////
// 
// /////////////////////////////