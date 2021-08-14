-- select m.* from miasta m;
-- select w.* from woj w;
-- 
-- select * from woj w, miasta m where w.kod_woj = m.kod_woj;

/************************************************************************/
/* TWORZENIE ZAPYTAŃ                                                    */
/************************************************************************/

-- select m.*
-- 	from	woj	w,
-- 		miasta	m
-- 	where	(w.kod_woj = m.kod_woj)
-- 	and	(m.nazwa like '%S%')
-- 	order by
-- 		w.nazwa,
-- 		m.nazwa
-- 		desc;

/************************************************************************/

-- select	m.*
-- 	from	woj	w
-- 	join	miasta	m on (w.kod_woj = m.kod_woj)
-- 	order by
-- 			w.nazwa,
-- 			m.nazwa
-- 			desc;

/************************************************************************/

-- select	e.stanowisko
-- ,		e.pensja
-- ,		convert(char(6), e.od, 112) as od
-- ,		convert(char(6), e.do, 112) as do
-- ,		o.imię
-- ,		o.nazwisko
-- ,		f.[nazwa] as [nazwa firmy]
-- ,		mo.[nazwa] as [miasto osoby]
-- ,		mf.[nazwa] as [miasto firmy]
-- 	from	etaty	e
-- 	,		osoby	o
-- 	,		firmy	f
-- 	,		miasta	mo
-- 	,		miasta	mf
-- 	where	(e.id_osoby = o.id_osoby)
-- 	and		(e.id_firmy = f.nazwa_skr)
-- 	and		(mo.id_miasta = o.id_miasta)
-- 	and		(mf.id_miasta = f.id_miasta)

/************************************************************************/
/* TWORZENIE ZAPYTAŃ Z WYKORZYSTANIEM SŁOWA 'JOIN'                      */
/************************************************************************/

-- SELECT	e.stanowisko
-- ,		e.pensja
-- ,		CONVERT(char(6), e.od, 112)	AS od
-- ,		CONVERT(char(6), e.do, 112)	AS do
-- ,		( left(o.imię,1) + '.' + o.nazwisko ) AS [imię i nazwisko]
-- ,		f.[nazwa]	AS [nazwa firmy]
-- ,		mo.[nazwa]	AS [miasto osoby]
-- ,		mf.[nazwa]	AS [miasto firmy]
-- ,		wo.[nazwa]	AS [woj osoby]
-- ,		wf.[nazwa]	AS [woj firmy]
-- ,		CASE	WHEN e.do IS NULL THEN 'Nadal pracuje'
-- 				ELSE 'etat zakończony ' + CONVERT(char(6), e.do, 112)
-- 				END AS [info o etacie]
-- ,		CASE	WHEN o.data_ur IS NULL
-- 				THEN 'Nieznana data urodzenia'
-- 				WHEN DATEDIFF(yy, o.data_ur, GETDATE() ) > 30
-- 				THEN 'starszy niż 30'
-- 				ELSE 'młodszy niż 30'
-- 				END AS [przedział wiekoy]
-- 	FROM	etaty	e
-- 	JOIN	osoby	o	ON ( e.id_osoby  = o.id_osoby   )
-- 	JOIN	firmy	f	ON ( e.id_firmy  = f.nazwa_skr  )
-- 	JOIN	miasta	mo	ON ( o.id_miasta = mo.id_miasta )
-- 	JOIN	miasta	mf	ON ( f.id_miasta = mf.id_miasta )
-- 	JOIN	woj		wo	ON ( mo.kod_woj  = wo.kod_woj   )
-- 	JOIN	woj		wf	ON ( mf.kod_woj  = wf.kod_woj   )

/************************************************************************/
/* TWORZENIE I MODYFIKACJA WIDOKÓW                                      */
/************************************************************************/

-- -- CREATE VIEW dbo.o_osobie AS
-- ALTER VIEW o_osobie AS
-- SELECT	o.id_osoby
-- ,		e.stanowisko
-- ,		e.pensja
-- ,		CONVERT(char(6), e.od, 112)	AS od
-- ,		CONVERT(char(6), e.do, 112)	AS do
-- ,		( left(o.imię,1) + '.' + o.nazwisko ) AS [imię i nazwisko]
-- ,		f.[nazwa]	AS [nazwa firmy]
-- ,		mo.[nazwa]	AS [miasto osoby]
-- ,		mf.[nazwa]	AS [miasto firmy]
-- ,		wo.[nazwa]	AS [woj osoby]
-- ,		wf.[nazwa]	AS [woj firmy]
-- ,		CASE	WHEN e.do IS NULL THEN 'Nadal pracuje'
-- 				ELSE 'etat zakończony ' + CONVERT(char(6), e.do, 112)
-- 				END AS [info o etacie]
-- ,		CASE	WHEN o.data_ur IS NULL
-- 				THEN 'Nieznana data urodzenia'
-- 				WHEN DATEDIFF(yy, o.data_ur, GETDATE() ) > 30
-- 				THEN 'starszy niż 30'
-- 				ELSE 'młodszy niż 30'
-- 				END AS [przedział wiekoy]
-- 	FROM	etaty	e
-- 	JOIN	osoby	o	ON ( e.id_osoby  = o.id_osoby   )
-- 	JOIN	firmy	f	ON ( e.id_firmy  = f.nazwa_skr  )
-- 	JOIN	miasta	mo	ON ( o.id_miasta = mo.id_miasta )
-- 	JOIN	miasta	mf	ON ( f.id_miasta = mf.id_miasta )
-- 	JOIN	woj		wo	ON ( mo.kod_woj  = wo.kod_woj   )
-- 	JOIN	woj		wf	ON ( mf.kod_woj  = wf.kod_woj   )

/************************************************************************/
/* TABELA TYMCZASOWA (ISTNIEJĄCA W OBRĘBIE POŁĄCZENIA)                  */
/************************************************************************/

--DROP TABLE #t

-- SELECT oo.*, o.imię_i_nazwisko AS [I_i_N]
-- --into #t
-- 	FROM o_osobie oo
-- 	JOIN osoby o ON (oo.id_osoby = o.id_osoby)
-- 	WHERE oo.[info o etacie] like '%nadal%'

-- SELECT * FROM #t

/************************************************************************/
/* SŁOWO KLULCZOWE 'IN'                                                 */
/************************************************************************/

SELECT * FROM osoby o;

-- SELECT *
-- 	FROM	osoby	o
-- 	WHERE	(		left(o.imię,1) = 'J'
-- 			OR		left(o.imię,1) = 'K' )
-- 	AND		o.nazwisko LIKE 'N%'

-- SELECT *
-- 	FROM	osoby	o
-- 	WHERE	left(o.imię,1) IN ('J','K')
-- 	AND		o.nazwisko LIKE 'N%'

