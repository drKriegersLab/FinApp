import sys
from PyQt5.QtWidgets import (QWidget, QPushButton,
                             QHBoxLayout, QVBoxLayout, QApplication)


class Example(QWidget):

	def __init__(self):
		super().__init__()

		self.initUI()

	def initUI(self):
		okButton = QPushButton("OK")
		cancelButton = QPushButton("Cancel")

		hbox = QHBoxLayout()
		hbox.addWidget(okButton)
		hbox.addStretch(1) #strechable space between items

		hbox.addWidget(cancelButton)

		vbox = QVBoxLayout()
		vbox.addStretch(10)
		vbox.addLayout(hbox)

		self.setLayout(vbox)

		self.setGeometry(300, 300, 300, 150)
		self.setWindowTitle('Buttons')
		self.show()


if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = Example()
	sys.exit(app.exec_())