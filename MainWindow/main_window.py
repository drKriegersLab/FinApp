from PyQt5.QtWidgets import QVBoxLayout, QHBoxLayout, QWidget, QTabWidget
from PyQt5.QtWidgets import QApplication, QPushButton
from PyQt5.QtGui import QIcon
import sys
import os
from MainWindow.tab_chart import TabChart
from MainWindow.tab_table import TabTransactionTable


class MainWindow(QWidget):
    """
    This class is responsible for the creation of GUI, managing the requests created by the user and tunnels is to
    the backend
    """

    # layouts
    _layout_main = None
    _layout_tabs = None
    _layout_selectors = None

    # tabs
    _tabs = None
    _tab1 = None
    _tab2 = None

    # selectors
    _button_select_date = None

    plot = None
    title = "FinApp"
    
    def __init__(self, parent=None):
        """
        Constructor of main GUI. Initializes the layouts: main, selectors, tabs and show the window.
        :param parent:  parent of the window
        """
        
        super(MainWindow, self).__init__(parent=parent)
        # set layout architecture
        self._layout_main = QVBoxLayout(self)
        self._layout_selectors = QHBoxLayout()
        self._layout_tabs = QHBoxLayout()

        self._layout_main.addLayout(self._layout_selectors)
        self._layout_main.addLayout(self._layout_tabs)

        self._set_selector_layout()
        self._set_tabs()

        self.show()
        
    def _set_selector_layout(self):
        # set selectors
        self._button_select_date = QPushButton("select date")

        # layout management
        self._layout_selectors.addWidget(self._button_select_date)
        self._layout_selectors.addStretch(1)
        return

    def _set_tabs(self):
        """
        Method for initializing tabulators into the already prepared layout structure
        :return: None
        """
        # set tabs
        self._tabs = QTabWidget()
        self._tab1 = TabTransactionTable()
        self._tab2 = TabChart()

        # layout management
        self._tabs.addTab(self._tab1, "transaction list")
        self._tabs.addTab(self._tab2, "graph")
        self._layout_tabs.addWidget(self._tabs)
        return

    def _set_window_settings(self):
        """
        Method for configure window parameters, configurations
        :return: None
        """
        # set window's title
        self.setWindowTitle(self.title)
        # current directory + filename with "/"
        self.setWindowIcon(QIcon(os.path.dirname(os.path.realpath(__file__)) + "/money_bag.png"))
        
    def handle_button(self):
        """
        Prototype method for handling click events on a button
        :return:
        """
        print("muhaha")


if __name__ == "__main__":
    app = QApplication(sys.argv)

    main_window = MainWindow()

    # plot = graph.PlotView()

    # main_window.setCentralWidget(plot)

    # xdata, ydata = data.createBalanceData()
    # plot.add_data(xdata, ydata)
    # plot.add_data(xdata, 2*ydata)

    # main_window.show()
    main_window.resize(500, 400)

    sys.exit(app.exec_())

