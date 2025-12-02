-- /////////////////////////////
-- MEMBERS TABLE
-- /////////////////////////////

INSERT INTO member (memberName, memberEmail, memberPHONE) VALUES
('Cameron Drake', 'camerondrake@cmail.carleton.ca', '6133129876'),
('Anakin Skywalker', 'anakin66@sw.com', '6130666666'),
('Obi-Wan Kenobi', 'obiwan60@example.com', '6134578907');

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- TRAINERS TABLE
-- /////////////////////////////

INSERT INTO trainer (trainerName, trainerEmail, trainerPhone) VALUES
('Yoda Trainer', 'yoda@dagobah.com', '6137778970'),
('Mace Windu Trainer', 'mace@nohand.com', '6137283456');

-- /////////////////////////////
-- 
-- /////////////////////////////

-- /////////////////////////////
-- ADMINS TABLE
-- /////////////////////////////

INSERT INTO admin (adminName, adminEmail, adminPhone) VALUES
('Palpatine Admin', 'palps@admin.com', '6138904587');

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- ROOMS TABLE
-- /////////////////////////////

INSERT INTO room (roomName, roomCapacity) VALUES
('Studio A', 20),
('Studio B', 10),
('PT Room 1', 6);

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- EQUIPMENT TABLE
-- /////////////////////////////

INSERT INTO equipment (roomID, equipmentName, status) VALUES
(1, 'Bench Press 1', 'functional'),
(1, 'Bench Press 2', 'functional'),
(2, 'Treadmill', 'functional'),
(3, 'Deadlift machine', 'functional');

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- HEALTH METRICS TABLE
-- /////////////////////////////

INSERT INTO healthMetric (memberID, weight, heartRate) VALUES
(1, 150.5, 72),
(1, 149.8, 75),
(2, 180.0, 82),
(3, 135.2, 65),
(3, 136.0, 66);

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- TRAINER AVAILABILITY TABLE
-- /////////////////////////////

INSERT INTO availability (trainerID, startTime, endTime) VALUES
(1, '2025-11-27 09:00:00', '2025-11-27 12:00:00'),
(1, '2025-11-28 15:00:00', '2025-11-28 17:00:00'),
(2, '2025-11-27 10:00:00', '2025-11-27 13:00:00');

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- PERSONAL TRAINING SESSIONS TABLE
-- /////////////////////////////

INSERT INTO ptSession (memberID, trainerID, roomID, sessionTime) VALUES
(1, 1, 3, '2025-11-29 10:00:00'),
(2, 1, 3, '2025-11-29 11:00:00'),
(3, 2, 2, '2025-11-28 12:00:00');

-- /////////////////////////////
-- 
-- /////////////////////////////


-- /////////////////////////////
-- MAINTENANCE RECORDS TABLE
-- /////////////////////////////

INSERT INTO maintenanceRecord (equipmentID, issueDescription) VALUES
(1, 'Bench Press cushion torn'),
(3, 'Treadmill randomly turning off'),
(4, 'Deadlift Machine missing weight clips');

-- /////////////////////////////
-- 
-- /////////////////////////////