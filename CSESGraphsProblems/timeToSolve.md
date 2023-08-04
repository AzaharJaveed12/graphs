# 1_countingRooms 
    Direct implementation of DFS.

# 2_Labyrinth 
    Took a lot of time to optimize how to find the path.
    NOTE: when we need to find directions in the matrix:
            1.  place a 2D parent matrix.
            2. update parent matrix when we visit parent[i + X[dir]][j + Y[dir]] to dir
            3. while retriving, use reverse operation of direction. i.e i -= X[dir]
                as we are changing the direction of traversing..

    WHEN HE SAYS MINIMUM PATHT THINK AS BFS...!!

# 3 