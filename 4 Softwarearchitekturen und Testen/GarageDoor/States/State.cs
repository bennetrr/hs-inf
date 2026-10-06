namespace GarageDoor.States;

public abstract class State
{
    public virtual void Close()
    {
        throw new NotSupportedException();
    }

    public virtual void CombinationEntered()
    {
        throw new NotSupportedException();
    }

    public virtual void ErrorEntered()
    {
        throw new NotSupportedException();
    }

    public virtual void Lock()
    {
        throw new NotSupportedException();
    }

    public virtual void Open()
    {
        throw new NotSupportedException();
    }

    public virtual void StartUnlock()
    {
        throw new NotSupportedException();
    }
}
