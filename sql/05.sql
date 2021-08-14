-- sp_help firmy

/******************************************************************************/

DECLARE @idf CHAR(3)
SET @idf = 'PW'

DECLARE cc INSENSITIVE CURSOR FOR
	SELECT f.nazwa_skr
		FROM firmy f
		ORDER BY 1
OPEN cc
FETCH NEXT FROM cc INTO @idf

/******************************************************************************/

WHILE @@FETCH_STATUS = 0
BEGIN
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
				WHERE	e.id_firmy = @idf
			) T
		JOIN	etaty	e	ON (T.[maks pensja] = e.pensja AND e.id_firmy = @idf)
		JOIN	osoby	o	ON (e.id_osoby      = o.id_osoby)
		JOIN	firmy	f	ON (e.id_firmy      = f.nazwa_skr)

	FETCH NEXT FROM cc INTO @idf
END

CLOSE cc
DEALLOCATE cc

/******************************************************************************/