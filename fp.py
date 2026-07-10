# basic data types 

lst = []
range(3) = [0, 1, 2]

"name"[0:3] = "name"[:3] # = "nam" 
"name"[3:] = "e"
"name"[3:-1] = ""

# sorting : O(nlogn)
# always try to sort first ! 
sorted_lst = sorted(lst, key=None, reverse=False) # new array
lst.sort(key=None, reverse=False)  # mutate array 

# key = rule to sort by
# lambda input: output 
lst = [(1, 'a'), (2, 'b')]
sorted_lst = sorted(lst, key=lambda x: x[0]) 
lst.sort(key=lambda x: x[1]) 
lst.sort(key=lambda x: x[1], reverse=True) # reverse order! put - in front of ints to reverse
lst.sort(key=lambda x: (-x[0], x[1])) # sort by 2 params at once

dict = {}
dict['a'] = 1 # {'a' : 1}
# for key, value in dict

from collections import defaultdict
dict = defaultdict(int) # default 0
dict = defaultdict(list) # default []


# element in set : O(1)
# faster than element in list : O(n) !
set = set([1], 2) # unordered UNIQUE data 
set.add('3')
set.remove(2)


str = "hi u"
indiv = str.split() # ["hi", "u"] 
" ".join(indiv) = "hi u" # join with " "
str.replace(" ", "") = "hiu"


# must wrap in list() ! 
list(map(lambda x: x**2, lst)) # apply to each item 
list(zip(lst, lst)) # (,) item tuple 
list(filter(lambda x: x % 2 == 0, lst)) # true items only


stack = [] # array O(1)
stack.append(1) # push
stack.pop() # pop


from collections import deque # doubly linked list O(1) (otherwise list O(n))
queue = deque() # double ended queue
queue.append(1) # enqueue
queue.popleft() # dequeue

queue.appendleft('2') # append left 
queue.append('2') # append right 
queue.popleft() # pop left 
queue.pop() # pop right


import heapq # heap = priority queue! (min by default, max by -1 * val)
q = [2, 3]
item = heapq.heappop(q) # delete min element 
heapq.heappush(q, 'ok')

q = [-4]
heapq.heappush(q, -2) # reverse heapq order (biggest first)


from collections import Counter
count = [2, 3, 4, 2]
tally = Counter(count) # = {2 : 2, 3 : 1, 4 : 1} dictionary that counts occurrences