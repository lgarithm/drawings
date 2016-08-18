find src | egrep "\.(h|c|cpp)$" | xargs -n 1 -I {} clang-format -i {}
