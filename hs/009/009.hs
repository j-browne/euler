main :: IO ()
main = print $ head [ a*b*(1000-a-b) | a <- [100..500], b <- [100..500], a^2+b^2 == (1000-a-b)^2]
