#include "string.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

String::String(const char * line) {
		
	if(strlen(line) < m_maxOnStack) {
		strcpy(m_str.onStack, line);
		m_size = strlen(line);
	}
	else {
		m_size = strlen(line);
		m_str.onHeap = new char [m_size + 1];
		strcpy(m_str.onHeap, line);
	}
}

String::String(String&& tmp) {
	m_size = tmp.m_size;
	if(m_size >= m_maxOnStack) {
		m_str.onHeap = tmp.m_str.onHeap;
		tmp.m_str.onHeap = nullptr;
	}
	else {
		for(int i = 0; i < m_size; ++i) {
			m_str.onStack[i] = tmp.m_str.onStack[i];
	
		}
	}
	tmp = nullptr;
}

void String::append(const char *str2) {
	if(m_size + strlen(str2) <  m_maxOnStack) {
		char * p = m_str.onStack + m_size;
		strcpy(p, str2);
	}	
	else {
		char * temp = new char [m_size + strlen(str2) + 1];
		if(m_size < m_maxOnStack) {
			strcpy(temp, m_str.onStack);
		}
		else {
			strcpy(temp, m_str.onHeap);
		}
		strcat(temp, str2);
		delete [] m_str.onHeap;
		m_str.onHeap = temp;
	}
	m_size += strlen(str2);
}

void String::insert(char ch, int indx) {
	if (indx > m_size) {
		throw std::invalid_argument("invalid index");
	}
	else if(m_size + 1 < m_maxOnStack) {
		for(int i = m_size; i > indx; --i) {
			m_str.onStack[i] = m_str.onStack[i - 1];
		}
		m_str.onStack[indx] = ch;
	}
	else if(m_size < m_maxOnStack) {
		char * temp = new char [m_size + 1];
		for(int i = 0, j = 0; i < m_size; ++i, ++j) {
			if(j == indx) {
				temp[j] = ch;
				j++;
			}
			else {
				temp[j] = m_str.onStack[i];
			}

		}
		m_str.onHeap = temp;
	}
	else {
		char * temp = new char [m_size + 1];
		for(int i = 0, j = 0; i < m_size; ++i, ++j) {
			if(j == indx) {
				temp[j] = ch;
				j++;
				temp[j] = m_str.onHeap[i];
			}
			else {
				temp[j] = m_str.onHeap[i];
			}

		}
		m_str.onHeap = temp;

	}
	m_size ++;
}

void String::erase() {
	if(m_size >= m_maxOnStack) {
		delete [] m_str.onHeap;
		m_str.onHeap = nullptr;
	}
	m_str.onStack[0] = '/0';
	m_size = 0;
	
}

bool String::empty() {
	return m_size == 0;
}

int String::length() {
	return m_size;
}

void String::print() {
	if (m_size < m_maxOnStack) {
		std::cout << m_str.onStack;
		
	}
	else {
		for (int i = 0; i < m_size; ++i) {
			std::cout << m_str.onHeap[i];
		}	
	}
	std::cout << std::endl;

}



void String::operator=(const char *str) {
	erase();
	append(str);
}

char& String::operator[](unsigned int indx) {
	if (m_size < m_maxOnStack) {
		return m_str.onStack[indx];
	}
	return m_str.onHeap[indx];
}

String String::operator+(const String& other) {
	String result;
	const char * operand1 = (m_size < m_maxOnStack) ? m_str.onStack : m_str.onHeap;
	const char * operand2 = (other.m_size < other.m_maxOnStack) ? other.m_str.onStack : other.m_str.onHeap;
	result.append(operand1);
	result.append(operand2);
	return result;
}

