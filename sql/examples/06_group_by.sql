/* !!! GRUPOWANIE !!! */

/******************************************************************************/

/*
SELECT	e.id_firmy
,	f.nazwa		AS [nazwa firmy]
,	m.nazwa		AS [miasto firmy]
,	MAX(e.pensja)	AS [max pensja]
,	MIN(e.pensja)	AS [min pensja]
,	COUNT(*)	AS [liczba etatow w firmie]
,	COUNT(DISTINCT e.id_osoby)
			AS [liczba zatrudnionych w firmie]
	FROM	etaty	e
	JOIN	firmy	f	ON (e.id_firmy = f.nazwa_skr)
	JOIN	miasta	m	ON (f.id_miasta = m.id_miasta)
	GROUP BY e.id_firmy, f.nazwa, m.nazwa
*/

/* Aby uniknąć blędów warto grupować maksymalnie po 1 kolumnie. A dopiero
   wynik złączać z kolejnym zapytaniem.*/

/* -- Przykład nieoczekiwanego zachowania zapytanie przy grupowaniu:
SELECT	e.id_osoby, e.id_firmy
,	f.nazwa		AS [nazwa firmy]
,	m.nazwa		AS [miasto firmy]
,	MAX(e.pensja)	AS [max pensja]
,	MIN(e.pensja)	AS [min pensja]
,	COUNT(*)	AS [liczba etatow w firmie]
,	COUNT(DISTINCT e.id_osoby)
			AS [liczba zatrudnionych w firmie]
	FROM	etaty	e
	JOIN	firmy	f	ON (e.id_firmy = f.nazwa_skr)
	JOIN	miasta	m	ON (f.id_miasta = m.id_miasta)
	GROUP BY e.id_osoby, e.id_firmy, f.nazwa, m.nazwa
*/

-- Przykład jak uniknąć błędów przy zapytaniach z grupowaniem:
SELECT	t.*
,	f.nazwa		AS [nazwa firmy]
,	m.nazwa		AS [miasto firmy]
	FROM	(
		SELECT	e.id_firmy
		,	MAX(e.pensja)	AS [max pensja]
		,	MIN(e.pensja)	AS [min pensja]
		,	COUNT(*)	AS [liczba etatow w firmie]
		,	COUNT(DISTINCT e.id_osoby)
					AS [liczba zatrudnionych w firmie]
			FROM	etaty	e
			GROUP BY e.id_firmy
		) t
	JOIN	firmy	f	ON (t.id_firmy = f.nazwa_skr)
	JOIN	miasta	m	ON (f.id_miasta = m.id_miasta)

/******************************************************************************/