import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Calendar;
import java.util.Observable;
import java.util.Observer;

class TimeObservable extends Observable implements ActionListener {
	private Timer timer;
	// 現在時刻を保持するインスタンス変数
	private int hour, min, sec;

	public TimeObservable() {
		// 1秒毎にactionPerformedを呼び出す
		timer = new Timer(1000, this);
		timer.start();
	}

	public void actionPerformed(ActionEvent arg0) {
		this.setValue();
		setChanged();
		notifyObservers();
	}

	void setValue() {
		Calendar cal = Calendar.getInstance();
		hour = cal.get(Calendar.HOUR_OF_DAY);
		min = cal.get(Calendar.MINUTE);
		sec = cal.get(Calendar.SECOND);
	}

	String getValue(int diff) {
		String currentTime = String.format("%02d:%02d:%02d", (hour+diff+24)%24, min, sec);
		return currentTime;
	}
}

class ClockPanel extends JPanel implements Observer {
	private TimeObservable timeObservable;
	private int diff;
	private JLabel timeLabel;
	public ClockPanel(TimeObservable to, String place, int diff) {
		timeObservable = to;
		this.diff = diff;
		timeObservable.addObserver(this);
		timeLabel = new JLabel(to.getValue(diff), JLabel.CENTER);
		this.setLayout(new GridLayout(1, 2));
		this.add(new JLabel(place));
		this.add(timeLabel);
	}
	public void update(Observable o, Object arg) {
		timeLabel.setText(timeObservable.getValue(diff));
	}
}

class ClockFrame extends JFrame {
	public ClockFrame() {
		TimeObservable t = new TimeObservable();
		this.setTitle("Global Clock");
		this.setLayout(new GridLayout(6,1));
		this.add(new ClockPanel(t, "Tokyo", 0));
		this.add(new ClockPanel(t, "Beijing", -1));
		this.add(new ClockPanel(t, "Paris", -8));
		this.add(new ClockPanel(t, "London", -9));
		this.add(new ClockPanel(t, "New York", -14));
		this.add(new ClockPanel(t, "Los Angels", -17));
		this.pack();
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	public static void main(String[] args) {
		new ClockFrame();
	}
}
