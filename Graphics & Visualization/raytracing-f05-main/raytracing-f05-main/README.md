# RayTracingGiVD 2020-21

## Equip:
F05: Álvaro Guillén, Sebastian Andrade, Josep Núñez, Ruben Blanco

### Features
- Fase 1
    - [X] Background amb degradat: Tots
   
    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [X] 4.1.a. Mapping de mons virtuals: Tots
        - [X] 4.1.b. Hit Triangle: Tots
        - [X] 4.1.c. Hit Boundary Object: Ruben, Josep
        - [X] 4.1.d. Hit Cilindre: Ruben, Josep
    - Creació de REAL DATA
        - [X] 4.2.a. Transformacions Translació i Escalat amb gizmos esferes: Sebastian, Ruben
        - [X] 4.2.b. Pla de terra: Ruben
        - [ ] 4.2.c. Gizmo de Triangle
        - [X] 4.2.d. Gizmo de Cilindre
        - [ ] Noves dades
       

- Fase 2
    - [X] Antialiasing: Sebastian
    - [X] Gamma Correction: Sebastian
    - [X] Blinn-Phong: Sebastian, Josep, Álvaro
    - [X] Ombres amb objectes opacs: Sebastian, Josep, Álvaro
    - [X] Reflexions: Sebastian
    - [X] Transparències: Josep
    - [X] Visualització amb dades reals: Tots
    
    
- Fase 3
    - [X] Texture mapping en el pla: Ruben
    - [X] MaterialTextura: Ruben
    - [ ] Nova escena de dades
   
- Parts opcionals
    - [ ] Nous objectes paramètrics 
    - [ ] Penombres 
    - [ ] Diferents tipus de llums 
    - [ ] Multiple-scattering 
    - [ ] Escena CSG 
    - [X] Ambient occlusion: Álvaro, Josep
    - [ ] Defocus blur
    - [ ] Més d'una propietat en les dades reals
    - [ ] Animacions amb dades temporals
    - [X] Ombres atenuades segons objectes transparents: Álvaro, Josep
    - [X] Colors d'ombra segons els colors dels objectes transparents: Álvaro, Josep
    - [ ] Mapeig de les dades reals en una esfera
    - [ ] Ús de diferents paletes 
    - [X] Textura en esfera: Ruben
    
### Explicació de la pràctica    
    
Puede pasar que parezca que hay Acné, pero si ponemos el scatter de Lambertian como False, vemos que no es que haya acné, es el efecto del material del suelo que afecta.
 
Vemos que no están los puntos azules en la esfera.

Entendimos como hacer la atenuación de las sombras según las transparencias, además de implementar la funcionalidad de las sombras con colores. Al implementarlo en el código, no supimos cómo combinar ambas opciones (sombra colorida o no), por lo que únicamente se puede seleccionar una opción.
    
### Screenshots més rellevants


      MIRAR CARPETA Screenshots 


### Informació addicional o observacions

IMPORTANTE: hemos tenido problemas con el .pro y por tanto, cada vez que hacemos pull del proyecto hay que añadir MaterialTextura.cpp y Transparent.cpp con sus respectivos .h

Nota: al usar objetos transparentes se tarda mucho más en compilar. Otro problema, a veces se bloquea la primera ejecución. Con parar la ejecución y volver a ejecutar basta. No sabemos la razón detrás de ese bucle. 

Álvaro: Yo desde 1 o 2 semanas antes de semana santa (cuando en SD se hizo la sesión de hamachi) no se que toqué del git, pero ya me dejó de funcionar (no podía hacer commit). Tiene problemas de identificación (los sigue teniendo de hecho). No obstante, este miércoles hablando con Irene (profesora de SD) conseguí una vía alternativa para que al menos pudiera hacer commit y push. Es por eso que prácticamente no hay ningún push mío, sino que era más bien trabajo en grupo en el skype debatiendo y deliberando juntos.
