#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

////////////////////////Some necessary Functions//////////////////////////////////////
bool isUppercase(const char& c)
{
	return ('A'<=c && c<='Z');
}

bool isLowercase(const char& c)
{
	return ('a'<=c && c<='z');
}

bool isDigit(char c)
{
	return ('0' <= c && c<='9');
}

bool isNumber(const string& s)
{
	//pre-condition: a string
	//post-condition: return true if the string is a number else otherwise
	for (int i=0;i<s.size();++i) if (!isDigit(s[i])) return 0;
	return 1;
}

int string2num(const string& s)
{
	//pre-condition: a string
	//post-condition: return the numberic type of string
	int n = 0;
	for (int i=0;i<s.size();++i) n = n*10 + (s[i]-'0');
	return n;
}

string format_string(string s)
{
	//pre-condition: a string
	//post-condition: reformat the string, the first letter will be uppercase, others will be lowercase
	while (s.size()>0 && s[0]==' ') s.erase(0,1);
	while (s.size()>0 && s[s.size()-1]==' ') s.erase(0,1);
	for (int i=0;i<s.size();++i)
	{
		if (i==0)
		{
			if (isLowercase(s[0])) s[0] = s[0]-32;
			continue;
		}
		for (int i=1;i<s.size();++i)
			if (isUppercase(s[i])) s[i] = s[i]+32;
	}
	return s;
}

bool check_num_in_string(int n,string s)
{
	//pre-condition: a string
	//post-condition: return 1 if there is a number n appear in string s
	for (int i=0;i<s.size();++i) if (s[i]-'0'==n) return 1;
	return 0;
}

//////////////////////////////////Book Class/////////////////////////////////////////

class Book
{
private:
	string Title,Author;
	int Date,Type,NOP;
	static string t[4];
public:
	Book()
	{
		Title = Author = "N/A";
		Type = Date = NOP = 0;
	}
	Book(const Book& x)
	{
		this->Title = x.Title;
		this->Author = x.Author;
		this->Date = x.Date;
		this->Type = x.Type;
		this->NOP = x.NOP;
	}
	Book(const string& Title,const string& Author,const int& Date,const int& Type, const int& NOP)
	{
		this->Title = Title;
		this->Author = Author;
		this->Date = Date;
		this->Type = Type;
		this->NOP = NOP;
	}
	~Book() {}

	static int getCategory_num(const string& s)
	{
		//pre-condition: a string data type
		//post-condition: return the ID number of the book type, (1) hardcover, (2) softcover, (3) digital
		for (int i=1;i<4;++i) if (t[i]==s) return i;
		return -1;
	}
	static string getCategory_word(const int& num)
	{
		//pre-condition: an ID number of the book type
		//post-condition: return the word of its type
		return Book::t[num];
	}

	void setTitle(const string& s)
	{	
		this->Title = s;
	}
	void setAuthor(const string& s)
	{
		this->Author = s;
	}
	void setDate(const string& s)
	{
		this->Date = string2num(s);
	}
	void setType(const string& s)
	{
		this->Type = string2num(s);
	}
	void setNOP(const string& s)
	{
		this->NOP = string2num(s);
	}

	string getTitle() const
	{
		return Title;
	}
	string getAuthor() const
	{
		return Author;
	}
	int getDate() const
	{
		return Date;
	}
	int getType() const
	{
		return Type;
	}
	int getNOP() const
	{
		return NOP;
	}

