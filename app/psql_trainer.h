#ifndef PSQL_TRAINER_H
#define PSQL_TRAINER_H

#include "psql_app.h"

// Trainer application functions

/*
# Trainer
1. Set Availability
    - Insert a time window for a trainer:
        - [startTime, endTime]
        - Check no-shared identical times

2. View Trainer Schedule
    - Show assigned PT sessions + classes
*/

void Trainer_SetAvailability(PSQLconnect* connection, int trainerID);
void Trainer_ViewSchedule(PSQLconnect* connection, int trainerID);

#endif