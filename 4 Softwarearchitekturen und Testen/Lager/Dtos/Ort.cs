namespace Lager.Dtos;

public class Ort
{
    public string OrtId { get; } = Guid.NewGuid().ToString();
    public required int X { get; set; }
    public required int Y { get; set; }
    public required int Z { get; set; }
}
