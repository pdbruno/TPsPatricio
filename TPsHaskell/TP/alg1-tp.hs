type Set a = [a]
type Usuario = (Integer, String) -- (id, nombre)
type Relacion = (Usuario, Usuario) -- usuarios que se relacionan
type Publicacion = (Usuario, String, Set Usuario) -- (usuario que publica, texto publicacion, likes)
type RedSocial = (Set Usuario, Set Relacion, Set Publicacion)

-- Funciones basicas

usuarios :: RedSocial -> Set Usuario
usuarios (us, _, _) = us

relaciones :: RedSocial -> Set Relacion
relaciones (_, rs, _) = rs

publicaciones :: RedSocial -> Set Publicacion
publicaciones (_, _, ps) = ps

idDeUsuario :: Usuario -> Integer
idDeUsuario (id, _) = id

nombreDeUsuario :: Usuario -> String
nombreDeUsuario (_, nombre) = nombre

usuarioDePublicacion :: Publicacion -> Usuario
usuarioDePublicacion (u, _, _) = u

likesDePublicacion :: Publicacion -> Set Usuario
likesDePublicacion (_, _, us) = us

-- Defino una red social de ejemplo para testear las funciones
redEjemplo :: RedSocial
redEjemplo = ([(1, "pato"), (2,"marto"), (3, "zion"), (4, "gonza"), (5, "rava"), (6, "nacho"), (7, "ale"), (8, "riki")], [((7, "ale"), (8, "riki")), ((1, "pato"), (2,"marto")), ((2,"marto"), (3, "zion")), ((3, "zion"), (4, "gonza")), ((5, "rava"), (6, "nacho")), ((1, "pato"), (3, "zion")), ((2,"marto"), (5, "rava")), ((5, "rava"), (3, "zion"))], [((1, "pato"), "hola me gusta el pan", [(1, "pato"), (2,"marto"), (3, "zion"), (5, "rava")]), ((2, "marto"), "skere", []), ((1, "pato"), "me sigue gustando el pan", [(3, "zion"), (5, "rava")])])

redEjemplo2 :: RedSocial
redEjemplo2 = ([(1, "1"), (2, "2"), (3, "3"), (4, "4"), (5, "5"), (6, "6"), (7, "7"), (8, "8"), (9, "9")],[((8, "8"), (9, "9")), ((1, "1"), (3, "3")), ((1, "1"), (4, "4")), ((6, "6"), (3, "3")), ((2, "2"), (4, "4")), ((7, "7"), (4, "4")), ((2, "2"), (5, "5"))] ,[])
-- Ejercicios

-- Dada una red social retorna un conjunto con los nombres de todos los usuarios.
nombresDeUsuarios :: RedSocial -> Set String
nombresDeUsuarios ([], _, _) = []
nombresDeUsuarios (((_, nombre):xs), _, _) = quitarRepeticiones([nombre] ++ nombresDeUsuarios (xs, [], []))

quitarRepeticiones :: Set String -> Set String
quitarRepeticiones [] = []
quitarRepeticiones (x:xs) | elem x xs = quitarRepeticiones xs
                          | otherwise = (x:(quitarRepeticiones xs))
-- nombresDeUsuarios redEjemplo = ["pato","marto","zion","gonza","rava","nacho","ale","riki"]

-- Dada una red social y un usuario retorna el conjunto de amigos del mismo
amigosDe :: RedSocial -> Usuario -> Set Usuario
amigosDe (_, [], _) usuario = []
amigosDe (_, ((a, b):xs), _) usuario | a == usuario = [b] ++ amigosDe ([], xs, []) usuario
amigosDe (_, ((a, b):xs), _) usuario | b == usuario = [a] ++ amigosDe ([], xs, []) usuario
amigosDe (_, ((a, b):xs), _) usuario | otherwise = amigosDe ([], xs, []) usuario
-- amigosDe redEjemplo (1, "pato") = [(2,"marto"),(3,"zion")]

-- Dada una red social y un usuario retorna la cantidad de amigos de dicho usuario
cantidadDeAmigos :: RedSocial -> Usuario -> Int
cantidadDeAmigos red usuario = length (amigosDe red usuario)
-- cantidadDeAmigos redEjemplo (1, "pato") = 2

