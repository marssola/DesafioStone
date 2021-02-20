# DesafioStone
Client básico para o Spotify

## Instalação - Linux
debug
```bash
[debug] $ sudo mkdir -p /opt/SpotQtd/db
[debug] $ sudo chown -R $USER /opt/SpotQtd

[release] $ sudo mkdir -p /opt/SpotQt/db
[release] $ sudo chown -R $USER /opt/SpotQt
```

#### Adicionar no QtCreator o passo para instalação
Menu lateral Projects -> Versão do Kit -> Build -> Build Stepes -> Add Build Step -> Make
```
Make arguments: install
```

#### Adicionar no QtCreator váriavel de ambiente para execução do plugin para o QML
Menu lateral Projects -> Versão do Kit -> Run -> Environment.

Adicionar à variavél LD_LIBRARY_PATH
```
[debug] /opt/SpotQtd/lib
[release] /opt/SpotQt/lib
```
