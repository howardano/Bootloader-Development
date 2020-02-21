#pragma once

#pragma once

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class ErrorWithFormat : public std::exception {
	std::string error;
public:
	ErrorWithFormat() {
		error.assign("Error. Trying to open unsupported format...\n");
	}
	explicit ErrorWithFormat(const std::string file_format) {
		error.assign("File format \"" + file_format + "\" is not supported!");
	}
	const char* what() const override {
		return error.c_str();
	}
};

class ErrorWithFindingTheFile : public std::exception {
	std::string error;
public:
	ErrorWithFindingTheFile() {
		error.assign("Error. Trying to open unexisting file...");
	}
	explicit ErrorWithFindingTheFile(const std::string file_) {
		error.assign("Error. Trying to open unexisting file...");
	}
	const char* what() const override {
		return error.c_str();
	}
};

#endif