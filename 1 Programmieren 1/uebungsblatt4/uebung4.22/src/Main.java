public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
    }

    public static int[][] calculateTable(int[][] array, char cmd) {
        switch (cmd) {
            case 's' -> {
                var newArray = new int[array.length+1][array[0].length+1];

                // Copy the array and calculate the row sums
                for (int i = 0; i < array.length; i++) {
                    int rowSum = 0;
                    for (int j = 0; j < array[0].length; j++) {
                        newArray[i][j] = array[i][j];
                        rowSum += array[i][j];
                    }
                    newArray[i][newArray[0].length-1] = rowSum;
                }

                // Calculate the column sums
                for (int i = 0; i < array[0].length; i++) {
                    int columnSum = 0;

                    for (int[] ints : array) {
                        columnSum += ints[i];
                    }

                    newArray[newArray.length-1][i] = columnSum;
                }

                return newArray;
            }

            case 'i' -> {
                var newArray = new int[array.length][array[0].length];
                int value = 10;

                for (int i = 0; i < newArray.length; i++) {
                    for (int j = 0; j < newArray[0].length; j++) {
                        newArray[i][j] = value++;
                    }
                }

                return newArray;
            }

            case 'r' -> {
                var newArray = new int[array.length][array[0].length];

                for (int i = 0; i < newArray[0].length; i++) {
                    for (int j = 0; j < newArray.length; j++) {
                        if (i == 0) {
                            newArray[j][i] = 0;
                            continue;
                        }

                        newArray[j][i] = array[j][i-1];
                    }
                }

                return newArray;
            }

            default -> throw new Error("Invalid command: " + cmd);
        }
    }
}
