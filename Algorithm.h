#pragma once

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>

template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}

template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value)
{
	for (; first != last; ++first) {
		if (*first == value) {
			return first;
		}
	}
	return last;
}

template<class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; ++first) {
		if (p(*first)) {
			return first;
		}
	}
	return last;
}

#endif