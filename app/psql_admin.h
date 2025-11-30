#ifndef PSQL_ADMIN_H
#define PSQL_ADMIN_H

#include "psql_app.h"

// Admin application functions

/*
# Admin
1. Room Booking
    - Admin can assign a room for a class or PT session

2. Equipment Maintenance Logging
    - Insert a maintenance issue
        - [equipmentID, description]
    - Allow updating the status to resolved
*/

void Admin_BookRoom(PSQLconnect* connection, int adminID);
void Admin_EquipmentMaintenanceLog(PSQLconnect* connection, int adminID);

#endif