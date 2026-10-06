import org.junit.jupiter.api.Test;

import java.util.Calendar;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TimeDisplayTest {
    @Test
    public void testMidnight() {
        // Arrange
        ITimeProvider timeProvider = new MockTimeProvider(0, 0, 0, Calendar.AM);
        TimeDisplay timeDisplay = new TimeDisplay(timeProvider);

        // Act
        String result = timeDisplay.getCurrentTimeAsHtmlFragment();

        // Assert
        assertEquals("<span class=\"tinyBoldText\">Midnight</span>", result);
    }
}