	static string Read_valid_Title(istream& in)
	{
		//pre-condition: 
		//post-condition: force user to enter the valid input for title and return it, the title can not be "..." because i use "..." as a special name for my searching
		string s;
		while (1)
		{
			cout << "Enter the title of the book: ";
			in >> s;
			if (s!="...") return s;
			else cout << "Invalid input, title can not be ...!\n";
		}
	}
	static string Read_valid_Author(istream& in)
	{
		//pre-condition: 
		//post-condition: force user to enter the valid input for author and return it, the author can not be "..." because i use "..." as a special name for my searching
		string s;
		while (1)
		{
			cout << "Enter the author name: ";
			in >> s;
			if (s!="...") return s;
			else cout << "Invalid input, author can not be ...!\n";
		}
	}
	static string Read_valid_Date(istream& in)
	{
		//pre-condition: 
		//post-condition: force user to enter the valid input for date and return it, date musts be a non negative number
		string s;
		while (1)
		{
			cout << "Enter the public year: ";
			in >> s;
			if (isNumber(s)) return s;
			else cout << "Invalid Date, date musts be a non negative number!\n";
		}
	}
	static string Read_valid_Type(istream& in)
	{
		//pre-condition: 
		//post-condition: force user to enter the valid input for type and return its ID number but string data type, Type can be the full word or one type ID Number
		string s;
		while (1)
		{
			cout << "(1) hardcover\t(2) softcover\t(3) digital\n";
			cout << "Enter the type you want to search for by the type ID number or full word: ";
			cin >> s;
			s = format_string(s);
			int n = Book::getCategory_num(s);
			if (n!=-1) s = n + '0';
			if (s.size()==1 && '1'<=s[0] && s[0]<='3') return s;
			else cout << "Invalid Type, type musts be 1, 2, 3!\n";
		}
	}
	static string Read_valid_NOP(istream& in)
	{
		//pre-condition: 
		//post-condition: force user to enter the valid input for number of pages and return it, number of pages musts be a non negative number
		string s;
		while (1)
		{
			cout << "Enter number of pages: ";
			in >> s;
			if (isNumber(s)) return s;
			else cout << "Invalid input, number of pages musts be a non negative number!\n";
		}
		
	}

	typedef Book* BookPtr;

	//pre-condition: take 2 book pointers
	//post-condition: compare 2 object by their title or author or date or ... (using for sorting function)
	static bool cmp_by_Title(const BookPtr& p,const BookPtr& q)
	{
		return p->getTitle()<q->getTitle();
	}
	static bool cmp_by_Author(const BookPtr& p,const BookPtr& q)
	{
		return p->getAuthor()<q->getAuthor();
	}
	static bool cmp_by_Date(const BookPtr& p,const BookPtr& q)
	{
		return p->getDate()<q->getDate();
	}
	static bool cmp_by_Type(const BookPtr& p,const BookPtr& q)
	{
		return p->getType()<q->getType();
	}
	static bool cmp_by_NOP(const BookPtr& p,const BookPtr& q)
	{
		return p->getNOP()<q->getNOP();
	}
	////////////////////////////////////////////////////////////////////////////////////////

	string toString() const
	{
		//pre-condition: 
		//post-condition: return the full detail of a book which format for exporting to file
		stringstream s;
		s << Title << "\t" << Author << "\t" << Date << "\t" << t[Type] << "\t" << NOP;
		return s.str();
	}

	friend istream& operator>>(istream& in, Book& b);
	friend ostream& operator<<(ostream& out,const Book& b);
};

string Book::t[] =  {"","Hardcover","Softcover","Digital"}; //A static string array for category word

istream& operator>>(istream& in,Book& b)
{
	//pre-condition: an istream and a book
	//post-condition: force the user enter the valid input and set it to the object
	b.setTitle(Book::Read_valid_Title(in));
	b.setAuthor(Book::Read_valid_Author(in));
	b.setDate(Book::Read_valid_Date(in));
	b.setType(Book::Read_valid_Type(in));
	b.setNOP(Book::Read_valid_NOP(in));
	return in;
}

ostream& operator<<(ostream& out, const Book& b)
{
	//pre-condition: A book object
	//post-condition: print it to the screen in nice format
	/*out << "Titile: " << b.getTitle() << "\n";
	out << "Author: " << b.getAuthor() << "\n";
	out << "Date of publication: " << b.getDate() << "\n";
	out << "Book type: " << Book::t[b.getType()] << "\n";
	out << "Number of pages: " << b.getNOP();*/
	out << "Title: " << b.Title << "\t|Author: " << b.Author << "\t|Date of publication: " << b.Date << "\t|Book type: " << Book::t[b.Type] << "\t|Number of pages: " << b.NOP;
	return out;
}

////////////////////////////////Database Class//////////////////////////////////////
typedef Book* BookPtr;
class Database
{
private:
	vector<BookPtr> v;

