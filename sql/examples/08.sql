/* Lista wszystkich osob w bazie i suma ich aktualnych zarobkow */

/******************************************************************************/

/*
-- 1) lista osob majacych chociaz 1 aktualny etat i suma ich aktualnych zarobkow
SELECT	o.id_osoby, o.imię, o.nazwisko, SUM(e.pensja) AS [suma zarobków]
	FROM	etaty	e
	JOIN	osoby	o	ON (e.id_osoby = o.id_osoby)
	WHERE	e.do IS null
	GROUP BY
		o.id_osoby, o.imię, o.nazwisko

-- 2) osoby ktore nie maja ZADNEGO aktualnego etatu:
SELECT	*
	FROM	osoby	o
	WHERE NOT EXISTS
		(
		SELECT	*
			FROM	etaty	inn_e
			WHERE	(inn_e.id_osoby = o.id_osoby)
			AND	(inn_e.do IS null)
		)
*/

/******************************************************************************/
/* Klejenie Zapytań - muszą być takie same liczby kolumn
   i takie same typy kolumn. */

SELECT	o.id_osoby, o.imię, o.nazwisko, SUM(e.pensja) AS [suma zarobków]
	FROM	etaty	e
	JOIN	osoby	o	ON (e.id_osoby = o.id_osoby)
	WHERE	e.do IS null
	GROUP BY
		o.id_osoby, o.imię, o.nazwisko

UNION ALL
SELECT	o.id_osoby, o.imię, o.nazwisko, CONVERT(MONEY, null) AS [suma zarobków]
	FROM	osoby	o
	WHERE NOT EXISTS
		(
		SELECT	*
			FROM	etaty	inn_e
			WHERE	(inn_e.id_osoby = o.id_osoby)
			AND	(inn_e.do IS null)
		)

/******************************************************************************/

SELECT * FROM osoby

/******************************************************************************/