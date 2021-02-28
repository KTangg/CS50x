SELECT name FROM directors
JOIN movies ON movies.id = directors.movie_id
JOIN ratings ON movies.id = ratings.movie_id
JOIN people ON directors.person_id = people.id
WHERE rating >= 9;