namespace CloudComputing.Api.Requests;

public class UploadPhotoRequest
{
    public required IFormFile Image { get; set; }

    public required string Name { get; set; }
}
