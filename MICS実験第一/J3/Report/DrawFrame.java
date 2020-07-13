import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

// 描画した図形を記録する Figure クラス（継承して利用する）
class Figure {
              protected int x, y, width, height;
              protected Color color;
              public Figure(int x, int y, int w, int h, Color c) {
                            this.x = x; this.y = y;                            //this.x, this.y はインスタンス変数
                            width = w; height = h;                            //ローカル変数で同名の変数がある場合は、this
                            color = c;                                                                      //を付けると、インスタンス変数を指す
              }
              public void setSize(int w, int h) {
                            width = w; height = h;
              }
              public void setLocation(int x, int y) {
                            this.x = x; this.y = y;
              }
              public void reshape(int x1, int y1, int x2, int y2) {
                            int newx = Math.min(x1, x2);
                            int newy = Math.min(y1, y2);
                            int neww = Math.abs(x1 - x2);
                            int newh = Math.abs(y1 - y2);
                            setLocation(newx, newy);
                            setSize(neww, newh);
              }
              public void draw(Graphics g) {}
}

/*********************
 * 種々の図形用のクラス
 *********************/
class RectangleFigure extends Figure {
              public RectangleFigure(int x, int y, int w, int h, Color c) {
                            super(x, y, w, h, c);
                            // 引数付きのコンストラクタは継承されないので、コンストラクタを定義
                            // superで親のコンストラクタを呼び出すだけ
              }
              public void draw(Graphics g) {
                            g.setColor(color);
                            g.drawRect(x, y, width, height);
              }
}

class LineFigure extends Figure {
              public LineFigure(int x, int y, int w, int h, Color c) {
                            super(x, y, w, h, c);
              }
              public void draw(Graphics g) {
                            g.setColor(color);
                            g.drawLine(x, y, width + x, height + y);
              }
              public void reshape(int x1, int y1, int x2, int y2) {
                            setLocation(x, y);
                            setSize(x2 - x1, y2 - y1);
              }
}

class OvalFigure extends Figure {
              public OvalFigure(int x, int y, int w, int h, Color c) {
                            super(x, y, w, h, c);
              }
              public void draw(Graphics g) {
                            g.setColor(color);
                            g.drawOval(x, y, width, height);
              }
}

class PolylineFigure extends Figure {
              private ArrayList<Integer> xPoints;
              private ArrayList<Integer> yPoints;
              public PolylineFigure(int x, int y, int w, int h, Color c) {
                            super(x, y, w, h, c);
                            xPoints = new ArrayList<Integer>();
                            yPoints = new ArrayList<Integer>();
                            xPoints.add(x);
                            yPoints.add(y);
              }
              public void draw(Graphics g) {
                            int[] arr_xPoints = new int[xPoints.size()];
                            int[] arr_yPoints = new int[yPoints.size()];
                            for (int i = 0; i < xPoints.size(); i++) {
                                          arr_xPoints[i] = xPoints.get(i);
                                          arr_yPoints[i] = yPoints.get(i);
                            }
                            g.setColor(color);
                            g.drawPolyline(arr_xPoints, arr_yPoints, xPoints.size());
              }
              public void reshape(int x1, int y1, int x2, int y2) {
                            xPoints.add(x2);
                            yPoints.add(y2);
              }
}

//////////////////////////////////////////////////////////
// Model (M)

// modelは java.util.Observable を継承する。View に監視される
class DrawModel extends Observable {
              protected ArrayList<Figure> fig;
              protected Figure drawingFigure;
              protected Color currentColor;
              private int figureID = 0;                            // 0:Rectangle, 1:Line, 2:Oval
              public DrawModel() {
                            fig = new ArrayList<Figure>();
                            drawingFigure = null;
                            currentColor = Color.red;
              }
              public ArrayList<Figure> getFigures() {
                            return fig;
              }
              public Figure getFigure(int idx) {
                            return fig.get(idx);
              }
              public void setFigureID(int id) {
                            figureID = id;
              }
              public void setColor(Color c) {
                            currentColor = c;
              }
              public void createFigure(int x, int y) {
                            Figure f ;
                            if (figureID == 1) {
                                          f = new LineFigure(x, y, 0, 0, currentColor);
                            } else if (figureID == 2) {
                                          f = new OvalFigure(x, y, 0, 0, currentColor);
                            } else if (figureID == 3) {
                                          f = new PolylineFigure(x, y, 0, 0, currentColor);
                            } else {
                                          f = new RectangleFigure(x, y, 0, 0, currentColor);
                            }
                            fig.add(f);
                            drawingFigure = f;
                            setChanged();
                            notifyObservers();
              }
              public void reshapeFigure(int x1, int y1, int x2, int y2) {
                            if (drawingFigure != null) {
                                          drawingFigure.reshape(x1, y1, x2, y2);
                                          setChanged();
                                          notifyObservers();
                            }
              }
}

