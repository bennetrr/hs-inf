namespace GarageDoor.States;

public class Opened(Controller controller) : State
{
    private static Opened? _instance;
    private readonly Controller _controller = controller;

    public static State Enter(Controller controller)
    {
        if (_instance == null || controller != _instance._controller)
        {
            _instance = new Opened(controller);
        }

        controller.ChangeState(_instance);
        return _instance;
    }

    public override void Close()
    {
        Closed.Enter(_controller);
    }
}
