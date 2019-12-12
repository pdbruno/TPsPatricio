#a)
l2 <- function(c, datos){
  sum((datos-c)^2)
}

vec <- rnorm(200, 4)
l2(0, vec)
l2(mean(vec), vec)

vec <- rpois(50, 4)
l2(4, vec)
l2(mean(vec), vec)

#el c que minimiza es el promedio de los datos. Esto se demuestra derivando e igualando a 0

#b) medio que ya lo explico la profe

#par
vec <- rnorm(10)
l1 <- function(c){
  sum(abs(vec-c))
}
kk <- sapply(vec, l1)
plot(vec, kk)

#impar
vec <- rnorm(9)
l1 <- function(c){
  sum(abs(vec-c))
}
kk <- sapply(vec, l1)
plot(vec, kk)
