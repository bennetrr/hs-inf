namespace GarageDoor.States;

public class Locked(Controller controller) : State
{
    private static Locked? _instance;
    private readonly Controller _controller = controller;

    public static State Enter(Controller controller)
    {
        if (_instance == null || controller != _instance._controller)
        {
            _instance = new Locked(controller);
        }

        controller.ChangeState(_instance);
        return _instance;
    }

    public override void StartUnlock()
    {
        AwaitingCombination.Enter(_controller);
    }
}
