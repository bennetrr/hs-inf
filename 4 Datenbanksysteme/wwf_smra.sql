-- Aufgabe 2
DROP DATABASE IF EXISTS wwf_smra;
CREATE DATABASE wwf_smra CHARSET utf8mb4 COLLATE utf8mb4_general_ci;
USE wwf_smra;

-- Create tables
-- Flugzeugtypen
CREATE TABLE buchungsklassen
(
    name VARCHAR(100) PRIMARY KEY NOT NULL
);

CREATE TABLE flugzeugtypen
(
    modellbezeichnung  VARCHAR(10) PRIMARY KEY NOT NULL,
    hersteller         VARCHAR(100)            NOT NULL,
    maxBetriebsstunden INT                     NOT NULL
);

CREATE TABLE flugzeugtyp_buchungsklassen
(
    platzangebot        INT          NOT NULL,

    buchungsklassenname VARCHAR(100) NOT NULL,
    modellbezeichnung   VARCHAR(10)  NOT NULL,

    PRIMARY KEY (buchungsklassenname, modellbezeichnung),
    FOREIGN KEY (buchungsklassenname) REFERENCES buchungsklassen (name),
    FOREIGN KEY (modellbezeichnung) REFERENCES flugzeugtypen (modellbezeichnung)
);

-- Flugzeuge
CREATE TABLE flugzeuge
(
    kennzeichen                  VARCHAR(10) PRIMARY KEY NOT NULL,
    indienststellung             DATE                    NOT NULL,
    betriebsstunden_gesamt       DOUBLE                  NOT NULL,
    betriebsstunden_seit_wartung DOUBLE                  NOT NULL,
    ist_außer_dienst_gestellt    BOOL DEFAULT FALSE      NOT NULL,

    modellbezeichnung            VARCHAR(10)             NOT NULL,

    FOREIGN KEY (modellbezeichnung) REFERENCES flugzeugtypen (modellbezeichnung)
);

CREATE TABLE merkmale
(
    name VARCHAR(100) PRIMARY KEY NOT NULL
);

CREATE TABLE flugzeug_merkmale
(
    flugzeugkennzeichen VARCHAR(10)  NOT NULL,
    name                VARCHAR(100) NOT NULL,

    PRIMARY KEY (flugzeugkennzeichen, name),
    FOREIGN KEY (flugzeugkennzeichen) REFERENCES flugzeuge (kennzeichen),
    FOREIGN KEY (name) REFERENCES merkmale (name)
);

-- Flughäfen
CREATE TABLE flughäfen
(
    kürzel            VARCHAR(3) PRIMARY KEY NOT NULL,
    bezeichnung       VARCHAR(100)           NOT NULL, -- Wegen Aufgabe 3 hinzugefügt
    flughafensteuer   DECIMAL(10, 2)         NOT NULL,
    sicherheitsgebühr DECIMAL(10, 2)         NOT NULL,
    adresse           VARCHAR(100)           NOT NULL,
    zeitzone          VARCHAR(6)             NOT NULL
);

CREATE TABLE flughäfen_in_der_nähe
(
    kürzel             VARCHAR(3) NOT NULL,
    kürzel_in_der_nähe VARCHAR(3) NOT NULL,
    distanz            DOUBLE     NOT NULL,

    PRIMARY KEY (kürzel, kürzel_in_der_nähe),
    FOREIGN KEY (kürzel) REFERENCES flughäfen (kürzel),
    FOREIGN KEY (kürzel_in_der_nähe) REFERENCES flughäfen (kürzel)
);

-- Flüge
CREATE TABLE flugverbindungen
(
    flugnummer              VARCHAR(10) PRIMARY KEY                        NOT NULL,
    abflugzeit              TIME                                           NOT NULL,
    ankunftszeit            TIME                                           NOT NULL,
    länge_der_flugstrecke   DOUBLE                                         NOT NULL,
    wochentage              SET ('mo', 'di', 'mi', 'do', 'fr', 'sa', 'so') NOT NULL,
    kerosinzuschlag         DECIMAL(10, 2)                                 NOT NULL,

    flugzeugtyp             VARCHAR(10)                                    NOT NULL,
    flughafenkürzel_abflug  VARCHAR(3)                                     NOT NULL,
    flughafenkürzel_ankunft VARCHAR(3)                                     NOT NULL,

    FOREIGN KEY (flugzeugtyp) REFERENCES flugzeugtypen (modellbezeichnung),
    FOREIGN KEY (flughafenkürzel_abflug) REFERENCES flughäfen (kürzel),
    FOREIGN KEY (flughafenkürzel_ankunft) REFERENCES flughäfen (kürzel)
);

CREATE TABLE flüge
(
    datum                DATE        NOT NULL,
    flugnummer           VARCHAR(10) NOT NULL,
    flugzeug_kennzeichen VARCHAR(10) NOT NULL,

    PRIMARY KEY (flugnummer, datum),
    FOREIGN KEY (flugnummer) REFERENCES flugverbindungen (flugnummer),
    FOREIGN KEY (flugzeug_kennzeichen) REFERENCES flugzeuge (kennzeichen)
);

