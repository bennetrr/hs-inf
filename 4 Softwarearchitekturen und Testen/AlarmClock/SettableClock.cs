using System.Diagnostics;

namespace AlarmClock;

public class SettableClock : Clock
{
    public void SetTime(int hour, int minute)
    {
        if (hour is <= 0 or >= 24)
        {
            throw new ArgumentOutOfRangeException(nameof(hour), "Hour must be between 0 and 24");
        }

        if (minute is <= 0 or >= 60)
        {
            throw new ArgumentOutOfRangeException(nameof(minute), "Minute must be between 0 and 60");
        }

        Hour = hour;
        Minute = minute;
        Second = 0;

        Debug.Assert(Hour == hour, "Hour was not set correctly");
        Debug.Assert(Minute == minute, "Minute was not set correctly");
        Debug.Assert(Second == 0, "Second was not set correctly");
    }
}
