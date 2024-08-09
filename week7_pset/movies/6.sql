SELECT AVG(rating) AS average_rating_2012 FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012) AND rating IS NOT NULL;
