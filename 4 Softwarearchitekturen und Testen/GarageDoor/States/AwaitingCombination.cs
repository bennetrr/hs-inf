namespace GarageDoor.States;

public class AwaitingCombination(Controller controller) : State
{
    private static AwaitingCombination? _instance;
    private readonly Controller _controller = controller;

    public static State Enter(Controller controller)
    {
        if (_instance == null || controller != _instance._controller)
        {
            _instance = new AwaitingCombination(controller);
        }

        controller.ChangeState(_instance);
        return _instance;
    }

    public override void CombinationEntered()
    {
        Closed.Enter(_controller);
    }

    public override void ErrorEntered()
    {
        Locked.Enter(_controller);
    }
}
