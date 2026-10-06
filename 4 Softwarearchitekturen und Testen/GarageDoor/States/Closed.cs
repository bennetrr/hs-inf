namespace GarageDoor.States;

public class Closed(Controller controller) : State
{
    private static Closed? _instance;
    private readonly Controller _controller = controller;

    public static State Enter(Controller controller)
    {
        if (_instance == null || controller != _instance._controller)
        {
            _instance = new Closed(controller);
        }

        controller.ChangeState(_instance);
        return _instance;
    }

    public override void Open()
    {
        Opened.Enter(_controller);
    }

    public override void Lock()
    {
        Locked.Enter(_controller);
    }
}
