import sys
from PyQt5 import QtGui, QtCore
from PyQt5.QtWidgets import QVBoxLayout, QHBoxLayout, QApplication, QWidget, QCalendarWidget, QLabel, QLineEdit, \
	QPushButton, \
	QMessageBox, QDialog
from PyQt5.QtGui import QFont
from PyQt5.QtCore import QDate
import os


class DateSelectorWidget(QDialog):
	"""	Class, which represents dialog for selecting a time interval. It shows two calendars, which initially shows the predefined
	start time and end time. You can select new "from" and "to" times, but you cannot able to select unlogical dates (for
	example earlier end date than the selected start date) or you cannot select date outside the predefined interval.
	- it also displays the selected "from" and "to" dates
	- you can reset the dates to the originally given date interval
	"""
	# layouts. Calendars, displays, control buttonrs associated to the main layout
	layout_main = None
	layout_calendars = None
	layout_displays = None
	layout_control_buttons = None

	# containers of calendar widgtets
	calendar_from = None
	calendar_to = None

	# variables for selected and original dates
	date_from_selected = None
	date_from_orig = None
	date_to_selected = None
	date_to_orig = None

	# displays
	layout_from = None  # layout for displaying "from" calendar's data
	label_from = None  # label for "from" calendar's result
	textbox_from = None  # textbox, where the result of the "from" calendar will be put
	layout_to = None  # layout for displaying "to" calendar's data
	label_to = None  # label for "to" calendar's result
	textbox_to = None  # textbox, where the result of the "to1" calendar will be put

	# buttons
	button_close = None  # close the dialog
	button_reset = None  # reset the calendars' selections to the originally specidied

	def __init__(self, min_date, max_date):
		super(DateSelectorWidget, self).__init__()

		# main level layout
		self.layout_main = QVBoxLayout(self)

		# second level layouts
		self.layout_calendars = QHBoxLayout()
		self.layout_displays = QHBoxLayout()
		self.layout_control_buttons = QHBoxLayout()
		self.layout_main.addLayout(self.layout_calendars)
		self.layout_main.addLayout(self.layout_displays)
		self.layout_main.addLayout(self.layout_control_buttons)

		# set up dialog
		self.set_displays()
		self.set_calendars(min_date, max_date)
		self.set_control_buttons_layout()

		# show the dialog
		self.show()

	def set_calendars(self, min_date, max_date):
		# set "from" calendar
		self.calendar_from = QCalendarWidget()
		# if clicked to a date --> sends the date to the handler as QDate object
		self.calendar_from.clicked[QDate].connect(self.handler_clicked_calendar_from)
		self.layout_calendars.addWidget(self.calendar_from)

		# set "to" calendar
		self.calendar_to = QCalendarWidget()
		# if clicked to a date --> sends the date to the handler as QDate object
		self.calendar_to.clicked[QDate].connect(self.handler_clicked_calendar_to)
		self.layout_calendars.addWidget(self.calendar_to)

		# set the calendars start and end time to predefined and save them for later use
		self.date_from_orig = min_date
		self.date_to_orig = max_date
		self.set_calendar_date_interval_to_orig()

	def set_calendar_date_interval_to_orig(self):
		"""
		Method for setting calendar's start and end time to the originally specified.
		Each calendar's possibly selected minimum and maximum date is the predefined time interval.
		"From" calendar's preselected date will be the possible minimum time and the "end" calendar's date will be the possible
		maximum.
		:return: void
		"""
		# set up "from" calendar
		self.calendar_from.setMinimumDate(self.date_from_orig)
		self.calendar_from.setMaximumDate(self.date_to_orig)
		self.calendar_from.setSelectedDate(self.date_from_orig)

		# set up "to" calendar
		self.calendar_to.setMinimumDate(self.date_from_orig)
		self.calendar_to.setMaximumDate(self.date_to_orig)
		self.calendar_to.setSelectedDate(self.date_to_orig)

		# set selected dates to the predefined minimum and maximum
		self.date_from_selected = self.date_from_orig
		self.date_to_selected = self.date_to_orig

		# display the predefined dates in the textboxes
		self.textbox_from.setText(self.date_from_selected.toString("MMMM d, yyyy"))
		self.textbox_to.setText(self.date_to_selected.toString("MMMM d, yyyy"))

	def set_displays(self):
		"""
		Method for setting up the displays
		:return: void
		"""
		# from (layout for label and textbox, set up the layout and the textbox and add them to the main layout of displaying)
		self.layout_from = QVBoxLayout()
		self.label_from = QLabel()
		self.label_from.setText("start date:")
		self.textbox_from = QLineEdit()
		self.textbox_from.setEnabled(False)
		self.layout_from.addWidget(self.label_from)
		self.layout_from.addWidget(self.textbox_from)
		self.layout_displays.addLayout(self.layout_from)

		# from (layout for label and textbox, set up the layout and the textbox and add them to the main layout of displaying)
		self.layout_to = QVBoxLayout()
		self.label_to = QLabel()
		self.label_to.setText("end date:")
		self.textbox_to = QLineEdit()
		self.textbox_to.setEnabled(False)
		self.layout_to.addWidget(self.label_to)
		self.layout_to.addWidget(self.textbox_to)
		self.layout_displays.addLayout(self.layout_to)

	def set_control_buttons_layout(self):
		"""
		Method for setting up the control buttons (close, reset)
		:return: void
		"""
		# close button (button object, title, connect to handler)
		self.button_close = QPushButton("close")
		self.button_close.setToolTip("nyeh")
		self.button_close.clicked.connect(self.close)

		# reset button (button object, title, connect to handler)
		self.button_reset = QPushButton("reset")
		self.button_close.setToolTip("nyeh")
		self.button_reset.clicked.connect(self.handler_button_reset_clicked)

		# add buttons to the correct layout
		self.layout_control_buttons.addStretch(1)
		self.layout_control_buttons.addWidget(self.button_close)
		self.layout_control_buttons.addStretch(2)
		self.layout_control_buttons.addWidget(self.button_reset)
		self.layout_control_buttons.addStretch(1)

	def handler_clicked_calendar_from(self, selected_date):
		"""
		Handler method of event triggered when on the "from" calendar the user clicked to a date
		:param selected_date: date, which is given by the event of calendar
		:return: void
		"""
		if selected_date > self.date_to_selected:  # avoid clicking to later date than the last selected "to" date
			# drop warning message
			error_popup = WrongDateSelectedPopup('the date you selected is after than the chosen end date')
			error_popup.exec_()
			# set the selected date back to the earlier one
			self.calendar_from.setSelectedDate(self.date_from_selected)
		else:  # if the date is correct, set it as selected date
			self.date_from_selected = selected_date

		# display the selected date in textbox
		self.textbox_from.setText(self.date_from_selected.toString("MMMM d, yyyy"))

	def handler_clicked_calendar_to(self, selected_date):
		"""
		Handler method of event triggered when on the "to" calendar the user clicked to a date
		:param selected_date: date, which is given by the event of calendar
		:return: void
		"""
		if selected_date < self.date_from_selected:  # avoid clicking to earlier date than the last selected "from" date
			# drop warning message
			error_popup = WrongDateSelectedPopup('the date you selected is later than the chosen end date')
			error_popup.exec_()
			# set the selected date back to the earlier one
			self.calendar_to.setSelectedDate(self.date_to_selected)
		else:  # if the date is correct, set it as selected date
			self.date_to_selected = selected_date

		# display the selected date in textbox
		self.textbox_to.setText(self.date_to_selected.toString("MMMM d, yyyy"))

	def get_selected_dates(self):
		"""
		Method for returning the selected date. Getter function for outside use after the dialog successfully closed
		:return: date where the new interval starts; date where it ends
		"""
		return self.date_from_selected, self.date_to_selected

	def handler_button_reset_clicked(self):
		"""
		Method for resetting the calendars.
		:return: void
		"""
		self.set_calendar_date_interval_to_orig()

	def close(self):
		"""
		Overwritten method, which sets the state to accepted, and proceed the close method
		:return: void
		"""
		self.accept()
		#super(DateSelectorWidget, self).close()


class WrongDateSelectedPopup(QMessageBox):
	"""
	Simple class for representing warning window, when the user selects wrong date
	"""
	def __init__(self, message, parent=None):
		super().__init__(parent)
		self.setText(message)
		self.setWindowTitle("oh no, wrong date ...")
		self.setStandardButtons(QMessageBox.Ok)
		path = os.path.dirname(os.path.abspath(__file__))
		path = os.path.join(path, 'warning_icon.png')
		self.setWindowIcon(QtGui.QIcon(path))


if __name__ == "__main__":
	app = QApplication(sys.argv)

	date_selector_dialog = DateSelectorWidget(QDate(2018, 9, 15), QDate(2018, 10, 31))
	if date_selector_dialog.exec_():
		print(date_selector_dialog.get_selected_dates())
		print("muhaha")

	#sys.exit(app.exec_())
