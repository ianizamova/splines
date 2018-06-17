#pragma once

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>


template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
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
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
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
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: ---" << t << "+++ != ---" << u
			<< "+++ hint: " << hint;
		throw std::runtime_error(os.str());
	}
};

template<class T, class U>
void AssertEqual(const std::vector<T>& vt, const std::vector<U>& vu, const std::string& hint)
{
	if (vt != vu) {
		std::ostringstream os;
		os << "Assertion failed: " << vt << " != " << vu
			<< " hint: " << hint;
		throw std::runtime_error(os.str());
	}
};

template<class T, class U>
void AssertEqual(const std::pair<T,U>& p1, const std::pair<T,U>& p2, const std::string& hint)
{
	if (!(p1 == p2)) {
		std::ostringstream os;
		os << "Assertion failed: " << p1 << " != " << p2
			<< " hint: " << hint;
		throw std::runtime_error(os.str());
	}
};


//
//void AssertEqual(const vector<string>& vt, const vector<string>& vu, const string& hint);

void Assert(bool b, const std::string& hint);


class TestRunner {
public:
	TestRunner() {};

	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name);

	~TestRunner();

private:
	int fail_count = 0;
};


template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string& test_name) {
	try {
		func();
		std::cerr << test_name << " OK" << std::endl;
	}
	catch (std::runtime_error& e) {
		++fail_count;
		std::cerr << test_name << " fail: " << e.what() << std::endl;
	}
}