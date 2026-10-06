using PackageVisitor.Visitors;

namespace PackageVisitor.Products;

public interface IProduct
{
    void Accept(IVisitor visitor);
}
