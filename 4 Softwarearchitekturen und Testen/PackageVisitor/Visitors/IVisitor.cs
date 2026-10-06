using PackageVisitor.Products;

namespace PackageVisitor.Visitors;

public interface IVisitor
{
    void VisitPackage(Package package);

    void VisitItem(Item item);
}
