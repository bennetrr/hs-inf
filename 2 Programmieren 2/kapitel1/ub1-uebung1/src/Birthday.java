import java.text.ParsePosition;
import java.text.SimpleDateFormat;

public class Birthday {
    private final String date;

    public Birthday(String s) throws InvalidBirthdayException {
        checkDay(s);
        date = s;
    }

    public void checkDay(String s) throws InvalidBirthdayException {
        SimpleDateFormat df = new SimpleDateFormat("dd.MM.yyyy");
        df.setLenient(false);
        var parsePosition = new ParsePosition(0);

        var date = df.parse(s, parsePosition);

        if (date == null) {
            throw new InvalidBirthdayException("Falsches Datum: " + s);
        }
    }

    public String toString() {
        return date;
    }
}
