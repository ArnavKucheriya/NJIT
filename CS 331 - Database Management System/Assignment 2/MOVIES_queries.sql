/* 
Jennifer Corte Juela
Arnav Kucheriya 

Resources Used:
- Class Notes
- Google Gemini (for help on the queries)
*/
    
.www
SELECT title
FROM Movie
JOIN Studio ON Movie.studioID = Studio.studioID
WHERE Studio.name = 'MGM Studios' AND year > 1990 AND length > 90
ORDER BY length DESC;

.www
SELECT title, length
FROM Movie
ORDER BY length ASC;


.www
SELECT name
FROM Actor
WHERE gender= 'F'
ORDER BY name ASC;

.www
SELECT DISTINCT S.name
FROM Studio S
JOIN Movie M ON S.studioID = M.studioID
WHERE M.title LIKE '%Star Wars%'
ORDER BY S.name ASC;

.www
SELECT M.title, S.name, M.rating, M.year
FROM Movie M
JOIN Studio S ON M.studioID = S.studioID
JOIN StarsIn SI ON M.movieID = SI.movieID
JOIN Actor A on SI.personID = A.personID
WHERE A.name = 'Leonardo DiCaprio'
ORDER BY M.year;

.www
SELECT S.name, SUM(M.length) AS total_length
FROM Studio S
JOIN Movie M on S.studioID = M.studioID
GROUP BY S.name
ORDER BY total_length DESC;

.www
SELECT name
FROM Studio
WHERE city='Los Angeles'
ORDER BY name ASC;

.www
SELECT A.name, AVG(M.rating) as average_rating
FROM Actor A
JOIN StarsIn SI ON A.personID = SI.personID
JOIN Movie M ON SI.movieID = M.movieID
GROUP BY A.name
ORDER BY average_rating DESC;
