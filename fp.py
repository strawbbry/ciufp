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


from collections import deque # doubly linked list O(1)
queue = deque()
queue.append(1) # enqueue
queue.popleft() # dequeue
