using Lager.Dtos;

namespace Lager.Daos;

public class LagerortDao(string jsonFilePath) : BaseDao<Ort>(jsonFilePath)
{
    public override List<Ort> GetAll()
    {
        return Read();
    }

    public override Ort Get(string id)
    {
        var ortList = Read();
        return ortList.First(a => a.OrtId == id);
    }

    public override void Add(Ort ort)
    {
        var ortList = Read();
        ortList.Add(ort);
        Write(ortList);
    }

    public override void AddRange(List<Ort> ort)
    {
        var ortList = Read();
        ortList.AddRange(ort);
        Write(ortList);
    }

    public override void Update(Ort ort)
    {
        var ortList = Read();
        var index = ortList.FindIndex(a => a.OrtId == ort.OrtId);

        if (index < 0)
        {
            throw new InvalidOperationException();
        }

        ortList[index] = ort;
        Write(ortList);
    }

    public override void Delete(Ort ort)
    {
        var ortList = Read();
        ortList.RemoveAll(a => a.OrtId == ort.OrtId);
        Write(ortList);
    }

    public override void Clear()
    {
        Write([]);
    }
}
