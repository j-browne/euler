sumOfPow 0 y = 0
sumOfPow x y = (mod x 10) ^ y + (sumOfPow (div x 10) y)

sumOfSums [] y = 0
sumOfSums (x:xs) y = (if x == (sumOfPow x y) then x else 0) + (sumOfSums xs y)

main = print $ sumOfSums [10..1000000] 5
