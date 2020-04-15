a :: Integer -> Integer
a n | mod n 2 == 0 = div n 2
    | mod n 2 /= 0 = 3*n + 1

cantPasos :: (Integer, Integer) -> (Integer, Integer)
cantPasos (n, pasos) | n == 1 = (1, pasos + 1)
                     | n > 1 = cantPasos (a n, pasos + 1)

checkMax :: Integer -> (Integer, Integer) -> (Integer, Integer)
checkMax i (n, pasos)| (i > 1) && (snd (cantPasos (i, 0)) >= pasos) = checkMax (i-1) (i, snd (cantPasos (i, 0)))
                     | (i > 1) && (pasos > snd (cantPasos (i, 0))) = checkMax (i-1) (n, pasos)
                     | i == 1 = (n, pasos)

maximoCollatz :: Integer -> (Integer, Integer)
maximoCollatz i = checkMax i (1,3)
