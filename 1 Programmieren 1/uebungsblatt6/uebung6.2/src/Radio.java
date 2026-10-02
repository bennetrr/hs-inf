public class Radio {
    private boolean powerState;
    private int volume;
    private double frequency;

    public Radio(boolean powerState, int volume, double frequency) {
        this.powerState = powerState;
        this.volume = volume < 0 || volume > 10 ? 0 : volume;
        this.frequency = powerState ? (frequency < 85.0 || frequency > 100.0 ? 99.9 : frequency) : 100.0;
    }

    public void an() {
        powerState = true;
    }

    public void aus() {
        powerState = false;
    }

    public void lauter() {
        if (!powerState) {
            return;
        }

        if (volume >= 10) {
            return;
        }

        volume++;
    }

    public void leiser() {
        if (!powerState) {
            return;
        }

        if (volume <= 0) {
            return;
        }

        volume--;
    }

    public void waehleSender(double frequency) {
        if (!powerState) {
            return;
        }

        if (frequency < 85.0 || frequency > 100.0) {
            this.frequency = 99.9;
            return;
        }

        this.frequency = frequency;
    }

    @Override
    public String toString() {
        return "Radio: " + powerState + " Freq= " + frequency + " Laut= " + volume;
    }
}
