using System.Text.Json.Serialization;

namespace Lager.Dtos;

[JsonDerivedType(typeof(Artikel), typeDiscriminator: nameof(Artikel))]
[JsonDerivedType(typeof(Kleidungsstück), typeDiscriminator: nameof(Kleidungsstück))]
[JsonDerivedType(typeof(Jacke), typeDiscriminator: nameof(Jacke))]
[JsonDerivedType(typeof(Jeans), typeDiscriminator: nameof(Jeans))]
[JsonDerivedType(typeof(Schuhe), typeDiscriminator: nameof(Schuhe))]
public class Artikel
{
    public string ArtikelId { get; init; } = Guid.NewGuid().ToString();
    public required int Breite { get; set; }
    public required int Höhe { get; set; }
    public required int Tiefe { get; set; }

    public string? EingelagertInId { get; set; }
}
