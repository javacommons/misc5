import java.awt.Color;
import java.awt.Component;

import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;

public class ToDoCellRenderer extends JPanel implements ListCellRenderer {
	private JCheckBox checkbox;
	private JLabel label;

	/**
	 * Create the panel.
	 */
	public ToDoCellRenderer() {
		setOpaque(true);
		setLayout(null);

		checkbox = new JCheckBox("");
		checkbox.setBounds(0, 0, 20, 20);
		add(checkbox);

		label = new JLabel("New label");
		label.setBounds(20, 4, 50, 13);
		add(label);

	}
	public Component getListCellRendererComponent(
			JList list,
			Object value,
			int index,
			boolean isSelected,
			boolean cellHasFocus) {
		label.setText(value.toString());
		setBackground(isSelected ? Color.red : Color.white);
		setForeground(isSelected ? Color.white : Color.black);

		return this;
	}
}
