class Solution {
public:

    struct Node {

        // Character at the beginning of this segment
        char leftChar;

        // Character at the end of this segment
        char rightChar;

        // Length of this segment
        int len;

        // Longest prefix containing the same character
        int leftLen;

        // Longest suffix containing the same character
        int rightLen;

        // Longest repeating-character substring
        // anywhere inside this segment
        int maxLen;
    };


    vector<Node> tree;


    // --------------------------------------------------
    // Merge two neighboring segments
    // --------------------------------------------------
    Node merge(Node left, Node right) {

        Node result;

        // Total length of the combined segment
        result.len = left.len + right.len;


        // The first character comes from the left segment
        result.leftChar = left.leftChar;

        // The last character comes from the right segment
        result.rightChar = right.rightChar;


        // Start with the best answer from either side.
        result.maxLen = max(left.maxLen, right.maxLen);


        // --------------------------------------------------
        // Find longest prefix
        // --------------------------------------------------

        // By default, prefix is the prefix of left segment.
        result.leftLen = left.leftLen;

        // If the entire left segment contains the same
        // character, and that character is also the first
        // character of the right segment, we can extend
        // the prefix into the right segment.
        if (left.leftLen == left.len &&
            left.rightChar == right.leftChar) {

            result.leftLen = left.len + right.leftLen;
        }


        // --------------------------------------------------
        // Find longest suffix
        // --------------------------------------------------

        // By default, suffix is the suffix of right segment.
        result.rightLen = right.rightLen;

        // If the entire right segment contains the same
        // character, and that character is also the last
        // character of the left segment, we can extend
        // the suffix into the left segment.
        if (right.rightLen == right.len &&
            left.rightChar == right.leftChar) {

            result.rightLen = right.len + left.rightLen;
        }


        // --------------------------------------------------
        // Find a repeating substring crossing the middle
        // --------------------------------------------------

        // If the last character of the left segment is the
        // same as the first character of the right segment,
        // their suffix and prefix can be joined.
        if (left.rightChar == right.leftChar) {

            int crossingLength =
                left.rightLen + right.leftLen;

            result.maxLen = max(result.maxLen, crossingLength);
        }


        return result;
    }


    // --------------------------------------------------
    // Build the segment tree
    // --------------------------------------------------
    void build(string &s, int node, int start, int end) {

        // Leaf node: represents one character
        if (start == end) {

            tree[node].leftChar = s[start];
            tree[node].rightChar = s[start];

            tree[node].len = 1;

            tree[node].leftLen = 1;
            tree[node].rightLen = 1;
            tree[node].maxLen = 1;

            return;
        }


        // Find middle of current segment
        int mid = start + (end - start) / 2;


        // Build left half
        build(s, node * 2, start, mid);

        // Build right half
        build(s, node * 2 + 1, mid + 1, end);


        // Combine left and right halves
        tree[node] = merge(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }


    // --------------------------------------------------
    // Update one character
    // --------------------------------------------------
    void update(int node, int start, int end,
                int index, char ch) {

        // We reached the required position
        if (start == end) {

            // Replace the character
            tree[node].leftChar = ch;
            tree[node].rightChar = ch;

            // Single character segment
            tree[node].len = 1;
            tree[node].leftLen = 1;
            tree[node].rightLen = 1;
            tree[node].maxLen = 1;

            return;
        }


        int mid = start + (end - start) / 2;


        // The index lies in the left half
        if (index <= mid) {

            update(
                node * 2,
                start,
                mid,
                index,
                ch
            );
        }

        // The index lies in the right half
        else {

            update(
                node * 2 + 1,
                mid + 1,
                end,
                index,
                ch
            );
        }


        // After updating one child, recompute the current
        // node using the information from both children.
        tree[node] = merge(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }


    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        int n = s.size();
        int k = queryIndices.size();


        // Segment tree needs approximately 4*n nodes.
        tree.resize(4 * n);


        // Build the initial tree.
        build(s, 1, 0, n - 1);


        vector<int> answer;


        // Process every query
        for (int i = 0; i < k; i++) {

            // Index that needs to be updated
            int index = queryIndices[i];

            // New character
            char ch = queryCharacters[i];


            // Update the segment tree
            update(
                1,
                0,
                n - 1,
                index,
                ch
            );


            // The root represents the entire string.
            //
            // Therefore root.maxLen is the longest
            // repeating-character substring in the
            // entire current string.
            answer.push_back(tree[1].maxLen);
        }


        return answer;
    }
};