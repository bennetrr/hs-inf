package window;

import database.DBHelper;
import window.bar.BarJPanel;

import javax.swing.*;
import java.awt.*;


/**
 * AppJFrame - Hauptklasse für Anwendungsfenster
 * verwaltet JFrame und zeigt verschiedene Panels über ein CardLayout an
 */
public class AppJFrame {

    private JFrame frame;
    private CardLayout cardLayout;
    private JPanel cardContainer;

    private ConnectionsJPanel connectionsJPanel;

    public AppJFrame() {
        init();
    }

    private void init() {
        frame = new JFrame();
        cardLayout = new CardLayout();
        cardContainer = new JPanel(cardLayout);

        frame.setTitle("Coburg Airlines");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1000, 600);
        frame.setLocationRelativeTo(null);
        frame.setLayout(new BorderLayout());

        //Connections Panel
        connectionsJPanel = new ConnectionsJPanel();
        cardContainer.add(connectionsJPanel.createConnectionsJPanel(), "connections");

        connectionsListener();

        frame.add(cardContainer);
        frame.setVisible(true);
    }

    public void connectionsListener() {
        sidebarListener(connectionsJPanel.getBarJPanel());

        connectionsJPanel.addInsertListener(e -> {
            String flightNumber = connectionsJPanel.getFlightNumber().getText();
            String departureTime = connectionsJPanel.getDepartureTimeField().getText();
            String arrivalTime = connectionsJPanel.getArrivalTimeField().getText();
            String distance = connectionsJPanel.getDistanceField().getText();
            String weekDays = connectionsJPanel.getWeekDaysField().getText();
            String kerosin = connectionsJPanel.getKerosinField().getText();
            String airplaneType = connectionsJPanel.getAirplaneTypeField().getText();
            String airportDeparture = connectionsJPanel.getAirportDepartureField().getText();
            String airportArrival = connectionsJPanel.getAirportArrivalField().getText();

            DBHelper.insertConnection(
                    flightNumber, departureTime, arrivalTime,
                    distance, weekDays, kerosin,
                    airplaneType, airportDeparture, airportArrival
            );
        });

    }

    public void sidebarListener(BarJPanel sidebarJPanel) {
        sidebarJPanel.addConnectionsListener(e -> {
            cardLayout.show(cardContainer, "connections");
        });
    }

}
