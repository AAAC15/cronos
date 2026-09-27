# CRONOS
relojuchi con figlets
otro proyecto por los jajas, queria aprender como manejarme mejor en c y hice esto

usa la libreria time para tooodo lo del tiempo, y bueno no tengo mucho q decir, les paso
las instrucciones

peace

- [montaje, instalación y desinstalación](#montaje-instalacion-y-desinstalacion)
- [flags](#flags)
- [cómo hacer fuentes](#como-hacer-fuentes)
  
## montaje, instalacion y desinstalacion
van a necesitar gcc para compilar en c justamente
tiene un makefile (vibecodeado, no los se hacer) con opcion de montaje y instalacion global
*montaje y limpieza del mismo*
``` make ```
montaje
``` make clean ```
limpieza de montaje

*instalacion global*
```sudo make install```
*DESinstalaciion*
```sudo make uninstall```

## flags
* `--font [nombre]` : elegir fuente
* `--no-font` : formato plano
si le erras con una flag se vuelve usuario de arch y te dice rtmf

## como hacer fuentes
cree mi propia extension pq me aburria (.cf) qque significa cronos font
tiene q ser una grilla 4y x 3x (4 alto, 3 ancho) JUSTA por cada letra
con justa me refiero a espacios para cumplir con la grilla

para cada letra se usan cabeceras que se arrancan con ''', ejemplo:
`''' 0 '''` 
un ejemplo de fuente es el classic.cf que basicamente es la fuente default
esta escrito asi para q usen de referencia:
```
''' classic.cf '''

''' 0 '''
###
# #
# #
###

''' 1 '''
 # 
## 
 # 
###

''' 2 '''
 ##
# #
 # 
###
```
...

y asi hasta el 9 y el :
bueno eso, si recomiendan algo pasen consejos
