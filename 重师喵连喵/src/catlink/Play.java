package catlink;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;


public class Play {
	Game game = new Game(8, 8);
	JFrame frame = new JFrame("重师喵连喵");
	JPanel controlPanel = new JPanel(null); // 用于放置控件
	JButton button1 = new JButton("提示");
	JButton button2 = new JButton("重置");
	JButton button3 = new JButton("重来");
	JLabel image_label = new JLabel();
	JLabel label1 = new JLabel("剩余图案个数");
	JLabel label2 = new JLabel("原始图案个数 64");
	JLabel title = new JLabel("重师喵连喵");
	JLabel developer_information_label = new JLabel("如有疏漏敬请斧正！");
	static JTextField textField = new JTextField(4);

	public Play() {
	    // 窗口样式设置
	    Image logo = Toolkit.getDefaultToolkit().getImage(".\\GameImages\\logo.png");
	    frame.setSize(720, 980);
	    frame.setResizable(false);
	    frame.setIconImage(logo);
	    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	
	    // 创建背景面板
	    BackgroundPanel backgroundPanel = new BackgroundPanel();
	    backgroundPanel.setLayout(null); // 使用绝对布局
	    game.setLocation(0, 0);
	    //controlPanel.add(game);
	    
	    // 控制面板样式设置
	    controlPanel.setSize(720, 980);
	    controlPanel.setOpaque(false); // 设置为透明
	    controlPanel.setLayout(null); // 使用绝对布局
	    
	    
	    ImageIcon icon = new ImageIcon(".\\GameImages\\icon.png");
	    icon.setImage(icon.getImage().getScaledInstance(175, 175, Image.SCALE_DEFAULT));
	    image_label.setIcon(icon);
	    image_label.setLocation(100, 100);
	    image_label.setSize(175, 175);
	    controlPanel.add(image_label);
	
	    
	    // 剩余提示样式设置
	    label1.setLocation(300, 167);
	    label1.setSize(150, 40);
	    label1.setFont(new Font("幼圆", Font.BOLD, 20));
	    label1.setForeground(Color.BLUE);
	    controlPanel.add(label1);
	    
	    // 原始提示样式设置
	    label2.setLocation(300, 190);
	    label2.setSize(250 , 40);
	    label2.setFont(new Font("幼圆", Font.BOLD, 20));
	    label2.setForeground(Color.BLUE);
	    controlPanel.add(label2);
	    
	
	    // 动态剩余数量样式设置
	    textField.setLocation(430, 175);
	    textField.setSize(36, 25);
	    textField.setEditable(true);
	    textField.setFont(new Font("幼圆", Font.BOLD, 20));
	    textField.setForeground(Color.BLUE);
	    textField.setBackground(Color.WHITE);
	    controlPanel.add(textField);
	
	    
	    // 标题样式设置
	    title.setLocation(300, 100);
	    title.setSize(500, 40);
	    title.setFont(new Font("幼圆", Font.BOLD, 36));
	    title.setForeground(Color.BLACK);
	    controlPanel.add(title);
	
	    // 开发者信息样式设置
	    developer_information_label.setLocation(300, 150);
	    developer_information_label.setSize(600, 15);
	    developer_information_label.setFont(new Font("幼圆", Font.PLAIN, 15));
	    developer_information_label.setForeground(Color.BLACK);
	    controlPanel.add(developer_information_label);   
	    
	    // 按钮样式设置
	    button1.setBounds(300, 230, 80, 40);
	    button1.setFont(new Font("幼圆", Font.BOLD, 15));
	    controlPanel.add(button1);
	
	
	    button2.setBounds(400, 230, 80, 40);
	    button2.setFont(new Font("幼圆", Font.BOLD, 15));
	    controlPanel.add(button2);
	
	    button3.setBounds(500, 230, 80, 40);
	    button3.setFont(new Font("幼圆", Font.BOLD, 15));
	    controlPanel.add(button3);
	
	    // 按钮事件处理
	    button1.addMouseListener(new MouseAdapter() {
	        public void mouseClicked(MouseEvent e) {
	            game.find2Block();
	        }
	    });
	
	    button2.addMouseListener(new MouseAdapter() {
	        public void mouseClicked(MouseEvent e) {
	            game.resetMap();
	        }
	    });
	
	    button3.addMouseListener(new MouseAdapter() {
	        public void mouseClicked(MouseEvent e) {
	            game.startNewGame();
	        }
	    });
	    
	     // 将控制面板添加到背景面板
	        controlPanel.add(game);
	        backgroundPanel.add(controlPanel);
	     
	  	  //菜单样式设置
		    JMenuBar jMenuBar = new JMenuBar();
	        jMenuBar.setSize(720, 30);
	        JMenu menu1 = new JMenu("关于");
	        jMenuBar.add(menu1);

	        JMenuItem item1 = new JMenuItem("猫猫图鉴");
	        item1.addActionListener(new ActionListener() {
	            @Override
	            public void actionPerformed(ActionEvent e) {
	            	 JDialog jDialog=new JDialog(frame, "猫猫图鉴", true);
	                 ImageIcon imageIcon1=new ImageIcon(".\\GameImages\\mao.jpg");
	                 JLabel jLabel=new JLabel(imageIcon1);
	                 jLabel.setBounds(0,0,500,500);
	                 //把图片放在弹框当中
	                 jDialog.add(jLabel);
	                 //给弹框试设置大小
	                 jDialog.setSize(500,500);
	                 //要把弹框设置为顶层---置顶效果
	                 jDialog.setAlwaysOnTop(true);
	                 //要让jDialog居中显示
	                 jDialog.setLocationRelativeTo(null);
	                 //让jDialog显示出来
	                 jDialog.setVisible(true);
	                 imageIcon1=null;
	               
	            }
	        });
	        
	        JMenuItem item2 = new JMenuItem("联系我们");
	        item2.addActionListener(new ActionListener() {
	            @Override
	            public void actionPerformed(ActionEvent e) {
	            	 JDialog jDialog=new JDialog(frame, "联系我们", true);
	                 ImageIcon imageIcon2=new ImageIcon(".\\GameImages\\info.jpg");
	                 JLabel jLabel=new JLabel(imageIcon2);
	                 jLabel.setBounds(0,0,600,400);
	                 //把图片放在弹框当中
	                 jDialog.add(jLabel);
	                 //给弹框试设置大小
	                 jDialog.setSize(600,400);
	                 //要把弹框设置为顶层---置顶效果
	                 jDialog.setAlwaysOnTop(true);
	                 //要让jDialog居中显示
	                 jDialog.setLocationRelativeTo(null);
	                 //让jDialog显示出来
	                 jDialog.setVisible(true);
	               
	            }
	        });
	        menu1.add(item1);
	        menu1.addSeparator();
	        menu1.add(item2);
	        frame.setJMenuBar(jMenuBar);
	    
	    // 设置内容面板
	    frame.setContentPane(backgroundPanel);
	    frame.setLocationRelativeTo(null);
	    frame.setVisible(true);
	    
	    
	   
}

public static void main(String[] args) {
    	String filepath = ".\\Music\\happy.wav";
		MusicPlayer musicObject = new MusicPlayer();
		musicObject.playMusic(filepath);
		new Play();
    	
	}
}
