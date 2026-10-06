using PackageVisitor.Visitors;

namespace PackageVisitor.Products;

public abstract class Item(string name, double price) : IProduct
{
    public string Name { get; } = name;

    public double Price { get; set; } = price;

    public void Accept(IVisitor visitor)
    {
        visitor.VisitItem(this);
    }
}
