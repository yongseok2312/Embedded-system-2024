# include <iostream>
using namespace std;

class Product
{
private:
	int id;
	int price;
	string producer;

public:
	Product(int inid, int inprice, string inproducer)
		: id(inid), price(inprice), producer(inproducer)
	{
		cout << "Product 객체" << endl;
	}

	virtual void ShowInfo() { cout << '[' << id << ']' << endl << '[' << producer << ']' << " 가격: " << price << endl; }
	string Showproducer() { return producer; }
	int getID() { return id; }

};


class Book : public Product
{
private:
	string ISBN;
	string author;
	string title;

public:
	Book(int inid, int inprice, string inproducer, string intitle, string inauthor, string inISBN)
		: Product(inid, inprice, inproducer), ISBN(inISBN), author(inauthor), title(intitle)
	{
		cout << "Book 객체" << endl;
	}

	virtual void ShowInfo()
	{
		Product::ShowInfo();
		cout << "제목: " << title << " 저자: " << author << " ISBN: " << ISBN << endl;
	}

};


class Handsphone : public Product
{
private:
	string model;
	int HpRam;

public:
	Handsphone(int inid, int inprice, string inproducer, string inmodel, int inHpRam)
		: Product(inid, inprice, inproducer), model(inmodel), HpRam(inHpRam)
	{
		cout << "Handsphone 객체" << endl;
	}

	virtual void ShowInfo()
	{
		Product::ShowInfo();
		cout << "모델명: " << model << " RAM: " << HpRam << endl << endl;
	}
};


class Computer : public Product
{
private:
	string model;
	int cptRam;

public:
	Computer(int inid, int inprice, string inproducer, string inmodel, int incptRam)
		: Product(inid, inprice, inproducer), model(inmodel), cptRam(incptRam)
	{
		cout << "Computer 객체" << endl;
	}

	virtual void ShowInfo()
	{
		Product::ShowInfo();
		cout << "모델명: " << model << " RAM: " << cptRam << endl << endl;
	}

	virtual string Name() { return model; }
};


// 카테고리 선택 번호 변수
int num;
void PoductList()
{
	cout << "[1] 도서	[2] 휴대폰	[3] 컴퓨터" << endl << "입력 >> ";
	cin >> num;
	cout << endl;
}



int main(void)
{
	Product* product[100];

	// product 입력 변수
	int id = -1;
	int inprice;
	string producer;

	// 도서 입력 변수
	string inISBN;
	string inauthor;
	string intitle;

	// 휴대폰 및 컴퓨터 입력 변수
	string inmodel;
	int inhpRam;

	// 검색키워드
	int search;


	while (1)
	{
		cout << "--------------- 상품 관리 프로그램 --------------- " << endl;
		cout << "[1] 상품추가	[2] 상품출력	[3] 상품검색	[0] 종료" << endl << "입력 >> ";
		cin >> num;

		if (num == 1) // 상품추가
		{
			id++;
			PoductList();

			if (num == 1) // 도서
			{
				producer = "도서";
				cout << endl << "가격, 제목, 저자, ISBN 입력 : ";
				cin >> inprice >> intitle >> inauthor >> inISBN;
				product[id] = new Book(id, inprice, producer, intitle, inauthor, inISBN);
				product[id]->ShowInfo();
				cout << endl;
			}

			if (num == 2) // 휴대폰
			{
				producer = "휴대폰";
				cout << endl << "가격, 모델명, RAM 크기 입력 : ";
				cin >> inprice >> inmodel >> inhpRam;
				product[id] = new Handsphone(id, inprice, producer, inmodel, inhpRam);
				product[id]->ShowInfo();
				cout << endl;
			}

			if (num == 3) // 컴퓨터
			{
				producer = "컴퓨터";
				cout << endl << "가격, 모델명, RAM 크기 입력 : ";
				cin >> inprice >> inmodel >> inhpRam;
				product[id] = new Computer(id, inprice, producer, inmodel, inhpRam);
				product[id]->ShowInfo();
				cout << endl;
			}

			continue;
		}

		// 상품출력
		else if (num == 2)
		{
			PoductList();

			if (num == 1)
			{
				cout << "[도서 상품 목록]" << endl << endl;
				for (int i = 0; i < id + 1; i++)
					if (product[i]->Showproducer() == "도서")
						product[i]->ShowInfo();
					else
						continue;
			}

			if (num == 2)
			{
				cout << "[핸드폰 상품 목록]" << endl << endl;
				for (int i = 0; i < id + 1; i++)
					if (product[i]->Showproducer() == "휴대폰")
						product[i]->ShowInfo();
					else
						continue;
			}

			if (num == 3)
			{
				cout << "[컴퓨터 상품 목록]" << endl << endl;
				for (int i = 0; i < id + 1; i++)
					if (product[i]->Showproducer() == "컴퓨터")
						product[i]->ShowInfo();
					else
						continue;
			}
			continue;
		}

		// 상품 검색
		else if (num == 3)
		{
			PoductList();


			if (num == 1)
			{
				cout << "------- 도서 검색 -------" << endl;
				cout << "상품 번호(ID)입력 >> ";
				cin >> search;

				for (int i = 0; i < id + 1; i++)
				{
					if (product[i]->Showproducer() != "도서")
						cout << "등록된 도서 상품이 없습니다" << endl;
					else
					{
						if (product[i]->getID() == search)
							product[i]->ShowInfo();

						else
							continue;
					}
				}
			}
			continue;


			if (num == 2)
			{
				cout << "------- 휴대폰 검색 -------" << endl;
				cout << "상품 번호(ID)입력 >> ";
				cin >> search;

				for (int i = 0; i < id + 1; i++)
				{
					if (product[i]->Showproducer() != "휴대폰")
						cout << "등록된 휴대폰 상품이 없습니다" << endl;
					else
					{
						if (product[i]->getID() == search)
							product[i]->ShowInfo();

						else
							continue;
					}
				}
			}

			if (num == 3)
			{
				cout << "------- 컴퓨터 검색 -------" << endl;
				cout << "상품 번호(ID)입력 >> ";
				cin >> search;

				for (int i = 0; i < id + 1; i++)
				{
					if (product[i]->Showproducer() != "컴퓨터")
						cout << "등록된 컴퓨터 상품이 없습니다" << endl;
					else
					{
						if (product[i]->getID() == search)
							product[i]->ShowInfo();

						else
							continue;
					}
				}
			}
			continue;
		}


		else if (num == 0) // 프로그램 종료
			for (int i = 0; i < id + 1; i++)
				delete product[i];
		break;

	}

	return 0;
}