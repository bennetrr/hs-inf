using Lager.Dtos;

namespace Lager.Daos;

public class ArtikelDao(string jsonFilePath) : BaseDao<Artikel>(jsonFilePath)
{
    public override List<Artikel> GetAll()
    {
        return Read();
    }

    public override Artikel Get(string id)
    {
        var artikelList = Read();
        return artikelList.First(a => a.ArtikelId == id);
    }

    public override void Add(Artikel artikel)
    {
        var artikelList = Read();
        artikelList.Add(artikel);
        Write(artikelList);
    }

    public override void AddRange(List<Artikel> artikel)
    {
        var artikelList = Read();
        artikelList.AddRange(artikel);
        Write(artikelList);
    }

    public override void Update(Artikel artikel)
    {
        var artikelList = Read();
        var index = artikelList.FindIndex(a => a.ArtikelId == artikel.ArtikelId);

        if (index < 0)
        {
            throw new InvalidOperationException();
        }

        artikelList[index] = artikel;
        Write(artikelList);
    }

    public override void Delete(Artikel artikel)
    {
        var artikelList = Read();
        artikelList.RemoveAll(a => a.ArtikelId == artikel.ArtikelId);
        Write(artikelList);
    }

    public override void Clear()
    {
        Write([]);
    }
}