	//Hidden Searching feature
	//static double calculating_score(const string& s1,const string& s2)
	//{
	//	//pre-condition: take 2 strings
	//	//post-condition: return the matching score which measures how much s1 is closed to s2.
	//	int score = 0;
	//	for (int i=0;i<s1.size();++i)
	//		if (i<s2.size()) score+=(s1[i]==s2[i]);
	//	return 1.*score/s1.size();
	//}

public:
	Database() {}
	Database(const Database& D)
	{
		for (int i=0;i<D.v.size();++i) v.push_back(D.v[i]);
	}
	void Import(const string& dir)
	{
		ifstream fin(dir);
		if (fin.fail())
		{
			cout << "Failing to open file!\n";
			fin.close();
			return;
		}
		Manual_Destructor();
		string Title, Type, Author;
		int Date,NOP,category_num;
		while (!fin.eof())
		{
			fin >> Title >> Author >> Date >> Type >> NOP;
			category_num = Book::getCategory_num(format_string(Type));
			this->Add(new Book(Title,Author,Date,category_num,NOP));
		}
		cout << "Importing Complete!\n";
		fin.close();
	}
	void Export(const string& dir)
	{
		ofstream fout(dir);
		if (fout.fail()) 
		{
			cout << "Fail to open file!\n";
			fout.close();
			return;
		}
		if (v.size()>0)
		{
			for (int i=0;i<v.size()-1;++i) fout << v[i]->toString() <<"\n";
			fout << v[v.size()-1]->toString();
		}
		cout << "Exporting Complete!\n";
		fout.close();
	}
	void Manual_Destructor()
	{
		for (int i=0;i<v.size();++i) 
		{
			delete v[i];
			v[i] = nullptr;
		}
		this->Clean();
	}
	BookPtr& operator[](const int& i)
	{
		return v[i];
	}

	int getNOR() const
	{
		//pre-condition: 
		//post-condition: return number of book record in database
		return v.size();
	}
	int getNewestDate() const
	{
		//pre-condition: 
		//post-condition: return the newest date in the database
		int max = 0;
		for (int i=0;i<v.size();++i) if (max<v[i]->getDate()) max = v[i]->getDate();
		return max;
	}
	int getMostNOP() const
	{
		//pre-condition: 
		//post-condition: return the largest number of book in the database
		int max = 0;
		for (int i=0;i<v.size();++i) if (max<v[i]->getNOP()) max = v[i]->getNOP();
		return max;
	}

	void Add(const BookPtr& b)
	{
		//pre-condition: a Book pointer
		//post-condition: adding the book pointer to the database
		v.push_back(b);
	}
	void Pop(const int& i)
	{
		//pre-condition: 
		//post-condition: remove the book from the database without delete it memory space
		this->v.erase(this->v.begin()+i);
	}
	void Delete(const int& i)
	{
		//pre-condition: 
		//post-condition: Delete the memory space of a book and remove it from the database
		delete v[i];
		v[i] = nullptr;
		this->Pop(i);
	}
	void Clean()
	{
		//pre-condition: 
		//post-condition: remove all the book with the special title "..." or the nullptr in the database
		for (int i=0;i<v.size();++i) 
		{
			if (v[i]==nullptr)
			{
				Pop(i--);
				continue;
			}
			if (v[i]->getTitle()=="...") Delete(i--);
		}
	}

	Database search_book_by_Title(const string& s) const
	{
		//pre-condition: a string
		//post-condition: return a database which contains all books have the title equal to the string
		Database ans;
		for (int i=0;i<v.size();++i)  if (format_string(v[i]->getTitle())==s) ans.Add(v[i]);
		return ans;
	}
	Database search_book_by_Author(const string& s) const
	{
		//pre-condition: a string
		//post-condition: return a database which contains all books have the author equal to the string
		Database ans;
		for (int i=0;i<v.size();++i)  if (format_string(v[i]->getAuthor())==s) ans.Add(v[i]);
		return ans;
	}
	Database search_book_by_Date(const int& x, const int& y) const
	{
		//pre-condition: 2 number x and y
		//post-condition: return a database which contains all books have x <= the public year <= y
		Database ans;
		for (int i=0;i<v.size();++i)  if (x<=v[i]->getDate() && v[i]->getDate()<=y) ans.Add(v[i]);
		return ans;
	}
	Database search_book_by_Type(const string& s) const
	{
		//pre-condition: a string
		//post-condition: return a database which contains all books have type equal to s
		Database ans;
		for (int i=0;i<v.size();++i)  if (check_num_in_string(v[i]->getType(),s)) ans.Add(v[i]);
		return ans;
	}
	Database search_book_by_NOP(const int& x, const int& y) const
	{
		//pre-condition: 2 number x and y
		//post-condition: return a database which contains all books have x <= the number of pages <= y
		Database ans;
		for (int i=0;i<v.size();++i)  if (x<=v[i]->getNOP() && v[i]->getNOP()<=y) ans.Add(v[i]);
		return ans;
	}
	Database Advanced_Search_Book(const string& Title,const string& Author,int Datex,int Datey,string Type,int NOPx, int NOPy) const
	{
		//pre-condition: 3 strings and 2 numbers
		//post-condition: return a database which contains all books have all the properties
		Database a = *this;
		for (int i=0;i<a.getNOR();++i)
		{
			bool flag = 0;
			if (Title!="..." && format_string(a[i]->getTitle())!=Title) flag = 1;
			if (Author!="..." && format_string(a[i]->getAuthor())!=Author) flag = 1;
			if (a[i]->getDate()<Datex || a[i]->getDate()>Datey) flag = 1;
			if (!check_num_in_string(a[i]->getType(),Type)) flag = 1;
			if (a[i]->getNOP()<NOPx || a[i]->getNOP()>NOPy) flag = 1;
			if (flag) a.Pop(i--);
		}
		return a;
	}