CREATE TABLE flug_buchungsklassen
(
    freie_plätze        INT          NOT NULL,

    buchungsklassenname VARCHAR(100) NOT NULL,
    flugnummer          VARCHAR(10)  NOT NULL,
    datum               DATE         NOT NULL,

    PRIMARY KEY (buchungsklassenname, flugnummer, datum),
    FOREIGN KEY (buchungsklassenname) REFERENCES buchungsklassen (name),
    FOREIGN KEY (flugnummer, datum) REFERENCES flüge (flugnummer, datum)
);

-- Buchungen
CREATE TABLE kunden
(
    kundennummer INT AUTO_INCREMENT PRIMARY KEY NOT NULL
);

CREATE TABLE tarife
(
    id                  INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    flugkosten          DECIMAL(10, 2)                 NOT NULL,
    name                VARCHAR(100)                   NOT NULL,

    buchungsklassenname VARCHAR(100)                   NOT NULL,
    flugnummer          VARCHAR(10)                    NOT NULL,

    FOREIGN KEY (buchungsklassenname) REFERENCES buchungsklassen (name),
    FOREIGN KEY (flugnummer) REFERENCES flugverbindungen (flugnummer)
);

CREATE TABLE buchungen
(
    buchungsnummer INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    -- gesamtkosten wird in einer View dynamisch berechnet

    kundennummer   INT                            NOT NULL,
    tarif_id       INT                            NOT NULL,
    flugnummer     VARCHAR(10)                    NOT NULL,
    flugdatum      DATE                           NOT NULL,

    FOREIGN KEY (kundennummer) REFERENCES kunden (kundennummer),
    FOREIGN KEY (tarif_id) REFERENCES tarife (id),
    FOREIGN KEY (flugnummer, flugdatum) REFERENCES flüge (flugnummer, datum)
);

-- Create views
CREATE VIEW tarif_gesamtkosten AS
SELECT t.id                                                                                              AS tarif_id,
       t.flugnummer,
       v.flughafenkürzel_abflug,
       v.flughafenkürzel_ankunft,
       fa.bezeichnung                                                                                    AS bezeichnung_abflug,
       fb.bezeichnung                                                                                    AS bezeichnung_ankunft,
       t.flugkosten + v.kerosinzuschlag + fa.flughafensteuer + fa.sicherheitsgebühr + fb.flughafensteuer AS gesamtkosten
FROM tarife t
         JOIN flugverbindungen v ON t.flugnummer = v.flugnummer
         JOIN flughäfen fa ON v.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen fb ON v.flughafenkürzel_ankunft = fb.kürzel;

CREATE VIEW buchung_gesamtkosten AS
SELECT t.*
FROM buchungen
         JOIN tarif_gesamtkosten t ON buchungen.tarif_id = t.tarif_id;

-- Add data
-- Flughäfen
INSERT INTO flughäfen
(kürzel, bezeichnung, flughafensteuer, sicherheitsgebühr, adresse, zeitzone)
VALUES ('NUE', 'Nürnberg', 30, 20, 'Flughafenstraße 100, 90411 Nürnberg, Deutschland', '+01:00'),
       ('MUC', 'München', 30, 25, 'Nordallee 25, 85356 München-Flughafen, Deutschland', '+01:00'),
       ('STR', 'Stuttgart', 30, 20, 'Flughafenstraße 32, 70629 Stuttgart, Deutschland', '+01:00'),
       ('FRA', 'Frankfurt', 30, 25, 'Hugo-Eckener-Ring, 60549 Frankfurt am Main, Deutschland', '+01:00'),
       ('TXL', 'Berlin-Tegel', 30, 20, 'Zufahrt zum Flughafen Tegel, 13405 Berlin, Deutschland', '+01:00'),
       ('CDG', 'Paris-Charles De Gaulle', 35, 25, '95700 Roissy-en-France, France', '+01:00'),
       ('LHR', 'London-Heathrow', 40, 30, 'Hounslow TW6 1SD, United Kingdom', '+00:00'),
       ('LCY', 'London-City', 40, 30, 'Hartmann Rd, London E16 2PX, United Kingdom', '+00:00'),
       ('SFO', 'San Francisco', 30, 50, 'San Francisco, CA 94128, United States', '-08:00');


INSERT INTO flughäfen_in_der_nähe
    (kürzel, kürzel_in_der_nähe, distanz)
VALUES ('NUE', 'MUC', 166),
       ('STR', 'FRA', 202),
       ('LHR', 'LCY', 103);

-- Flugzeugtypen
INSERT INTO buchungsklassen
    (name)
VALUES ('Economy'),
       ('Business'),
       ('First');

INSERT INTO flugzeugtypen
    (hersteller, modellbezeichnung, maxBetriebsstunden)
VALUES ('Airbus', 'A321', 50000),
       ('Airbus', 'A340-600', 60000),
       ('Boeing', '747-400', 50000),
       ('Boeing', '737-300', 45000),
       ('Bombardier', 'CRJ900', 55000);

