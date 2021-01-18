#pragma once

#include <ostream>
#include <iostream>
#include <chrono>
#include <iomanip>

namespace alloy::debug {
enum class LogSeverity : uint8_t {
	NORMAL = 0,
	WARNING,
	ERROR
};

inline std::string LogSeverityToString(const LogSeverity severity) {
	switch(severity){
	case LogSeverity::NORMAL:
		return "Normal";
	case LogSeverity::WARNING:
		return "Warning";
	case LogSeverity::ERROR:
		return "Error";
	}

	return "";
}

enum class LogType : uint8_t {
	CORE_ENGINE = 0,
	GRAPHICS,
	PHYSICS,
	GAMEPLAY
};

inline std::string LogTypeToString(const LogType type) {
	switch(type) {

	case LogType::CORE_ENGINE:
		return "CoreEngine";
	case LogType::GRAPHICS:
		return "Graphics";
	case LogType::PHYSICS:
		return "Physics";
	case LogType::GAMEPLAY:
		return "Gameplay";
	default: 
		return "";
	}

	return "";
}

/// <summary>
/// This function is to be used inside other logger function. Prefer using Log
/// </summary>
/// <param name="msg"></param>
/// <param name="type"></param>
/// <param name="severity"></param>
void LogIntern(const char* msg, const LogType type, LogSeverity severity) {
	//Date
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm ltm;
	localtime_s(&ltm, &end_time);

	/*
	 * Name            FG  BG
		Black           30  40
		Red             31  41
		Green           32  42
		Yellow          33  43
		Blue            34  44
		Magenta         35  45
		Cyan            36  46
		White           37  47
		Bright Black    90  100
		Bright Red      91  101
		Bright Green    92  102
		Bright Yellow   93  103
		Bright Blue     94  104
		Bright Magenta  95  105
		Bright Cyan     96  106
		Bright White    97  107
	 */
	
	//Color
	switch(severity) {

	case LogSeverity::NORMAL:
		std::cout << "\033[97m"; //white
		break;
	case LogSeverity::WARNING:
		std::cout << "\033[93m"; //yellow
		break;
	case LogSeverity::ERROR:
		std::cout << "\033[91m"; //red
		break;
	default: ;
	}
	
	std::cout << "[" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << "]" << "[" <<  LogTypeToString(type) << "] " << msg;
	std::cout << "\033[0m\n"; //Close color and add return
}

inline void Log(const std::string_view msg, const LogType type = LogType::GAMEPLAY) {
	LogIntern(msg.data(), type, LogSeverity::NORMAL);
}

inline void LogWarning(const std::string_view msg, const LogType type = LogType::GAMEPLAY) {
	LogIntern(msg.data(), type, LogSeverity::WARNING);
}

inline void LogError(const std::string_view msg, const LogType type = LogType::GAMEPLAY) {
	LogIntern(msg.data(), type, LogSeverity::ERROR);
}
}
