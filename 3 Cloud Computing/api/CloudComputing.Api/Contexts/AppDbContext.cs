using CloudComputing.Api.Models;
using Microsoft.EntityFrameworkCore;

namespace CloudComputing.Api.Contexts;

public class AppDbContext(DbContextOptions<AppDbContext> options) : DbContext(options)
{
    public DbSet<Photo> Photos { get; set; }
}