	static void Read_valid_Date(istream& in,const Database& D,int& n1,int& n2)
	{
		//pre-condition: the current database, the starting year and the ending year
		//post-condition: force user to enter a valid starting year and the ending year
		string s;
		while (1)
		{
			n1=-1,n2=-1;
			cout << "Enter the starting year, type [-1] if unspecified: ";
			in >> s;
			if (s=="-1") n1 = 0;
			else if (isNumber(s)) n1 = string2num(s);
			cout << "Enter the destination year, type [-1] if unspecified: ";
			in >> s;
			if (s=="-1") n2 = D.getNewestDate();
			else if (isNumber(s)) n2 = string2num(s);
			if (n1<=n2 && n1!=-1 && n2!=-1) break;
			else  cout << "Input invalid! Years must be number and the destination year musts be larger than the start year\n";
		}
	}
	static void Read_valid_NOP(istream& in,const Database& D,int& n1,int& n2)
	{
		//pre-condition: the current database, the left bound and the right bound
		//post-condition: force user to enter a valid left bound and the right bound
		string s;
		while (1)
		{
			n1=-1,n2=-1;
			cout << "Enter the left bound, type [-1] if unspecified: ";
			in >> s;
			if (s=="-1") n1 = 0;
			else if (isNumber(s)) n1 = string2num(s);
			cout << "Enter the right bound, type [-1] if unspecified: ";
			cin >> s;
			if (s=="-1") n2 = D.getMostNOP();
			else if (isNumber(s)) n2 = string2num(s);
			if (n1<=n2 && n1!=-1 && n2!=-1) break;
			else  cout << "Input invalid! The bounds must be number and the right bound musts be larger than the left bound\n";
		}
	}
	static void Read_valid_Type(istream& in,Database& D,string& s)
	{
		//pre-condition: the current database, a string s
		//post-condition: force user to enter a valid type
		int n;
		while (1)
		{
			cout << "Enter the book type: ";
			in >> s;
			s = format_string(s);
			n = Book::getCategory_num(s);
			if (n!=-1)
			{
				s = n + '0';
				break;
			}
			else
			{
				bool flag = 1;
				for (int i=0;i<s.size();++i) if (s[i]<'1' || '3'<s[i]) flag = 0;
				if (flag) break;
			}
			cout << "Invalid input, type is supposed to be 1, 2, 3 or the full word!\n";
		}
		for (int i=0;i<s.size();++i)
			for (int j=i+1;j<s.size();++j) if (s[i]==s[j]) s.erase(j--,1);
	}

	////Hidden feautures in searching option
	//Database Suggest_by_title(const string& s,int num) const
	//{
	//	//pre-condition: take a string s and a number num
	//	//post-condition: return a database that has num book record(s) which are the most similiar to the given title
	//	Database a;
	//	Database b = *this;
	//	num = (num<b.getNOR()) ? num : b.getNOR();
	//	vector<double> score;
	//	for (int i=0;i<b.getNOR();++i) score.push_back(calculating_score(s,format_string(b[i]->getTitle())));
	//	for (int i=0;i<num;++i)
	//	{
	//		int max = 0;
	//		for (int j=0;j<b.getNOR();++j) if (score[max]<score[j]) max = j;
	//		a.Add(b[max]);
	//		b.Pop(max);
	//		score.erase(score.begin()+max);
	//	}
	//	return a;
	//}
	//Database Suggest_by_author(const string& s,int num) const
	//{
	//	//pre-condition: take a string s and a number num
	//	//post-condition: return a database that has num book record(s) which are the most similiar to the given author
	//	Database a;
	//	Database b = *this;
	//	num = (num<b.getNOR()) ? num : b.getNOR();
	//	vector<double> score;
	//	for (int i=0;i<b.getNOR();++i) score.push_back(calculating_score(s,format_string(b[i]->getAuthor())));
	//	for (int i=0;i<num;++i)
	//	{
	//		int max = 0;
	//		for (int j=0;j<b.getNOR();++j) if (score[max]<score[j]) max = j;
	//		a.Add(b[max]);
	//		b.Pop(max);
	//		score.erase(score.begin()+max);
	//	}
	//	return a;
	//}

