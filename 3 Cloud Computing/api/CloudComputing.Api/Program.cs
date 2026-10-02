using System.Security.Claims;
using Amazon;
using Amazon.Runtime;
using Amazon.S3;
using Clerk.Net.DependencyInjection;
using CloudComputing.Api.Config;
using CloudComputing.Api.Contexts;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using Wemogy.AspNet.Startup;
using Wemogy.Configuration;

var options = new StartupOptions();
var builder = WebApplication.CreateBuilder(args);

options.AddOpenApi("v0.0.1");

builder.Services.AddDefaultSetup(options);

// Database
builder.Services
    .AddDbContext<AppDbContext>(opt => opt
        .UseMySql(
            builder.Configuration.GetConnectionString("Db"),
            new MariaDbServerVersion(new Version(11, 4, 4)))
        .LogTo(Console.WriteLine, builder.Environment.IsDevelopment() ? LogLevel.Debug : LogLevel.Warning)
        .EnableSensitiveDataLogging(builder.Environment.IsDevelopment())
        .EnableDetailedErrors(builder.Environment.IsDevelopment()));

// S3
var s3Config = builder.Configuration.GetRequiredSection("S3");
builder.Services.Configure<S3Config>(s3Config);

if (s3Config["ServiceUrl"] != null)
{
    builder.Services
        .AddSingleton<IAmazonS3>(new AmazonS3Client(
            new BasicAWSCredentials(s3Config.GetRequiredValue("AccessKey"), s3Config.GetRequiredValue("SecretKey")),
            new AmazonS3Config
            {
                ServiceURL = s3Config.GetRequiredValue("ServiceUrl"),
                ForcePathStyle = true
            }));
}
else
{
    builder.Services.AddSingleton<IAmazonS3>(new AmazonS3Client(RegionEndpoint.EUCentral1));
}

// Authorization
builder.Services.AddClerkApiClient(opt =>
{
    opt.SecretKey = builder.Configuration.GetSection("Authentication").GetRequiredValue("ClerkSecretKey");
});

builder.Services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
    .AddJwtBearer(x =>
    {
        // Authority is the URL of your clerk instance
        x.Authority = builder.Configuration.GetSection("Authentication").GetRequiredValue("Authority");
        x.TokenValidationParameters = new TokenValidationParameters
        {
            // Disable audience validation as we are not using it
            ValidateAudience = false,
            NameClaimType = ClaimTypes.NameIdentifier
        };
        x.Events = new JwtBearerEvents
        {
            // Additional validation for AZP claim
            OnTokenValidated = context =>
            {
                var azp = context.Principal?.FindFirstValue("azp");

                // AuthorizedParty is the base URL of your frontend.
                if (string.IsNullOrEmpty(azp) || !azp.Equals(builder.Configuration.GetSection("Authentication").GetRequiredValue("AppBaseUrl")))
                {
                    context.Fail("AZP Claim is invalid or missing");
                }

                return Task.CompletedTask;
            }
        };
    });

var app = builder.Build();

app.UseDefaultSetup(app.Environment, options);

app.Run();
