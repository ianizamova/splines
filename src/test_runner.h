#pragma once

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

//template<class T, class U>
//bool operator==(const pair<T, U> p1, const pair<T, U> p2)
//{
//	return ((p1.first == p2.first) && (p1.second == p2.second));
//}
//
//template<class T, class U>
//bool operator!=(const pair<T, U> p1, const pair<T, U> p2)
//{
//	return !((p1.first == p2.first) && (p1.second == p2.second));
//}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
};

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "[";
	bool first = true;
	for (const auto& x : v) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "]";
};

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
};

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: ---" << t << "+++ != ---" << u
			<< "+++ hint: " << hint;
		throw runtime_error(os.str());
	}
};

template<class T, class U>
void AssertEqual(const vector<T>& vt, const vector<U>& vu, const string& hint)
{
	if (vt != vu) {
		ostringstream os;
		os << "Assertion failed: " << vt << " != " << vu
			<< " hint: " << hint;
		throw runtime_error(os.str());
	}
};

template<class T, class U>
void AssertEqual(const pair<T,U>& p1, const pair<T,U>& p2, const string& hint)
{
	if (!(p1 == p2)) {
		ostringstream os;
		os << "Assertion failed: " << p1 << " != " << p2
			<< " hint: " << hint;
		throw runtime_error(os.str());
	}
};


//
//void AssertEqual(const vector<string>& vt, const vector<string>& vu, const string& hint);

void Assert(bool b, const string& hint);


class TestRunner {
public:
	TestRunner() {};

	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name);

	~TestRunner();

private:
	int fail_count = 0;
};


template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
	try {
		func();
		cerr << test_name << " OK" << endl;
	}
	catch (runtime_error& e) {
		++fail_count;
		cerr << test_name << " fail: " << e.what() << endl;
	}
}