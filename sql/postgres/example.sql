-- Tworzy tabelę contacts z kolumną id jako klucz główny
-- kolumna id jest generowana automatycznie jako autoinkrementująca
-- kolumna name jest typu VARCHAR o maksymalnej długości 100 znaków
-- kolumna e_mail jest typu VARCHAR o maksymalnej długości 100 znaków
-- kolumna phone jest typu VARCHAR o maksymalnej długości 15 znaków
-- kolumna added_at jest typu TIMESTAMP i domyślnie ustawia się na aktualny czas
CREATE TABLE contacts (
    id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    fname VARCHAR(100),
    lname VARCHAR(100),
    email VARCHAR(100),
    phone VARCHAR(15),
    added TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Wstawia przykładowe dane do tabeli contacts
INSERT INTO contacts (fname, lname, email, phone) VALUES
    ('James T.'  , 'Kirk'    , 'kirk@starfleet.org'    , '+44 111 222 333'),
    ('Jean-Luc'  , 'Picard'  , 'picard@starfleet.org'  , '+44 123 123 123'),
    ('Katherine' , 'Janeway' , 'janeway@starfleet.org' , '+44 555 111 222');

-- Wybiera wszystkie dane z tabeli contacts
SELECT * FROM contacts;

-- Usuwa tabelę contacts
DROP TABLE contacts;