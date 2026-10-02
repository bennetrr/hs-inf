package database;

import javax.swing.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * DBHelper Klasse - Hilfsklasse, stellt Methoden für den Datenbankzugriff bereit
 * insertConnection - Funktion, die eine neue Flugverbindung einfügt
 */

public class DBHelper {
    //Daten für Datenbankzugriff, hier ändern falls notwendig!!
    private static final String URL = "jdbc:mysql://localhost:3306/wwf_smra";
    private static final String USERNAME = "root";
    private static final String PASSWORD = "test";

    public static void insertConnection(
            String flightNumber, String departureTime, String arrivalTime,
            String distance, String weekDays, String kerosin,
            String airplaneType, String airportDeparture, String airportArrival
    ) {
        String sql = "INSERT INTO flugverbindungen (flugnummer, abflugzeit, ankunftszeit, länge_der_flugstrecke, wochentage, kerosinzuschlag, flugzeugtyp, flughafenkürzel_abflug, flughafenkürzel_ankunft) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

        try (Connection conn = DriverManager.getConnection(URL, USERNAME, PASSWORD);
             java.sql.PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, flightNumber);
            stmt.setString(2, departureTime);
            stmt.setString(3, arrivalTime);
            stmt.setString(4, distance);
            stmt.setString(5, weekDays);
            stmt.setString(6, kerosin);
            stmt.setString(7, airplaneType);
            stmt.setString(8, airportDeparture);
            stmt.setString(9, airportArrival);

            stmt.executeUpdate();
            System.out.println("Inserted!!");
            JOptionPane.showMessageDialog(null, "Inserted!!!11");
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "Error: " + e.getMessage());
        }
    }
}
