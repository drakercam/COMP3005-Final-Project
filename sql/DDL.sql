-- /////////////////////////////
-- DROP THE TABLES WHEN RESETTING
-- /////////////////////////////

DROP TABLE IF EXISTS member;
DROP TABLE IF EXISTS trainer;
DROP TABLE IF EXISTS healthMetric;
DROP TABLE IF EXISTS availability;
DROP TABLE IF EXISTS room;
DROP TABLE IF EXISTS equipment;
DROP TABLE IF EXISTS maintenanceRecord;
DROP TABLE IF EXISTS ptSession;

-- /////////////////////////////


-- /////////////////////////////
-- CREATE THE TABLES
-- /////////////////////////////

CREATE TABLE member
(
    memberID SERIAL PRIMARY KEY,
    memberName TEXT NOT NULL,
    memberEmail TEXT NOT NULL UNIQUE,
    memberPhone TEXT NOT NULL UNIQUE
);

CREATE TABLE trainer
(
    trainerID SERIAL PRIMARY KEY,
    trainerName TEXT NOT NULL,
    trainerEmail TEXT NOT NULL UNIQUE,
    trainerPhone TEXT NOT NULL UNIQUE
);

CREATE TABLE admin
(
    adminID SERIAL PRIMARY KEY,
    adminName TEXT NOT NULL,
    adminEmail TEXT NOT NULL UNIQUE,
    adminPhone TEXT NOT NULL UNIQUE
);

CREATE TABLE healthMetric
(
    metricID SERIAL PRIMARY KEY,
    memberID INTEGER NOT NULL REFERENCES member(memberID),
    metricTimeStamp TIMESTAMP NOT NULL DEFAULT NOW(),
    weight NUMERIC(5, 2),
    heartRate INTEGER
);

CREATE TABLE availability
(
    availabilityID SERIAL PRIMARY KEY,
    trainerID INTEGER NOT NULL REFERENCES trainer(trainerID),
    startTime TIMESTAMP NOT NULL,
    endTime TIMESTAMP NOT NULL
);

CREATE TABLE room
(
    roomID SERIAL PRIMARY KEY,
    roomName TEXT NOT NULL UNIQUE,
    roomCapacity INTEGER NOT NULL
);

CREATE TABLE equipment
(
    equipmentID SERIAL PRIMARY KEY,
    roomID INTEGER REFERENCES room(roomID),
    equipmentName TEXT NOT NULL,
    status TEXT NOT NULL DEFAULT 'functional'
);

CREATE TABLE maintenanceRecord
(
    recordID SERIAL PRIMARY KEY,
    equipmentID INTEGER NOT NULL REFERENCES equipment(equipmentID),
    issueDescription TEXT NOT NULL,
    loggedAt TIMESTAMP NOT NULL DEFAULT NOW(),
    status TEXT NOT NULL DEFAULT 'open'
);

CREATE TABLE ptSession
(
    sessionID SERIAL PRIMARY KEY,
    memberID INTEGER NOT NULL REFERENCES member(memberID),
    trainerID INTEGER NOT NULL REFERENCES trainer(trainerID),
    roomID INTEGER NOT NULL REFERENCES room(roomID),
    sessionTime TIMESTAMP NOT NULL
);

-- /////////////////////////////


-- /////////////////////////////
-- VIEW
-- /////////////////////////////

CREATE VIEW memberLatestMetric AS
SELECT 
    m.memberID,
    m.memberName,
    hm.weight,
    hm.heartRate,
    hm.metricTimeStamp
FROM member m
LEFT JOIN LATERAL (
    SELECT 
        weight,
        heartRate,
        metricTimeStamp
    FROM healthMetric
    WHERE memberID = m.memberID
    ORDER BY metricTimeStamp DESC
    LIMIT 1
) hm ON TRUE;

-- /////////////////////////////


-- /////////////////////////////
-- TRIGGER
-- /////////////////////////////

CREATE OR REPLACE FUNCTION setMaintenanceTimestamp()
RETURNS TRIGGER AS $$
BEGIN
    NEW.loggedAt = NOW();
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trgMaintenanceTimestamp
BEFORE INSERT ON maintenanceRecord
FOR EACH ROW
EXECUTE FUNCTION setMaintenanceTimestamp();

-- /////////////////////////////


-- /////////////////////////////
-- INDEX
-- /////////////////////////////

CREATE INDEX idxHealthMetricMemberID
ON healthMetric(memberID);

-- /////////////////////////////