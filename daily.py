from collections import defaultdict, deque

def find_min_changes(directed_edges):
    graph = defaultdict([])
    for a, b in directed_edges:
        graph[a].append((b, True))
        graph[b].append((a, False))
    
    count = 0
    visited = set([0])
    q = deque([0])

    while len(q):
        cur_node = q.popleft()
        for neighbor, directed in graph[cur_node]:
            if neighbor not in visited:
                q.append(neighbor)
                visited.add(neighbor)
                if directed:
                    count += 1
    return count

def find_custom(func, val):
    x, y = 1, 1000
    ret = []
    while x <= 1000 and y >= 1:
        temp = func(val)
        if temp == val:
            ret.append([x, y])
        elif temp < val:
            x += 1
        else:
            y -= 1
    return ret

def find_hamming(num1, num2):
    diff = num1 ^ num2
    count = 0
    while diff > 0:
        count += diff & 0b1
        diff >>= 1

def nim_game(n):
    return n % 4 != 0

def order_colors(nums):
    left, mid, right = 0, 0, len(nums) - 1
    while left <= right:
        if nums[mid] == 0:
            nums[left], nums[mid] = nums[mid], nums[left]
            left += 1
            mid += 1
        elif nums[mid] == 1:
            mid += 1
        else:
            nums[right], nums[mid] = nums[mid], nums[right]
            high -= 1

def min_digits(num: str, k:int):
    stack = []
    for digit in num:
        if k>0 and stack and digit > stack[-1]:
            stack.pop()
            k -= 1
        stack.append(digit)
    while k > 0:
        stack.pop()
    
    ret = ''.join(stack).lstrip('0')
    return ret if ret else '0'


class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        stack = []
        cur_str  = ''
        for i in range(len(s) - 1, -1, -1):
            letter = s[i]
            if letter == '-':
                continue
            cur_str += letter.upper()
            if len(cur_str) == k:
                stack.append(cur_str)
                cur_str = ''
        if cur_str:
            stack.append(cur_str)
        
        return '-'.join(stack)[::-1]

def find_longest(input: str):
    path = {}
    longest = 0
    for line in input.split('\n'):
        depth = line.count('\t')
        name = line.lstrip('\t')
        if '.' in name:
            longest = max(longest, len(path[depth] + '/' + name))
        else:
            path[depth + 1] = path[depth] + '/' + name
    return longest


def two_sum(nums, target):
    sums = {}
    for i, num in enumerate(nums):
        if num in sums:
            return [sums[num], i]
        
        sums[target - num] = i

def prisoner_swap(cells, n):
    memo = {}

    def swap(curcell):
        return [0] + [int(curcell[i-1] == curcell[i+1])for i in range(1, len(cells) - 1)] + [0]
    
    while n > 0:
        index = tuple(cells)
        if index in memo:
            n %= (memo[index] - n)
            if n == 0:
                break
        else:
            memo[index] = n
        
        if n > 0:
            n -= 1
            cells = swap(cells)
    return cells

def isolate_vps(s):
    if not s:
        return s
    stack = []
    left = 0
    ret = ""
    for right, char in enumerate(s):
        if stack == '(':
            stack.append(char)
        else:
            stack.pop()
        if not stack:
            ret += s[right + 1: left]
    return ret

def alice_game(n):
    return n % 2 == 0

def most_words(paragraph: str, blocked: list[str]):
    blocked = set(blocked)
    cleaned_par = []
    for letter in paragraph:
        if ord('A') <= ord(letter) <= ord('z'):
            cleaned_par.append(letter.lower())
        else:
            cleaned_par.append(' ')
    paragraph = ''.join(cleaned_par)

    word_count = defaultdict(int)
    max_word = ''
    max_count = 0
    for word in cleaned_par.split(' '):
        if word not in blocked:
            word_count[word] += 1
            if word_count[word] > max_count:
                max_count = word_count[word]
                max_word = word
    return max_word

def removeMinUnique(nums, maxUnique):
    counts = {}
    for num in nums:
        if num in counts:
            counts[num] += 1
        else:
            counts[num] = 1
    
    sorted_nums = sorted(nums, reverse=True)
    removals = 0

    while(len(sorted_nums) > maxUnique):
        removals += counts.pop()

def maxMedian(nums):
    sorted_nums = sorted(nums)

    maxMedian = 0

    while(len(sorted_nums) >= 3):
        sorted_nums.pop()
        maxMedian += sorted_nums.pop()
        sorted_nums.pop(0)
    
    return maxMedian

def returnToOrigin(sequence):
    steps = sequence.split()
    dirs = {
        "N": [0, 1],
        "S": [0, -1],
        "W": [-1, 0],
        "E": [0, 1]
    }
    origin = [0, 0]
    for step in steps:
        direction = dir[step[0]]
        mag = int(step[1:])
        origin += [direction[0]*mag + origin[0], direction[1]*mag + origin[1]]
    return origin == [0, 0]

