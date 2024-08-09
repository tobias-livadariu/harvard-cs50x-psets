SELECT b_movies.title AS jb_movies FROM
(SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Bradley Cooper"))) AS b_movies
JOIN
(SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Jennifer Lawrence"))) AS j_movies
ON b_movies.title = j_movies.title;
