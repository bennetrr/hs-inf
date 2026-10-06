// ReSharper disable RedundantAssignment
// ReSharper disable NotAccessedVariable
using Lager;
using Lager.Daos;
using Lager.Dtos;

// DAOs und Lagersteuerung initialisieren
var artikelDao = new ArtikelDao("../../../artikel.json");
artikelDao.Clear();

var ortDao = new LagerortDao("../../../lagerorte.json");
ortDao.Clear();

var lagerSteuerung = new LagerSteuerung(ortDao, artikelDao);

// Orte initialisieren
for (var x = 1; x <= 5; x++)
{
    for (var y = 1; y <= 2; y++)
    {
        for (var z = 1; z <= 2; z++)
        {
            ortDao.Add(new Ort { X = x, Y = y, Z = z });
        }
    }
}

// Artikel initialisieren
artikelDao.Add(new Schuhe
{
    Breite = 20,
    Höhe = 16,
    Tiefe = 40,
    Absatzform = "Flach",
    Obermaterial = "Gore-Tex",
    Schuhgröße = 49,
    EingelagertInId = lagerSteuerung.ErmittleFreienOrt()?.OrtId
});
artikelDao.Add(new Jacke
{
    Breite = 36,
    Höhe = 5,
    Tiefe = 36,
    Bezeichnung = "Regenjacke",
    Farbe = "Grau/Orange",
    Wassersäule = 20000,
    Kleidergröße = 58,
    EingelagertInId = lagerSteuerung.ErmittleFreienOrt()?.OrtId
});
artikelDao.Add(new Jeans
{
    Breite = 30,
    Höhe = 2,
    Tiefe = 30,
    Bezeichnung = "Jeans",
    Farbe = "Blau",
    Kleidergröße = 32,
    Schrittlänge = 36,
    EingelagertInId = lagerSteuerung.ErmittleFreienOrt()?.OrtId
});

// Neuen Artikel hinzufügen und ID speichern
var artikelId = Guid.NewGuid().ToString();
artikelDao.Add(new Artikel
{
    ArtikelId = artikelId,
    Breite = 20,
    Höhe = 16,
    Tiefe = 40,
    EingelagertInId = lagerSteuerung.ErmittleFreienOrt()?.OrtId
});

// Artikel abrufen
var einArtikel = artikelDao.Get(artikelId);

// Artikel verändern und speichern
einArtikel.Breite = 100;
artikelDao.Update(einArtikel);

// Artikel löschen
artikelDao.Delete(einArtikel);

Environment.Exit(0);
