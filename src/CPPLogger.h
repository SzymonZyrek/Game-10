#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <sstream>
#include "Aggregation.h"

enum DebugKey {
	EVENTS, OBJECT_CREATION, OBJECT_DESTRUCTION, COPY_CONSTRUCTORS, CONFIGURATION, LOGGING, RENDERING, ACCUMULATOR, GL_ERRORS
};

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

	template<typename T>
	bool DaFunc(std::string Arg1, T&& Arg2){
		if (Arg1 > 0){
			return Arg2(Arg1);
		}

		return false; // <== DO NOT FORGET A return STATEMENT IN A VALUE-RETURNING
		//     FUNCTION, OR YOU WILL GET UNDEFINED BEHAVIOR IF FLOWING
		//     OFF THE END OF THE FUNCTION WITHOUT RETURNING ANYTHING
	}

};
