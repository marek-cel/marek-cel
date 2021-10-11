/* TRIGGER-y - odmiana procedury bazodanowej
   sa zwiazane z konretna tabela
   z operacjami na tabelach (SELECT, INSERT, UPDATE)
   Wlasciwosci: 
   1) TRIGGER-a nie da sie wywolac jak procedury
   2) TRIGGER nie ma parametrow
   Zastosowania:
   1) Zmiana aplikacji do ktorej nie mamy kodow zrodlowych
*/

/***************** PRZYKLAD 1 ******************/

CREATE TRIGGER dbo.tr1 ON woj FOR INSERT
AS
	RAISERROR('Nie pozwalam - zapłać', 16, 1)
	ROLLBACK TRAN
GO

INSERT INTO WOJ (kod_woj, nazwa) VALUES ('x', 'x')

SELECT * FROM woj

/***************** PRZYKLAD 2 ******************/

CREATE TABLE dbo.nazwiska
(	id_historii	INT		NOT NULL IDENTITY CONSTRAINT pk_nazwiska PRIMARY KEY
,	z_nazwiska	VARCHAR(40)	NOT NULL
,	na_nazwisko	VARCHAR(40)	NOT NULL
,	kto		VARCHAR(40)	NOT NULL DEFAULT USER_NAME()
,	kiedy		DATETIME	NOT NULL DEFAULT GETDATE()
,	komputer	VARCHAR(40)	NOT NULL DEFAULT HOST_NAME()
)
GO
ALTER TABLE nazwiska ADD id_osoby INT NULL
GO

CREATE TRIGGER dbo.tro ON osoby FOR UPDATE
AS
	/* deleted - stare dane */
	/* inserted - nowe dane */
	INSERT INTO nazwiska ( z_nazwiska, na_nazwisko , id_osoby )
		SELECT d.nazwisko, i.nazwisko, i.id_osoby
			FROM inserted i JOIN DELETED d ON (i.id_osoby = d.id_osoby)
GO

BEGIN TRAN t1
	UPDATE osoby SET nazwisko='X'
	SELECT * FROM osoby
	SELECT * FROM nazwiska
ROLLBACK TRAN t1

/***************** PRZYKLAD 3 ******************/

CREATE TRIGGER dbo.trp ON etaty FOR UPDATE
AS
	UPDATE etaty
		SET pensja = ROUND(pensja,2)
		WHERE id_etatu IN ( SELECT i.id_etatu FROM inserted i )
		AND NOT pensja = ROUND(pensja,2)
GO

UPDATE etaty SET pensja = 1.2567 WHERE id_etatu = 1

SELECT * FROM etaty

/***************** PRZYKLAD 4 ******************/

ALTER TABLE firmy ADD nip VARCHAR(20) NULL, nip_bk VARCHAR(20) NULL

CREATE TRIGGER dbo.trf ON firmy FOR UPDATE
AS
	IF UPDATE(nip)
	UPDATE firmy SET NIP_BK = REPLACE( nip, '-', '' )
		WHERE nazwa_skr IN ( SELECT i.nazwa_skr FROM inserted i )
GO

UPDATE firmy SET nip='XX-YY-ZZ'

select * from firmy