using System.Diagnostics;

namespace AlarmClock;

public class AlarmClock : SettableClock
{
    public int AlarmHour { get; private set; }
    public int AlarmMinute { get; private set; }
    public bool AlarmEnabled { get; private set; }

    private IAlarmListener? _alarmListener;

    public void SetAlarmTime(int hour, int minute, IAlarmListener listener)
    {
        if (hour is < 0 or >= 24)
        {
            throw new ArgumentOutOfRangeException(nameof(hour), "Hour must be between 0 and 24.");
        }

        if (minute is < 0 or >= 60)
        {
            throw new ArgumentOutOfRangeException(nameof(minute), "Minute must be between 0 and 60.");
        }

        // Precondition listener is not null is checked by the compiler

        AlarmHour = hour;
        AlarmMinute = minute;
        _alarmListener = listener;

        Debug.Assert(AlarmHour == hour, "AlarmHour was not set correctly");
        Debug.Assert(AlarmMinute == minute, "AlarmMinute was not set correctly");
        Debug.Assert(_alarmListener == listener, "AlarmListener was not set correctly");
    }

    public void AlarmOn()
    {
        if (_alarmListener is null)
        {
            throw new InvalidOperationException("AlarmListener is not set. Please set the alarm time first.");
        }

        AlarmEnabled = true;
        Debug.Assert(AlarmEnabled, "AlarmEnabled should be true after calling AlarmOn");
    }

    public void AlarmOff()
    {
        AlarmEnabled = false;
        Debug.Assert(!AlarmEnabled, "AlarmEnabled should be false after calling AlarmOff");
    }

    public override void Tick()
    {
        base.Tick();

        if (AlarmEnabled && Hour == AlarmHour && Minute == AlarmMinute)
        {
            _alarmListener?.Alarm();
        }

        // TODO: How to check this?
        Debug.Assert(true, "_alarmListener.Alarm() sollte aufgerufen werden, wenn der Wecker klingelt");
    }
}
