namespace Lager.Dtos;

public class Kleidungsstück : Artikel
{
    public required int Kleidergröße { get; set; }
    public required string Bezeichnung { get; set; }
    public required string Farbe { get; set; }
}
