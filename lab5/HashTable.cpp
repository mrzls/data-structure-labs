#include "HashTable.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

const char* ERROR_FULL_TABLE = "ERROR: hash table is full";
const char* ERROR_TABLE_SIZE = "ERROR: table size must be positive integer";
const char* ERROR_KEY_NOT_FOUND = "ERROR: key not found";
const char* ERROR_KEY_ALREADY_EXISTS = "ERROR: key already exists";

unsigned int HashTable::hash(const char* key) const
{
    unsigned int h = 0;
    while (*key) {
        h = (h * 31 + static_cast<unsigned char>(*key)) % size_;
        key++;
    }
    return h;
}

int HashTable::probe(int hashValue, int attempt) const
{
    // Квадратичное пробирование: h(k, i) = (h(k) + c1*i + c2*i*i) % size
    // Используем c1 = 1, c2 = 1 для простоты
    return (hashValue + attempt + attempt * attempt) % size_;
}

HashTable::HashTable(int size) : size_(size), number_(0), colNum_(0) 
{
    if (size_ <= 0)
        throw std::invalid_argument(ERROR_TABLE_SIZE);
    table_ = new KeyValue[size_]();
}

HashTable::~HashTable() { delete[] table_; }

void HashTable::insert(const char* key, const std::string& val)
{
    if (static_cast<double>(number_+1) / size_ >= 0.7)
        throw std::overflow_error(ERROR_FULL_TABLE);
    
    int h = hash(key);
    int attempt = 0;
    int index = h;
    
    while (attempt < size_) {

        if (table_[index].status_ == EMPTY || table_[index].status_ == DELETED) {
            
            // Вставляем
            char* newKey = new char[strlen(key) + 1]; // +1 для '\0'
            strcpy_s(newKey, strlen(key) + 1, key);
            table_[index].key_ = newKey;
            table_[index].value_ = val;
            table_[index].status_ = OCCUPIED;
            number_++;
            return;
        }
        else if (table_[index].status_ == OCCUPIED && strcmp(table_[index].key_, key) == 0) {
            throw std::runtime_error(ERROR_KEY_ALREADY_EXISTS);
        }

        // Коллизия
        colNum_++;
        attempt++;
        index = probe(h, attempt);
    }
    throw std::out_of_range(ERROR_FULL_TABLE);
}

std::string* HashTable::search(const char* key)
{
    int h = hash(key);
    int attempt = 0;
    int index = h;

    while (attempt < size_) {
        if (table_[index].status_ == EMPTY) {
            throw std::runtime_error(ERROR_KEY_NOT_FOUND);
        }
        if (table_[index].status_ == OCCUPIED && strcmp(table_[index].key_, key) == 0) {
            return &table_[index].value_;  // найден, возвращаем указатель на значение
        }
        attempt++;
        index = probe(h, attempt);
    }
    throw std::runtime_error(ERROR_KEY_NOT_FOUND);  // не найден после всех попыток
}

void HashTable::remove(const char* key)
{
    int h = hash(key);
    int attempt = 0;
    int index = h;

    while (attempt < size_) {
        if (table_[index].status_ == EMPTY) {
            throw std::runtime_error(ERROR_KEY_NOT_FOUND);  // ключ не найден
        }
        if (table_[index].status_ == OCCUPIED && strcmp(table_[index].key_, key) == 0) {
            // Освобождаем память ключа
            delete[] table_[index].key_;
            table_[index].key_ = nullptr;
            table_[index].value_ = "";
            table_[index].status_ = DELETED;  // помечаем как удалённый
            number_--;
            return;
        }
        attempt++;
        index = probe(h, attempt);
    }
    throw std::runtime_error(ERROR_KEY_NOT_FOUND);
}

void HashTable::print() const
{
    for (int i = 0; i < size_; ++i) {
        if (table_[i].status_ == OCCUPIED) {
            std::cout << "[" << i << "]: " << table_[i].key_ << " -> " << table_[i].value_ << "\n";
        }
    }
}

int HashTable::getColNum() const { return colNum_; }
int HashTable::getNumber() const { return number_; }
int HashTable::getSize() const { return size_; }
