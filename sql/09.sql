/******************************************************************************/
/* wojewodztwa w kktorych nie ma miast */

--SELECT * FROM woj
--SELECT null FROM woj

SELECT	*
	FROM	woj	w
	WHERE NOT EXISTS
		(
		SELECT	null
			FROM	miasta	inn_m
			WHERE	(inn_m.kod_woj = w.kod_woj)
		)

/******************************************************************************/
/* srednia w miastach - z etatow firm -> w ktorych nie znajdziemy osoby 
   mieszkajacej w miescie wesola */

SELECT	m.id_miasta
,	m.nazwa		AS [miasto firmy]
,	AVG(e.pensja)	AS [sr w miastach]
	FROM	etaty	e
	JOIN	firmy	f	ON (f.nazwa_skr = e.id_firmy)
	JOIN	miasta	m	ON (m.id_miasta = f.id_miasta)
	WHERE	e.do IS null
	AND	NOT EXISTS (
		SELECT	null
			FROM	miasta	inn_m
			JOIN	osoby	inn_o	ON (inn_o.id_miasta = inn_m.id_miasta)
			JOIN	etaty	inn_e	ON (inn_e.id_osoby  = inn_o.id_osoby)
			WHERE	(inn_m.nazwa = 'Wesoła')
			AND	(f.nazwa_skr = inn_e.id_firmy)
			AND	(inn_e.do IS null)
		)
	GROUP BY m.id_miasta, m.nazwa