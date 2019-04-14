from MainWindow.table_management import *
from data import *


class TabTransactionTable(QWidget):
    """
    This class is responsible for user interface tasks of the Transaction Table's tab. It contains the Table Widget's
    implementation and any future functions associated to the table.
    """
    _grid_layout = None  # main layout of the tab
    # its children:
    _table_widget = None  # widget contains the table
    
    def __init__(self, parent=None):
        """
        Constructor method. It creates a gridlayout in the tab's main widget (later, you can put here more stuff).
        The Table is handled by the TableManager class. Here, it creates it and calls the necessary methods from it for
        initializing the table.
        :param parent: The parent widget
        """
        super(TabTransactionTable, self).__init__(parent)
        self._grid_layout = QGridLayout()
        
        self._table_widget = TableManager()
        
        self._grid_layout.addWidget(self._table_widget, 0, 0, 0, 0)
        
        self.setLayout(self._grid_layout)
        
        self._table_widget.set_transaction_database(create_db())
        self._table_widget.create_table()
        return
