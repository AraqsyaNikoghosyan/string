#ifndef STRING_H
#define STRING_H

class String{
public:
	String() : m_size(0) {}
	String(const char * line);
	String(String &&);
	~String() {
		if(m_size >= m_maxOnStack) {
			delete [] m_str.onHeap;
		}
	}
 	void append(const char *);
	void insert(char, int);
	void erase();
	bool empty();
	int length();
	void print();
	void operator=(const char *);
	String operator+(const String&);
	char& operator[](unsigned int);

private:
	static const int m_maxOnStack = 17;
	int m_size;
	union {
		char * onHeap;
		char onStack[m_maxOnStack];
	} m_str;

};

#endif // STRING_H