INSERT INTO flugzeugtyp_buchungsklassen
    (modellbezeichnung, buchungsklassenname, platzangebot)
VALUES ('A321', 'Economy', 190),
       ('A340-600', 'Economy', 238),
       ('A340-600', 'Business', 60),
       ('A340-600', 'First', 8),
       ('747-400', 'Economy', 270),
       ('747-400', 'Business', 66),
       ('747-400', 'First', 16),
       ('737-300', 'Economy', 127),
       ('CRJ900', 'Economy', 86);

-- Flugzeuge
INSERT INTO flugzeuge
(kennzeichen, modellbezeichnung, indienststellung, betriebsstunden_gesamt, betriebsstunden_seit_wartung)
VALUES ('D-ABYZ', 'A321', '2005-04-09', 12345, 643),
       ('D-CDUX', 'A321', '2005-04-09', 15223, 804),
       ('D-BAXY', 'A321', '2001-03-27', 45632, 231),
       ('D-EFST', 'A340-600', '2013-02-02', 4102, 998),
       ('D-GHQR', 'A340-600', '2015-10-05', 2023, 654),
       ('D-IKOP', '747-400', '2002-03-04', 45632, 821),
       ('D-BORD', '737-300', '2003-08-10', 9854, 678),
       ('D-LMNA', 'CRJ900', '2013-03-08', 1432, 70);

INSERT INTO merkmale
    (name)
VALUES ('WLAN'),
       ('Satellitentelefon');

INSERT INTO flugzeug_merkmale
    (flugzeugkennzeichen, name)
VALUES ('D-EFST', 'WLAN'),
       ('D-EFST', 'Satellitentelefon'),
       ('D-GHQR', 'WLAN'),
       ('D-IKOP', 'WLAN'),
       ('D-IKOP', 'Satellitentelefon');

-- Flüge
INSERT INTO flugverbindungen
(flugnummer, abflugzeit, ankunftszeit, länge_der_flugstrecke, wochentage, kerosinzuschlag, flugzeugtyp,
 flughafenkürzel_abflug, flughafenkürzel_ankunft)
VALUES ('WWF 925', '09:40', '10:30', 0, 'mo,di,mi,do,fr', 20, 'A321', 'NUE', 'FRA'),
       ('WWF 926', '12:00', '13:10', 0, 'mo,di,mi,do,fr', 10, 'A321', 'FRA', 'NUE'),
       ('WWF 929', '09:40', '10:30', 0, 'sa,so', 10, 'CRJ900', 'NUE', 'FRA'),
       ('WWF 310', '06:45', '08:00', 0, 'mo,di,mi,do,fr', 10, 'A321', 'NUE', 'TXL'),
       ('WWF 312', '09:15', '10:30', 0, 'mo,di,mi,do,fr', 10, 'A321', 'TXL', 'NUE'),
       ('WWF 4756', '13:05', '14:05', 0, 'mo,di,mi,do,fr,sa,so', 20, 'A340-600', 'MUC', 'LHR'),
       ('WWF 9488', '16:00', '17:20', 0, 'mo,di,mi,do,fr', 20, '737-300', 'MUC', 'LCY'),
       ('WWF 4210', '16:00', '17:20', 0, 'mo,mi,fr', 20, 'A340-600', 'MUC', 'CDG'),
       ('WWF 5210', '17:50', '21:00', 0, 'mo,mi,fr', 40, 'A340-600', 'CDG', 'SFO'),
       ('WWF 4711', '10:00', '13:50', 0, 'di,do', 40, '747-400', 'MUC', 'SFO');

INSERT INTO tarife
    (flugnummer, buchungsklassenname, name, flugkosten)
