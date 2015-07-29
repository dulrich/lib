# lib: structures and algorithms
# Copyright (C) 2015  David Ulrich
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

array_input = [2,5,7,3,87,34,67,40,29,47,4]


def sort_heap(arr):
	arr = sort_heap_heapify(arr,len(arr))
	end = len(arr) - 1
	while end > 0:
		swap = arr[end]
		arr[end] = arr[0]
		arr[0] = swap
		end -= 1
		arr = sort_heap_sift_down(arr,0,end)
	return arr

def sort_heap_heapify(arr,length):
	start = (length - 2) / 2
	while start >= 0:
		arr = sort_heap_sift_down(arr,start,length - 1)
		start -= 1
	return arr

def sort_heap_sift_down(arr,start,end):
	while start * 2 + 1 <= end:
		child = start * 2 + 1
		swap = start
		if arr[swap] < arr[child]:
			swap = child
		if child + 1 <= end and arr[swap] < arr[child + 1]:
			swap = child + 1
		if swap == start:
			break
		else:
			temp = arr[swap]
			arr[swap] = arr[start]
			arr[start] = temp
			start = swap
	return arr


def sort_merge(arr):
	return sort_merge_split(arr,0,len(arr),list(arr))[0]

def sort_merge_split(L,start,end,R):
	if (end - start) < 2:
		return (L,R)
	mid = (end + start) / 2
	(L,R) = sort_merge_split(L,start,mid,R)
	(L,R) = sort_merge_split(L,mid,end,R)
	(L,R) = sort_merge_merge(R,start,mid,end,L)
	(L,R) = sort_merge_copy(R,start,end,L)
	return (L,R)

def sort_merge_merge(L,start,mid,end,R):
	iL = start
	iR = mid
	for i in range(start,end):
		if iL < mid and (iR >= end or L[iL] < L[iR]):
			R[i] = L[iL]
			iL += 1
		else:
			R[i] = L[iR]
			iR += 1
	return (L,R)

def sort_merge_copy(R,start,end,L):
	for i in range(start,end):
		L[i] = R[i]
	return (L,R)


def sort_quick(arr):
	return sort_quick_quick(arr,0,len(arr))

def sort_quick_quick(arr,start,end):
	if start < end:
		(arr,pivot) = sort_quick_partition(arr,start,end)
		arr = sort_quick_quick(arr,start,pivot-1)
		arr = sort_quick_quick(arr,pivot+1,end)
	return arr

def sort_quick_partition(arr,start,end):
	iP = sort_quick_pivot(arr,start,end)
	vP = arr[iP]
	arr[iP] = arr[end-1]
	arr[end-1] = vP
	iC = start
	for i in range(start,end):
		if arr[i] < vP:
			swap = arr[i]
			arr[i] = arr[iC]
			arr[iC] = swap
			iC += 1
	swap = arr[end-1]
	arr[end-1] = arr[iC]
	arr[iC] = swap
	return (arr,iC)

def sort_quick_pivot(arr,start,end):
	return (start + end) / 2


print "raw:   {0}".format(array_input)
array_merge = sort_merge(array_input)
print "merge: {0}".format(array_merge)
array_quick = sort_quick(array_input)
print "quick: {0}".format(array_quick)
array_heap  = sort_heap(array_input)
print "heap:  {0}".format(array_heap)
