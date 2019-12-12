type Set a = [a]

incluido :: Set Integer -> Set Integer -> Bool
incluido (x:xs) conj2 = elem x conj2 && incluido xs conj2
incluido [] (x:xs) = True
incluido (x:xs) [] = False

iguales :: Set Integer -> Set Integer -> Bool
iguales conj1 conj2 = incluido conj2 conj1 && incluido conj1 conj2

agregar :: Integer -> Set Integer -> Set Integer
agregar n conj | elem n conj = conj
			   | otherwise = (n:conj)

agregar2 :: Set Integer -> Set (Set Integer) -> Set (Set Integer)
agregar2 n conj | perteneceCjto n conj = conj
			    			| otherwise = (n:conj)

perteneceCjto :: Set Integer -> Set (Set Integer) -> Bool
perteneceCjto c [] = False
perteneceCjto c (x:xs) = iguales c x || perteneceCjto c xs

vacio :: Set Integer
vacio = []

agregarATodos :: Integer -> Set (Set Integer) -> Set (Set Integer)
agregarATodos n (x:xs) = agregar2 (agregar n x) (agregarATodos n xs)
agregarATodos n [] = []

partes :: Integer -> Set (Set Integer)
partes 0 = [[]]
partes n = partes (n-1) ++ agregarATodos n (partes (n-1))

productoCartesiano :: Set Integer -> Set Integer -> Set (Integer, Integer)
productoCartesiano (x1:xs1) conj2 = (prodInterno x1 conj2) ++ (productoCartesiano xs1 conj2)
productoCartesiano [] _ = []

prodInterno :: Integer -> Set Integer -> Set (Integer,Integer)
prodInterno x1 (x2:xs2) | length xs2 > 0 = [(x1, x2)] ++ prodInterno x1 xs2
						| otherwise = [(x1, x2)]



agregarATodosTrucho :: Integer -> [[Integer]] -> [[Integer]]
agregarATodosTrucho n (x:xs) = [(n:x)] ++ agregarATodosTrucho n xs
agregarATodosTrucho n [] = []

variaciones :: Set Integer -> Integer -> Set [Integer]
variaciones conj 0 = [[]]
variaciones (x:xs) l = agregarATodosTrucho x (variaciones (x:xs) (l-1)) ++ agregarATodosTrucho (head xs) (variaciones (x:xs) (l-1))

insertarEn :: [Integer] -> Integer -> Integer -> [Integer]
insertarEn conj n i | toInteger (length conj) >= i = insertarAux conj n i 1
										| toInteger (length conj) < i = conj ++ [n]
										| conj == [] = [n]

insertarAux :: [Integer] -> Integer -> Integer -> Integer -> [Integer]
insertarAux (x:xs) n i cont | i > cont = [x] ++ insertarAux xs n i (cont+1)
														| i == cont = [n] ++ (x:xs)

permutaciones :: Integer -> [[Integer]]
permutaciones 0 = [[]]
permutaciones n = iterConj (permutaciones (n-1)) n

iterIns :: [Integer] -> Integer -> Integer -> [[Integer]]
iterIns conj n i | i > 1 = [insertarEn conj n i] ++ (iterIns conj n (i-1))
								 | i == 1 = [insertarEn conj n 1]

iterConj :: [[Integer]] -> Integer -> [[Integer]]
iterConj (x:xs) n | xs /= [] = iterIns x n n ++ iterIns (head xs) n n
									| xs == [] = iterIns x n n

--una paja sacarle las repeticiones, mas alla de eso anda bien
nBolitaskCajas :: Integer -> Integer -> Set (Set (Set Integer))
nBolitaskCajas 0 k = kCajas k
nBolitaskCajas n k = iterSoluciones n (nBolitaskCajas (n-1) k)

--perteneceCjto [[2,3],[1]] [[[2,3],[1]],[[2],[1,3]],[[3],[1,2]],[[],[1,2,3]],[[2,3],[1]],[[2],[1,3]],[[3],[1,2]],[[],[1,2,3]]]

--eliminarRepetidos2 :: Set (Set (Set Integer)) -> Set (Set (Set Integer))
--eliminarRepetidos2 (x:xs) | xs == [] = [x]
--													| perteneceCjto x xs = eliminarRepetidos2 xs
--													| not (perteneceCjto x xs) = [x] ++ eliminarRepetidos2 xs

iterSoluciones :: Integer -> Set (Set (Set Integer)) -> Set (Set (Set Integer))
iterSoluciones n (x:xs) | xs == [] = iterAgregar n x
												| xs /= [] = iterAgregar n x ++ iterSoluciones n xs

iterAgregar :: Integer -> Set (Set Integer) -> Set (Set (Set Integer))
iterAgregar n conj   | conj == [] = [[[n]]]
										 | tail conj == [] = [conj ++ [[n]]]
										 | tail conj /= [] = iterReemplazar n conj conj 1

