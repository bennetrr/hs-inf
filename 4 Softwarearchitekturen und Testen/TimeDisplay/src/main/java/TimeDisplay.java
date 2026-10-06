import java.text.SimpleDateFormat;
import java.util.Calendar;

public class TimeDisplay {
    private final ITimeProvider timeProvider;

    public TimeDisplay() {
        this.timeProvider = new DefaultTimeProvider();
    }

    public TimeDisplay(ITimeProvider timeProvider) {
        this.timeProvider = timeProvider;
    }

    public String getCurrentTimeAsHtmlFragment() {
        Calendar currentTime;

        try {
            currentTime = timeProvider.getTime();
        } catch (Exception e) {
            return e.getMessage();
        }

        String s;

        if (currentTime.get(Calendar.HOUR) == 0 && currentTime.get(Calendar.MINUTE) == 0 && currentTime.get(Calendar.AM_PM) == Calendar.AM)
            s = "Midnight";
        else {
            SimpleDateFormat formatter = new SimpleDateFormat("E hh:mm:ss a");
            s = formatter.format(currentTime.getTime());
        }

        return "<span class=\"tinyBoldText\">" + s + "</span>";
    }
}
