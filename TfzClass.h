#pragma once

//Без copy-and-swap
class Class1 {
public:
	Class1() : a_size{ 0 }, b_size{ 0 }, a { nullptr }, b{ nullptr } {}
	Class1(size_t a_size, size_t b_size) : a_size{ a_size }, b_size{ b_size }, a { new int[a_size] }, b{ new double[b_size] } {}

	//Конструктор копирования
	Class1(const Class1& other) {
		std::cout << "Class1 copy ctr started" << std::endl;
		a = new int[other.a_size];
		try {
			b = new double[other.b_size];
		}
		catch (...) {
			delete a;
			a = nullptr;
			throw;
		}
		a_size = other.a_size;
		b_size = other.b_size;
	}

	//Конструктор перемещения
	Class1(Class1&& other) noexcept : a_size{ 0 }, b_size{ 0 }, a{ nullptr }, b{ nullptr }{
		std::cout << "Class1 move ctr started" << std::endl;
		std::swap(a_size, other.a_size);
		std::swap(b_size, other.b_size);
		std::swap(a, other.a);
		std::swap(b, other.b);
	}

	//Оператор присваивания копированием
	Class1& operator=(const Class1& other) {
		if (this == &other) {
			return *this;
		}
		std::cout << "Class1 copy = started" << std::endl;
		size_t a_size_temp = other.a_size;
		size_t b_size_temp = other.b_size;
		delete a;//Подразумевается, что a либо nullptr, либо ещё не удалено
		delete b;//То же самое, что и с a
		int* a_temp = new int[a_size_temp];
		double* b_temp;
		try {
			b_temp = new double[other.b_size];
		}
		catch (...) {
			delete a;
			a = nullptr;
			throw;
		}
		a = a_temp;
		b = b_temp;
		a_size = a_size_temp;
		b_size = b_size_temp;
		return *this;
	}

	//Оператор присваивания перемещением
	Class1& operator=(Class1&& other) {
		if (this == &other) {
			return *this;
		}
		std::cout << "Class1 move = started" << std::endl;
		//Обнуляем переменные
		delete[] a;
		delete[] b;
		a = nullptr;
		b = nullptr;
		a_size = 0;
		b_size = 0;
		//Меняем местами
		std::swap(a, other.a);
		std::swap(b, other.b);
		std::swap(a_size, other.a_size);
		std::swap(b_size, other.b_size);
		return *this;
	}
	~Class1() {
		//std::cout << "Class1 dtr started" << std::endl;
		delete[] a;
		delete[] b;
	}
private:
	size_t a_size, b_size;
	int* a;
	double* b;
};

//С copy-and-swap
class Class2 {
public:
	Class2() : a_size{ 0 }, b_size{ 0 }, a{ nullptr }, b{ nullptr } {}
	Class2(size_t a_size, size_t b_size) : a_size{ a_size }, b_size{ b_size }, a{ new int[a_size] }, b{ new double[b_size] } {}

	//Конструктор копирования
	Class2(const Class2& other) {
		std::cout << "Class2 copy ctr started" << std::endl;
		a = new int[other.a_size];
		try {
			b = new double[other.b_size];
		}
		catch (...) {
			delete a;
			a = nullptr;
			throw;
		}
		a_size = other.a_size;
		b_size = other.b_size;
	}

	//Конструктор перемещения
	Class2(Class2&& other) noexcept : a_size{ 0 }, b_size{ 0 }, a{ nullptr }, b{ nullptr } {
		std::cout << "Class2 move ctr started" << std::endl;
		std::swap(a_size, other.a_size);
		std::swap(b_size, other.b_size);
		std::swap(a, other.a);
		std::swap(b, other.b);
	}

	//Оператор присваивания копированием и перемещением
	Class2& operator=(Class2 other) {
		std::cout << "Class2 copy or move = started" << std::endl;
		swap(*this, other);
		return *this;
	}

	~Class2() {
		//std::cout << "Class2 dtr started" << std::endl;
		delete[] a;
		delete[] b;
	}
private:
	friend void swap(Class2& left, Class2& right) {
		std::swap(left.a_size, right.a_size);
		std::swap(left.b_size, right.b_size);
		std::swap(left.a, right.a);
		std::swap(left.b, right.b);
	}
	size_t a_size, b_size;
	int* a;
	double* b;
};

