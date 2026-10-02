using Amazon.S3;
using Amazon.S3.Model;
using CloudComputing.Api.Config;
using CloudComputing.Api.Contexts;
using CloudComputing.Api.Dtos;
using CloudComputing.Api.Models;
using CloudComputing.Api.Requests;
using Mapster;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Options;

namespace CloudComputing.Api.Controllers;

[ApiController]
[Route("photos")]
public class PhotoController(AppDbContext db, IAmazonS3 s3, IOptions<S3Config> s3Config) : ControllerBase
{
    [HttpGet]
    public async Task<ActionResult<IEnumerable<PhotoDto>>> GetPhotos()
    {
        var result = await db.Photos.ToListAsync();
        var dtoTasks = result.Select(async x =>
        {
            var dto = x.Adapt<PhotoDto>();

            var preSignedUrl = await s3.GetPreSignedURLAsync(new GetPreSignedUrlRequest
            {
                BucketName = s3Config.Value.BucketName,
                Key = dto.Id,
                Expires = DateTime.Now.AddMinutes(10),
                Protocol = Protocol.HTTP
            });

            dto.ImageUrl = new Uri(preSignedUrl);
            return dto;
        });

        return await Task.WhenAll(dtoTasks);
    }

    [HttpPost]
    [Authorize]
    public async Task<ActionResult<PhotoDto>> UploadPhoto([FromForm] UploadPhotoRequest request)
    {
        var photo = new Photo
        {
            Name = request.Name,
            Creator = new User { Id = Guid.NewGuid().ToString() }
        };

        await s3.PutObjectAsync(new PutObjectRequest
        {
            BucketName = s3Config.Value.BucketName,
            Key = photo.Id,
            ContentType = request.Image.ContentType,
            InputStream = request.Image.OpenReadStream()
        });

        await db.Photos.AddAsync(photo);
        await db.SaveChangesAsync();

        var preSignedUrl = await s3.GetPreSignedURLAsync(new GetPreSignedUrlRequest
        {
            BucketName = s3Config.Value.BucketName,
            Key = photo.Id,
            Expires = DateTime.Now.AddMinutes(10),
            Protocol = Protocol.HTTP
        });

        var dto = photo.Adapt<PhotoDto>();
        dto.ImageUrl = new Uri(preSignedUrl);

        return CreatedAtAction(
            nameof(UploadPhoto),
            new { id = photo.Id },
            dto);
    }

    [HttpGet("search")]
    public async Task<ActionResult<IEnumerable<PhotoDto>>> SearchPhotos([FromQuery] string q)
    {
        var result = await db.Photos
            .Where(x => x.Name.ToLower().Contains(q.ToLower()))
            .ToListAsync();

        var dtoTasks = result.Select(async x =>
        {
            var dto = x.Adapt<PhotoDto>();

            var preSignedUrl = await s3.GetPreSignedURLAsync(new GetPreSignedUrlRequest
            {
                BucketName = s3Config.Value.BucketName,
                Key = dto.Id,
                Expires = DateTime.Now.AddMinutes(10),
                Protocol = Protocol.HTTP
            });

            dto.ImageUrl = new Uri(preSignedUrl);
            return dto;
        });

        return await Task.WhenAll(dtoTasks);
    }
}
