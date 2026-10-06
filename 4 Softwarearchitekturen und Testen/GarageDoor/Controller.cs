using GarageDoor.States;

namespace GarageDoor;

public class Controller
{
    private const string Combination = "1234";
    private readonly TextReader _in;
    private readonly TextWriter _out;
    private State? _state;

    public Controller(TextReader? input = null, TextWriter? output = null)
    {
        _in = input ?? Console.In;
        _out = output ?? Console.Out;

        Closed.Enter(this);
    }

    public void ChangeState(State state)
    {
        _state = state;
    }

    public void Run()
    {
        while (true)
        {
            switch (_state)
            {
                case Closed:
                {
                    _out.WriteLine("The door is closed\nOptions: 'open',  'lock', 'exit':");
                    var opt = _in.ReadLine();

                    switch (opt)
                    {
                        case "open":
                        {
                            _state.Open();
                            break;
                        }

                        case "lock":
                        {
                            _state.Lock();
                            break;
                        }

                        case "exit":
                        {
                            return;
                        }

                        default:
                        {
                            _out.WriteLine("Invalid option");
                            break;
                        }
                    }

                    break;
                }

                case Opened:
                {
                    _out.WriteLine("The door is opened\nOptions: 'close', 'exit':");
                    var opt = _in.ReadLine();

                    switch (opt)
                    {
                        case "close":
                        {
                            _state.Close();
                            break;
                        }

                        case "exit":
                        {
                            return;
                        }

                        default:
                        {
                            _out.WriteLine("Invalid option");
                            break;
                        }
                    }

                    break;
                }

                case Locked:
                {
                    _out.WriteLine("The door is locked\nOptions: 'start unlock', 'exit':");
                    var opt = _in.ReadLine();

                    switch (opt)
                    {
                        case "start unlock":
                        {
                            _state.StartUnlock();
                            break;
                        }

                        case "exit":
                        {
                            return;
                        }

                        default:
                        {
                            _out.WriteLine("Invalid option");
                            break;
                        }
                    }

                    break;
                }

                case AwaitingCombination:
                {
                    _out.WriteLine("Enter the combination:");
                    var combination = _in.ReadLine();

                    if (combination == Combination)
                    {
                        _state.CombinationEntered();
                        break;
                    }

                    _state.ErrorEntered();
                    break;
                }
            }
        }
    }
}
