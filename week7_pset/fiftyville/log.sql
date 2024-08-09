-- Known information:
-- The theft took place on July 28, 2023.
-- The theft took place on Humphrey Street.
-- The theif took a flight out of town with the help of an accomplice.
-- - The names of the theif, the accomplice, and the country where the Thief flew must be found.

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Querying the crime_scene_reports table for information on the crime.

SELECT description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Duck theft crime description:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
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

-- Querying through bakery security looks on the day when the theft took place, including the hour of 10am when the theft took place.
