namespace PizzaOnlineStore.Pizzas;

public class MakkaroniCalzonePizza() : Pizza("Calzone", [], 6, 30, 350)
{
    public override void Cut()
    {
        Console.WriteLine("No Cut Calzone");
    }

    public override void Box()
    {
        Console.WriteLine("Choosing special box for Calzone");
    }
}
