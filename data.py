import numpy as np
from datetime import date
from copy import deepcopy
import hashlib
import utils

balances = [
			959228,
			958036,
			948536,
			946656,
			944970,
			937320,
			930945,
			915945,
			915414,
			959398,
			914294,
			911294,
			901294,
			898674,
			896984,
			887344,
			885888,
			879344,
			877895,
			874775,
			872021,
			853549,
			843549,
			830621,
			761621,
			725041,
			724341,
			710566,
			708488,
			706785,
			690885,
			689085,
			686985,
			680566,
]

dates = ["20180901",
		"20180901",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180903",
		"20180904",
		"20180904",
		"20180906",
		"20180907",
		"20180910",
		"20180910",
		"20180910",
		"20180910",
		"20180911",
		"20180913",
		"20180913",
		"20180913",
		"20180913",
		"20180917",
		"20180917",
		"20180917",
		"20180917",
		"20180917",
		"20180917",
		"20180917",
		"20180917",
		"20180918",
]

comments = [
	"",
	"",
	"SPAR PARTNER 6911200       PPASS",
	"BKK AUTOMATA - A51",
	"OTPMOBL * NETPINCER.HU",
	"TESCO 44033",
	"Diákhitel Központ Zrt.    40193864",
	"Diákhitel Központ Zrt.    70257225",
	"Kemecseiné Nagy Terézia    ÁRPITÓL",
	"SPAR 5440                  PPASS",
	"MCD OKTOGON                PPASS",
	"TERROR HÁZA - PÉNZTÁR        PPASS",
	"Bosch Útterem              PPASS",
	"SPAR PARTNER 6911200       PPASS",
	"OTPMOBL * NETPINCER.HU",
	"AUCHAN ALBERTFALVA",
	"",
	"SPAR 5440                  PPASS",
	"MEDIA MARKT BUDA           PPASS",
	"SPAR PARTNER 6911200       PPASS",
	"SPAR PARTNER 6911200       PPASS",
	"AIRBNB * HMFM4W35NT",
	"Bosch Útterem              PPASS",
	"AUCHAN ALBERTFALVA         PPASS",
	"Budapest, XI.Fehérvári út",
	"WIZZ AIRLREI45N",
	"LACI PAPA KONYHÁJA         PPASS",
	"TELEKOM.HU / UZLETI / UGYINTE",
	"AUCHAN ALBERTFALVA         PPASS",
	"PAYPAL * SPOTIFY",
	"Hardverker Online          PPASS",
	"MIR Etterem",
	"MAGYAR MEZŐG.MÚZEUM ÉS KT  PPASS",
	"AUCHAN ALBERTFALVA"
]






class TransactionRecord():

	tr_date = None
	tr_comment = None
	tr_new_balance = None
	ID = None

	def __init__(self, transaction_date, transaction_comment, transaction_new_balance):
		self._parse_transaction_date(transaction_date)
		self.tr_comment = transaction_comment
		self.tr_new_balance = transaction_new_balance

		# I used md5 hash for ID, because it provides unique 16 byte hash for a string combination.
		# (Birthday paradox: we need a few trillion hash for collision :-) )
		# the hash generated from the appended string of the fields of the record --> it is unique
		md5_hash = hashlib.md5()
		hash_base_string = self.tr_comment + str(self.tr_new_balance) + self.tr_date.strftime("%d-%m-%y")
		md5_hash.update(hash_base_string.encode('utf-8'))
		self.ID = md5_hash.hexdigest()

		return

	def _parse_transaction_date(self, date_of_transaction):
		self.tr_date = date(int(date_of_transaction[0:4]), int(date_of_transaction[4:6]), int(date_of_transaction[6:]))
		return


class TransactionCollection():
	current_balance = None
	transaction_list = np.array([])

	def __init__(self, records = None):

		if records is not None:
			for rec in records:
				self.transaction_list = np.append(self.transaction_list, deepcopy(rec))

		return

	def add_record(self, tr_date, tr_comment, tr_new_balance):
		tmp_record = TransactionRecord(tr_date, tr_comment, tr_new_balance)
		self.transaction_list = np.append(self.transaction_list, deepcopy(tmp_record))

		return

	def sort_transaction(self, sorted_field_string, increasing):
		"""
		method for managing sorting procedure in the records of database. You can specify, what field do you want to
		sort to an increasing or decreasing sequence

		:param (string) sorted_field_string: field, which indicates what field do you want to sort (it have to be identical
		one of the attributes in this class)
		:param increasing: (boolean) indicates the sorting directions
		:return: list of sorted transactions
		"""
		# init
		sorted_attrs = np.array([])
		sorted_ids = np.array([])

		# get the correct attributes and the ids of transactions
		for tr in self.transaction_list:
			sorted_attrs = np.append(sorted_attrs, getattr(tr, sorted_field_string))
			sorted_ids = np.append(sorted_ids, tr.ID)

		# proceed the sorting
		sorted_attrs, sorted_ids = utils.quicksort_with_id(sorted_attrs, sorted_ids)

		# based on the ids given by the sorting, collect all transactions in the correct sequence
		sorted_transactions = np.array([])
		if increasing:
			for sort_id in sorted_ids:
				for tr in self.transaction_list:
					if tr.ID == sort_id:
						sorted_transactions = np.append(sorted_transactions, tr)
						break

		else: # reversed direction
			for sort_id in sorted_ids:
				for tr in self.transaction_list:
					if tr.ID == sort_id:
						sorted_transactions = np.append(tr, sorted_transactions)
						break

		return sorted_transactions







def createBalanceData():
	xdata = np.array([])
	ydata = np.array([])

	i = 0
	"""for cyc in range(len(balances)):
		xdata.append(cyc)
		ydata.append(balances[cyc])
		print(str(balances[cyc]) + "\n")
		i += 1
	"""
	for balance in balances:
		xdata = np.append(xdata, i)
		ydata = np.append(ydata, balance)
		i += 1
		#print(str(i) + "  " + str(balance) + "\n")

	return xdata, ydata


def create_db():

	collection = TransactionCollection()

	for cyc_balance in range(len(balances)):
		#print(str(dates[cyc_balance]) + "  " + str(comments[cyc_balance]) + "  " + str(balances[cyc_balance]))
		collection.add_record(dates[cyc_balance], comments[cyc_balance], balances[cyc_balance])

	return collection