VALUES ('WWF 925', 'Economy', 'Normaltarif', 190),
       ('WWF 925', 'Economy', 'Frühbucher', 140),
       ('WWF 925', 'Economy', 'Last Minute', 100),


       ('WWF 926', 'Economy', 'Normaltarif', 190),
       ('WWF 926', 'Economy', 'Frühbucher', 140),
       ('WWF 926', 'Economy', 'Last Minute', 100),


       ('WWF 929', 'Economy', 'Normaltarif', 190),
       ('WWF 929', 'Economy', 'Frühbucher', 140),
       ('WWF 929', 'Economy', 'Last Minute', 100),


       ('WWF 310', 'Economy', 'Normaltarif', 210),
       ('WWF 310', 'Economy', 'Frühbucher', 165),
       ('WWF 310', 'Economy', 'Last Minute', 120),


       ('WWF 312', 'Economy', 'Normaltarif', 210),
       ('WWF 312', 'Economy', 'Frühbucher', 165),
       ('WWF 312', 'Economy', 'Last Minute', 120),


       ('WWF 4756', 'Economy', 'Normaltarif', 240),
       ('WWF 4756', 'Economy', 'Frühbucher', 210),
       ('WWF 4756', 'Economy', 'Last Minute', 160),

       ('WWF 4756', 'Business', 'Normaltarif', 470),
       ('WWF 4756', 'Business', 'Frühbucher', 390),

       ('WWF 4756', 'First', 'Normaltarif', 690),
       ('WWF 4756', 'First', 'Frühbucher', 590),


       ('WWF 4210', 'Economy', 'Normaltarif', 240),
       ('WWF 4210', 'Economy', 'Frühbucher', 210),
       ('WWF 4210', 'Economy', 'Last Minute', 160),

       ('WWF 4210', 'Business', 'Normaltarif', 490),
       ('WWF 4210', 'Business', 'Frühbucher', 400),

       ('WWF 4210', 'First', 'Normaltarif', 700),
       ('WWF 4210', 'First', 'Frühbucher', 600),


       ('WWF 5210', 'Economy', 'Normaltarif', 350),
       ('WWF 5210', 'Economy', 'Frühbucher', 300),
       ('WWF 5210', 'Economy', 'Last Minute', 290),

       ('WWF 5210', 'Business', 'Normaltarif', 690),
       ('WWF 5210', 'Business', 'Frühbucher', 630),

       ('WWF 5210', 'First', 'Normaltarif', 810),
       ('WWF 5210', 'First', 'Frühbucher', 750),


       ('WWF 4711', 'Economy', 'Normaltarif', 610),
       ('WWF 4711', 'Economy', 'Frühbucher', 540),
       ('WWF 4711', 'Economy', 'Last Minute', 480),

       ('WWF 4711', 'Business', 'Normaltarif', 1050),
       ('WWF 4711', 'Business', 'Frühbucher', 890),
       ('WWF 4711', 'Business', 'Last Minute', 950),

       ('WWF 4711', 'First', 'Normaltarif', 1820),
       ('WWF 4711', 'First', 'Frühbucher', 1500),


       ('WWF 9488', 'Economy', 'Normaltarif', 240),
       ('WWF 9488', 'Economy', 'Frühbucher', 210),
       ('WWF 9488', 'Economy', 'Last Minute', 160);

INSERT INTO flüge
    (flugnummer, datum, flugzeug_kennzeichen)
VALUES ('WWF 925', '2025-05-22', 'D-ABYZ'),
       ('WWF 926', '2025-05-23', 'D-CDUX'),
       ('WWF 929', '2025-05-24', 'D-LMNA'),
       ('WWF 310', '2025-05-25', 'D-CDUX'),
       ('WWF 312', '2025-05-26', 'D-BAXY'),
       ('WWF 4756', '2025-05-27', 'D-EFST'),
       ('WWF 9488', '2025-05-28', 'D-BORD'),
       ('WWF 4210', '2025-05-29', 'D-GHQR'),
       ('WWF 5210', '2025-05-30', 'D-EFST'),
       ('WWF 4711', '2025-05-31', 'D-IKOP');

INSERT INTO flug_buchungsklassen
    (flugnummer, datum, buchungsklassenname, freie_plätze)
VALUES ('WWF 310', '2025-05-25', 'Economy', 190),
       ('WWF 312', '2025-05-26', 'Economy', 190),
       ('WWF 4210', '2025-05-29', 'Economy', 238),
       ('WWF 4210', '2025-05-29', 'Business', 60),
       ('WWF 4210', '2025-05-29', 'First', 8),
       ('WWF 4711', '2025-05-31', 'Economy', 270),
       ('WWF 4711', '2025-05-31', 'Business', 66),
       ('WWF 4711', '2025-05-31', 'First', 16),
       ('WWF 4756', '2025-05-27', 'Economy', 238),
       ('WWF 4756', '2025-05-27', 'Business', 60),
       ('WWF 4756', '2025-05-27', 'First', 8),
       ('WWF 5210', '2025-05-30', 'Economy', 238),
       ('WWF 5210', '2025-05-30', 'Business', 60),
       ('WWF 5210', '2025-05-30', 'First', 8),
       ('WWF 925', '2025-05-22', 'Economy', 190),
       ('WWF 926', '2025-05-23', 'Economy', 190),
       ('WWF 929', '2025-05-24', 'Economy', 86),
       ('WWF 9488', '2025-05-28', 'Economy', 127);

-- Aufgabe 3
-- Flugzeuge aktualisieren
UPDATE flugzeuge SET indienststellung = '2010-04-09' WHERE kennzeichen = 'D-ABYZ';
UPDATE flugzeuge SET indienststellung = '2010-04-09' WHERE kennzeichen = 'D-CDUX';
UPDATE flugzeuge SET indienststellung = '2006-03-27' WHERE kennzeichen = 'D-BAXY';
UPDATE flugzeuge SET indienststellung = '2012-02-02' WHERE kennzeichen = 'D-EFST';
UPDATE flugzeuge SET indienststellung = '2014-10-05' WHERE kennzeichen = 'D-GHQR';
UPDATE flugzeuge SET indienststellung = '2007-03-04' WHERE kennzeichen = 'D-IKOP';
UPDATE flugzeuge SET indienststellung = '2008-08-10' WHERE kennzeichen = 'D-BORD';
UPDATE flugzeuge SET indienststellung = '2012-03-08' WHERE kennzeichen = 'D-LMNA';

