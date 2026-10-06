using PizzaOnlineStore.PizzaFactories;
using PizzaOnlineStore.Pizzas;

namespace PizzaOnlineStore;

public class PizzaOnlineStore
{
    public Pizza Order(string pizzaType)
    {
        var pizza = new PizzaFactory().CreatePizza(pizzaType);

        pizza.Prepare();
        pizza.Bake();
        pizza.Cut();
        pizza.Box();

        return pizza;
    }
}
