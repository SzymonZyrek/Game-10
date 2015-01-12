#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <sstream>
#include <ostream>
#include <fstream>
#include "Aggregation.h"

#define LOG Logger::_sdg78su(""); logger<<(Logger::_sdg78su

enum DebugKey {
	EVENTS, OBJECT_CREATION, OBJECT_DESTRUCTION, COPY_CONSTRUCTORS, CONFIGURATION, LOGGING, RENDERING, ACCUMULATOR, GL_ERRORS, SHADERS, MODEL_LOADING, TEXTURES
};
enum LoggingMode {
	INFO, ERROR, DEBUG, AGGREGATION, INFO_PERIODIC, DEBUG_PERIODIC, DEBUG_AGGREGATION
};

class Logger {
public:
	static std::stringstream _sdg78su;
	Logger();
	Logger(DebugKey);
	Logger(unsigned int periodicKey, DebugKey);
	Logger(unsigned int periodicKey);
	Logger(std::vector<std::string(*)(std::vector<std::string>&)> functions, unsigned int periodicKey);
	Logger(std::vector<std::string(*)(std::vector<std::string>&)> functions, unsigned int periodicKey, DebugKey);
	
	LoggingMode mode;
	DebugKey debugKey;
	unsigned int periodicKey;
	std::vector<std::string(*)(std::vector<std::string>&)> functions;
};

std::ostream& operator<<(Logger &a, std::ostream &ss);
void operator<<(std::string sa, std::string ss);

class Log
{
public:
	Log();
	Log(std::string logFilePath);
	~Log();
	static void error(std::string err);
	static void warning(std::string warn);
	static void info(std::string msg);
	static void periodic(std::string msg, int key);
	bool isLogToConsole();
	bool isLogToFile();
	void setLogToConsole(bool val);
	void setLogToFile(bool val);
	static Log* getInstance();
	unsigned int getLogPeriodicKey(double period);
	static void debug(std::string msg, DebugKey key);
	static void debugPeriodic(std::string msg, int key, DebugKey dkey);
	static DebugKey debugKeyFromString(std::string keyAsString);
	static void periodicAggregate(std::string msg, std::vector<std::string(*)(std::vector<std::string>&)> functions, int key);
	static void periodicAggregate(std::string msg, std::vector<std::string(*)(std::vector<std::string>&)> functions, int key, DebugKey dkey);
	static std::string debugKeyAsString(DebugKey key);
	void flush();
private:
	static Log* _instance;
	bool _logToConsole = false;
	std::map<int, double> _periodsByKey;
	std::map<int, double> _lastLogByKey;
	std::map<int, std::vector<std::vector<std::string>>> _aggregationParamsByKey;
	static std::set<DebugKey> _activeDebugKeys;
	bool _logToFile;
	int _lastLogPeriodicKey = 0;
	std::string _logFilePath;
	void printToConsole(std::string msg);
	void printToLogFile(std::string msg);
	static std::map<DebugKey, std::string> getDebugKeyToString();
	static std::map<std::string, DebugKey> getStringToDebugKey();
	const std::map<DebugKey, std::string> _debugKeyToString = getDebugKeyToString();
	const std::map<std::string, DebugKey> _stringToDebugKey = getStringToDebugKey();
};