-- Dada una red social retorna el usuario con mas amigos. De existir más de uno devuelve cualquiera de ellos.
usuarioConMasAmigos :: RedSocial -> Usuario
usuarioConMasAmigos ((x:xs), [], _) = x
usuarioConMasAmigos (usuarios, relaciones, _) = masAmigosAux (tail usuarios) relaciones (head usuarios)

masAmigosAux :: Set Usuario -> Set Relacion -> Usuario -> Usuario
masAmigosAux [] _ masAmigos = masAmigos
masAmigosAux (x:xs) relaciones masAmigos | cantActual >= maxAmigos = masAmigosAux xs relaciones x
                                         | cantActual < maxAmigos = masAmigosAux xs relaciones masAmigos
                                         where maxAmigos = cantidadDeAmigos ([], relaciones, []) masAmigos
                                               cantActual = cantidadDeAmigos ([], relaciones, []) x

-- usuarioConMasAmigos redEjemplo = (3,"zion")

-- Dada una red social retorna True si algún usuario tiene más de un millón de amigos
estaRobertoCarlos :: RedSocial -> Bool
estaRobertoCarlos ([], _, _) = False
estaRobertoCarlos ((x:xs), relaciones, _) | cantidadDeAmigos ((x:xs), relaciones, []) x > 1000000 = True
                                          | otherwise = estaRobertoCarlos (xs, relaciones, [])
-- estaRobertoCarlos redEjemplo = False

-- Dada una red social y un usuario retorna el conjunto de publicaciones del mismo.
publicacionesDe :: RedSocial -> Usuario -> Set Publicacion
publicacionesDe (_, _, []) _ = []
publicacionesDe (_, _, (x:xs)) usuario | usuarioDePublicacion x == usuario = [x] ++ publicacionesDe ([], [], xs) usuario
                                       | otherwise = publicacionesDe ([], [], xs) usuario
-- publicacionesDe redEjemplo (1, "pato") = [((1,"pato"),"hola me gusta el pan",[(1,"pato"),(2,"marto"),(3,"zion")]),((1,"pato"),"me sigue gustando el pan",[(3,"zion"),(5,"rava")])]


-- Dada una red social y un usuario retorna el conjunto de publicaciones a las que el usuario les dió like.
publicacionesQueLeGustanA :: RedSocial -> Usuario -> Set Publicacion
publicacionesQueLeGustanA (_, _, []) _ = []
publicacionesQueLeGustanA (_, _, (x:xs)) usuario | elem usuario (likesDePublicacion x) = [x] ++ publicacionesQueLeGustanA ([], [], xs) usuario
                                                 | otherwise = publicacionesQueLeGustanA ([], [], xs) usuario

-- publicacionesQueLeGustanA redEjemplo (3,"zion") = [((1,"pato"),"hola me gusta el pan",[(1,"pato"),(2,"marto"),(3,"zion")]),((1,"pato"),"me sigue gustando el pan",[(3,"zion"),(5,"rava")])]

-- Dada una red social y dos usuarios indica si les gustan las mismas publicaciones
lesGustanLasMismasPublicaciones :: RedSocial -> Usuario -> Usuario -> Bool
-- En este caso puedo usar "==" porque las listas van a tener el mismo orden
-- También se puede checkear que el primer conjunto está incluído en el segundo y viceversa
lesGustanLasMismasPublicaciones red usr1 usr2 = publicacionesQueLeGustanA red usr1 == publicacionesQueLeGustanA red usr2

-- lesGustanLasMismasPublicaciones redEjemplo (3,"zion") (5,"rava") = True
-- lesGustanLasMismasPublicaciones redEjemplo (3,"zion") (1,"pato") = False

-- Dada una red social y un usuario u, indica si existe un usuario que le puso like a todas las publicaciones de u.
tieneUnSeguidorFiel :: RedSocial -> Usuario -> Bool
tieneUnSeguidorFiel ([], _, _) _ = False
tieneUnSeguidorFiel ((x:xs), _, pub) usuario | publicacionesDe ([], [], pub) usuario == [] = False
                                             | (usuario /= x) && (incluidoPub (publicacionesDe ([], [], pub) usuario) (publicacionesQueLeGustanA ([], [], pub) x)) = True
                                             | otherwise = tieneUnSeguidorFiel (xs, [], pub) usuario

