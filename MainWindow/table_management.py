from PyQt5.QtWidgets import *
import numpy as np
import utils

IDX_DATE = 0
IDX_COMMENT = 1
IDX_NEW_BALANCE = 2


class TableColumnHeader:
    """
    Class which tasks is mainly the storing and managing information, which can be necessary for drawing a header.
    """
    id = None
    # name = None
    resize_mode = None
    associated_name = None
    increasing = None  # shows that the data in this column should increase or decrease, if you click to it.  If you
    # After you clicked to it, it should be automatically negated.
    # TODO: do it like a property (https://www.geeksforgeeks.org/python-property-function/)
    
    def __init__(self, column_id, associated_name_in_db, resizing):
        """
        Constructor. With it, you can define a new Header.
        :param column_id: the column number in sequence. It must be unique.
        :param associated_name_in_db: what parameter name associated to this column from the db
        :param resizing: resizing mode of this column
        """
        self.id = column_id
        # self.name = column_name
        self.associated_name = associated_name_in_db
        self.resize_mode = resizing
        self.increasing = True


"""
hardcoded container of defined header used by tableView. If you want to insert a new column, define it here
the resize mode should be set to Stretch for at least one column, because with this way the table will fill 
the available space 
"""
column_headers = {
    "date": TableColumnHeader(0, "tr_date", QHeaderView.ResizeToContents),
    "comment": TableColumnHeader(1, "tr_comment", QHeaderView.Stretch),
    "balance": TableColumnHeader(2, "tr_new_balance", QHeaderView.ResizeToContents)
}


class TableManager(QWidget):
    """
    Here, the table related methods and functions are collected. The base class is a general Widget, which contains
    a table widget. This table widget will show the transactions which should be shown.
    """
    
    _table_widget = None  # container of table widget
    _header = None  # container of the columns' header
    _transaction_database = None  # the base transaction collection, on which we working on. (not a deep copy)
    _current_transaction_list = None  # the shown transaction records' collection. On the GUI, this collection will be
    #  shown. So, if you search, or use filters on the used db, the results should be put here, not into the main db.
    
    def __init__(self):
        """
        Constructor of the table management. It will do the following:
        - initializes the main widget on we working on
        - set up the table
        - assign box layout to the main widget as main layout (in the future, you can add many more functionality)
        - add the table widget to the box layout
        """
        super(TableManager, self).__init__()
        self._set_table()

        # assign layout and show the result to the world
        self.layout = QVBoxLayout()
        self.layout.addWidget(self._table_widget)
        self.setLayout(self.layout)
        self.show()
    
    def _set_table(self):
        """
        Method for creating a table widget and initializing the headers.
        :return: None
        """
        
        self._table_widget = QTableWidget()
        self._table_widget.setColumnCount(3)
        
        # horizontal header settings
        self._header = self._table_widget.horizontalHeader()
        header_names = np.array([])
        for header_key, header_item in column_headers.items():
            header_names = np.append(header_names, header_key)
            self._header.setSectionResizeMode(header_item.id, header_item.resize_mode)
        
        self._table_widget.setHorizontalHeaderLabels(header_names)
        
        # vertical header setting
        # elf._header.verticalheader().hide()
        self._table_widget.verticalHeader().hide()
        
        # connect handlers
        self._header.sectionClicked.connect(self._handler_header_clicked)  # header click
        self._table_widget.doubleClicked.connect(self.on_click)  # double click on an element
        
    def _handler_header_clicked(self, header_number):
        """
        handler method of click event on a column's header
        :param header_number: what header had been clicked
        :return: None
        """
        if self._transaction_database is not None:
            
            # get the corresponding column
            for col_name, col_head in column_headers.items():
                if col_head.id == header_number:
                    
                    # call the sorting method of the database
                    self._current_transaction_list = self._transaction_database.sort_transaction(
                        col_head.associated_name, col_head.increasing)
                    # negate the increasing flag in the headers object (at the next time,
                    # it should be decreasing and so on)
                    col_head.increasing = not col_head.increasing
                    break
            
            # create the table from the sorting result
            self.create_table()
    
    def set_transaction_database(self, transaction_collection):
        """
        Method for give new transaction collection to the table widget. It will assign it to the
        self._transaction_database, as new basis, on which we will work, and to the currently shown transaction list.
        :param transaction_collection: the new collection of transactions from the database
        :return: None
        """
        
        self._transaction_database = transaction_collection
        self._current_transaction_list = self._transaction_database.transaction_list
    
    def create_table(self):
        """
        Method for filling the table with data
        :return: None
        """
        self._table_widget.setRowCount(self._current_transaction_list.size)
        
        tr_idx = 0
        for transaction in self._current_transaction_list:
            self._table_widget.setItem(tr_idx, 0, QTableWidgetItem(str(transaction.tr_date)))
            self._table_widget.setItem(tr_idx, 1, QTableWidgetItem(transaction.tr_comment))
            self._table_widget.setItem(tr_idx, 2, QTableWidgetItem(str(transaction.tr_new_balance)))
            tr_idx = tr_idx + 1
        
        return
    
    # @pyqtSlot()
    def on_click(self):
        """
        QT Slot function. If the user clicks on an  element, this method will be called.
        :return:
        """
        for current_item in self._table_widget.selectedItems():
            print(current_item.row(), current_item.column(), current_item.text())
