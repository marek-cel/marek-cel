-- ALTER TABLE osoby ADD data_ur DATETIME NULL;

-- sp_help osoby;

-- SELECT * FROM osoby;

-- UPDATE osoby 
-- 	SET data_ur = DATEADD( yy, -40, GETDATE() )
-- 	WHERE id_osoby in (4,5);


-- UPDATE osoby 
-- 	SET data_ur = DATEADD( yy, -30, GETDATE() )
-- 	WHERE id_osoby in (2,3);