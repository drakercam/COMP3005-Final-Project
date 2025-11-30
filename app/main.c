#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psql_app.h"

int main(void)
{
    // Connect to the database
    PSQLconnect connection = PSQL_ConnectInit("dbname=mydb user=postgres password-password");

    char email[100];
    int userRole = 0;   // 1 = member, 2 = trainer, 3 = admin
    int userID = 0;

    char hasAccount;
    int c;

    printf("--- Login ---\n");

    printf("Do you have an account? (y/n): ");
    scanf("%c", &hasAccount);
    while ((c = getchar()) != '\n' && c != EOF);

    if (hasAccount == 'n' || hasAccount == 'N')
    {
        const char* registeredEmail = Member_UserRegistration(&connection);
        strncpy(email, registeredEmail, sizeof(email));
        email[sizeof(email)-1] = '\0';
    }
    else    // user already exists in system so no need to register
    {
        printf("Enter your email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
    }

    const char* params[1] =
    {
        email
    };  

    // See if the user is a member
    PGresult* result = PSQL_ExecuteParams
    (
        &connection, 
        "SELECT memberID FROM member WHERE memberEmail = $1;",
        1,
        params
    );

    if (result != NULL && PQntuples(result) > 0)
    {
        userRole = 1;   //member
        userID = atoi(PQgetvalue(result, 0, 0));
    }

    PSQL_ClearResult(result);

    // See if the user is a trainer
    if (!userRole)
    {
        result = PSQL_ExecuteParams
        (
            &connection,
            "SELECT trainerID FROM trainer WHERE trainerEmail = $1;",
            1,
            params
        );

        if (result != NULL && PQntuples(result) > 0)
        {
            userRole = 2;
            userID = atoi(PQgetvalue(result, 0, 0));
        }

        PSQL_ClearResult(result);
    }

    // See if the user is an admin
    if (!userRole)
    {
        result = PSQL_ExecuteParams
        (
            &connection,
            "SELECT adminID FROM admin WHERE adminEmail = $1;",
            1,
            params
        );

        if (result != NULL && PQntuples(result) > 0)
        {
            userRole = 3;
            userID = atoi(PQgetvalue(result, 0, 0));
        }

        PSQL_ClearResult(result);
    }

    // email is not associated with any account
    if (!userRole)
    {
        printf("No account found with entered email\n");
        PSQL_ConnectClose(&connection);
        return 1;
    }

    // User has logged in with a role, we can proceed

    if (userRole == 1)  // member
    {
        int choice = 0;

        while (choice != 4)
        {
            printf("\n--- Member Menu ---\n");

            printf("1. Update Profile\n");
            printf("2. Log Health Metric\n");
            printf("3. View Dashboard\n");
            printf("4. Logout\n");

            printf("Choice: ");
            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (choice)
            {
                case 1: Member_ProfileUpdate(&connection, userID); break;
                case 2: Member_HealthHistLog(&connection, userID); break;
                case 3: Member_Dashboard(&connection, userID); break;
            }
        }
    }
    else if (userRole == 2) // trainer
    {
        int choice = 0;

        while (choice != 3)
        {
            printf("\n--- Trainer Menu ---\n");

            printf("1. Set Availability\n");
            printf("2. View Schedule\n");
            printf("3. Logout\n");

            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (choice)
            {
                case 1: Trainer_SetAvailability(&connection, userID); break;
                case 2: Trainer_ViewSchedule(&connection, userID); break;
            }
        }
    }

    else if (userRole == 3) // admin
    {
        int choice = 0;

        while (choice != 3)
        {
            printf("\n--- Admin Menu ---\n");

            printf("1. Book Room\n");
            printf("2. Maintenance Log\n");
            printf("3. Logout\n");

            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (choice)
            {
                case 1: Admin_BookRoom(&connection, userID); break;
                case 2: Admin_EquipmentMaintenanceLog(&connection, userID); break;
            }
        }
    }
    
    // Close the connection to the database
    PSQL_ConnectClose(&connection);

    printf("Thank you for using the application!\n");

    return 0;
}