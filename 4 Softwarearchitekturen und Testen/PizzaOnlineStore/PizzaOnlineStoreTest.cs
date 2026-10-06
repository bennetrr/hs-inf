using FluentAssertions;

namespace PizzaOnlineStore;

public class PizzaOnlineStoreTest
{
    [Theory]
    [InlineData("Cheese", "Preparing 5 min Cheese Pizza\nBaking 25 min at 350° Cheese\nCut Cheese\nBoxing Cheese\nWe ordered a ----Cheese----")]
    [InlineData("Vegetarian", "Preparing 3 min Vegetarian Pizza\nBaking 20 min at 350° Vegetarian\nCut Vegetarian\nBoxing Vegetarian\nWe ordered a ----Vegetarian----")]
    [InlineData("Calzone", "Preparing 6 min Calzone Pizza\nBaking 30 min at 350° Calzone\nNo Cut Calzone\nChoosing special box for Calzone\nWe ordered a ----Calzone----")]
    [InlineData("Pepperoni", "Preparing 4 min Pepperoni Pizza\nBaking 27 min at 350° Pepperoni\nCut Pepperoni\nBoxing Pepperoni\nWe ordered a ----Pepperoni----")]
    public void TestOrder(string pizzaType, string expected)
    {
        using var output = new StringWriter();
        Console.SetOut(output);
        var store = new PizzaOnlineStore();

        var pizza = store.Order(pizzaType);

        // ReSharper disable once Xunit.XunitTestWithConsoleOutput
        Console.WriteLine($"We ordered a ----{pizza}----");

        output.ToString().Trim().Should().Be(expected);
    }
}
