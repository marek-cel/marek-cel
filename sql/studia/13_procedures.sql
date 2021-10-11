/* PROCEDURY BAZODANOWE */

/* srednia w firmach w wybranym wojewodztwie */

CREATE PROCEDURE dbo.pp1 (@kw char(3)='maz')
AS
	SELECT *
		FROM	firmy	f
		JOIN	miasta	mf	ON ( mf.id_miasta = f.id_miasta )
		WHERE mf.kod_woj=@kw
GO

DROP PROCEDURE pp1

ALTER PROCEDURE dbo.pp1 (@kw char(3)='maz')
AS
	SELECT mf.nazwa AS [miasto], mf.kod_woj, f.nazwa AS [firma], AVG(e.pensja) AS [srednia pensja w firmie]
		FROM	firmy	f
		JOIN	miasta	mf	ON ( mf.id_miasta = f.id_miasta )
		JOIN	etaty	e	ON ( e.id_firmy = f.nazwa_skr )
		GROUP BY mf.nazwa, mf.kod_woj, f.nazwa
GO

EXEC pp1 @kw ='maz'