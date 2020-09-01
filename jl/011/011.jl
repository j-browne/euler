#!/usr/bin/env julia

using DelimitedFiles

function product(grid, start, direction, len)
  product = 1
  pos = start
  for _ in 1:len
    product *= grid[pos[1], pos[2]]
    pos = (pos[1] + direction[1], pos[2] + direction[2])
  end
  product
end

function biggest_product(grid, len)
  biggest = 0
  (height, width) = size(grid)

  for i in 1:(height - len + 1)
    for j in 1:width
      biggest = max(biggest, product(grid, (i, j), (1, 0), len))
    end
  end

  for i in 1:height
    for j in 1:(width - len + 1)
      biggest = max(biggest, product(grid, (i, j), (0, 1), len))
    end
  end

  for i in 1:(height - len + 1)
    for j in 1:(width - len + 1)
      biggest = max(biggest, product(grid, (i, j), (1, 1), len))
    end
  end

  for i in 1:(height - len + 1)
    for j in len:width
      biggest = max(biggest, product(grid, (i, j), (1, -1), len))
    end
  end

  biggest
end

grid = readdlm("input.txt", ' ', Int, '\n')
println(biggest_product(grid, 4))
