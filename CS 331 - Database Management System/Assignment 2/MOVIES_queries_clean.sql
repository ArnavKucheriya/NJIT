/*
CS331 - Assignment #2 - SQL Queries

Jennifer Corte Juela
Arnav Kucheriya

Resources Used:
- Class Notes
- Google Gemini (for help on the queries)
*/

.www
SELECT M.title
FROM Movie AS M
JOIN Studio AS S
    ON M.studioID = S.studioID
WHERE S.name = 'MGM Studios'
  AND M.year > 1990
  AND M.length > 90
ORDER BY M.length DESC;

.www
SELECT title, length
FROM Movie
ORDER BY length ASC;

.www
SELECT name
FROM Actor
WHERE gender = 'F'
ORDER BY name ASC;

.www
SELECT DISTINCT S.name
FROM Studio AS S
JOIN Movie AS M
    ON S.studioID = M.studioID
WHERE M.title LIKE '%Star Wars%'
ORDER BY S.name ASC;

.www
SELECT M.title, S.name AS studio, M.rating, M.year
FROM Movie AS M
JOIN Studio AS S
    ON M.studioID = S.studioID
JOIN StarsIn AS SI
    ON M.movieID = SI.movieID
JOIN Actor AS A
    ON SI.personID = A.personID
WHERE A.name = 'Leonardo DiCaprio'
ORDER BY M.year ASC;

.www
SELECT S.name, SUM(M.length) AS total_length
FROM Studio AS S
JOIN Movie AS M
    ON S.studioID = M.studioID
GROUP BY S.name
ORDER BY total_length DESC;

.www
SELECT name
FROM Studio
WHERE city = 'Los Angeles'
ORDER BY name ASC;

.www
SELECT A.name, AVG(M.rating) AS average_rating
FROM Actor AS A
JOIN StarsIn AS SI
    ON A.personID = SI.personID
JOIN Movie AS M
    ON SI.movieID = M.movieID
GROUP BY A.name
ORDER BY average_rating DESC;
