#include "psql_app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// /////////////////////////////
// PSQL FUNCTION HELPERS
// /////////////////////////////

PSQLconnect PSQL_ConnectInit(char* connectionInfo)
{
    PSQLconnect c;

    c.info = connectionInfo;
    c.conn = PQconnectdb(c.info);

    if (PQstatus(c.conn) != CONNECTION_OK)
    {
        printf("Connection failed! %s\n", PQerrorMessage(c.conn));
        PQfinish(c.conn);
        exit(EXIT_FAILURE);
    }

    return c;
}

void PSQL_ConnectClose(PSQLconnect* connection)
{
    if (connection)
        PQfinish(connection->conn);
}

PGresult* PSQL_ExecuteQuery(PSQLconnect* connection, const char* query)
{
    PGresult* result = PQexec(connection->conn, query);

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        printf("Query failed! %s\n", PQerrorMessage(connection->conn));
        PSQL_ClearResult(result);
        return NULL;
    }

    return result;
}

PGresult* PSQL_ExecuteParams(PSQLconnect* connection, const char* query, int numParams, const char* const* paramValues)
{
    PGresult* result = PQexecParams(connection->conn, query, numParams, NULL, paramValues, NULL, NULL, 0);

    ExecStatusType status = PQresultStatus(result);

    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK)
    {
        printf("Query Failed: %s\n", PQerrorMessage(connection->conn));
        PSQL_ClearResult(result);
        return NULL;
    }

    return result;
}

void PSQL_ClearResult(PGresult* result)
{
    if (result)
        PQclear(result);
}

// /////////////////////////////
// 
// /////////////////////////////