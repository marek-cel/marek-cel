-- SELECT * FROM miasta, woj WHERE miasta.kod_woj=woj.kod_woj

/******************************************************************************/

/* to nie bedzie działać, trzebo używać zdefiniowanych aliasów */
-- SELECT * FROM miasta m, woj w WHERE miasta.kod_woj=woj.kod_woj
-- SELECT * FROM miasta m, woj w WHERE m.kod_woj=w.kod_woj

/******************************************************************************/

/* klucz główny i relacja zabezpiecza przed wykonaniem takiego kody */
-- INSERT INTO miasta (kod_woj, nazwa) VALUES ('XXX', 'Przykład')
-- DELETE FROM woj WHERE kod_woj='MAZ'

/******************************************************************************/

-- SELECT * FROM miasta m, woj w WHERE m.kod_woj=w.kod_woj AND m.nazwa LIKE 'w%'
/*
SELECT * FROM miasta m
	JOIN woj w ON (m.kod_woj = w.kod_woj)
	WHERE m.nazwa LIKE 'w%'
*/

/******************************************************************************/

/* miasto, dane osoby, pensja, w jakiej firmie, miasto firmy */
/* !!! zapytanie zaczynamy pisać od słowa from !!! */

/* -- krok 1
SELECT
	FROM	etaty	e
	,	osoby	o
	,	firmy	f
	,	miasta	m
*/

/* -- krok 2
SELECT	m.nazwa AS [miasto osoby]
,	o.id_osoby, o.imię, o.nazwisko
,	e.pensja
,	f.nazwa	AS [nazwa firmy]
,	m.nazwa AS [miasto firmy]
	FROM	etaty	e
	,	osoby	o
	,	firmy	f
	,	miasta	m
*/

/* -- krok 3
SELECT	mo.nazwa AS [miasto osoby]
,	o.id_osoby, o.imię, o.nazwisko
,	e.pensja
,	f.nazwa AS [nazwa firmy]
,	mf.nazwa AS [miasto firmy]
	FROM	etaty	e
	,	osoby	o
	,	firmy	f
	,	miasta	mf
	,	miasta	mo
	WHERE	o.id_osoby=e.id_osoby
	AND	e.id_firmy=f.nazwa_skr
	AND	o.id_miasta=mo.id_miasta
	AND	f.id_miasta=mf.id_miasta
*/

/* -- krok 3 (postać alternatywna - według nowego standardu)
SELECT	mo.nazwa AS [miasto osoby]
,	o.id_osoby, o.imię, o.nazwisko
,	e.pensja
,	f.nazwa AS [nazwa firmy]
,	mf.nazwa AS [miasto firmy]
	FROM	etaty	e
	JOIN	osoby	o	ON (e.id_osoby	= o.id_osoby)
	JOIN	firmy	f	ON (e.id_firmy	= f.nazwa_skr)
	JOIN	miasta	mf	ON (f.id_miasta	= mf.id_miasta)
	JOIN	miasta	mo	ON (o.id_miasta	= mo.id_miasta)
*/

/******************************************************************************/

/* FUNKCJE AGREGUJĄCE - w zapytaniach z wykorzystaniem funkcji agregujących
   można używać tylko i wyłącznie zapytań wykorzystujących owe funkcje
   ( nie wolno do SELECT dodawać kolumn ).
   Postać:
   SELECT funkcje_agregujące FROM tabelki WHERE warunki */

/*
SELECT	MAX(e.pensja)	AS [maks pensja]
,	MIN(e.pensja)	AS [najmniejsza pensja]
,	COUNT(*)	AS [ile etatów]
,	COUNT(DISTINCT e.id_osoby)
			AS [ile osób pracuje na tych etatach]
	FROM	etaty	e
*/

/* -- zapis to tabelki tymczasowej (istniejącej tylko w obrębie pojedyńczej sesji)
SELECT	MAX(e.pensja)	AS [maks pensja]
,	MIN(e.pensja)	AS [najmniejsza pensja]
,	COUNT(*)	AS [ile etatów]
,	COUNT(DISTINCT e.id_osoby)
			AS [ile osób pracuje na tych etatach]
	INTO	#t
	FROM	etaty	e
*/


-- SELECT * FROM #t JOIN etaty e ON (#t.[maks pensja] = e.pensja)

/* -- bez użycia tabelki tymczasowej (zagnieżdżone zapytanie)
SELECT	*
	FROM	(
		SELECT	MAX(e.pensja)	AS [maks pensja]
		,	MIN(e.pensja)	AS [najmniejsza pensja]
		,	COUNT(*)	AS [ile etatów]
		,	COUNT(DISTINCT e.id_osoby)
					AS [ile osób pracuje na tych etatach]
			FROM	etaty	e
		) T
	JOIN	etaty e ON (T.[maks pensja] = e.pensja)
*/

/*
SELECT	T.*
,	o.imię, o.nazwisko
,	f.nazwa
	FROM	(
		SELECT	MAX(e.pensja)	AS [maks pensja]
		,	MIN(e.pensja)	AS [najmniejsza pensja]
		,	COUNT(*)	AS [ile etatów]
		,	COUNT(DISTINCT e.id_osoby)
					AS [ile osób pracuje na tych etatach]
			FROM	etaty	e
		) T
	JOIN	etaty	e	ON (T.[maks pensja] = e.pensja)
	JOIN	osoby	o	ON (e.id_osoby      = o.id_osoby)
	JOIN	firmy	f	ON (e.id_firmy      = f.nazwa_skr)
*/