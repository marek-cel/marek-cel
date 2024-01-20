CREATE FUNCTION dbo.ff(@d DATETIME)
RETURNS CHAR(6)
AS
BEGIN
	IF @d IS NULL
		RETURN '<null>'

	RETURN CONVERT( CHAR(6), @d, 112 ) /* 112 - YYYYMMDD */		
END
GO

SELECT e.*, dbo.ff(e.do) AS [mies koncowy]
	FROM etaty e
	WHERE dbo.ff(e.do) NOT LIKE '<%'