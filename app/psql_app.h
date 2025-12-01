#ifndef PSQL_APP_H
#define PSQL_APP_H

#include <libpq-fe.h>

typedef struct
{
    PGconn* conn;
    char* info;

} PSQLconnect;

// PSQL connection helper functions
PSQLconnect PSQL_ConnectInit(char* connectionInfo);

void PSQL_ConnectClose(PSQLconnect* connection);

// PSQL Query helpers
PGresult* PSQL_ExecuteQuery(PSQLconnect* connection, const char* query);
PGresult* PSQL_ExecuteParams(PSQLconnect* connection, const char* query, int numParams, const char* const* paramValues);
void PSQL_ClearResult(PGresult* result);

#include "psql_member.h"
#include "psql_trainer.h"
#include "psql_admin.h"

#endif