incluidoPub :: Set Publicacion -> Set Publicacion -> Bool
incluidoPub [] (x:xs) = True
incluidoPub (x:xs) [] = False
incluidoPub (x:xs) conj2 = elem x conj2 && incluidoPub xs conj2
-- tieneUnSeguidorFiel redEjemplo (2,"marto") = False
-- tieneUnSeguidorFiel redEjemplo (1,"pato") = True (el seguidor fiel es (3,"zion"))

-- Dada una red social y dos usuarios, indica si existe una secuencia de usuarios relacionados para llegar del primero al segundo.
existeSecuenciaDeAmigos :: RedSocial -> Usuario -> Usuario -> Bool
existeSecuenciaDeAmigos red start target = elem target (generarConjFinal red (start:(amigosDe red start)))

-- existeSecuenciaDeAmigos redEjemplo (1, "pato") (6, "nacho") = True
-- existeSecuenciaDeAmigos redEjemplo (1, "pato") (7, "ale") = False
-- existeSecuenciaDeAmigos redEjemplo2 (1, "1") (8, "8") = False
-- existeSecuenciaDeAmigos redEjemplo2 (7, "7") (6, "6") = True

-- Devuelve todos los usuarios a los que se puede llegar empezando por "start"
generarConjFinal :: RedSocial -> Set Usuario -> Set Usuario
generarConjFinal red conjstart | incluidoUsr ultimoresultado anteultimoresultado = ultimoresultado
                               | otherwise = generarConjFinal red ultimoresultado
  where todos = usuarios red
        anteultimoresultado = generarConjParcial red conjstart todos
        ultimoresultado = generarConjParcial red anteultimoresultado todos

generarConjParcial :: RedSocial -> Set Usuario -> Set Usuario -> Set Usuario
generarConjParcial red conjstart [] = conjstart
generarConjParcial red conjstart todos | hayInterseccion amigosactual conjstart = agregar amigosactual (generarConjParcial red conjstart (tail todos))
                                       | otherwise = generarConjParcial red conjstart (tail todos)
  where amigosactual = ((head todos):(amigosDe red (head todos)))

hayInterseccion :: Set Usuario -> Set Usuario -> Bool
hayInterseccion [] conj2 = False
hayInterseccion (x:xs) conj2 = elem x conj2 || hayInterseccion xs conj2

agregar :: Set Usuario -> Set Usuario -> Set Usuario
agregar [] conj = conj
agregar (x:xs) conj | elem x conj = agregar xs conj
			    		      | otherwise = agregar xs (x:conj)

incluidoUsr :: Set Usuario -> Set Usuario -> Bool
incluidoUsr [] (x:xs) = True
incluidoUsr (x:xs) [] = False
incluidoUsr (x:xs) conj2 = elem x conj2 && incluidoUsr xs conj2

-- Ejemplos

usuario1 = (1, "Juan")
usuario2 = (2, "Natalia")
usuario3 = (3, "Pedro")
usuario4 = (4, "Mariela")
usuario5 = (5, "Natalia")

relacion1_2 = (usuario1, usuario2)
relacion1_3 = (usuario1, usuario3)
relacion1_4 = (usuario4, usuario1) -- Notar que el orden en el que aparecen los usuarios es indistinto
relacion2_3 = (usuario3, usuario2)
relacion2_4 = (usuario2, usuario4)
relacion3_4 = (usuario4, usuario3)

publicacion1_1 = (usuario1, "Este es mi primer post", [usuario2, usuario4])
publicacion1_2 = (usuario1, "Este es mi segundo post", [usuario4])
publicacion1_3 = (usuario1, "Este es mi tercer post", [usuario2, usuario4])
publicacion1_4 = (usuario1, "Este es mi cuarto post", [])

publicacion2_1 = (usuario2, "Hello World", [usuario4])
publicacion2_2 = (usuario2, "Good Bye World", [usuario1, usuario4])

publicacion3_1 = (usuario3, "Lorem Ipsum", [])
publicacion3_2 = (usuario3, "dolor sit amet", [usuario2])
publicacion3_3 = (usuario3, "consectetur adipiscing elit", [usuario2, usuario4])

