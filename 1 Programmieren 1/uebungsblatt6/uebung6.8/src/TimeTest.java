class TimeTest {
    public static void testTheTimeClass() {
        var time = new Time(12, 0, 55);

        for (int i = 0; i < 100; i++) {
            time.tick();
            System.out.println("Current time" + time);
        }
    }
}