-- (01) Kürzel, Bezeichnung und Zeitzone aller Flughäfen, geordnet nach Bezeichnung
CREATE VIEW abfrage01 AS
SELECT kürzel, bezeichnung, zeitzone
FROM flughäfen
ORDER BY bezeichnung;

-- (02) Kennzeichen aller Flugzeuge, die nicht vom Hersteller Boeing stammen, geordnet nach Kennzeichen
CREATE VIEW abfrage02 AS
SELECT kennzeichen
FROM flugzeuge
WHERE modellbezeichnung NOT IN (SELECT modellbezeichnung FROM flugzeugtypen WHERE hersteller = 'Boeing')
ORDER BY kennzeichen;

-- (03) Hersteller, Modell und Kennzeichen aller unterschiedlichen Flugzeuge mit mindestens einem Ausstattungsmerkmal,
--      geordnet nach Hersteller, Modell, Kennzeichen
CREATE VIEW abfrage03 AS
SELECT t.hersteller, t.modellbezeichnung, f.kennzeichen
FROM flugzeuge AS f
         JOIN flugzeugtypen AS t ON f.modellbezeichnung = t.modellbezeichnung
WHERE f.kennzeichen IN (SELECT flugzeugkennzeichen FROM flugzeug_merkmale)
ORDER BY t.hersteller, t.modellbezeichnung, f.kennzeichen;

-- (04) Anzahl von Flugzeugen mit Satellitentelefon
CREATE VIEW abfrage04 AS
SELECT COUNT(*)
FROM flugzeug_merkmale
WHERE (name = 'Satellitentelefon');

-- (05) Gesamtanzahl von Flugzeugen pro Hersteller, geordnet nach Herstellername
CREATE VIEW abfrage05 AS
SELECT t.hersteller, COUNT(*)
FROM flugzeuge AS f
         JOIN flugzeugtypen AS t ON f.modellbezeichnung = t.modellbezeichnung
GROUP BY t.hersteller
ORDER BY t.hersteller;

-- (06) Hersteller und Modell derjenigen Flugzeugtypen, die nur auf einer einzigen Verbindung eingesetzt werden,
--      geordnet nach Hersteller, Model
CREATE VIEW abfrage06 AS
SELECT hersteller, modellbezeichnung
FROM flugzeugtypen
WHERE (SELECT COUNT(*) FROM flugverbindungen WHERE modellbezeichnung = flugzeugtyp) = 1
ORDER BY hersteller, modellbezeichnung;

-- (07) Hersteller, Modell und Gesamtzahl an Sitzplätzen aller Flugzeugtypen mit mindestens 150 Plätzen,
--      geordnet nach Hersteller, Modell
CREATE OR REPLACE VIEW abfrage07 AS
SELECT t.hersteller, t.modellbezeichnung, SUM(b.platzangebot) AS gesamtanzahl
FROM flugzeugtypen AS t
         JOIN flugzeugtyp_buchungsklassen AS b ON t.modellbezeichnung = b.modellbezeichnung
WHERE (SELECT SUM(platzangebot) from flugzeugtyp_buchungsklassen WHERE modellbezeichnung = b.modellbezeichnung) >= 150
GROUP BY t.hersteller, t.modellbezeichnung
ORDER BY t.hersteller, modellbezeichnung;

-- (08) Start- und Zielflughafen (ohne Duplikate) aller Flugverbindungen, die mindestens 250 € (ohne Steuern und Gebühren)
--      pro Platz kosten (Spalten: Flugnummer, Bezeichnung Start- bzw. Zielflughafen, Mindestpreis;
--      geordnet nach Bezeichnung Startflughafen, Bezeichnung Zielflughafen. Achtung: Bezeichnung Flughafen, nicht Kürzel)

-- Die Frage wurde so ausgelegt, dass mindestens ein Tarif des Fluges über 250 € kostet und der kleinste Preis,
-- der über 250 € liegt, zurückgegeben wird
CREATE VIEW abfrage08 AS
SELECT f.flugnummer,
       ha.bezeichnung AS bezeichung_startflughafen,
       hb.bezeichnung AS bezeichnung_endflughafen,
       MIN(t.flugkosten)
FROM flugverbindungen AS f
         JOIN tarife AS t ON f.flugnummer = t.flugnummer
         JOIN flughäfen AS ha ON f.flughafenkürzel_abflug = ha.kürzel
         JOIN flughäfen AS hb ON f.flughafenkürzel_ankunft = hb.kürzel
# WHERE t.flugkosten >= 250
WHERE (SELECT MIN(flugkosten) FROM tarife WHERE flugnummer = f.flugnummer ) >= 250
GROUP BY f.flugnummer, ha.bezeichnung, hb.bezeichnung
ORDER BY ha.bezeichnung, hb.bezeichnung;

