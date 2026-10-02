FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y curl && apt -y clean && rm -rf /var/lib/apt/lists/*
WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
ARG BUILD_CONFIGURATION=Release
WORKDIR /src
COPY ["CloudComputing.Api/CloudComputing.Api.csproj", "CloudComputing.Api/"]
RUN dotnet restore "CloudComputing.Api/CloudComputing.Api.csproj"
COPY . .
WORKDIR "/src/CloudComputing.Api"
RUN dotnet build "CloudComputing.Api.csproj" -c $BUILD_CONFIGURATION -o /app/build

FROM build AS publish
ARG BUILD_CONFIGURATION=Release
RUN dotnet publish "CloudComputing.Api.csproj" -c $BUILD_CONFIGURATION -o /app/publish /p:UseAppHost=false

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENV ASPNETCORE_HTTP_PORTS=80
ENTRYPOINT ["dotnet", "CloudComputing.Api.dll"]
