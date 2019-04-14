from PyQt5.QtWidgets import QWidget, QGridLayout, QVBoxLayout, QHBoxLayout, QPushButton
from MainWindow import chart_management


class TabChart(QWidget):
	_grid_layout = None
	_button_layout_ver = None
	_button_layout_hor = None
	_plot = None
	_button = None

	def __init__(self, parent=None):
		super(TabChart, self).__init__(parent)

		self._set_tab()
		self._set_plot()

		self._grid_layout = QGridLayout()
		self._grid_layout.addWidget(self._plot, 1, 0, 5, 0)

		self._add_button()

		self._button_layout_ver.addWidget(self._button)
		self._button_layout_hor.addStretch(1)
		self._button_layout_hor.addLayout(self._button_layout_ver)
		self._button_layout_hor.addStretch(1)
		self._grid_layout.addLayout(self._button_layout_hor, 6, 0)
		self.setLayout(self._grid_layout)

		return

	def _set_tab(self):
		self._grid_layout = QGridLayout()
		self._button_layout_ver = QVBoxLayout()
		self._button_layout_hor = QHBoxLayout()
		self._grid_layout.setSpacing(10)

	def _set_plot(self):
		self._plot = chart_management.PlotView()
		self._plot.addBalance()

	def _add_button(self):
		self._button = QPushButton("test", self)
		self._button.clicked.connect(self._handler_test_button)





	def _handler_test_button(self):
		print("muhaha")