//////////////////////////////////////////////////////////
// View (v)

// View は、Observer を implements にする。Model を監視して、
// モデルが更新された update する。実際には、Model から
// update が呼び出される。
class ViewPanel extends JPanel implements Observer {
              protected DrawModel model;
              public ViewPanel(DrawModel m, DrawController c) {
                            this.setBackground(Color.white);
                            this.addMouseListener(c);
                            this.addMouseMotionListener(c);
                            model = m;
                            model.addObserver(this);
              }
              public void paintComponent(Graphics g) {
                            super.paintComponent(g);
                            ArrayList<Figure> fig = model.getFigures();
                            for(int i = 0; i < fig.size(); i++) {
                                          Figure f = fig.get(i);
                                          f.draw(g);
                            }
              }
              public void update(Observable o, Object arg) {
                            repaint();
              }
}

// どの図形を描画するかを指定する ComboBoxを追加する
class FigComboBox extends JPanel implements ActionListener{
              protected DrawModel model;
              protected JComboBox figtype;
              public FigComboBox(DrawModel m) {
                            model = m;

                            String[] combodata = {"Rectangle", "Line", "Oval", "Polyline"};
                            figtype = new JComboBox<String>(combodata);

                            this.add(figtype);
                            figtype.addActionListener(this);
                            this.setVisible(true);
              }

              public void actionPerformed(ActionEvent ev) {
                            int id = 0;
                            String name = (String)figtype.getSelectedItem();
                            if (name == "Line") { model.setFigureID(1); }
                            if (name == "Oval") { model.setFigureID(2); }
                            if (name == "Polyline") { model.setFigureID(3); }
              }
}

// 図形の色をしていする Colorchooser を追加する。
class FigColorChooser extends JFrame implements ChangeListener{
              protected DrawModel model;
              protected JColorChooser colorChooser;
              
              FigColorChooser(DrawModel m) {
                            model = m;

                            colorChooser = new JColorChooser();
                            colorChooser.getSelectionModel().addChangeListener(this);

                            getContentPane().add(colorChooser, BorderLayout.CENTER);
                            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                            this.setBounds(10, 10, 450, 400);
                            this.setTitle("ColorChooser");
                            this.setVisible(true);
              }

              public void stateChanged(ChangeEvent e) {
                            Color color = colorChooser.getColor();
                            model.setColor(color);
              }
}

//////////////////////////////////////////////////////////
// Main class
//              (GUIを組み立てているので、view の一部と考えても良い)
public class DrawFrame extends JFrame{
              DrawModel model;
              ViewPanel view;
              DrawController cont;
              FigComboBox combobox;
              public DrawFrame() {
                            model = new DrawModel();
                            cont = new DrawController(model);
                            view = new ViewPanel(model, cont);
                            combobox = new FigComboBox(model);
                            new FigColorChooser(model);
                            this.setBackground(Color.black);
                            this.setTitle("Draw Editor");
                            this.setSize(500, 500);
                            this.add(view);
                            this.add(combobox, BorderLayout.NORTH);
                            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                            this.setVisible(true);
              }
              public static void main(String[] args) {
                            new DrawFrame();
              }
}

//////////////////////////////////////////////////////////
// Conttroller (C)
class DrawController implements MouseListener, MouseMotionListener {
              protected DrawModel model;
              protected int dragStartX, dragStartY;
              public DrawController(DrawModel a) {
                            model = a;
              }
              public void mouseClicked(MouseEvent e) {}
              public void mousePressed(MouseEvent e) {
                            dragStartX = e.getX(); dragStartY = e.getY();
                            model.createFigure(dragStartX, dragStartY);
              }
              public void mouseDragged(MouseEvent e) {
                            model.reshapeFigure(dragStartX, dragStartY, e.getX(), e.getY());
              }
              public void mouseReleased(MouseEvent e) {}
              public void mouseEntered(MouseEvent e) {}
              public void mouseExited(MouseEvent e) {}
              public void mouseMoved(MouseEvent e) {}
}