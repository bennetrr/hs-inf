import java.util.Calendar;

public class MockTimeProvider implements ITimeProvider {
    private final int hour;
    private final int minute;
    private final int second;
    private final int amPm;

    public MockTimeProvider(int hour, int minute, int second, int amPm) {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
        this.amPm = amPm;
    }

    public Calendar getTime() {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.HOUR, hour);
        calendar.set(Calendar.MINUTE, minute);
        calendar.set(Calendar.SECOND, second);
        calendar.set(Calendar.AM_PM, amPm);
        return calendar;
    }
}
