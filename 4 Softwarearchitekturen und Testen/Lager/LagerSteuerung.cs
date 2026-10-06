using Lager.Daos;
using Lager.Dtos;

namespace Lager;

public class LagerSteuerung(LagerortDao ortDao, ArtikelDao artikelDao)
{
    public Ort? ErmittleFreienOrt()
    {
        var artikel = artikelDao.GetAll();
        var orte = ortDao.GetAll();
        return orte.Find(o => !artikel.Exists(a => a.EingelagertInId == o.OrtId));
    }
}
