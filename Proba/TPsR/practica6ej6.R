#a)  Generar  muestras  de  tama ̃no  25,  50  y  100  de  una  distribuci ́on  normal.  ConstruirQQ–plots para cada una de ellas, para comparar con los quantiles de la distribici ́onnormal. Repetir varias veces.
muestra25norm <- rnorm(25, 0,1)
muestra50norm <- rnorm(50, 0,1)
muestra100norm <- rnorm(100, 0,1)
qqnorm(rnorm(25, 0,1))
qqnorm(rnorm(50, 0,1))
qqnorm(rnorm(100, 0,1))

#b)  Repetir para una Γ(5,12) (con los cuantiles de la distribuci ́on normal y tambi ́en conlos de la Γ).
muestra100gamma <- rgamma(100, shape = 5, scale = 2)
qqnorm(muestra100gamma)
qqplot(muestra100gamma, qgamma(seq(0, 1, length = 100), shape = 5, scale = 2))
#c)  Repetir paraY=ZUdondeZ∼N(0,1) yU∼U(0,1) independientes.
#no se bro
#d)  Repetir para una distribuci ́on uniforme.
qqnorm(runif(100))
#e)  Repetir para una distribuci ́on exponencial.
qqnorm(rexp(100, 2))
#f)  ¿Puede distinguir, en base a los QQ–plots, entre la distribuci ́on normal y las siguien-tes distribuciones que no son normales?
#mmmm, si?
