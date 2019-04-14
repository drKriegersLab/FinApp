from PyQt5.QtWidgets import *
import numpy as np
import utils


IDX_DATE = 0
IDX_COMMENT = 1
IDX_NEW_BALANCE = 2

class TableColumnHeader:
	id = None
	#name = None
	resize_mode = None
	associated_name = None
	increasing = None

	def __init__(self, column_id, associated_name_in_db, resizing):
		self.id = column_id
		#self.name = column_name
		self.associated_name = associated_name_in_db
		self.resize_mode = resizing
		self.increasing = True


"""
container of defined header used by tableView
the resize mode should be set to Stretch for at least one column, because with this way the table will fill 
the available space 
"""
column_headers = {
	"date":     TableColumnHeader(0, "tr_date", QHeaderView.ResizeToContents),
	"comment":  TableColumnHeader(1, "tr_comment", QHeaderView.Stretch),
	"balance":  TableColumnHeader(2, "tr_new_balance", QHeaderView.ResizeToContents)
}

class TableManager(QWidget):
	_table_widget = None
	_header = None
	_transaction_database = None
	_current_transaction_list = None

	def __init__(self):
		super(TableManager, self).__init__()

		self._set_table()


	def _set_table(self):
		self._table_widget = QTableWidget()
		self._table_widget.setColumnCount(3)

		# horzontal header settings
		self._header = self._table_widget.horizontalHeader()
		header_names = np.array([])
		for header_key, header_item in column_headers.items():
			header_names = np.append(header_names, header_key)
			self._header.setSectionResizeMode(header_item.id, header_item.resize_mode)

		self._table_widget.setHorizontalHeaderLabels(header_names)

		# vertical header setting
		#elf._header.verticalheader().hide()
		self._table_widget.verticalHeader().hide()




		# connect header click to handler
		self._header.sectionClicked.connect(self._handler_header_clicked)

		self._table_widget.doubleClicked.connect(self.on_click)

		# set layout and show the widget to the world
		self.layout = QVBoxLayout()
		self.layout.addWidget(self._table_widget)
		self.setLayout(self.layout)
		self.show()

	def _handler_header_clicked(self, header_number):
		"""
		handler method of clickevent on a column's header
		:param header_number: what header had been clicked
		:return: None
		"""
		if self._transaction_database is not None:
			# get the corresponding column
			for col_name, col_head in column_headers.items():
				if col_head.id == header_number:
					# call the sorting method of the database
					self._current_transaction_list = self._transaction_database.sort_transaction(col_head.associated_name, col_head.increasing)
					# negate the increasing flag in the headers object (at the next time, it should be decreasing and so on)
					col_head.increasing = not col_head.increasing
					break

			# create the table from the sorting result
			self.create_table()

	def set_transaction_database(self, transaction_collection):
		self._transaction_database = transaction_collection
		self._current_transaction_list = self._transaction_database.transaction_list

	def create_table(self):
		self._table_widget.setRowCount(self._current_transaction_list.size)

		tr_idx = 0
		for transaction in self._current_transaction_list:
			self._table_widget.setItem(tr_idx, 0, QTableWidgetItem(str(transaction.tr_date)))
			self._table_widget.setItem(tr_idx, 1, QTableWidgetItem(transaction.tr_comment))
			self._table_widget.setItem(tr_idx, 2, QTableWidgetItem(str(transaction.tr_new_balance)))
			tr_idx = tr_idx + 1


		return

	#@pyqtSlot()
	def on_click(self):
		for current_item in self._table_widget.selectedItems():
			print(current_item.row(), current_item.column(), current_item.text())


