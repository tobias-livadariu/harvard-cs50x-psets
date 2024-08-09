-- Known information:
-- The theft took place on July 28, 2023.
-- The theft took place on Humphrey Street.
-- The theif took a flight out of town with the help of an accomplice.
-- - The names of the theif, the accomplice, and the country where the Thief flew must be found.

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Querying the crime_scene_reports table for information on the crime.

SELECT description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Duck theft crime description:
-- *Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- *Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Since all witnesses mentioned the bakery, I will look through the backery_security_logs table next.

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

-- Nothing came up, so I decided to keep trying incrementing the minute by 1 until something was found.
SELECT activity FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 16;
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 16;
/*
+----------+
| activity |
+----------+
| entrance |
+----------+
*/
-- Activity log.

/*
+---------------+
| license_plate |
+---------------+
| 13FNH73       |
+---------------+
*/
-- Liscence plate log.
-- Maybe the theif stole the duck from its owner at the bakery, and then drove away immediately after.
-- If this is true, that would mean the liscence plate of 13FNH73 is the theif's.
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

-- Also, the theif left the 
