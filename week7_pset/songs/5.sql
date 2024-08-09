SELECT (SUM(energy) / COUNT(*)) AS average_energy FROM songs WHERE energy IS NOT NULL;
