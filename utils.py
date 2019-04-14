import numpy as np
from datetime import date


def quicksort(array):
	less = np.array([])
	equal = np.array([])
	greater = np.array([])

	if len(array) > 1:
		pivot = array[0]
		for x in array:
			if x < pivot:
				less = np.append(less, x)
			elif x == pivot:
				equal = np.append(equal, x)
			elif x > pivot:
				greater = np.append(greater, x)

		# result: quicksort(less) .. equal .. quicksort(greater)
		result = np.append(quicksort(less), equal)
		result = np.append(result, quicksort(greater))
		return result
	else:
		return array


def quicksort_with_id(array, ids):
	less = np.array([])
	equal = np.array([])
	greater = np.array([])

	id_less = np.array([])
	id_equal = np.array([])
	id_greater = np.array([])

	if len(array) > 1:
		pivot = array[0]
		for i in range(len(array)):
			if array[i] < pivot:
				less = np.append(less, array[i])
				id_less = np.append(id_less, ids[i])
			elif array[i] == pivot:
				equal = np.append(equal, array[i])
				id_equal = np.append(id_equal, ids[i])
			elif array[i] > pivot:
				greater = np.append(greater, array[i])
				id_greater = np.append(id_greater, ids[i])

		# result: quicksort(less) .. equal .. quicksort(greater)
		less_result, less_result_ids = quicksort_with_id(less, id_less)
		greater_result, greater_result_ids = quicksort_with_id(greater, id_greater)

		result = np.append(less_result, equal)
		result = np.append(result, greater_result)

		result_ids = np.append(less_result_ids, id_equal)
		result_ids = np.append(result_ids, greater_result_ids)
		return result, result_ids
	else:
		return array, ids


if __name__ == "__main__":
	#original_array = np.array([3, 5, 2, 8, 10,  9, 1,0])
	#new_array = inserting_sort(original_array)

	#array = np.array([9, 7, 8, 3, 2, 1])
	#array = np.array(["aca", "aba", "aaa", "ada"])
	array = np.array([
					date(1990, 1, 1),
					date(2000, 1, 1),
					date(2010, 1, 1),
					date(1982, 1, 1),
					date(1790, 1, 1)
					])
	ids = np.array(["a", "b", "c", "d", "e"])

	result, result_ids = quicksort_with_id(array, ids)

	print(result)
	print(result_ids)
