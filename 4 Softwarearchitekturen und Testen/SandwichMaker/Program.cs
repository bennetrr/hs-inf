using SandwichMaker;

Console.WriteLine(new Bread(new Sandwich()));
Console.WriteLine(new Cheese(new Bread(new Sandwich())));
Console.WriteLine(new Bread(new Meat(new Cheese(new Bread(new Sandwich())))));
Console.WriteLine(new Meat(new Cheese(new Bread(new Sandwich()))));
Console.WriteLine(new Meat(new Cheese(new Butter(new Bread(new Sandwich())))));
