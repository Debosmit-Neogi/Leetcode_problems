func recurse(curr, num int, matr *[][]int) {
    if curr == num {
        return
    }

    // Create the current row using the previous row from matr
    prevRow := (*matr)[curr-1]
    matrRow := []int{1}
    for i := 1; i < curr; i++ {
        matrRow = append(matrRow, prevRow[i-1]+prevRow[i])
    }
    matrRow = append(matrRow, 1)

    *matr = append(*matr, matrRow)
    recurse(curr+1, num, matr)
}

func generate(numRows int) [][]int {
	if numRows == 1 {
		return [][]int{[]int{1}}
	}
	matr := [][]int{[]int{1}, []int{1, 1}}

	recurse(2, numRows, &matr)

	return matr
}