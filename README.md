### 6. Documentación

Modifica `README.md` usando [Markdown](https://guides.github.com/features/mastering-markdown/) para:

1. Explicar cómo compilar y probar el proyecto, incluyendo requisitos adicionales, si los hubiera.
1. Comentar las características implementadas, opcionales y bugs conocidos.

No te olvides de hacer un _commit_ en _develop_ para preservar los cambios en README.md.

## Pasos para utilizar el rastreador
```console
foo@bar:~$$git clone https://github.com/ull-esit-sistemas-operativos/soa-1920-rastreador-web-david-daniel.git
```
- Abrir el proyecto en qtcreator, usando tanto "rastreador_web.pro" como "indexing-client.pro"
- Descargar y configurar GumboParser y GumboQuery según lo siguiente:
  - https://github.com/google/gumbo-parser
  - En el directorio lib/ dentro del proyecto, seguir estas indicaciones: https://github.com/lazytiger/gumbo-query
- Entrar en la pestaña "build", y ejecutar "build all projects"
- En el menú inferior izquierdo, arrancar ambos ejecutables.
- En el cliente gráfico, buscar una dirección
  - file:// en caso de una dirección del sistema
  - https:// en caso de una dirección web

## Errores conocidos
- En caso de buscar en mucha profundidad, es posible que de un error de GLIB

### GCC Code Coverage Report


| File                                                                            | Lines | Exec | Cover | Missing                                                                                                             |
| ------------------------------------------------------------------------------- | ----- | ---- | ----- | ------------------------------------------------------------------------------------------------------------------- |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/actor.cpp            | 40    | 35   | 87%   | 18, 58, 63-65                                                                                                       |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/actormanager.cpp     | 18    | 15   | 83%   | 27, 39, 44                                                                                                          |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/actorthread.cpp      | 6     | 6    | 100%  |                                                                                                                     |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/mailbox.h            | 15    | 15   | 100%  |                                                                                                                     |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/moc_actor.cpp        | 11    | 3    | 27%   | 58, 76, 78, 81, 83-86                                                                                               |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/moc_actormanager.cpp | 11    | 0    | 0%    | 58, 76, 78, 81, 83-86, 89, 91-92,                                                                                   |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/actors/moc_actorthread.cpp  | 11    | 2    | 18%   | 58,81,83-86,89,91-92                                                                                                |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/actor.h               | 15    | 9    | 60%   | 44-49                                                                                                               |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/actormanager.h        | 5     | 5    | 100%  |                                                                                                                     |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/moc_testactor.cpp     | 83    | 32   | 38%   | 102,107-108,112-118,120,140,142-143,145-149,151-154,156-157,179,181-184,191,193-195,197-199,203,206-215,222,224-225 |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/testactor.h           | 24    | 22   | 91%   | 25, 27                                                                                                              |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/tst_actortest.cpp     | 54    | 49   | 90%   | 79-81, 96-97                                                                                                        |
| build-rastreador_web-Qt_5_15_0_in_PATH_System-Debug/tests/tst_actortest.moc     | 35    | 17   | 48%   | 130,132-135,138,140-150,152                                                                                         |
|                                                                                 |       |      |       |                                                                                                                     |
| TOTAL                                                                           | 328   | 210  | 64%   |                                                                                                                     |
