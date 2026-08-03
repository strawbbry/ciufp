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


# stacks & queues

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


# trees & graphs 

def bfs(graph, root):
    queue = deque()
    visited = set()
    
    queue.append(root)
    visited.add(root)
    
    while queue:
        node = queue.popleft()
        for neighbour in graph[node]:
            if neighbour not in visited:
                visited.add(neighbour)
                queue.append(neighbour)
            
def dfs(graph, root):
    stack = [] # for backtrack via lifo
    visited = set()
    
    stack.append(root)
    visited.add(root)
    
    while stack:
        node = stack.pop()
        for neighbour in graph[node]:
            if neighbour not in visited:
                visited.add(neighbour)
                stack.append(neighbour)
                
                
# dynamic programming 

prac1 = [
    *[f"a{i}" for i in range(8)], # * unpacks one into [a0, ... a7, 2]
    2
] 

prac2 = {
    **{"x": 0}, # ** unpack for combining multiple 
    **{f"a{i}": f"a{p}" for i, p in zip(range(3), [1, 2, 3])}, # zip maps [0, 1, 2] with [1, 2, 3] 
}

def knapsack(total_weight, items): # 0/1 
    total_items = len(items)
    
    # 2d list:
    # [0] * (total_weight + 1) : create row of 0s
    # for _ in range(total_items + 1) : create row of 0s for each = cols
    dp = [[0] * (total_weight + 1) for _ in range(total_items + 1)]
    
    for i in range(total_items):
        for j in range(1, total_weight + 1):
            weight, value = items[i]
            
            dp[i + 1][j] = max(dp[i + 1][j - 1], dp[i][j])
            
            if j - weight >= 0:
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - weight] + value)
                
    return dp[total_items][total_weight]