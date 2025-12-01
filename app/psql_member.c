#include "psql_member.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// /////////////////////////////
// MEMBER FUNCTIONS
// /////////////////////////////

const char* Member_UserRegistration(PSQLconnect* connection)
{
    char name[100];
    static char email[100];
    char phone[50];

    printf("--- Member Registration ---\n");

    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';   // stripping the newline

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter phone number: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    const char* params[3] = 
    {
        name, email, phone 
    };

    PGresult* result = PSQL_ExecuteParams
    (
        connection,
        "INSERT INTO member (memberName, memberEmail, memberPhone) "
        "VALUES ($1, $2, $3);",
        3,
        params
    );

    if (result != NULL)
    {
        printf("Registration successful!\n");
        PSQL_ClearResult(result);
    }

    return email;
}

void Member_ProfileUpdate(PSQLconnect* connection, int memberID)
{
    int choice;
    char newValue[100];

    printf("--- Updating Member Profile ---\n");

    printf("What do you want to update?\n");
    printf("1. Name\n2. Email\n3. Phone\n");
    printf("Choice: ");
    scanf("%d", &choice);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter new value: ");
    fgets(newValue, sizeof(newValue), stdin);
    newValue[strcspn(newValue, "\n")] = '\0';

    char memberIDbuff[10];
    snprintf(memberIDbuff, sizeof(memberIDbuff), "%d", memberID);

    const char* params[2] =
    {
        newValue,
        memberIDbuff
    };

    PGresult* result = NULL;

    if (choice == 1)
    {
        result = PSQL_ExecuteParams
        (
            connection,
            "UPDATE member SET memberName = $1 WHERE memberID = $2;",
            2,
            params
        );
    }   
    else if (choice == 2)
    {
        result = PSQL_ExecuteParams
        (
            connection,
            "UPDATE member SET memberEmail = $1 WHERE memberID = $2;",
            2,
            params
        );
    }
    else if (choice == 3)
    {
        result = PSQL_ExecuteParams
        (
            connection,
            "UPDATE member SET memberPhone = $1 WHERE memberID = $2;",
            2,
            params
        );
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    if (result != NULL)
    {
        printf("Profile Updated Successfully!\n");
        PSQL_ClearResult(result);
    }
}

void Member_HealthHistLog(PSQLconnect* connection, int memberID)
{
    char weight[20];
    char heartRate[20];

    printf("--- Logging Health History ---\n");

    printf("Enter your weight: ");
    fgets(weight, sizeof(weight), stdin);
    weight[strcspn(weight, "\n")] = '\0';

    printf("Enter your heart rate: ");
    fgets(heartRate, sizeof(heartRate), stdin);
    heartRate[strcspn(heartRate, "\n")] = '\0';

    char memberIDbuff[10];
    snprintf(memberIDbuff, sizeof(memberIDbuff), "%d", memberID);

    const char* params[3] =
    {
        memberIDbuff,
        weight,
        heartRate
    };

    PGresult* result = PSQL_ExecuteParams
    (
        connection,
        "INSERT INTO healthMetric (memberID, weight, heartRate) "
        "VALUES ($1, $2, $3);",
        3,
        params
    );

    if (result != NULL)
    {
        printf("Health Metric logged successfully!\n");
        PSQL_ClearResult(result);
    }
}

void Member_Dashboard(PSQLconnect* connection, int memberID)
{
    printf("--- Member Dashboard ---\n");

    char memberIDbuff[10];
    snprintf(memberIDbuff, sizeof(memberIDbuff), "%d", memberID);
    
    const char* params[1] =
    {
        memberIDbuff
    };

    PGresult* result = NULL;

    const char* latestMetricsQ =
    "SELECT weight, heartRate, metricTimeStamp "
    "FROM memberLatestMetric "
    "WHERE memberID = $1";

    result = PSQL_ExecuteParams(connection, latestMetricsQ, 1, params);

    if (result == NULL)
    {
        printf("Error retrieving metric data: %s\n", PQerrorMessage(connection->conn));
        return;
    }

    if (PQntuples(result) > 0)
    {
        printf("Latest Health Metrics:\n");
        printf("Weight: %s\n", PQgetvalue(result, 0, 0));
        printf("Heart Rate: %s\n", PQgetvalue(result, 0, 1));
        printf("Timestamp: %s\n", PQgetvalue(result, 0, 2));
    }
    else
    {
        printf("No Health Metrics have been logged yet\n");
    }
    printf("\n");

    PSQL_ClearResult(result);

    const char* pastSessionQ =
    "SELECT COUNT(*) "
    "FROM ptSession "
    "WHERE memberID = $1 AND sessionTime < NOW();";

    result = PSQL_ExecuteParams(connection, pastSessionQ, 1, params);
    if (PQntuples(result) > 0)
    {
        printf("Past Training Sessions: %s\n", PQgetvalue(result, 0, 0));
    }

    PSQL_ClearResult(result);

    const char* nextSessionQ =
    "SELECT sessionTime, trainerName, roomName "
    "FROM ptSession "
    "JOIN trainer ON ptSession.trainerID = trainer.trainerID "
    "JOIN room ON ptSession.roomID = room.roomID "
    "WHERE memberID = $1 AND sessionTime > NOW() "
    "ORDER BY sessionTime ASC "
    "LIMIT 1;";

    result = PSQL_ExecuteParams(connection, nextSessionQ, 1, params);
    if (PQntuples(result) > 0)
    {
        printf("Next PT Session:\n");
        printf("Session Time: %s\n", PQgetvalue(result, 0, 0));
        printf("Trainer Name: %s\n", PQgetvalue(result, 0, 1));
        printf("Room Name: %s\n", PQgetvalue(result, 0, 2));
    }
    else
    {
        printf("No upcoming sessions\n");
    }

    PSQL_ClearResult(result);
}

// /////////////////////////////
// 
// /////////////////////////////