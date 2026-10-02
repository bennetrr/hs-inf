import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import javax.swing.*;

import com.formdev.flatlaf.FlatDarkLaf;
import window.AppJFrame;

/**
 * Main Klasse - stellt eine Verbindung zur MySQL(!)-Datenbank her
 * Startet das Hauptfenster AppJFrame
 */


public class Main {
    public static void main(String[] args) throws Exception {
        //Link und alles, ändern falls notwendig, AUCH in DBHelper Klasse!!
        String url = "jdbc:mysql://localhost:3306/wwf_smra";
        String username = "root";
        String password = "test";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            System.out.println("Connected!");
        } catch (SQLException e) {
            System.out.println(":(");
            e.printStackTrace();
        }

        try {
            UIManager.setLookAndFeel(new FlatDarkLaf());
        } catch (Exception ex) {
            System.out.println("Failed to initialize LAF");
        }

        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                AppJFrame frame = new AppJFrame();
            }
        });
    }
}