	//pre-condition: 
	//post-condition: sorting the database
	void sort_by_Title()
	{
		sort(v.begin(),v.end(),Book::cmp_by_Title);
	}
	void sort_by_Author()
	{
		sort(v.begin(),v.end(),Book::cmp_by_Author);
	}
	void sort_by_Date()
	{
		sort(v.begin(),v.end(),Book::cmp_by_Date);
	}
	void sort_by_Type()
	{
		sort(v.begin(),v.end(),Book::cmp_by_Type);
	}
	void sort_by_NOP()
	{
		sort(v.begin(),v.end(),Book::cmp_by_NOP);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////

	string toString() const
	{
		//pre-condition: 
		//post-condition: print the database to the screen in nice format, contains only elements, no size of the database
		stringstream ss;
		if (this->getNOR()>0)
		{
			for (int i=0;i<getNOR()-1;++i) ss << i+1 << ". " << *v[i] << "\n";
			ss << getNOR() << ". " << *v[getNOR()-1];
		}
		return ss.str();
	}

	friend ostream& operator<<(ostream& out,const Database& D);
};

ostream& operator<<(ostream& out, Database& D)
{
	//pre-condition: 
	//post-condition: print the database to the screen in nice format with the size of the database
	out << "There are " << D.getNOR() << " book record(s) in the database";
	if (D.getNOR()>0)
	{
		cout << "\n";
		for (int i=0;i<D.getNOR()-1;++i) cout << i+1 << ". " << *D[i] << "\n";
		cout << D.getNOR() << ". " << *D[D.getNOR()-1];
	}
	return out;
}

///////////////////////////////Menu Design/////////////////////////////////////////

int choice(const int& l,const int& r)
{
	//pre-condition: 2 integer numbers l and r
	//post-condition: force user to enter the valid input which is in range [l,r]
	string s;
	int n;
	cin >> s;
	while (1)
	{
		if (isNumber(s))
		{
			n = string2num(s);
			if (l<=n && n<=r) return n;
		}
		cout << "Invalid input! please enter again: ";
		cin >> s;
	}
}

void print_split()
{
	for (int i=0;i<100;++i) cout << "#";
	cout << "\n";
}

void Adding_Menu(Database& D)
{
	//pre-condition: Taking the main database 
	//post-condition: Adding a new book record to it
	system("cls");
	print_split();
	cout << "Adding a book record\n";
	print_split();
	BookPtr x = new Book();
	cin >> *x;
	D.Add(x);
	cout << "Added!\n";
	system("Pause");
}

void Sort_Engine(Database& D,const int& option)
{
	//pre-condition: a database D and an integer
	//post-condition: sort the database by the integer option
	switch (option)
	{
	case 1:
		D.sort_by_Title();
		break;
	case 2:
		D.sort_by_Author();
		break;
	case 3:
		D.sort_by_Date();
		break;
	case 4:
		D.sort_by_Type();
		break;
	case 5:
		D.sort_by_NOP();
		break;
	}
}
void Sort_list_Menu(Database& D)
{
	//pre-condition: 
	//post-condition: Menu for sorting
	system("cls");
	cout << D << "\n";
	print_split();
	cout << "(1).Sort by title\n";
	cout << "(2).Sort by author\n";
	cout << "(3).Sort by date of publication\n";
	cout << "(4).Grouping by type\n";
	cout << "(5).Sort by number of pages\n\n";

	cout << "(0).Back to main menu\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,5);
	switch (n)
	{
	case 0:
		return;
	default:
		Sort_Engine(D,n);
	}
}

void Search_Mode_result_Print(Database& a)
{
	//pre-condition: Taking a database 
	//post-condition: print that database which is the search result in nice format
	print_split();
	if (a.getNOR()==0) cout << "Sorry, no book record matched!\n";
	else
	{
		cout << a << "\n";
		print_split();
		return;
	}
	print_split();
}

void print_status_AS(string& title, string& author, int& datex, int& datey, string& type, int& NOPx,int& NOPy)
{
	//pre-condition: Taking detail of a book record
	//post-condition: print the status of Advanced Searching in nice format
	system("cls");
	cout << "Title: " << title <<"\n";
	cout << "Author: " << author << "\n";
	if (datex==-1 && datey==-1) cout << "The books were published from _ to _\n";
	else cout << "The books were published from " << datex << " to " << datey << "\n";
	cout << "The books have type: ";
	if (type.size()>0)
	{
		for (int i=0;i<type.size()-1;++i) cout << Book::getCategory_word(type[i]-'0') << ", ";
		cout << Book::getCategory_word(type[type.size()-1]-'0');
	}
	cout << "\n";

	if (NOPx==-1 && NOPy==-1) cout << "The books have _ to _ pages\n";
	else cout << "The books have " << NOPx << " to " << NOPy << " pages\n";
}
Database Searching_Engine(Database& D,string& s,const int& n)
{
	//pre-condition: Taking a database and the option
	//post-condition: return the sorting database
	int n1=-1,n2=-1;
	switch (n)
	{
	case 1:
		cout << "Enter the title: ";
		cin >> s;
		s = format_string(s);
		return D.search_book_by_Title(s);
	case 2:
		cout << "Enter the author name: ";
		cin >> s;
		s = format_string(s);
		return D.search_book_by_Author(s);
	case 3:
		
		Database::Read_valid_Date(cin,D,n1,n2);
		return D.search_book_by_Date(n1,n2);
	case 4:
		print_split();
		cout << "Instruction\n";
		cout << "(1) hardcover\t(2) softcover\t(3) digital\n";
		cout << "Enter the ID number or full word of the type, if you want multicategory, just enter the ID number without space no matter order.\n";
		cout << "For example: if you want hardcover and digital only, type[13]\n";
		print_split();
		Database::Read_valid_Type(cin,D,s);
		return D.search_book_by_Type(s);
	case 5:
		Database::Read_valid_NOP(cin,D,n1,n2);
		return D.search_book_by_NOP(n1,n2);
	case 6:
		string title,author,type;
		int datex=-1,datey=-1,NOPx=-1,NOPy=-1;
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);
		print_split();
		string s;

		cout << "Enter the title, type [...] if unspecified: ";
		cin >> s;
		title = s;
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);
		print_split();

