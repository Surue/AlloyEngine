#pragma once

#include <string>
#include <iostream>

static void Log(const std::string& message) {
	std::cout << message << "\n";
}

static void Log(const char* message) {
	std::cout << message << "\n";
}

static void LogError(const std::string& message) {
	std::cerr << "ERROR : " << message << "\n";
}

static void LogError(const char* message) {
	std::cerr << "ERROR : " << message << "\n";
}