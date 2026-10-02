package window;

import window.bar.BarJPanel;

import javax.swing.*;
import javax.swing.text.DateFormatter;
import java.awt.*;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Date;

/** 
 * ConnectionsJPanel - Klasse für Flugverbindungen, Tabellenänderungen hier
 */

public class ConnectionsJPanel {
    private BarJPanel barJPanel;
    private JPanel connectionsPanel;

    private JTextField flightNumber;
    private JFormattedTextField departureTimeField;
    private JFormattedTextField arrivalTimeField;
    private JTextField distanceField;
    private JTextField weekDaysField;
    private JTextField kerosinField;
    private JTextField airplaneTypeField;
    private JTextField airportDepartureField;
    private JTextField airportArrivalField;

    private JButton insertButton;

    public ConnectionsJPanel() {}

    public JPanel createConnectionsJPanel() {
        connectionsPanel = new JPanel(new BorderLayout());

        barJPanel = new BarJPanel();
        barJPanel.createBarJPanel();

        JPanel connections = new JPanel();
        connections.setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        flightNumber = new JTextField();

        SimpleDateFormat format = new SimpleDateFormat("HH:mm");
        DateFormatter formatter = new DateFormatter(format);
        departureTimeField = new JFormattedTextField(formatter);
        departureTimeField.setValue(new Date());

        arrivalTimeField = new JFormattedTextField(formatter);
        arrivalTimeField.setValue(new Date());

        distanceField = new JTextField();
        weekDaysField = new JTextField();
        kerosinField = new JTextField();
        airplaneTypeField = new JTextField();
        airportDepartureField = new JTextField();
        airportArrivalField = new JTextField();

        insertButton = new JButton("Insert");

        gbc.gridx = 0; gbc.gridy = 0;
        connections.add(new JLabel("Flight Number:"), gbc);
        gbc.gridx = 1; gbc.gridy = 0;
        connections.add(flightNumber, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        connections.add(new JLabel("Departure time:"), gbc);
        gbc.gridx = 1; gbc.gridy = 1;
        connections.add(departureTimeField, gbc);
        gbc.gridx = 0; gbc.gridy = 2;
        connections.add(new JLabel("Arrival time:"), gbc);

        gbc.gridx = 1; gbc.gridy = 2;
        connections.add(arrivalTimeField, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        connections.add(new JLabel("Distance:"), gbc);
        gbc.gridx = 1; gbc.gridy = 3;
        connections.add(distanceField, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        connections.add(new JLabel("Week Days:"), gbc);
        gbc.gridx = 1; gbc.gridy = 4;
        connections.add(weekDaysField, gbc);

        gbc.gridx = 0; gbc.gridy = 5;
        connections.add(new JLabel("Kerosin:"), gbc);
        gbc.gridx = 1; gbc.gridy = 5;
        connections.add(kerosinField, gbc);

        gbc.gridx = 0; gbc.gridy = 6;
        connections.add(new JLabel("Airplane Type:"), gbc);
        gbc.gridx = 1; gbc.gridy = 6;
        connections.add(airplaneTypeField, gbc);

        gbc.gridx = 0; gbc.gridy = 7;
        connections.add(new JLabel("Airport Departure:"), gbc);
        gbc.gridx = 1; gbc.gridy = 7;
        connections.add(airportDepartureField, gbc);

        gbc.gridx = 0; gbc.gridy = 8;
        connections.add(new JLabel("Airport Arrival:"), gbc);
        gbc.gridx = 1; gbc.gridy = 8;
        connections.add(airportArrivalField, gbc);

        gbc.gridx = 1; gbc.gridy = 9;
        connections.add(insertButton, gbc);

        connectionsPanel.add(barJPanel.getSidebar(), BorderLayout.WEST);
        connectionsPanel.add(barJPanel.getTopBar(),  BorderLayout.NORTH);
        connectionsPanel.add(connections, BorderLayout.CENTER);

        return connectionsPanel;

    }

    public void addInsertListener(ActionListener actionListener) {
        insertButton.addActionListener(actionListener);
    }

    public JTextField getFlightNumber() {
        return flightNumber;
    }
    public JTextField getDepartureTimeField() {
        return departureTimeField;
    }
    public JTextField getArrivalTimeField() {
        return arrivalTimeField;
    }
    public JTextField getDistanceField() {
        return distanceField;
    }
    public JTextField getWeekDaysField() {
        return weekDaysField;
    }
    public JTextField getKerosinField() {
        return kerosinField;
    }
    public JTextField getAirplaneTypeField() {
        return airplaneTypeField;
    }
    public JTextField getAirportDepartureField() {
        return airportDepartureField;
    }
    public JTextField getAirportArrivalField() {
        return airportArrivalField;
    }

    public BarJPanel getBarJPanel() {
        return barJPanel;
    }
    public JPanel getConnectionsPanel() {
        return connectionsPanel;
    }
}