		cout << "Enter the author name, type [...] if unspecified: ";
		cin >> s;
		author = s;
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);
		print_split();

		Database::Read_valid_Date(cin,D,datex,datey);
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);
		print_split();

		cout << "Instruction\n";
		cout << "(1) hardcover\t(2) softcover\t(3) digital\n";
		cout << "Enter the category you want to search for by the ID number or full word, if you want to search multicategory, just enter the ID number without space no matter order.\n";
		cout << "For example: if you want to search for hardcover and digital only, type[13]\n\n";
		Database::Read_valid_Type(cin,D,type);
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);
		print_split();

		Database::Read_valid_NOP(cin,D,NOPx,NOPy);
		print_status_AS(title,author,datex,datey,type,NOPx,NOPy);

		title = format_string(title);
		author = format_string(author);
		return D.Advanced_Search_Book(title,author,datex,datey,type,NOPx,NOPy);
	}
	return D;
}
bool Search_Mode_result_Menu(Database& a)
{
	//pre-condition: Taking a database 
	//post-condition: print searching result and suggest some sorting options for Advanced Search only
	system("cls");
	Search_Mode_result_Print(a);
	cout << "(1).Sort by title\n";
	cout << "(2).Sort by author\n";
	cout << "(3).Sort by date of publication\n";
	cout << "(4).Grouping by type\n";
	cout << "(5).Sort by number of pages\n\n";

	cout << "(0).Back to main menu\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,5);
	switch (n)
	{
	case 0:
		return 1;
	default:
		Sort_Engine(a,n);
	}
	return 0;
}
void Search_Mode_print(Database& D,const int& n)
{
	//pre-condition: 
	//post-condition: print searching result in nice format for normal search, and suggests the closest book in some situation that the input of user is not accurate
	system("cls");
	string s;
	Database a = Searching_Engine(D,s,n);
	if (a.getNOR()==0)
	{
		Search_Mode_result_Print(a);

		////Hidden feature in searching option
		//if (n==1 || n==2)
		//{
		//	Database S;
		//	if (n==1) S = D.Suggest_by_title(s,5);
		//	else S = D.Suggest_by_author(s,5);
		//	cout << "Suggestions: \n";
		//	cout << S.toString() << "\n";
		//}

		system("Pause");
	} else while (!Search_Mode_result_Menu(a)) ;
}
bool Search_Sub_Menu(Database& D)
{
	//pre-condition: 
	//post-condition: print searching menu options in nice format
	system("cls");
	if (D.getNOR()==0)
	{
		cout << "No book record found!\n";
		system("Pause");
		return 1;
	}
	print_split();
	cout << "(1).Searching by title\n";
	cout << "(2).Searching by author\n";
	cout << "(3).Searching by date of publication\n";
	cout << "(4).Searching by type\n";
	cout << "(5).Searching by number of pages\n";
	cout << "(6).Advanced Searching\n\n";

	cout << "(0).Return to main menu\n";
	print_split();
	string s;
	cout << "Enter your choice: ";
	int n = choice(0,6);
	switch (n)
	{
	case 0:
		return 1;
	default:
		Search_Mode_print(D,n);
	}
	return 0;
} 

