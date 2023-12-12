SELECT `last_name`, `first_name`
FROM `user_card`
WHERE TRIM(`last_name`) LIKE '%-%' OR TRIM(`first_name`) LIKE '%-%'
ORDER BY last_name, first_name;