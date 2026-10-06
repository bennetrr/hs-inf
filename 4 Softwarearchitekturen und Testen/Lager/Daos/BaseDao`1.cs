using System.Text.Json;

namespace Lager.Daos;

public abstract class BaseDao<TDto>
{
    private readonly string _jsonFilePath;
    private readonly JsonSerializerOptions _jsonOptions = new()
    {
        WriteIndented = true,
        Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping,
    };

    protected BaseDao(string jsonFilePath)
    {
        _jsonFilePath = jsonFilePath;

        if (!File.Exists(_jsonFilePath))
        {
            Write([]);
        }
    }

    protected List<TDto> Read()
    {
        var json = File.ReadAllText(_jsonFilePath);
        return JsonSerializer.Deserialize<List<TDto>>(json) ?? [];
    }

    protected void Write(List<TDto> dtos)
    {
        var json = JsonSerializer.Serialize(dtos, _jsonOptions);
        File.WriteAllText(_jsonFilePath, json);
    }

    public abstract List<TDto> GetAll();

    public abstract TDto Get(string id);

    public abstract void Add(TDto dto);

    public abstract void AddRange(List<TDto> dtos);

    public abstract void Update(TDto dto);

    public abstract void Delete(TDto dto);

    public abstract void Clear();
}
