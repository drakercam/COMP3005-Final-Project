#ifndef PSQL_MEMBER_H
#define PSQL_MEMBER_H

#include "psql_app.h"

// Member application functions

/*
# MEMBER
1. User Registration
    - Only need unique for email/phone

2. Profile Management
    - Allow update name, phone, email. etc.

3. Health History Logging
    - Allow inserting weight/heart-rate entry with a timestamp

4. Basic Dashboard
    - Show latest metrics of health history
    - Past classes
    - Next upcoming PT session
*/

const char* Member_UserRegistration(PSQLconnect* connection);
void Member_ProfileUpdate(PSQLconnect* connection, int memberID);
void Member_HealthHistLog(PSQLconnect* connection, int memberID);
void Member_Dashboard(PSQLconnect* connection, int memberID);

#endif