void print_status_Book(const Book& x)
{
	//pre-condition: taking a book
	//post-condition: print the book detail in nice format
	cout << "Title: " << x.getTitle() << "\n";
	cout << "Author: " << x.getAuthor() << "\n";
	cout << "Date of publication: " << x.getDate() << "\n";
	cout << "Type: " << Book::getCategory_word(x.getType()) <<"\n";
	cout << "Number of pages: " << x.getNOP() << "\n";
}
void Editing_title(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: allow user to modifying the book object's title
	system("cls");
	print_status_Book(*x);
	print_split();
	string s;
	cout << "Enter the title: ";
	cin >> s;
	while (s=="...")
	{
		cout << "Invalid input! the title name can not be ...!\n";
		cout << "Enter the title: ";
		cin >> s;
	}
	x->setTitle(s);
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "Modified!\n";
	system("Pause");
}
void Editing_author(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: allow user to modifying the book object's author
	system("cls");
	print_status_Book(*x);
	print_split();
	string s;
	cout << "Enter the new author name: ";
	cin >> s;
	while (s=="...")
	{
		cout << "Invalid input! the author name can not be ...!\n";
		cout << "Enter the new author name: ";
		cin >> s;
	}
	x->setAuthor(s);
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "Modified!\n";
	system("Pause");
}
void Editing_Date(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: allow user to modifying the book object's public date
	system("cls");
	print_status_Book(*x);
	print_split();
	string s;
	cout << "Enter the new publication year: ";
	cin >> s;
	while (!isNumber(s))
	{
		cout << "Invalid input! the publication year musts be a non negative number!\n";
		cout << "Enter the new publication date: ";
		cin >> s;
	}
	x->setDate(s);
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "Modified!\n";
	system("Pause");
}
void Editing_Type(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: allow user to modifying the book object's type
	system("cls");
	print_status_Book(*x);
	print_split();
	string s;
	cout << "(1) Hardcover\t(2) Softcover\t(3) Digital\n";
	cout << "Enter the new type ID number: ";
	cin >> s;
	while (s.size()!=1 || s[0]<'1' || s[0]>'3')
	{
		cout << "Invalid input! please choose one of those type ID number!\n";
		cout << "Enter the new type ID number: ";
		cin >> s;
	}
	x->setType(s);
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "Modified!\n";
	system("Pause");
}
void Editing_NOP(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: allow user to modifying the book object's number of pages
	system("cls");
	print_status_Book(*x);
	print_split();
	string s;
	cout << "Enter the new number of pages: ";
	cin >> s;
	while (!isNumber(s))
	{
		cout << "Invalid input! the number of pages musts be a non negative number!\n";
		cout << "Enter the new number of pages: ";
		cin >> s;
	}
	x->setNOP(s);
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "Modified!\n";
	system("Pause");
}

bool Modifying_Menu(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: print all the Updating options
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "(1).Modifying the title\n";
	cout << "(2).Modifying the author\n";
	cout << "(3).Modifying the date of publication\n";
	cout << "(4).Modifying the type\n";
	cout << "(5).Modifying the number of pages\n\n";

	cout << "(0).Return to previous page\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,5);
	switch (n)
	{
	case 1:
		Editing_title(x);
		break;
	case 2:
		Editing_author(x);
		break;
	case 3:
		Editing_Date(x);
		break;
	case 4:
		Editing_Type(x);
		break;
	case 5:
		Editing_NOP(x);
		break;
	case 0:
		return 1;
	}
	return 0;
}
void Removing_Menu(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: set the book object's title to "..." to delete it later
	system("cls");
	print_status_Book(*x);
	print_split();
	x->setTitle("...");
	cout << "Removed!\n";
	system("Pause");
}