reemplazar :: [[Integer]] -> [Integer] -> Integer -> [[Integer]]
reemplazar conj el i | toInteger (length conj) >= i = reemplazarAux conj el i 1
										 | toInteger (length conj) < i = init conj ++ [el]
										 | conj == [] = [el]

reemplazarAux :: [[Integer]] -> [Integer] -> Integer -> Integer -> [[Integer]]
reemplazarAux (x:xs) el i cont | i > cont = [x] ++ reemplazarAux xs el i (cont+1)
										 				  | i == cont = [el] ++ (xs)

iterReemplazar :: Integer -> Set (Set Integer) -> Set (Set Integer) -> Integer -> Set (Set (Set Integer))
iterReemplazar n conjRef (y:ys) i | ys == [] = [reemplazar conjRef (y ++ [n]) i]
															  	| ys /= [] = [reemplazar conjRef (y ++ [n]) i] ++ iterReemplazar n conjRef ys (i+1)


kCajas :: Integer -> Set (Set (Set Integer))
kCajas k | k > 1 = [[[]]] ++ kCajas (k-1)
				 | k == 1 = [[[]]]

--no anda bien nBolitaskCajas

listasOrdKNum :: Integer -> Integer -> Set (Set Integer)
listasOrdKNum 0 n = [[]]
listasOrdKNum k n = iterConj2 (listasOrdKNum (k-1) n) n

iterConj2 :: Set (Set Integer) -> Integer -> Set (Set Integer)
iterConj2 (x:xs) n | xs == [] = iterSubConj n x
									 | xs /= [] = iterSubConj n x ++ iterConj2 xs n


iterSubConj :: Integer -> Set Integer -> Set (Set Integer)
iterSubConj n conj | n == 0 = []
									 | elem n conj = iterSubConj (n-1) conj
									 | not(elem n conj) = [(n:conj)] ++ iterSubConj (n-1) conj


punto3 :: [[Integer]]
punto3 = filtrarPunto3 (variaciones [0,1] 6)

filtrarPunto3 :: [[Integer]] -> [[Integer]]
filtrarPunto3 (x:xs) | xs == [] && sumaConj x == 3 = [x]
										 | xs == [] && sumaConj x /= 3 = []
										 | xs /= [] && sumaConj x == 3 = [x] ++ filtrarPunto3 xs
										 | xs /= [] && sumaConj x /= 3 = filtrarPunto3 xs


sumaConj :: [Integer] -> Integer
sumaConj (x:xs) | xs == [] = x
								| xs /= [] = x + sumaConj xs

punto4 :: [[Integer]]
punto4 = filtrarPunto4 (variaciones [0,1] 5)

filtrarPunto4 :: [[Integer]] -> [[Integer]]
filtrarPunto4 (x:xs) | xs == [] && sumaConj x > 2 = [x]
										 | xs == [] && sumaConj x < 3 = []
										 | xs /= [] && sumaConj x > 2 = [x] ++ filtrarPunto4 xs
										 | xs /= [] && sumaConj x < 3 = filtrarPunto4 xs




subConj :: Integer -> Integer -> Set (Set Integer)
subConj k n = filtrarPartes k (partes n)

filtrarPartes :: Integer -> Set (Set Integer) -> Set (Set Integer)
filtrarPartes k (x:xs) | xs == [] && toInteger (length x) == k = [x]
											 | xs == [] && toInteger (length x) /= k = []
											 | xs /= [] && toInteger (length x) == k = [x] ++ filtrarPartes k xs
											 | xs /= [] && toInteger (length x) /= k = filtrarPartes k xs



subConj2 :: Integer -> Integer -> Set (Set Integer)
subConj2 0 n = [[]]
subConj2 k n = eliminarRepetidos (iterConj3 (subConj2 (k-1) n) n)

iterConj3 :: Set (Set Integer) -> Integer -> Set (Set Integer)
iterConj3 (x:xs) n | xs == [] = iterSubConj2 n x
									 | xs /= [] = iterSubConj2 n x ++ iterConj3 xs n


iterSubConj2 :: Integer -> Set Integer -> Set (Set Integer)
iterSubConj2 n conj | n == 0 = []
									 | elem n conj = iterSubConj2 (n-1) conj
									 | not(elem n conj) = [(n:conj)] ++ iterSubConj2 (n-1) conj

eliminarRepetidos :: Set (Set (Integer)) -> Set (Set (Integer))
eliminarRepetidos (x:xs) | xs == [] = [x]
								| perteneceCjto x xs = eliminarRepetidos xs
								| not (perteneceCjto x xs) = [x] ++ eliminarRepetidos xs
