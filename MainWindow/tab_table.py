from PyQt5.QtWidgets import QWidget, QGridLayout
from MainWindow.table_management import *
from data import *

class TabTransactionTable(QWidget):
	_grid_layout = None
	_table_widget = None


	def __init__(self, parent=None):
		super(TabTransactionTable, self).__init__(parent)

		self._grid_layout = QGridLayout()

		self._table_widget = TableManager()

		self._grid_layout.addWidget(self._table_widget, 0, 0, 0, 0)

		self.setLayout(self._grid_layout)

		self._table_widget.set_transaction_database(create_db())
		self._table_widget.create_table()
		return