namespace CloudComputing.Api.Dtos;

public class PhotoDto
{
    public string Id { get; init; } = Guid.NewGuid().ToString();

    public required string Name { get; set; }

    public DateTime Created { get; init; } = DateTime.UtcNow;

    public DateTime Updated { get; set; } = DateTime.UtcNow;

    public required UserDto Creator { get; init; }

    public Uri ImageUrl { get; set; } = null!;
}
