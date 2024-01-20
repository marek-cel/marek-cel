/******************************************************************************/

/* -- Średnia AKTUALNA pensja w miastach - osób tam mieszkających:
SELECT	mo.id_miasta
,	mo.nazwa	AS [miasto os]
,	MAX(e.pensja)	AS [max miasta]
,	AVG(e.pensja)	AS [srednia miasta]
,	COUNT(*)	AS [l. akt. etatow w miescie]
,	COUNT(DISTINCT o.id_osoby)
			AS [l. osob z akt. etatami w danym miescie]
	FROM	miasta	mo
	JOIN	osoby	o	ON ( o.id_miasta = mo.id_miasta)
	JOIN	etaty	e	ON ( e.id_osoby = o.id_osoby)
	WHERE	e.do IS null
	GROUP BY
		mo.id_miasta
	,	mo.nazwa
*/

SELECT	t.*
,	oz.*
,	ez.*
	FROM	etaty	ez
	JOIN	osoby	oz	ON (ez.id_osoby = oz.id_osoby)
	JOIN	(
		SELECT	mo.id_miasta
		,	mo.nazwa	AS [miasto os]
		,	MAX(e.pensja)	AS [max miasta]
		,	AVG(e.pensja)	AS [srednia miasta]
		,	COUNT(*)	AS [l. akt. etatow w miescie]
		,	COUNT(DISTINCT o.id_osoby)
					AS [l. osob z akt. etatami w danym miescie]
			FROM	miasta	mo
			JOIN	osoby	o	ON ( o.id_miasta = mo.id_miasta)
			JOIN	etaty	e	ON ( e.id_osoby = o.id_osoby)
			WHERE	e.do IS null
			GROUP BY
				mo.id_miasta
			,	mo.nazwa
		) t	ON (ez.pensja = t.[max miasta] AND oz.id_miasta = t.id_miasta)
	