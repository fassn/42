SELECT REVERSE(SUBSTR(`phone_number`, 2)) AS 'enhopelet'
FROM `distrib`
WHERE LEFT(`phone_number`, 2) = '05';