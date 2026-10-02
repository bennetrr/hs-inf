using System.ComponentModel.DataAnnotations;

namespace CloudComputing.Api.Models;

public class Photo
{
    [MaxLength(36)]
    public string Id { get; init; } = Guid.NewGuid().ToString();

    public required string Name { get; set; }

    public DateTime Created { get; init; } = DateTime.UtcNow;

    public DateTime Updated { get; set; } = DateTime.UtcNow;

    public required User Creator { get; init; }
}
