-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get to know the crime scene 1st like every crime movie
SELECT * FROM crime_scene_reports;
-- Filter for Chamberlin Street to see what happen on the street, dozen of crime happen there
SELECT * FROM crime_scene_reports WHERE street LIKE '%chamberlin street%';
-- 29/07/2020 10.15am at Chamberlin Street courthouse 3 witnesses --> look further at interviews section
SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- Shortly (Jose, Euhene, Barbara doesnt giving any info(maybe))
-- Ruth 10 Min(10.15 - 10.25am) look at security footage
-- Eugene Check ATM Fifer Street before Eugene come to courthouse
-- Raymond earliest flight on 29/07/2020 to WHERE??, Accomplice buy ticket

-- Look for Courthouse Parking Lot footage as Ruth said
SELECT license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit';

-- 8 Suspect here  5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55
-- Check for the time Eugene reach courthouse
SELECT year, month, day, hour, minute From courthouse_security_logs
JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE name = 'Eugene';
-- No parking log of Eugene on 28/07/2020
-- Filter for the one who use ATM at fifer street  before 10.15 and with 8 suspect license plate
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location LIKE 'fifer street' AND license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55');

-- Down to 4 person Ernest, Russell, Elizabeth, Danielle
-- Check for this 4 people flight out of fiftyville
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city LIKE 'fiftyville' AND year = 2020 AND month = 7 AND day = 29 AND name IN ('Ernest', 'Russell', 'Elizabeth', 'Danielle');

-- 3 Suspect left Russell, Ernest, Danielle 2 of them may be the theft lets check the destination
SELECT name, airports.city FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.destination_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND name IN ('Ernest', 'Russell', 'Danielle');

--Check for phone call less than a minute on 28/07 as Raymond mention
SELECT name FROM people WHERE phone_number IN (SELECT caller From phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) AND name IN ('Ernest', 'Russell', 'Danielle');

-- Russell and Ernest make a call lets Find the reciever of those call Search for reciever Ernest call Berthold
SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Ernest');
-- Ernest call Berthold
SELECT name FROM people WHERE phone_number ='(375) 555-8161';
-- Russell call
SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Russell');
-- Russell call Philip
SELECT name FROM people WHERE phone_number ='(725) 555-3243'

-- Looklike we miss something
-- may be earliest really mean 1st flight on 29/07/2020
SELECT id, hour, minute FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'Fiftyville') ORDER BY hour;

-- Earliest is flight id 36
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE people.name IN ('Ernest', 'Russell') AND flights.id = 36;

-- Finally, Ernest is the one we looking for and he call Berthold
-- Check for flights 36, It's London
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;