-- (09) Hersteller, Modell und Kennzeichen aller zwischen 5 und 10 Jahre alten Flugzeuge, geordnet nach Kennzeichen
CREATE VIEW abfrage09 AS
SELECT t.hersteller, t.modellbezeichnung, f.kennzeichen
FROM flugzeuge AS f
         JOIN flugzeugtypen AS t ON f.modellbezeichnung = t.modellbezeichnung
WHERE f.indienststellung BETWEEN DATE_SUB(CURDATE(), INTERVAL 10 YEAR) AND DATE_SUB(CURDATE(), INTERVAL 5 YEAR)
ORDER BY t.hersteller, t.modellbezeichnung, f.kennzeichen;

-- (10) Kürzel, Bezeichnung und Zusatzkosten des oder der Flughäfen mit den niedrigsten Zusatzkosten
--      (Steuer plus Sicherheitsgebühr), geordnet nach Bezeichnung Flughafen
CREATE VIEW abfrage10 AS
SELECT f.kürzel, f.bezeichnung, f.flughafensteuer + f.sicherheitsgebühr AS zusatzkosten
FROM flughäfen AS f
WHERE (SELECT MIN(flughafensteuer + sicherheitsgebühr) FROM flughäfen) = f.flughafensteuer + f.sicherheitsgebühr
ORDER BY f.bezeichnung;

-- (11) Hersteller, Modell und Kennzeichen des oder der Flugzeuge ohne irgendein spezielles Ausstattungsmerkmal,
--      geordnet nach Hersteller, Modell, Kennzeichen
CREATE VIEW abfrage11 AS
SELECT t.hersteller, t.modellbezeichnung, f.kennzeichen
FROM flugzeuge AS f
         JOIN flugzeugtypen AS t ON f.modellbezeichnung = t.modellbezeichnung
WHERE f.kennzeichen NOT IN (SELECT flugzeugkennzeichen FROM flugzeug_merkmale)
ORDER BY t.hersteller, t.modellbezeichnung, f.kennzeichen;

-- (12) Die Gesamtpreise, d.h. einschließlich Steuer, Sicherheitsgebühr und Kerosinzuschlag,
--      aller Flugverbindungen ab Frankfurt oder München (mit dem zugehörigen Ziel) mit dem Normaltarif der Economy-Klasse
CREATE VIEW abfrage12 AS
SELECT gk.flugnummer,
       gk.flughafenkürzel_abflug AS kürzel_abflug,
       gk.flughafenkürzel_ankunft,
       gk.gesamtkosten           AS kürzel_ankunft
FROM tarif_gesamtkosten AS gk
         JOIN tarife AS t ON gk.tarif_id = t.id
WHERE (gk.flughafenkürzel_abflug = 'MUC' OR gk.flughafenkürzel_abflug = 'FRA')
  AND t.buchungsklassenname = 'Economy'
  AND t.name = 'Normaltarif';

-- (13) Sämtliche Flughäfen mit der Anzahl der dort beginnenden und der Anzahl der dort endenden Flugverbindungen,
--      geordnet nach Flughafen-Kürzel (Achtung: Die Zahl 0 muss auch als „0“ angezeigt werden und nicht als „NULL“)
CREATE VIEW abfrage13 AS
SELECT h.kürzel,
       (SELECT COUNT(*) FROM flugverbindungen AS f WHERE f.flughafenkürzel_abflug = h.kürzel)  AS abflüge,
       (SELECT COUNT(*) FROM flugverbindungen AS f WHERE f.flughafenkürzel_ankunft = h.kürzel) AS ankünfte
FROM flughäfen AS h;

-- (14) Hersteller, Modell und Kennzeichen der Maschine(-n) mit den wenigsten noch verbleibenden Betriebsstunden
--      bis zur maximal zulässigen Zahl von Betriebsstunden des zugehörigen Flugzeugtyps
CREATE VIEW abfrage14 AS
SELECT t.hersteller,
       t.modellbezeichnung,
       f.kennzeichen,
       t.maxBetriebsstunden - f.betriebsstunden_gesamt AS verbleibende_betriebsstunden
FROM flugzeuge AS f
         JOIN flugzeugtypen AS t ON t.modellbezeichnung = f.modellbezeichnung
WHERE (t.maxBetriebsstunden - f.betriebsstunden_gesamt) = (SELECT MIN(t.maxBetriebsstunden - f.betriebsstunden_gesamt)
                                                           FROM flugzeuge AS f
                                                                    JOIN flugzeugtypen AS t ON t.modellbezeichnung = f.modellbezeichnung);

-- (15) Die günstigsten reinen Flugkosten (ohne Steuern, Gebühren und Zuschläge) zwischen allen Paaren von Flughäfen
--      mit mindestens einer Direktverbindung (Spalten: von, nach, günstigster Preis; von bzw. nach sind die Bezeichnung
--      der Flughäfen, nicht die Kürzel), sortiert zunächst nach von (Bezeichnung), nach (Bezeichnung)
CREATE VIEW abfrage15 AS
SELECT fa.bezeichnung AS von, fb.bezeichnung AS nach, MIN(t.flugkosten) AS günstigster_preis
FROM flugverbindungen AS fv
         JOIN tarife t on fv.flugnummer = t.flugnummer
         JOIN flughäfen fa on fv.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen fb on fv.flughafenkürzel_ankunft = fb.kürzel
