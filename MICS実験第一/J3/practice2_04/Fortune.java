import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class HelloFrame extends JFrame implements ActionListener {
	private JLabel label;

	public HelloFrame() {
		this.setSize(300, 200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JButton b = new JButton("Hello");
		this.add(b, BorderLayout.SOUTH);
		label = new JLabel(" ", JLabel.CENTER);
		this.add(label, BorderLayout.CENTER);
		b.addActionListener(this);
		this.setVisible(true);
	}
	public void actionPerformed(ActionEvent ev) {
		double r = Math.random();
		if (r > 0.7) {
			label.setText("good");
		} else if (r <= 0.2) {
			label.setText("bad");
		} else {
			label.setText("so so");
		}
	}
	public static void main(String[] args) {
		new HelloFrame();
	}
}