bool Choose_Book_Sub_Menu(BookPtr& x)
{
	//pre-condition: taking a book pointer
	//post-condition: Showing some options allow user to modifying or removing a book in database
	system("cls");
	print_status_Book(*x);
	print_split();
	cout << "(1).Modifying\n";
	cout << "(2).Removing\n\n";

	cout << "(0).Return to the previous menu\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,2);
	switch (n)
	{
	case 1:
		while (!Modifying_Menu(x)) ;
		break;
	case 2:
		Removing_Menu(x);
		return 1;
	case 0:
		return 1;
	}
	return 0;
}
void Choose_Book_Menu(Database& D)
{
	//pre-condition: taking database
	//post-condition: take input from user which is the index of the book record
	system("cls");
	cout << D << "\n";
	print_split();
	cout << "Enter the index of the book record: ";
	int i = choice(1,D.getNOR());
	while (!Choose_Book_Sub_Menu(D[i-1])) ;
}

Database Filter_Menu(Database D)
{
	//pre-condition: taking a database
	//post-condition: create a new database that contains all the books that match the requirement of the user
	system("cls");
	cout << D << "\n";
	print_split();
	cout << "(1).Filter by title\n";
	cout << "(2).Filter by author\n";
	cout << "(3).Filter by public date\n";
	cout << "(4).Filter by type\n";
	cout << "(5).Filter by number of pages\n";

	print_split();
	cout << "Enter your choice: ";
	int n = choice(1,5);
	string s;
	system("cls");
	return Searching_Engine(D,s,n);
}
bool Remove_Update_Sub_Menu_filter_on(Database D)
{
	//pre-condition: 
	//post-condition: Show option for user to choose
	system("cls");
	cout << D << "\n";
	print_split();
	if (D.getNOR()==0)
	{
		cout << "No book record found!\n";
		system("Pause");
		return 1;
	}
	cout << "(1).Choose book\n";
	cout << "(2).Unfilter\n\n";

	cout << "(0).Return to main menu\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,2);
	switch (n)
	{
	case 1:
		Choose_Book_Menu(D);
		return 1;
	case 2:
		return 1;
	default:
		return 0;
	}
}
bool Remove_Update_Sub_Menu(Database& D)
{
	//pre-condition:  
	//post-condition: similiar to Remove_Update_Sub_Menu_filter_on but this function call when the filter is off
	bool flag;
	system("cls");
	cout << D << "\n";
	print_split();
	if (D.getNOR()==0)
	{
		cout << "No book record found!\n";
		system("Pause");
		return 1;
	}
	cout << "(1).Choose book\n";
	cout << "(2).Sort list\n";
	cout << "(3).Filter\n\n";

	cout << "(0).Return to main menu\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,3);
	switch (n)
	{
	case 1:
		Choose_Book_Menu(D);
		D.Clean();
		break;
	case 2:
		Sort_list_Menu(D);
		break;
	case 3:
		flag = Remove_Update_Sub_Menu_filter_on(Filter_Menu(D));
		D.Clean();
		if (flag) break;
		else return 1;
	case 0:
		return 1;
	}
	return 0;
}

bool Main_Menu(Database& D)
{
	//pre-condition: 
	//post-condition: Show options for user in main menu
	system("cls");
	cout << D << "\n";
	print_split();
	cout << "(1).Add a new book record\n";
	cout << "(2).Updating or removing an existing book record\n";
	cout << "(3).Search books\n";
	cout << "(4).Import database from a file\n";
	cout << "(5).Export database to a file\n\n";

	cout << "(0).Quit\n";
	print_split();
	cout << "Enter your choice: ";
	int n = choice(0,5);
	switch (n)
	{
	case 1:
		Adding_Menu(D);
		break;
	case 2:
		while (!Remove_Update_Sub_Menu(D)) ;
		break;
	case 3:
		while (!Search_Sub_Menu(D)) ;
		break;
	case 4:
		D.Import("Database.txt");
		system("Pause");
		break;
	case 5:
		D.Export("MyDataBase.txt");
		system("Pause");
		break;
	case 0:
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
 {
	Database D;
	while (!Main_Menu(D)) ;
	D.Manual_Destructor();
	return 0;
}