GROUP BY fa.bezeichnung, fb.bezeichnung
ORDER BY fa.bezeichnung, fb.bezeichnung;

-- (16) Die Gesamtflugzeit für jede Flugverbindung mit Flugnummer [a], Bezeichnung Abflugflughafen [b],
--      Bezeichnung Ankunftsflughafen [c], Dauer (in Stunden : Minuten : Sekunden) [d] geordnet nach b,
--      c (Achtung: Zeitzone ist zu beachten!); recherchieren Sie bzgl. Berechnungsmethoden und hilfreichen Funktionen
--      des MySQL-Servers im Internet
CREATE VIEW abfrage16 AS
SELECT fv.flugnummer,
       fa.bezeichnung AS bezeichnung_abflug,
       fb.bezeichnung AS bezeichnung_ankunft,
       SEC_TO_TIME(TIMESTAMPDIFF(
               SECOND,
               fv.abflugzeit,
               IF(
                       CONVERT_TZ(fv.ankunftszeit, fb.zeitzone, fa.zeitzone) < fv.abflugzeit,
                       DATE_ADD(CONVERT_TZ(fv.ankunftszeit, fb.zeitzone, fa.zeitzone), INTERVAL 1 DAY),
                       CONVERT_TZ(fv.ankunftszeit, fb.zeitzone, fa.zeitzone)
               )
                   )) AS dauer
FROM flugverbindungen AS fv
         JOIN flughäfen fa ON fv.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen fb ON flughafenkürzel_ankunft = fb.kürzel
ORDER BY fa.bezeichnung, fb.bezeichnung;

-- (17) Alle Flugverbindungen mit Abflug- und Ankunftszeit von München nach entweder London-City oder einem dazu
--      benachbarten Flughafen mit Flugnummer [a], Bezeichnung Abflugflughafen [b], Bezeichnung Ankunftsflughafen [c],
--      Abflugzeit [d] und Ankunftszeit [e]
CREATE VIEW abfrage17 AS
SELECT fv.flugnummer,
       fa.bezeichnung AS bezeichnung_abflug,
       fb.bezeichnung AS bezeichnung_ankunft,
       fv.abflugzeit,
       fv.ankunftszeit
FROM flugverbindungen AS fv
         JOIN flughäfen_in_der_nähe AS fidn ON fv.flughafenkürzel_ankunft = fidn.kürzel
    OR fv.flughafenkürzel_ankunft = fidn.kürzel_in_der_nähe
         JOIN flughäfen AS fa ON fv.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen AS fb ON fv.flughafenkürzel_ankunft = fb.kürzel
WHERE fv.flughafenkürzel_abflug = 'MUC'
  AND (fv.flughafenkürzel_ankunft = 'LCY'
    OR fv.flughafenkürzel_ankunft = fidn.kürzel_in_der_nähe OR fv.flughafenkürzel_ankunft = fidn.kürzel);