publicacion4_1 = (usuario4, "I am Alice. Not", [usuario1, usuario2])
publicacion4_2 = (usuario4, "I am Bob", [])
publicacion4_3 = (usuario4, "Just kidding, i am Mariela", [usuario1, usuario3])


usuariosA = [usuario1, usuario2, usuario3, usuario4]
relacionesA = [relacion1_2, relacion1_4, relacion2_3, relacion2_4, relacion3_4]
publicacionesA = [publicacion1_1, publicacion1_2, publicacion2_1, publicacion2_2, publicacion3_1, publicacion3_2, publicacion4_1, publicacion4_2]
redA = (usuariosA, relacionesA, publicacionesA)

usuariosB = [usuario1, usuario2, usuario3, usuario5]
relacionesB = [relacion1_2, relacion2_3]
publicacionesB = [publicacion1_1, publicacion1_2, publicacion1_3, publicacion1_4, publicacion3_1, publicacion3_2, publicacion3_3]
redB = (usuariosB, relacionesB, publicacionesB)


{-
Tests:
======

nombresDeUsuarios redA ~~~> {Juan, Natalia, Pedro, Mariela}

amigosDe redA usuario1 ~~~> {usuario2, usuario4}
amigosDe redA usuario2 ~~~> {usuario1, usuario3, usuario4}
amigosDe redA usuario4 ~~~> {usuario2, usuario1, usuario3}

cantidadDeAmigos redA usuario1 ~~~> 2

Notar que para usuarioConMasAmigos podría haber más de un resultado válido.
usuarioConMasAmigos redA == usuario2 || usuarioConMasAmigos redA == usuario4 ~~~> True

estaRobertoCarlos redA ~~~> False

publicacionesDe redA usuario2 ~~~> {publicacion2_1, publicacion2_2}

publicacionesQueLeGustanA redA usuario1 ~~~> {publicacion2_2, publicacion4_1}

lesGustanLasMismasPublicaciones redB usuario1 usuario2 ~~~> False

tieneUnSeguidorFiel redA usuario1 ~~> True
tieneUnSeguidorFiel redA usuario2 ~~> True
tieneUnSeguidorFiel redA usuario3 ~~> False

existeSecuenciaDeAmigos redA usuario1 usuario3 ~~~> True

----

nombresDeUsuarios redB ~~~> {Juan, Pedro, Natalia}

amigosDe redB usuario1 ~~~> {usuario2}
amigosDe redB usuario2 ~~~> {usuario1, usuario3}
amigosDe redB usuario3 ~~~> {usuario2}
amigosDe redB usuario5 ~~~> {}

cantidadDeAmigos redB usuario1 ~~~> 1
cantidadDeAmigos redB usuario2 ~~~> 2
cantidadDeAmigos redB usuario3 ~~~> 1
cantidadDeAmigos redB usuario5 ~~~> 0

usuarioConMasAmigos redB ~~~> usuario2

estaRobertoCarlos redB ~~~> False

publicacionesDe redB usuario1 ~~~> {publicacion1_1, publicacion1_2, publicacion1_3, publicacion1_4}
publicacionesDe redB usuario2 ~~~> {}
publicacionesDe redB usuario3 ~~~> {publicacion3_1, publicacion3_2, publicacion3_3}
publicacionesDe redB usuario5 ~~~> {}

publicacionesQueLeGustanA redB usuario1 ~~~> {}
publicacionesQueLeGustanA redB usuario2 ~~~> {publicacion1_1, publicacion1_3, publicacion3_2, publicacion3_3}
publicacionesQueLeGustanA redB usuario3 ~~~> {}
publicacionesQueLeGustanA redB usuario5 ~~~> {}

lesGustanLasMismasPublicaciones redB usuario1 usuario3 ~~~> True
lesGustanLasMismasPublicaciones redB usuario1 usuario2 ~~~> False

tieneUnSeguidorFiel redB usuario1 ~~> False
tieneUnSeguidorFiel redB usuario2 ~~> False
tieneUnSeguidorFiel redB usuario3 ~~> False
tieneUnSeguidorFiel redB usuario5 ~~> False

existeSecuenciaDeAmigos redB usuario1 usuario3 ~~~> True
existeSecuenciaDeAmigos redB usuario1 usuario5 ~~~> False

-}
