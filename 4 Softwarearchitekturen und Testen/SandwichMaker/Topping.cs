namespace SandwichMaker;

public abstract class Topping(ISandwich decorated, double cost, string name) : ISandwich
{
    public double Cost => decorated.Cost + cost;

    public string Toppings => $"{decorated.Toppings} with {name}";

    public override string ToString()
    {
        return $"{Toppings} (Price: {Cost:F2} €)";
    }
}
