# Построение Docker-образа
docker build -t my-lua-compiler .

# Запуск контейнера в фоновом режиме с автоудалением после завершения
docker run --rm -d --name temp_lua_compiler_container my-lua-compiler tail -f /dev/null

# Копирование нужного файла из контейнера в локальную систему
docker cp temp_lua_compiler_container:/app/lua_parser.tab.h ./lua_parser.tab.h

docker kill temp_lua_compiler_container
