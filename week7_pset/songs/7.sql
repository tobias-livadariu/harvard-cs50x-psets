SELECT (SUM(energy) / COUNT(*)) AS average_energy_drake FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake') AND energy IS NOT NULL;
