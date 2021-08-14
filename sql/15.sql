/* zmiana pensji w rekordzie z tabeli ETATY */
/* taka zmiana MUSI spowodowac zapamietanie poprzednich danych */
/* w nowym rekordzie z kolumna DO rowna aktualnej dacie */
/* rekord ktory zmieniamy bedzie mial OD rowne aktualnej dacie a do bedzie mial NULL */

SELECT * FROM etaty

/*
ALTER TABLE etaty ADD z_etatu INT NULL
	CONSTRAINT fk_et_et REFERENCES etaty(id_etatu)
*/

CREATE PROCEDURE dbo.zmp (@id_etatu INT=1, @nowa_pensja MONEY=9999)
AS
	DECLARE @tr INT, @blad INT, @nowy INT, @trc INT
	SELECT @tr = @@TRANCOUNT
	
	IF @tr = 0
		BEGIN TRAN TR_ZP
	ELSE
		SAVE TRAN TR_ZP
	
	INSERT INTO etaty ( id_osoby, id_firmy, pensja, od, do, stanowisko, z_etatu )
		SELECT e.id_osoby, e.id_firmy, e.pensja, e.od, GETDATE(), e.stanowisko, e.id_etatu
			FROM etaty e WHERE e.id_etatu = @id_etatu AND e.do IS NULL
	
	SELECT @blad = @@ERROR, @nowy = SCOPE_IDENTITY(), @trc = @@ROWCOUNT
	
	IF @trc = 0
	BEGIN
		SET @blad = 1
		RAISERROR('Etat id=%d jest archiwalny', 16, 1, @id_etatu)
	END
	
	IF @blad = 0
	BEGIN
		UPDATE etaty SET pensja = @nowa_pensja, od = GETDATE() WHERE id_etatu = @id_etatu
		SELECT @blad = @@ERROR
	END
	
	IF @blad = 0
	BEGIN
		IF @tr = 0
		BEGIN
			COMMIT TRAN TR_ZP
		END
	END
	ELSE
	BEGIN
		ROLLBACK TRAN TR_ZP
	END
GO

EXEC zmp @id_etatu=3, @nowa_pensja=8888