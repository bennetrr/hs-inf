import java.util.Calendar;

public class DefaultTimeProvider implements ITimeProvider {
    public Calendar getTime() {
        return Calendar.getInstance();
    }
}
