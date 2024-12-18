package catlink;

import javax.swing.*;
import java.awt.*;

public class BackgroundPanel extends JPanel {
    private ImageIcon img;

    public BackgroundPanel() {
        img = new ImageIcon(".\\GameImages\\background.jpg");
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(img.getImage(), 0, 0, this.getWidth(), this.getHeight(), this);
    }
}
