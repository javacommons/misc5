import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

public class Main extends JFrame {

	private JPanel contentPane;
	private JTextField textField;
	@SuppressWarnings("rawtypes")
	private DefaultListModel listModel = new DefaultListModel();
	private CheckBoxList list;
	private JScrollPane scrollPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Main frame = new Main();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	@SuppressWarnings("unchecked")
	public Main() {
		setTitle("To-Doアプリ");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 549);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);

		JButton btnNewButton = new JButton("New button");
		btnNewButton.setBounds(148, 432, 183, 21);
		btnNewButton.addActionListener(new ActionListener() {
			@SuppressWarnings("unchecked")
			public void actionPerformed(ActionEvent e) {
				textField.setText("clicked");
				listModel.addElement(new JCheckBox("abc"));
			}
		});
		contentPane.setLayout(null);
		contentPane.add(btnNewButton);

		textField = new JTextField();
		textField.setBounds(5, 5, 424, 19);
		contentPane.add(textField);
		textField.setColumns(10);

		scrollPane = new JScrollPane();
		scrollPane.setBounds(0, 100, 424, 206);
		contentPane.add(scrollPane);

		list = new CheckBoxList();
		list.setModel(listModel);
		list.setCellRenderer(new ToDoCellRenderer());
		list.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				var cbl = (CheckBoxList)e.getSource();
				if (e.getClickCount() == 2) {
					int index = list.locationToIndex(e.getPoint());
					System.out.println("index: "+index);
				}
			}
		});
		scrollPane.setViewportView(list);

		JList list_1 = new JList();
		list_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
			}
		});
		list_1.setBounds(72, 352, 58, 43);
		contentPane.add(list_1);
	}
}