using System;
using System.Collections.Generic;

// Abstract Product
public abstract class Dish
{
    public string Name { get; set; }
    public double BasePrice { get; set; }

    public abstract double GetPrice();
    public abstract string GetDescription();
}

// Concrete Products
public class Steak : Dish
{
    public Steak()
    {
        Name = "Steak";
        BasePrice = 20.0;
    }

    public override double GetPrice() => BasePrice;
    public override string GetDescription() => Name;
}

public class Lobster : Dish
{
    public Lobster()
    {
        Name = "Lobster";
        BasePrice = 30.0;
    }

    public override double GetPrice() => BasePrice;
    public override string GetDescription() => Name;
}

// Factory
public class DishFactory
{
    public static Dish CreateDish(string type)
    {
        return type switch
        {
            "Steak" => new Steak(),
            "Lobster" => new Lobster(),
            _ => throw new ArgumentException("Invalid dish type")
        };
    }
}

//
//

// Abstract Decorator
public abstract class DishDecorator : Dish
{
    protected Dish _dish;

    public DishDecorator(Dish dish)
    {
        _dish = dish;
    }

    public override double GetPrice() => _dish.GetPrice();
    public override string GetDescription() => _dish.GetDescription();
}

// Concrete Decorators
public class ExtraCheese : DishDecorator
{
    public ExtraCheese(Dish dish) : base(dish) { }

    public override double GetPrice() => _dish.GetPrice() + 2.0;
    public override string GetDescription() => _dish.GetDescription() + ", Extra Cheese";
}

public class Sauce : DishDecorator
{
    public Sauce(Dish dish) : base(dish) { }

    public override double GetPrice() => _dish.GetPrice() + 1.5;
    public override string GetDescription() => _dish.GetDescription() + ", Sauce";
}











// Command Interface
public interface ICommand
{
    void Execute();
    void Undo();
}

// Concrete Commands
public class AddToppingCommand : ICommand
{
    private Dish _dish;
    private DishDecorator _topping;

    public AddToppingCommand(Dish dish, DishDecorator topping)
    {
        _dish = dish;
        _topping = topping;
    }

    public void Execute()
    {
        _dish = _topping;
        Console.WriteLine($"Added: {_topping.GetDescription()}");
    }

    public void Undo()
    {
        // Logic to remove the topping
        Console.WriteLine($"Removed: {_topping.GetDescription()}");
    }
}

// Invoker
public class Order
{
    private readonly Stack<ICommand> _commands = new Stack<ICommand>();

    public void ExecuteCommand(ICommand command)
    {
        command.Execute();
        _commands.Push(command);
    }

    public void UndoCommand()
    {
        if (_commands.Count > 0)
        {
            var command = _commands.Pop();
            command.Undo();
        }
    }
}