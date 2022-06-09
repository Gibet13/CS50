-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE day = 28 -- Find Description of the crime scene
    AND month = 7
    AND year = 2020
    AND street = "Chamberlin Street";


-- Find interview of the 3 witness knowing the date and that they all mention the courthose
SELECT * FROM interviews WHERE day = 28
    AND month = 7
    AND year = 2020
    AND transcript LIKE "%courthouse%";

SELECT * FROM people WHERE license_plate IN( -- find someone who :
SELECT license_plate FROM courthouse_security_logs WHERE day = 28 -- 1. left within 10 minutes of the crime
    AND month = 7
    AND year = 2020
    AND hour = 10
    AND minute > 15
    AND minute < 25
    AND activity = "exit")
    AND phone_number IN (
SELECT caller FROM phone_calls WHERE day = 28 -- 2. made a call lasting less than a minute
    AND month = 7
    AND year = 2020
    AND duration < 60)
    AND passport_number IN (
SELECT passport_number FROM passengers WHERE flight_id IN (
SELECT id FROM flights WHERE day = 29 -- 3. has booked the first flight leaving fiftyville
    AND month = 7
    AND year = 2020
    ORDER BY hour LIMIT 1))
    AND name IN (
SELECT name FROM people -- 4. made a withdrawal the day of the crime at the fifer street atm
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    WHERE account_number IN (
SELECT account_number FROM atm_transactions WHERE day = 28
    AND month = 7
    AND year = 2020
    AND atm_location = "Fifer Street"));


-- Find who received the call
SELECT name FROM people
    JOIN phone_calls ON people.phone_number = receiver
    WHERE day = 28
    AND month = 7
    AND year = 2020
    AND duration < 60;
