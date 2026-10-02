package window.bar;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

/**
 * Klasse für sidebar, wo Buttons und so sind, und topBar (für den schönen Coburg Airlines Satz)
 * Hier sind auch Listeners für diese Buttons
 */

public class BarJPanel {
    private JButton connectionButton;

    private JPanel sidebar;
    private JPanel topBar;

    public BarJPanel() {}

    public JPanel createBarJPanel() {
        sidebar = new JPanel();
        sidebar.setLayout(new GridLayout(6, 1, 0, 10));
        sidebar.setBorder(BorderFactory.createMatteBorder(0, 0, 0, 1, new Color(60, 60, 60)));
        sidebar.setPreferredSize(new Dimension(180, 0));

        connectionButton = makeButton("Connections", sidebar);

        topBar = new JPanel(new BorderLayout());
        topBar.setPreferredSize(new Dimension(0, 60));
        JLabel title = new JLabel("Coburg Airlines");
        title.setFont(new Font("SansSerif", Font.BOLD, 20));
        topBar.add(title, BorderLayout.WEST);

        JPanel barPanel = new JPanel();
        barPanel.add(sidebar, BorderLayout.WEST);
        barPanel.add(topBar, BorderLayout.NORTH);
        return barPanel;
    }

    private JButton makeButton(String label, JPanel panel) {
        JButton btn = new JButton(label);
        btn.setFocusPainted(false);
        btn.setFont(new Font("SansSerif", Font.PLAIN, 14));
        btn.setBorderPainted(false);
        panel.add(btn);
        return btn;
    }

    public void addConnectionsListener(ActionListener listener) {
        connectionButton.addActionListener(listener);
    }

    public JPanel getSidebar() {
        return sidebar;
    }
    public JPanel getTopBar() {
        return topBar;
    }
}