using PizzaOnlineStore.Pizzas;

namespace PizzaOnlineStore.PizzaFactories;

public interface IPizzaFactory
{
    Pizza CreatePizza(string pizzaType);
}
