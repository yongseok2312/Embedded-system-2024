/*
    File: product_manager.cpp

    Created:24-03-06
    Author: 이용석
*/



#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    int price;
    string producer;

public:
    Product(int id, int price, string producer) : id(id), price(price), producer(producer) {}
    virtual ~Product() {}

    int getId() const {
        return id;
    }

    int getPrice() const {
        return price;
    }

    string getProducer() const {
        return producer;
    }

    virtual void printInfo() const = 0; // 순수 가상 함수
};

class Book : public Product {
private:
    string ISBN;
    string author;
    string title;

public:
    Book(int id, int price, string producer, string ISBN, string author, string title)
        : Product(id, price, producer), ISBN(ISBN), author(author), title(title) {}

    void printInfo() const override {
        cout << "ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "저자: " << author << endl;
        cout << "제목: " << title << endl;
    }
};

class HandPhone : public Product {
private:
    string model;
    int RAM;

public:
    HandPhone(int id, int price, string producer, string model, int RAM)
        : Product(id, price, producer), model(model), RAM(RAM) {}

    void printInfo() const override {
        cout << "ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "Model: " << model << endl;
        cout << "RAM: " << RAM << "GB" << endl;
    }
};

class Computer : public Product {
private:
    string model;
    string cpu;
    int RAM;

public:
    Computer(int id, int price, string producer, string model, string cpu, int RAM)
        : Product(id, price, producer), model(model), cpu(cpu), RAM(RAM) {}

    void printInfo() const override {
        cout << "ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "Model: " << model << endl;
        cout << "CPU: " << cpu << endl;
        cout << "RAM: " << RAM << "GB" << endl;
    }
};

// 제품 출력 함수
void printProductsByType(Product* products[], int numProducts, int type) {
    cout << "Printing products:" << endl;
    for (int i = 0; i < numProducts; ++i) {
        if ((type == 1 && dynamic_cast<Book*>(products[i])) ||
            (type == 2 && dynamic_cast<HandPhone*>(products[i])) ||
            (type == 3 && dynamic_cast<Computer*>(products[i]))) {
            cout << "Product " << i + 1 << ":" << endl;
            products[i]->printInfo();
            cout << endl;
        }
    }
}

int main() {
    const int MAX_PRODUCTS = 100;
    Product* products[MAX_PRODUCTS]; // 객체 포인터 배열

    int numProducts = 0;
    int choice;

    while (true) {
        cout << "------ 상품 관리 프로그램 ------" << endl;
        cout << "1. 상품 추가\n2. 상품 출력\n3. 상품 검색\n0. 종료\n";
        cout << "원하는 작업을 선택하세요: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int type;
            cout << "추가할 상품의 종류를 선택하세요:\n1. 책\n2. 핸드폰\n3. 컴퓨터\n";
            cin >> type;

            int id, price, RAM;
            string producer, ISBN, author, title, model, cpu;

            cout << "상품 정보를 입력하세요:" << endl;
            cout << "ID: ";
            cin >> id;
            cout << "가격: ";
            cin >> price;
            cout << "생산자: ";
            cin >> producer;

            switch (type) {
            case 1:
                cout << "ISBN: ";
                cin >> ISBN;
                cout << "저자: ";
                cin >> author;
                cout << "제목: ";
                cin >> title;
                products[numProducts++] = new Book(id, price, producer, ISBN, author, title);
                break;
            case 2:
                cout << "모델: ";
                cin >> model;
                cout << "RAM (GB): ";
                cin >> RAM;
                products[numProducts++] = new HandPhone(id, price, producer, model, RAM);
                break;
            case 3:
                cout << "모델: ";
                cin >> model;
                cout << "CPU: ";
                cin >> cpu;
                cout << "RAM (GB): ";
                cin >> RAM;
                products[numProducts++] = new Computer(id, price, producer, model, cpu, RAM);
                break;
            default:
                cout << "잘못된 유형 선택!" << endl;
                break;
            }
            cout << "상품이 추가되었습니다." << endl;
            break;
        }
        case 2: {
            int type;
            cout << "출력할 상품의 종류를 선택하세요:\n1. 책\n2. 핸드폰\n3. 컴퓨터\n";
            cin >> type;
            printProductsByType(products, numProducts, type);
            break;
        }
        case 3: {
            int searchId;
            cout << "검색할 상품의 ID를 입력하세요: ";
            cin >> searchId;
            bool found = false;
            for (int i = 0; i < numProducts; ++i) {
                if (products[i]->getId() == searchId) {
                    found = true;
                    cout << "상품을 찾았습니다:" << endl;
                    products[i]->printInfo();
                    break;
                }
            }
            if (!found) {
                cout << "상품을 찾을 수 없습니다!" << endl;
            }
            break;
        }
        case 0:
            // 할당된 메모리 해제
            for (int i = 0; i < numProducts; ++i) {
                delete products[i];
            }
            cout << "프로그램을 종료합니다." << endl;
            return 0;
        default:
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
            break;
        }
    }

    return 0;
}