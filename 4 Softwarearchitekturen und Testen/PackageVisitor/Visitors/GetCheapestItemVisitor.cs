using PackageVisitor.Products;

namespace PackageVisitor.Visitors;

public class GetCheapestItemVisitor : IVisitor
{
    public Item? CheapestProduct { get; private set; }

    public void VisitPackage(Package package)
    {
        package.Products.ForEach(product => product.Accept(this));
    }

    public void VisitItem(Item item)
    {
        if (CheapestProduct == null || item.Price < CheapestProduct.Price)
        {
            CheapestProduct = item;
        }
    }
}
