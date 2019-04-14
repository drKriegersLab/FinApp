# -*- coding: utf-8 -*-
#
# Licensed under the terms of the MIT License
# Copyright (c) 2015 Pierre Raybaut


from PyQt5.QtChart import QChart, QChartView, QLineSeries
from PyQt5.QtGui import QPolygonF, QPainter, QColor
import numpy as np
import data


def series_to_polyline(xdata, ydata):
	"""Convert series data to QPolygon(F) polyline
	This code is derived from PythonQwt's function named
	`qwt.plot_curve.series_to_polyline`"""
	size = len(xdata)
	polyline = QPolygonF(size)
	pointer = polyline.data()
	dtype, tinfo = np.float, np.finfo  # integers: = np.int, np.iinfo
	pointer.setsize(2 * polyline.size() * tinfo(dtype).dtype.itemsize)
	memory = np.frombuffer(pointer, dtype)
	memory[:(size - 1) * 2 + 1:2] = xdata
	memory[1:(size - 1) * 2 + 2:2] = ydata
	return polyline

class PlotView(QChartView):
	def __init__(self):
		self.ncurves = 0
		self.chart = QChart()
		self.chart.legend().hide()
		self.chart.setTitle("muhaha")
		super(PlotView, self).__init__(self.chart)
		self.setRenderHint(QPainter.Antialiasing)

	def addData(self, xdata, ydata, color=None):
		curve = QLineSeries()
		pen = curve.pen()
		pen.setWidthF(.1)

		if color is not None:
			pen.setColor(color)


		curve.setPen(pen)
		curve.setUseOpenGL(True)
		curve.append(series_to_polyline(xdata, ydata))
		self.chart.addSeries(curve)
		self.chart.createDefaultAxes()
		self.ncurves += 1

	def addBalance(self):
		xdata, ydata = data.createBalanceData()
		self.addData(xdata, ydata)

	def addBalance2(self):
		xdata, ydata = data.createBalanceData()
		self.addData(xdata, ydata, QColor.black())