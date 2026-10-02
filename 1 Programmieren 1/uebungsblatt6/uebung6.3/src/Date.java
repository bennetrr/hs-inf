public class Date {
    private final int day;
    private final int month;
    private final int year;

    public Date(int month, int day, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }

    public Date(String month, int day, int year) {
        this(
                switch (month) {
                    case "Januar" -> 1;
                    case "Februar" -> 2;
                    case "März" -> 3;
                    case "April" -> 4;
                    case "Mai" -> 5;
                    case "Juni" -> 6;
                    case "Juli" -> 7;
                    case "August" -> 8;
                    case "September" -> 9;
                    case "Oktober" -> 10;
                    case "November" -> 11;
                    case "Dezember" -> 12;
                    default -> throw new IllegalArgumentException("Invalid month: " + month);
                },
                day,
                year
        );
    }

    public Date(int month, int year) {
        this(month, 1, year);
    }

    public int getDay() {
        return day;
    }

    public int getMonth() {
        return month;
    }

    public int getYear() {
        return year;
    }

    @Override
    public String toString() {
        return "Month: " + month + " Day: " + day + " Year: " + year;
    }

    public String getDate(int format) {
        String[] monat = {"", "Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "November", "Dezember"};

        return switch (format) {
            case 1 -> "Month: " + month + " Day: " + day + " Year: " + year;

            case 2 -> "Day:" + day + " Month:" + monat[month] + " Year: " + year;

            default -> "Day:" + day + " Month: " + month + " Year: " + year;
        };
    }
}
