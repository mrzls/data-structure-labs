#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <string>

class HashTable
{
private:
	static const int EMPTY = 0;     // €чейка пуста
	static const int OCCUPIED = 1;  // €чейка зан€та
	static const int DELETED = 2;   // €чейка удалена

	struct KeyValue {
		char* key_ = nullptr;
		std::string value_ = "";
		int status_ = EMPTY;

		KeyValue() = default;
		~KeyValue() { delete[] key_; }
	};

	int size_ = 0;
	KeyValue* table_ = nullptr;
	int number_ = 0; // количество зан€тых элементов
	int colNum_ = 0; // количество коллизий

	unsigned int hash(const char* key) const;
	int probe(int hashValue, int attempt) const;

public:
	HashTable(int size);
	~HashTable();

	HashTable(const HashTable&) = delete;
	HashTable(HashTable&&) = delete;
	HashTable& operator=(const HashTable&) = delete;
	HashTable& operator=(HashTable&&) = delete;

	void insert(const char* key, const std::string& val);
	std::string* search(const char* key);
	void remove(const char* key);
	void print() const;

	int getColNum() const;
	int getNumber() const;
	int getSize() const;

};

#endif


