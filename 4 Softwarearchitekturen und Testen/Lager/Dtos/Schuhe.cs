namespace Lager.Dtos;

public class Schuhe : Artikel
{
    public required int Schuhgröße { get; set; }
    public required string Obermaterial { get; set; }
    public required string Absatzform { get; set; }
}
