using FluentAssertions;
using PackageVisitor.Products;
using PackageVisitor.Visitors;

namespace PackageVisitor;

public class PackageVisitorTest
{
    [Fact]
    public void TestGetCheapestItemVisitor()
    {
        // Arrange
        var cheapestItem = new FreshVegetable("Salat", 1.85);

        var package = new Package([
            new Package([
                new FreshVegetable("0,5kg Möhren", 3.20),
                new FreshVegetable("1kg Kartoffeln", 5.00),
                cheapestItem,
                new FreshVegetable("Tomaten", 2.50)]),
            new CannedItem("Tomatensoße", 2.32),
            new CannedItem("Feta", 2.99),
            new CannedItem("Erbsen & Möhren", 1.99)]);

        var visitor = new GetCheapestItemVisitor();

        // Act
        package.Accept(visitor);

        // Assert
        visitor.CheapestProduct.Should().Be(cheapestItem);
    }

    [Fact]
    public void TestReducePrizeVisitor()
    {
        // Arrange
        var package = new Package([
            new FreshVegetable("0,5kg Möhren", 3.20),
            new FreshVegetable("1kg Kartoffeln", 5.00),
            new FreshVegetable("Salat", 1.85),
            new FreshVegetable("Tomaten", 2.50),
            new CannedItem("Tomatensoße", 2.32),
            new CannedItem("Feta", 2.99),
            new CannedItem("Erbsen & Möhren", 1.99)]);

        var expected = new Package([
            new FreshVegetable("0,5kg Möhren", 2.95),
            new FreshVegetable("1kg Kartoffeln", 4.75),
            new FreshVegetable("Salat", 1.60),
            new FreshVegetable("Tomaten", 2.25),
            new CannedItem("Tomatensoße", 2.07),
            new CannedItem("Feta", 2.74),
            new CannedItem("Erbsen & Möhren", 1.74)]);

        var visitor = new ReducePrizeVisitor(0.25);

        // Act
        package.Accept(visitor);

        // Assert
        package.Should().BeEquivalentTo(expected);
    }
}
