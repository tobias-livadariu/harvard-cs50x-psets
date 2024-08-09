-- Known information:
-- The theft took place on July 28, 2023.
-- The theft took place on Humphrey Street.
-- The theif took a flight out of town with the help of an accomplice.
-- - The names of the theif, the accomplice, and the country where the Thief flew must be found.

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Querying the crime_scene_reports table for information on the crime.
SELECT description, street FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Duck theft crime description:
-- *Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- *Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Since all witnesses mentioned the bakery, I will look through the bakery_security_logs table next.
-- The crime occured on Humphrey Street.

-- Querying through bakery security logs on the day when the theft took place, including the hour of 10am when the theft took place.
SELECT activity FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10;
/*
+----------+
| activity |
+----------+
| entrance |
| entrance |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| entrance |
| entrance |
| entrance |
+----------+
*/
-- The resulting activity log, not sure if this is very useful.

-- Querying through bakery liscence plates log as well on the day when the theft took place, including the hour of 10am when the theft took place.
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10;
/*
+---------------+
| license_plate |
+---------------+
| R3G7486       |
| 13FNH73       |
| 5P2BI95       |
| 94KL13X       |
| 6P58WS2       |
| 4328GD8       |
| G412CB7       |
| L93JTIZ       |
| 322W7JE       |
| 0NTHK55       |
| 1106N58       |
| NRYN856       |
| WD5M8I6       |
| V47T75I       |
+---------------+
*/
-- The resulting liscence log, not sure if this is very useful.

-- Next, I will repeat the activity and liscence log queries including the minute at which the crime occured.
SELECT activity FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 15;
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 15;

-- Nothing came up, so I decided to keep trying incrementing the minute by 1 until an exit was found.
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 16;
/*
+----------+---------------+
| activity | license_plate |
+----------+---------------+
| exit     | 5P2BI95       |
+----------+---------------+
*/
-- Liscence plate log.
-- Maybe the theif stole the duck from its owner at the bakery, and then drove away immediately after.
-- If this is true, that would mean the liscence plate of 5P2BI95 is the theif's.
-- There doesn't seem to be a liscence plate table so I will move on to interviews.

-- Querying for the transcripts and names of the interviewed people for all interviews
-- that were taken on the day that the duck was stolen.
SELECT name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
-- Here are all the transcripts relating to the stolen duck:
/* Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame. */
/* I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. */
/* As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket. */

-- From this, I learned that the theif left the bakery within ten minutes after the duck was stolen, so from minutes of 15 - 26
-- (adding one extra minute to be safe).
-- They were also seen withdrawing money from an ATM on Legget Street earlier that morning.

-- Also, the theif flew out of the country the next day ON THE EARLIEST FLIGHT, so I need to look for plane tickets
-- on the day of July 29, 2023.

-- Finally, the theif's accomplice bought the ticket, so I need to see who bought a ticket on either
-- July 29, 2023 or July 28, 2023 for a flight on July 29, 2023 to find the accomplice.

-- To find all possible liscence plates of the theif, I will have to further analyze the bakery's
-- security logs and liscence plate logs for all cars leaving the premises from minutes of 15 - 26.
-- Note that I already queried for 16 minutes, but I will include that result here as well for convinence.
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 26 AND activity = "exit";
-- 8 exits
/*
+---------------+
| license_plate |
+---------------+
| 5P2BI95       |
| 94KL13X       |
| 6P58WS2       |
| 4328GD8       |
| G412CB7       |
| L93JTIZ       |
| 322W7JE       |
| 0NTHK55       |
+---------------+
*/
-- Note that adding the minute of 26 did nothing

/* Our suspect's possible liscense plates are shown above.
Since all of the log activities were exits, all liscence plates are suspects. */

-- To remind, a suspect saw the thief withdrawing money from an ATM on Legget Street
-- earlier in the morning before the robbery took place.
-- I will query the atm_transactions table to try and find the bank account number,
-- which can be used to find the culprit's name in the people table.
SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";
/*
+----------------+
| account_number |
+----------------+
| 28500762       |
| 28296815       |
| 76054385       |
| 49610011       |
| 16153065       |
| 25506511       |
| 81061156       |
| 26013199       |
+----------------+
*/
-- Many account numbers were found using the ATM that day

-- Now, I must find the intersection between the list of suspect account_numbers
-- and the list of suspect liscence_plates in the people database to find the culprit's
-- name.
SELECT id, name, passport_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 26
)
AND
id in (
    SELECT person_id FROM bank_accounts WHERE account_number in (
        SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"
    )
);
-- Here is the output:
/*
+--------+-------+-----------------+
|   id   | name  | passport_number |
+--------+-------+-----------------+
| 396669 | Iman  | 7049073643      |
| 467400 | Luca  | 8496433585      |
| 514354 | Diana | 3592750733      |
| 686048 | Bruce | 5773159633      |
+--------+-------+-----------------+
*/
-- Sadly it seems like I still have four suspects.
-- To narrow the suspect list down to a single suspect, I will compare it to the flights
-- database for people that flew out of fiftyville the day after the crime.

-- Finding the name of the airport.
SELECT * FROM airports LIMIT 50;
-- It looks like Fiftyville's airport can be accessed through city = "Fiftyville".

-- Comparing the current suspect list to the individuals who flew out of Fiftyville the
-- day after the robbery on the earliest flight.
SELECT id, name, passport_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 26
)
AND
id in (
    SELECT person_id FROM bank_accounts WHERE account_number in (
        SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"
    )
)
AND
passport_number in (
    SELECT passport_number FROM passengers WHERE flight_id in (
        SELECT id FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = (
            SELECT id FROM airports WHERE city = "Fiftyville"
        ) ORDER BY minute ASC LIMIT 1
    )
);
-- Here is the output:
/*
+--------+-------+-----------------+
|   id   | name  | passport_number |
+--------+-------+-----------------+
| 514354 | Diana | 3592750733      |
+--------+-------+-----------------+
*/
-- Diana is the only remaining suspect!
-- That means she stole the duck!

-- Now I will have to figure out who she called that morning
-- to find her accomplice.
SELECT * FROM phone_calls LIMIT 50;
-- Looks like there is a caller and receiver section for numbers,
-- and a duration section in seconds

-- Checking to see that Diana did in fact call someone that morning,
-- and their call lasted less than a minute.
SELECT id, name, passport_number, license_plate FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 26
)
AND
id in (
    SELECT person_id FROM bank_accounts WHERE account_number in (
        SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"
    )
)
AND
passport_number in (
    SELECT passport_number FROM passengers WHERE flight_id in (
        SELECT id FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = (
            SELECT id FROM airports WHERE city = "Fiftyville"
        ) ORDER BY minute ASC LIMIT 1
    )
)
AND
id in (
    SELECT id FROM people WHERE phone_number IN (
        SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
    )
);
-- Output:
/*
+--------+-------+-----------------+---------------+
|   id   | name  | passport_number | license_plate |
+--------+-------+-----------------+---------------+
| 514354 | Diana | 3592750733      | 322W7JE       |
+--------+-------+-----------------+---------------+
*/
-- Diana is infact the theif.

-- Querying for the person that Diana called that morning.
SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE caller IN (
        SELECT phone_number FROM people WHERE license_plate = "322W7JE"
    )
    AND year = 2023 AND month = 7 AND day = 28 AND duration <= 60
);
-- Output:
/*
+--------+
|  name  |
+--------+
| Philip |
+--------+
*/
-- Therefore, it can be concluded that Philip was the accomplice to Diana.

-- Last, I will have to query for the city that the theif escaped to.
SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id 
)
