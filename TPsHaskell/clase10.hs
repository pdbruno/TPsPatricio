ype Polinomio = [Float]
type Complejo = (Float, Float)

limpiar :: [Float] -> Polinomio
limpiar (0:xs) = limpiar xs
limpiar pol = pol

grado :: Polinomio -> Integer
grado [] = undefined
grado pol = toInteger(length pol) - 1

evaluar :: Polinomio -> Float -> Float
evaluar [x] _ = x
evaluar (x:xs) var = x * var^(grado (x:xs)) + evaluar xs var

derivada :: Polinomio -> Polinomio
derivada [x] = []
derivada (x:xs) = [fromInteger(grado (x:xs)) * x] ++ derivada xs

derivadaNesima :: Integer -> Polinomio -> Polinomio
derivadaNesima 0 pol = pol
derivadaNesima n pol = derivadaNesima (n-1) (derivada pol)

suma :: Polinomio -> Polinomio -> Polinomio
suma [] pol = pol
suma pol [] = pol
suma a b = limpiar ((suma (init a) (init b)) ++ [last a + last b])

productoPorEscalar :: Float -> Polinomio -> Polinomio
productoPorEscalar 0 _ = []
productoPorEscalar _ [] = []
productoPorEscalar a (x:xs) = [a*x] ++ productoPorEscalar a xs

productoPorMonomio :: (Float, Integer) -> Polinomio -> Polinomio
productoPorMonomio (0, _) _ = []
productoPorMonomio _ [] = []
productoPorMonomio (a, n) pol = productoPorEscalar a pol ++ listaDeNCeros n

listaDeNCeros :: Integer -> [Float]
listaDeNCeros 0 = []
listaDeNCeros n = (0:(listaDeNCeros (n-1)))

producto :: Polinomio -> Polinomio -> Polinomio
producto [] pol = []
producto pol [] = []
producto (x:xs) b = suma (productoPorMonomio (x, (grado (x:xs))) b) (producto xs b)

sumaC :: Complejo -> Complejo -> Complejo
sumaC (a,b) (c,d) = (a+c, b+d)

productoC :: Complejo -> Complejo -> Complejo
productoC (a,b) (c,d) = ((a*c)-(b*d), (a*d)-(b*c))

potencia :: Complejo -> Integer -> Complejo
potencia z 0 = (1, 0)
potencia z 1 = z
potencia z 2 = productoC z z
potencia z n | mod n 2 == 0 = potencia (potencia z 2) (div n 2)
			 | otherwise = productoC z (potencia z (n-1))

evaluarComplejo :: Polinomio -> Complejo -> Complejo
evaluarComplejo [x] _ = (x, 0)
evaluarComplejo (x:xs) z = sumaC (productoC (x,0) (potencia z (grado (x:xs)))) (evaluarComplejo xs z)

