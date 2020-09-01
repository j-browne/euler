fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
main :: IO ()
main = print $ sum [x | x <- take 35 fibs, x < 4000000, even x]
