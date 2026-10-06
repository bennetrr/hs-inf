using PackageVisitor.Visitors;

namespace PackageVisitor.Products;

public class Package(List<IProduct> products) : IProduct
{
    public List<IProduct> Products { get; } = products;

    public void Accept(IVisitor visitor)
    {
        visitor.VisitPackage(this);
    }
}
