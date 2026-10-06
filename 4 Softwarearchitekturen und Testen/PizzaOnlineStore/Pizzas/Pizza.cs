namespace PizzaOnlineStore.Pizzas;

public abstract class Pizza(string name, List<string> toppings, int preparationTime, int bakingTime, int bakingTemp)
{
    public virtual void Prepare()
    {
        Console.WriteLine($"Preparing {preparationTime} min {name} Pizza");
    }

    public virtual void Bake()
    {
        Console.WriteLine($"Baking {bakingTime} min at {bakingTemp}° {name}");
    }

    public virtual void Cut()
    {
        Console.WriteLine($"Cut {name}");
    }

    public virtual void Box()
    {
        Console.WriteLine($"Boxing {name}");
    }

    public override string ToString()
    {
        return name;
    }
}
