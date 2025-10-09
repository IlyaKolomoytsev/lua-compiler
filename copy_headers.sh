# Построение Docker-образа
docker build -t my-lua-compiler .

# Запуск контейнера в фоновом режиме с автоудалением после завершения
docker run --rm -d --name temp_lua_compiler_container my-lua-compiler tail -f /dev/null

# Проверка успешности запуска контейнера
if [ $? -ne 0 ]; then
  echo "Ошибка при запуске контейнера."
  exit 1
fi

# Копирование нужного файла из контейнера в локальную систему
docker cp temp_lua_compiler_container:/app/lua_parser.tab.h ./lua_parser.tab.h

# Проверка успешности копирования
if [ $? -ne 0 ]; then
  echo "Ошибка при копировании файла."
  docker kill temp_lua_compiler_container
  exit 1
fi

echo "Файл успешно скопирован."
docker kill temp_lua_compiler_container
