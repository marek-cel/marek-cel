/************************************************************************/
/* ZAPYTANIA Z FUNKCJAMI AGREGUJĄCYMI                                   */
/************************************************************************/

/* Te zapytanie daje dokładnie jeden wiersz */

-- SELECT * FROM etaty e order by e.id_osoby
-- 
-- SELECT	MAX(e.pensja)	AS [najw.pensja]
-- ,		AVG(e.pensja)	AS [śr.pensja]
-- ,		COUNT(*)		AS [ilość etatów]
-- ,		COUNT(DISTINCT e.id_osoby)
-- 						AS [ile osób pracuje na tych etatach]
-- 	INTO #w
-- 	FROM etaty e
-- 	WHERE e.do IS NULL

/************************************************************************/
/* ŁĄCZENIE WYNIKÓW ZAPYTAŃ FUNKCJI AGREGUJĄCYCH Z TABELAMI             */
/* PRZY UŻYCIU TABEL TYMCZASOWYCH                                       */
/************************************************************************/

-- select * from #w JOIN etaty e ON (e.pensja = #w.[najw.pensja] AND e.do IS NULL)

-- INSERT INTO etaty (id_osoby, id_firmy, stanowisko, pensja, od, do)
-- VALUES(1, 'PW', 'X', 65200, GETDATE(), GETDATE())

/************************************************************************/
/* ŁĄCZENIE WYNIKÓW ZAPYTAŃ FUNKCJI AGREGUJĄCYCH Z TABELAMI             */
/* PRZY UŻYCIU ZMIENNE                                                  */
/************************************************************************/

-- DECLARE @MP MONEY
-- 
-- SELECT	@MP = MAX(e.pensja)
-- 	FROM etaty e
-- 	WHERE e.do IS NULL
-- 
-- SELECT @MP
-- 
-- SELECT * FROM etaty e WHERE e.pensja = @MP AND e.do IS NULL

/************************************************************************/
/* ŁĄCZENIE WYNIKÓW ZAPYTAŃ FUNKCJI AGREGUJĄCYCH Z TABELAMI             */
/* PRZY UŻYCIU ZAPYTANIA W ZAPYTANIU                                    */
/************************************************************************/

/* Korzystamy z faktu, że wynikiem zapytania jest tabela.
   Tej tabeli nadajemy alias 'x', do którego się odwołujemy
   w dalszej części zapytania */

SELECT	x.*
,		o_max.imię_i_nazwisko AS [osoba z najw. pensją]
,		o_min.imię_i_nazwisko AS [osoba z najm. pensją]
	FROM	(
				SELECT	MAX(ew.pensja) AS [najw.pensja]
				,		MIN(ew.pensja) AS [najm.pensja]
					FROM	etaty ew
					WHERE	ew.do IS NULL
			) x
	JOIN	etaty e_max ON (e_max.pensja = x.[najw.pensja] AND e_max.do IS NULL)
	JOIN	osoby o_max ON (e_max.id_osoby = o_max.id_osoby)
 	JOIN	etaty e_min ON (e_min.pensja = x.[najm.pensja] AND e_min.do IS NULL)
 	JOIN	osoby o_min ON (e_min.id_osoby = o_min.id_osoby)