-- (18) Alle Reisemöglichkeiten von München nach San Francisco mit höchstens einmaligem Umsteigen.
--      Eine Abfrage muss Direktflüge und Flüge mit Zwischenstopp gemäß nachfolgender Tabelle anzeigen.
--      Die Spalten „Abflug“ und „Ankunft“ beinhalten die zugehörigen Ankunfts- bzw. Abflugzeiten
--      (Tipp: Über den SQL-Befehl „UNION“ können Sie die Ergebnisse von zwei SELECT-Befehlen in einer Tabelle zusammenfassen
CREATE VIEW abfrage18 AS
SELECT fa.bezeichnung  AS bezeichnung_abflug,
       fa.bezeichnung  AS bezeichnung_umstieg,
       fb.bezeichnung  AS bezeichnung_ankunft,
       fv.abflugzeit   AS abflugszeit,
       fv.abflugzeit   AS abflugzeit_umstieg,
       fv.ankunftszeit AS ankunftszeit
FROM flugverbindungen AS fv
         JOIN flughäfen AS fa ON fv.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen AS fb ON fv.flughafenkürzel_ankunft = fb.kürzel
WHERE fa.kürzel = 'MUC'
  AND fb.kürzel = 'SFO'
UNION
SELECT fa.bezeichnung   AS bezeichnung_abflug,
       fb.bezeichnung   AS bezeichnung_umstieg,
       fc.bezeichnung   AS bezeichnung_ankunft,
       fva.abflugzeit   AS abflugszeit,
       fvb.abflugzeit   AS abflugzeit_umstieg,
       fvb.ankunftszeit AS ankunftszeit
FROM flugverbindungen AS fva
         JOIN flugverbindungen AS fvb ON fva.flughafenkürzel_ankunft = fvb.flughafenkürzel_abflug
         JOIN flughäfen AS fa ON fva.flughafenkürzel_abflug = fa.kürzel
         JOIN flughäfen AS fb on fvb.flughafenkürzel_abflug = fb.kürzel
         JOIN flughäfen AS fc on fvb.flughafenkürzel_ankunft = fc.kürzel
WHERE fva.flughafenkürzel_abflug = 'MUC'
  AND fvb.flughafenkürzel_ankunft = 'SFO'
  AND fvb.flughafenkürzel_abflug != 'SFO';

-- Aufgabe 4
-- (01) Mit Außerdienststellung (Löschung) eines Flugzeugs wird auch die Information gelöscht,
--      welche Ausstattungsmerkmale es besitzt (ALTER TABLE)
ALTER TABLE flugzeug_merkmale
    DROP FOREIGN KEY flugzeug_merkmale_ibfk_1;

ALTER TABLE flugzeug_merkmale
    ADD CONSTRAINT flugzeug_merkmale_ibfk_1
        FOREIGN KEY (flugzeugkennzeichen) REFERENCES flugzeuge (kennzeichen)
            ON DELETE CASCADE;

-- (02) Für einen Flug dürfen nur Maschinen des für die Flugverbindung vorgesehenen Typs eingesetzt werden (TRIGGER)
DELIMITER $$

CREATE TRIGGER flug_typ
    BEFORE INSERT
    ON flüge
    FOR EACH ROW
BEGIN
    IF NOT EXISTS(SELECT TRUE
                  FROM flugverbindungen AS fv
                           JOIN flugzeuge AS fz ON fv.flugzeugtyp = fz.modellbezeichnung
                  WHERE new.flugzeug_kennzeichen = fz.kennzeichen
                    AND fv.flugnummer = new.flugnummer) THEN
        SIGNAL SQLSTATE '40999'
            SET MESSAGE_TEXT =
                    'Für einen Flug dürfen nur Maschinen des für die Flugverbindung vorgesehenen Typs eingesetzt werden!';
    END IF;
END$$

DELIMITER ;

-- (03) Bei Neuanlage eines Flugs wird die Anzahl freier Plätze pro Klasse mit der Maximalzahl an Plätzen der
--      entsprechenden Klasse im verwendeten Flugzeugtyp initialisiert (TRIGGER)
DELIMITER $$

CREATE TRIGGER flug_plätze
    AFTER INSERT
    ON flüge
    FOR EACH ROW
BEGIN
    INSERT INTO flug_buchungsklassen
        (freie_plätze, buchungsklassenname, flugnummer, datum)
    SELECT b.platzangebot, b.buchungsklassenname, new.flugnummer, new.datum
    FROM flugzeugtyp_buchungsklassen AS b
    WHERE (SELECT f.modellbezeichnung FROM flugzeuge AS f WHERE f.kennzeichen = new.flugzeug_kennzeichen) =
          b.modellbezeichnung;
END$$

DELIMITER ;

-- (04) Schreiben Sie eine gespeicherte PROZEDUR, die Flugnummer, Abflug- und Ankunftszeit und noch verfügbare
--      Plätze in der Economy-Klasse aller Flüge zwischen zwei Flughäfen an einem bestimmten Datum ermittelt.
--      Die Kürzel der beiden Flughäfen und das Flugdatum werden als Parameter übergeben
DELIMITER $$

CREATE PROCEDURE flüge_zwischen_flughäfen(flughafen_a VARCHAR(3), flughafen_b VARCHAR(3), flugdatum DATE)
BEGIN
    SELECT f.flugnummer, fv.abflugzeit, fv.ankunftszeit, b.freie_plätze
    FROM flüge AS f
             JOIN flugverbindungen AS fv ON f.flugnummer = fv.flugnummer
             JOIN flug_buchungsklassen AS b ON f.flugnummer = b.flugnummer AND f.datum = b.datum
    WHERE ((fv.flughafenkürzel_abflug = flughafen_a AND fv.flughafenkürzel_ankunft = flughafen_b)
        OR (fv.flughafenkürzel_abflug = flughafen_b AND fv.flughafenkürzel_ankunft = flughafen_a))
      AND f.datum = flugdatum
      AND b.buchungsklassenname = 'Economy';
END $$

DELIMITER ;

-- (05) Erstellen Sie eine FUNKTION, die für eine Flugverbindung die Gesamtflugdauer in Minuten ermittelt
--      (in Anlehnung an Abfrage 16 von Aufgabenblatt 3). Die Kennung der Flugverbindung wird als Parameter übergeben
DELIMITER $$

CREATE FUNCTION gesamtflugzeit(flugnummer VARCHAR(10)) RETURNS INT
    DETERMINISTIC
BEGIN
    DECLARE result INT;

    SELECT TIME_TO_SEC(dauer) / 60 INTO result FROM abfrage16 AS g WHERE g.flugnummer = flugnummer;

    RETURN result;
END $$

DELIMITER ;
