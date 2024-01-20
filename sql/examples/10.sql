-- SELECT * FROM woj;
-- SELECT * FROM miasta;
-- SELECT * FROM woj JOIN miasta ON (miasta.kod_woj = woj.kod_woj );

/* dane z 2 tabel ale tylko wiersze spelniajace warunek laczacy */
--SELECT * FROM woj INNER JOIN miasta ON (miasta.kod_woj = woj.kod_woj );

/* lewostronnie otwarte poł A i B to takie ktore pokaże WSZYSTKO z A i B
i ewentualnie odpowiedniki z B - jak nie ma odpowiednika to NULL-e */
--SELECT * FROM woj LEFT OUTER JOIN miasta ON (miasta.kod_woj = woj.kod_woj );

/* niebezpieczenstwo uzywania zlaczen otwartych */
--SELECT * FROM osoby o LEFT OUTER JOIN miasta m ON
--	(m.id_miasta = o.id_miasta AND m.nazwa LIKE 'S%')
--	JOIN woj w ON (m.kod_woj = w.kod_woj)

/* lista osób wraz z sumą ich zarobków */

/* P1 - osoby pracujace */
SELECT o.id_osoby, o.imię, o.nazwisko, SUM(e.pensja) AS [suma pensji]
	FROM osoby o
	JOIN etaty e ON (o.id_osoby = e.id_osoby AND e.do IS NULL)
	GROUP BY o.id_osoby, o.imię, o.nazwisko

UNION ALL /* P2 - osoby aktualnie bez etatu */
SELECT o.id_osoby, o.imię, o.nazwisko, CONVERT(MONEY,NULL) AS [brak pensji]
	FROM osoby o
	WHERE NOT EXISTS ( SELECT * FROM etaty ew WHERE ew.id_osoby = o.id_osoby AND ew.do IS NULL)
	GROUP BY o.id_osoby, o.imię, o.nazwisko
SELECT o.id_osoby, o.imię, o.nazwisko, SUM(e.pensja) AS [suma pensji]
	FROM osoby o LEFT OUTER
	JOIN etaty e ON (o.id_osoby = e.id_osoby AND e.do IS NULL)
	GROUP BY o.id_osoby, o.imię, o.nazwisko