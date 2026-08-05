# LeetCode 3310 - Remove Methods From Project

## Approach

We model the project as a **directed graph**, where:

- Each method is represented as a node.
- An edge `u → v` means **method `u` invokes method `v`**.

The problem consists of two main tasks:

1. Find all **suspicious methods** starting from the buggy method `k`.
2. Determine whether this entire suspicious group can be removed.

---

## Step 1: Build the Graph

We first convert the `invocations` array into an adjacency list.

For every invocation

```cpp
[u, v]
```

we add an edge

```text
u → v
```

This allows us to efficiently traverse all methods invoked by any method.

For example,

```text
invocations = [[0,1],[1,2],[1,3]]
```

produces the graph

```text
0
|
v
1
|\
| \
v  v
2  3
```

---

## Step 2: Find All Suspicious Methods

The buggy method `k` is already known.

Every method that can be reached from `k` (either directly or indirectly) is also considered suspicious.

To find all such methods, we perform a **Depth First Search (DFS)** starting from `k`.

During DFS:

- Mark the current method as suspicious.
- Visit every method it invokes.
- Continue recursively until no new methods can be reached.

For example,

```text
k = 1

0 → 1 → 2
    |
    v
    3
```

Starting DFS from `1` visits

```text
1
2
3
```

Therefore,

```text
Suspicious = {1,2,3}
```

Method `0` is not suspicious because it is not reachable from `1`.

---

## Step 3: Check Whether Removal Is Possible

According to the problem statement:

> A group of methods can only be removed if **no method outside the group invokes any method inside the group.**

This means we must inspect every invocation in the graph.

Suppose we find an edge

```text
u → v
```

where

- `u` is **not suspicious**
- `v` **is suspicious**

Then a safe method depends on a suspicious method.

Removing the suspicious group would leave a broken invocation.

Hence, removal is **not allowed**.

In that case, we return **all methods** unchanged.

The condition is simply:

```cpp
if (!suspicious[u] && suspicious[v])
```

then

```text
Return every method from 0 to n−1.
```

---

## Step 4: Remove the Suspicious Methods

If no outside method invokes a suspicious method, then the suspicious group is completely isolated.

It is safe to remove every suspicious method.

Therefore, we simply return all methods that are **not** marked as suspicious.

---

# Dry Run

## Example 1

### Input

```text
n = 4

k = 1

invocations =
[
 [1,2],
 [0,1],
 [3,2]
]
```

### Graph

```text
0 → 1 → 2
      ^
      |
3 ----+
```

### DFS from 1

Visited methods:

```text
1
2
```

Suspicious methods:

```text
{1,2}
```

Now inspect every edge.

Edge

```text
0 → 1
```

connects

```text
Non-suspicious → Suspicious
```

which violates the condition.

Therefore,

```text
Answer = [0,1,2,3]
```

Nothing can be removed.

---

## Example 2

### Input

```text
n = 5

k = 0

invocations =
[
 [1,2],
 [0,2],
 [0,1],
 [3,4]
]
```

### Graph

```text
0
|\
| \
v  v
1  2

3 → 4
```

### DFS from 0

Visited methods

```text
0
1
2
```

Suspicious methods

```text
{0,1,2}
```

Check every invocation.

There is **no** edge

```text
Non-suspicious → Suspicious
```

Therefore the suspicious group is isolated.

Remove it.

Remaining methods

```text
[3,4]
```

---

## Example 3

### Input

```text
n = 3

k = 2

invocations =
[
 [1,2],
 [0,1],
 [2,0]
]
```

### Graph

```text
0 → 1
^   |
|   v
2 ←-
```

DFS from `2` reaches

```text
2
0
1
```

Every method becomes suspicious.

Since there are **no outside methods**, removal is valid.

Answer

```text
[]
```

---

# Why DFS Works

DFS explores every method reachable from the buggy method.

Since every reachable method is directly or indirectly invoked by `k`, DFS correctly identifies every suspicious method.

Each node is visited only once.

---

# Correctness

The algorithm works because:

1. DFS marks **exactly** all methods reachable from `k`.

2. Every invocation is checked once to ensure there is no dependency from outside the suspicious group.

3. If such a dependency exists, removing the suspicious methods would break the project, so we return every method.

4. Otherwise, the suspicious group is completely isolated and can safely be removed.

Hence, the algorithm always returns the correct answer.

---

# Complexity Analysis

Let

- **V** = number of methods (`n`)
- **E** = number of invocations

### Time Complexity

Building the graph:

```text
O(E)
```

DFS traversal:

```text
O(V + E)
```

Checking every invocation:

```text
O(E)
```

Overall:

```text
O(V + E)
```

---

### Space Complexity

Adjacency list:

```text
O(V + E)
```

Suspicious array:

```text
O(V)
```

DFS recursion stack (worst case):

```text
O(V)
```

Overall:

```text
O(V + E)
```

---

# Key Idea

Instead of trying to remove methods immediately:

1. Treat the methods as a **directed graph**.
2. Use **DFS** to find every suspicious method.
3. Verify that **no non-suspicious method invokes a suspicious one**.
4. If such an invocation exists, return every method.
5. Otherwise, return only the remaining non-suspicious methods.

This results in an efficient graph traversal solution with **O(V + E)** time complexity.
