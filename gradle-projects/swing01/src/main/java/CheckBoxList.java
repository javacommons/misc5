// https://maku77.github.io/java/swing/widget/jlist-checkbox.html
import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JCheckBox;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

@SuppressWarnings({ "serial", "rawtypes" })
public class CheckBoxList extends JList {
     @SuppressWarnings("unchecked")
	public CheckBoxList() {
          super();
          setCellRenderer(cellRenderer);
          addMouseListener(mouseListener);
     }

     private MouseListener mouseListener = new MouseAdapter() {
          public void mousePressed(MouseEvent e) {
               int index = locationToIndex(e.getPoint());
               if (index != -1) {
                    JCheckBox checkbox = (JCheckBox) getModel().getElementAt(index);
                    checkbox.setSelected(!checkbox.isSelected());
                    repaint();
               }
          }
     };

    private ListCellRenderer cellRenderer = new ListCellRenderer() {
          @Override
          public Component getListCellRendererComponent(JList list, Object value,
                    int index, boolean isSelected, boolean cellHasFocus) {
               JCheckBox checkbox = (JCheckBox) value;
               //checkbox.setBackground(isSelected ? getSelectionBackground() : getBackground());
               //checkbox.setForeground(isSelected ? getSelectionForeground() : getForeground());
               //checkbox.setEnabled(isEnabled());
               //checkbox.setFont(getFont());
               //checkbox.setFocusPainted(false);
               //checkbox.setBorderPainted(true);
               return checkbox;
          }
     };
}