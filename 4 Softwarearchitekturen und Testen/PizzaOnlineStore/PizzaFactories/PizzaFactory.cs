using PizzaOnlineStore.Pizzas;

namespace PizzaOnlineStore.PizzaFactories;

public class PizzaFactory : IPizzaFactory
{
    public Pizza CreatePizza(string pizzaType)
    {
        return pizzaType switch
        {
            "Cheese" => new AlbertoCheesePizza(),
            "Vegetarian" => new AlbertoVegetarianPizza(),
            "Calzone" => new AlbertoCalzonePizza(),
            "Pepperoni" => new AlbertoPepperoniPizza(),
            _ => throw new ArgumentException("Invalid pizza type")
        };
    }
}
