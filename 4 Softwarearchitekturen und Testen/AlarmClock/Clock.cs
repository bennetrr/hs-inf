using System.Diagnostics;

namespace AlarmClock;

public class Clock
{
    public int Hour { get; protected set; }
    public int Minute { get; protected set; }
    public int Second { get; protected set; }

    public virtual void Tick()
    {
        Second++;
        if (Second < 60)
        {
            return;
        }

        Second = 0;
        Minute++;
        if (Minute < 60)
        {
            return;
        }

        Minute = 0;
        Hour++;
        if (Hour < 24)
        {
            return;
        }

        Hour = 0;

        Debug.Assert(true, "Zeit wurde um eine Sekunde erhöht"); // TODO: How to check this?
    }
}
