
/**
 *
 * @mainpage Простой рехэширования на C++
 * @section Описание
 * Пример использования рехэширования с использованием псевдослучайных чисел и простого списка для разрешения коллизий в хэш-таблице
 *
 * @section Требования
 * 1. CMake 3.16 или выше
 * 2. Компилятор, поддерживающий стандарт C++17
 * 3. Рекомендуется использовать среду разработки CLion
 *
 * @author
 * Ващенко Лев Сергеевич
 *
 * @version 1.6
 *
 * @date 06.2023
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <random>

/**
 * @brief Размер хеш-таблицы
 */
const int TABLE_SIZE = 200;

/**
 * @brief Функция для вычисления хеша
 * @param key Ключ, для которого вычисляется хеш
 * @return Вычисленное значение хеша для ключа
 */
int hash_function(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % TABLE_SIZE;
    }
    return hash;
}

/**
 * @brief Функция для добавления элемента в таблицу
 * @param table Хэш-таблица, содержащая списки коллизий
 * @param key Ключ для добавления в таблицу
 */
void add_element(std::vector<std::list<std::string>>& table, const std::string& key) {
    int index = hash_function(key);
    table[index].push_back(key);
}

/**
 * @brief Функция для поиска элемента в таблице
 * @param table Хэш-таблица, содержащая списки коллизий
 * @param key Искомый ключ
 * @return True, если элемент найден, иначе False
 */
bool search_element(std::vector<std::list<std::string>>& table, const std::string& key) {
    int index = hash_function(key);
    for (const std::string& k : table[index]) {
        if (k == key) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Тест 1: добавление и поиск элемента без коллизий
 * @return True, если тест успешен, иначе False
 */
bool test1() {
    std::vector<std::list<std::string>> table(TABLE_SIZE);
    std::string key = "apple";
    add_element(table, key);

    return search_element(table, key);
}

/**
 * @brief Тест 2: добавление и поиск элемента с коллизиями
 * @return True, если тест успешен, иначе False
 */
bool test2() {
    std::vector<std::list<std::string>> table(TABLE_SIZE);
    std::string key1 = "apple";
    add_element(table, key1);

    std::string key2 = "banana";
    add_element(table, key2);

    return search_element(table, key1) && search_element(table, key2);
}

/**
 * @brief Тест 3: поиск элемента, которого нет в таблице
 * @return True, если тест успешен, иначе False
 */
bool test3() {
    std::vector<std::list<std::string>> table(TABLE_SIZE);
    std::string key1 = "apple";
    add_element(table, key1);

    std::string key2 = "cherry";

    return !search_element(table, key2);
}

/**
 * @brief Главная функция - выполняет тесты
 */
int main() {
    if (test1()) {
        std::cout << "Тест 1: успешно" << std::endl;
    } else {
        std::cout << "Тест 1: неудачно" << std::endl;
    }

    if (test2()) {
        std::cout << "Тест 2: успешно" << std::endl;
    } else {
        std::cout << "Тест 2: неудачно" << std::endl;
    }

    if (test3()) {
        std::cout << "Тест 3: успешно" << std::endl;
    } else {
        std::cout << "Тест 3: неудачно" << std::endl;
    }

    return 0;
}
