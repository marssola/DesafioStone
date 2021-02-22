# DesafioStone
Client básico para o Spotify

#### Adicionar no QtCreator váriavel de ambiente para execução do plugin para o QML
Menu lateral Projects -> Versão do Kit -> Run -> Environment.

Adicionar à variavél LD_LIBRARY_PATH o path da build da lib SpotQt
Ex:
```
[Linux] $USER/build-DesafioStone-Desktop_Qt_5_15_2_GCC_64bit-[Debug/Release]/src/SpotQt/lib
[Windows] $USER/build-DesafioStone-Desktop_Qt_5_15_2_GCC_64bit-[Debug/Release]/src/SpotQt/[debug/release]/lib
```
No Windows é necessário ter a lib openSSL definida na PATH corretamente
