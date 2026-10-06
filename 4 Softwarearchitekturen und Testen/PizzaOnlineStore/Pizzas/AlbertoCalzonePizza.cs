namespace PizzaOnlineStore.Pizzas;

public class AlbertoCalzonePizza() : Pizza("Calzone", ["Tomato Sauce", "Mozzarella Cheese", "Champions", "Ham"], 6, 30, 350)
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
