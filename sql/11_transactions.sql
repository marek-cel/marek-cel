SELECT @@TRANCOUNT AS poziom

/* otwieramy tranzakcję */
BEGIN TRAN t1

SELECT @@TRANCOUNT AS poziom

DELETE FROM etaty WHERE id_osoby = 1

	--BEGIN TRAN t2
	SAVE TRAN t2 /* save point */
	SELECT @@TRANCOUNT AS poziom

	UPDATE osoby SET nazwisko = 'X' WHERE id_osoby = 1

	ROLLBACK TRAN t2 /* odwoluje zmiany do punktu t2 */

	SELECT * FROM osoby
	SELECT * FROM etaty

	SELECT @@TRANCOUNT AS poziom

ROLLBACK TRAN t1 /* odwoluje wszystkie zmiany w ramach tranzakcji */

SELECT @@TRANCOUNT AS poziom