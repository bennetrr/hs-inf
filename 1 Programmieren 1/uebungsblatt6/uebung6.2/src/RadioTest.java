public class RadioTest {
    public static void main(String[] args) {
        testTheRadioClass();
    }

    public static void testTheRadioClass() {
        var radio = new Radio(true, 5, 87.6);
        System.out.println(radio);

        radio.waehleSender(95.3);
        System.out.println(radio);

        radio.aus();
        System.out.println(radio);

        radio.an();
        radio.waehleSender(99.6);
        System.out.println(radio);

        radio.aus();
        System.out.println(radio);
    }
}
