# Average of Subtree — Approach

## Problem

Given the `root` of a binary tree, return the number of nodes where the
value of the node equals the **average** (rounded down / floor division)
of the values in its subtree — including the node itself.

For each node `x`, let `subtree(x)` be `x` together with all of its
descendants. The node `x` counts toward the answer if:

```
x.val == floor( sum(v for v in subtree(x)) / count(v for v in subtree(x)) )
```

## Key Idea

The average of a subtree depends only on two things:

1. The **sum** of all node values in that subtree.
2. The **count** of nodes in that subtree.

Both of these can be computed bottom-up: the sum/count of a subtree
rooted at `x` is just `x.val` plus the sum/count from the left subtree
and the right subtree. This is a classic **post-order (bottom-up) DFS**
pattern — you need the answers from the children before you can compute
the answer for the parent.

So instead of recomputing the sum and count for every subtree from
scratch (which would be `O(n)` per node, `O(n^2)` overall), each node
computes its own `(sum, count)` pair in `O(1)` extra work once its
children's pairs are known, giving a single linear pass over the tree.

## Algorithm (Post-order DFS)

For each call `dfs(root)`:

1. **Base case:** if `root == nullptr`, this represents an empty
   subtree, which contributes nothing to any sum/count. Return
   `{sum: 0, count: 0}`.

2. **Recurse left, then right:**
   - `left = dfs(root->left)` → `{sum, count}` of the left subtree.
   - `right = dfs(root->right)` → `{sum, count}` of the right subtree.

   Because both children are fully resolved before we touch the
   current node, this is post-order traversal.

3. **Combine at the current node:**
   ```cpp
   int sum   = left.first  + right.first  + root->val;
   int count = left.second + right.second + 1;
   ```
   `sum` is the total of every value in the subtree rooted at
   `root` (left subtree + right subtree + the node itself).
   `count` is the total number of nodes in that subtree
   (left count + right count + 1 for the node itself).

4. **Check the average condition:**
   ```cpp
   int average = sum / count;   // integer division => floor, since sum, count >= 0
   if (root->val == average) {
       ans++;
   }
   ```
   Integer division in C++ on two non-negative operands (`sum >= 0`
   and `count >= 1`) truncates toward zero, which is exactly the
   `floor()` behavior required by the problem.

5. **Propagate results upward:**
   ```cpp
   return {sum, count};
   ```
   The caller (the parent's `dfs` call) uses this pair to compute its
   own sum/count without ever re-walking the subtree.

The wrapper function `averageOfSubtree(root)` just kicks off the
recursion and returns the accumulated `ans` counter once the full
traversal is done.

## Why `count` starts at 0, not 1

The base case returns `{0, 0}` for a `nullptr` child, not `{0, 1}`,
because a null child contributes **zero** nodes and **zero** value to
its parent's subtree — it isn't itself a node. The `+1` for "count the
current node" only happens once, at the node that actually exists,
in the combine step (`count = left.second + right.second + 1`).

## Dry-Run Example

```
        7
       / \
      3   5
```

- `dfs(nullptr)` (children of leaves 3 and 5) → `{0, 0}` each time.
- `dfs(3)`: `left = {0,0}`, `right = {0,0}`
  → `sum = 3`, `count = 1`, `average = 3/1 = 3`
  → `3 == 3` → `ans++` (ans = 1)
  → returns `{3, 1}`
- `dfs(5)`: similarly `sum = 5`, `count = 1`, `average = 5`
  → `ans++` (ans = 2)
  → returns `{5, 1}`
- `dfs(7)`: `left = {3,1}`, `right = {5,1}`
  → `sum = 3 + 5 + 7 = 15`, `count = 1 + 1 + 1 = 3`
  → `average = 15 / 3 = 5`
  → `7 != 5` → not counted
  → returns `{15, 3}`

Final answer: `ans = 2` (nodes `3` and `5` each equal the average of
their own single-node subtree).

## Complexity

- **Time:** `O(n)` — each node is visited exactly once, and the work
  done per node (sum/count combination, division, comparison) is
  `O(1)`.
- **Space:** `O(h)` for the recursion call stack, where `h` is the
  height of the tree — `O(log n)` for a balanced tree, `O(n)` in the
  worst case (a completely skewed/linear tree).

## Why This Pattern Generalizes

This "return an aggregate up the recursion, decide something at each
node using that aggregate, keep a running global answer" shape shows
up constantly in tree problems: subtree sums, subtree sizes, diameter
of a binary tree, balanced-tree checks, "count subtrees satisfying
property X", etc. The reusable template is:

```cpp
ResultType dfs(TreeNode* node) {
    if (!node) return /* identity value(s) */;

    auto left  = dfs(node->left);
    auto right = dfs(node->right);

    // combine left, right, and node->val into this node's result
    ResultType current = combine(left, right, node->val);

    // optionally use `current` to update a global answer here
    maybeUpdateGlobalAnswer(current, node);

    return current;
}
```
