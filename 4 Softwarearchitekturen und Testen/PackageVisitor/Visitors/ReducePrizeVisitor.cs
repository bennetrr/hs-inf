using PackageVisitor.Products;

namespace PackageVisitor.Visitors;

public class ReducePrizeVisitor(double reduceBy) : IVisitor
{
    public void VisitPackage(Package package)
    {
        package.Products.ForEach(product => product.Accept(this));
    }

    public void VisitItem(Item item)
    {
        item.Price -= reduceBy;
    }
}
