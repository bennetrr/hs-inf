using CloudComputing.Api.Contexts;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace CloudComputing.Api.Controllers;

[ApiController]
[Route("migration")]
public class MigrationController(AppDbContext db) : ControllerBase
{
    [HttpGet]
    public async Task<ActionResult> GetMigrations()
    {
        await db.Database.MigrateAsync();
        return Ok();
    }
}
