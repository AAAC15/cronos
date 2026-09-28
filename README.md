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

  *instalacion global* <br>
```sudo make install``` <br>
*DESinstalaciion* <br>
```sudo make uninstall```

## flags
* `--font [nombre]` : elegir fuente  
* `--no-font` : formato plano  
* `--help` : ayuda  
si le erras con una flag se vuelve usuario de arch y te dice rtmf

## fuentes
las base estan en layout, y al momento de esta modificacion, hay 4  
- `classic`: compuesta casi en su totalidad por #, es la predeterminada del reloj <br> esta buena para algo bien "sobrio"
- `numerical`: como dice el nombre, esta compuesta por numeros, por ejemplo, el 0 esta hecho de 0s, el 1 de 1s, y asi <br> (es clon de la classic pero con esa modificacion)
- `blocks`: esta hecha de bloques ansi (█). nunca esta demas meter algo con esos bloques, inspirado en las artes ansi viejas de los DOS
- `gradient`: es un clon de blocks pero con bloques ansi de gradiente (░, ▒, ▓) mi personal favorita, alta facha

## como hacer fuentes
cree mi propia extension pq me aburria (.cf) qque significa cronos font <br>
tiene q ser una grilla 4y x 3x (4 alto, 3 ancho) JUSTA por cada letra <br>
con justa me refiero a espacios para cumplir con la grilla

para cada letra se usan cabeceras que se arrancan con ''', ejemplo:
`''' 0 '''`  <br>
un ejemplo de fuente es el classic.cf que basicamente es la fuente default <br>
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

y asi hasta el 9 y el : <br>
las fuentes se guardan en /usr/local/share/cronos/layout/nombre.cf o en la carpeta base en la que tengan instalado cronos, dentro de layout

bueno eso, si recomiendan algo pasen consejos
