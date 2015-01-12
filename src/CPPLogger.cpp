#include "CPPLogger.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "Config.h"
#include <cstdio>
#include <regex>

#define LOG_FILE_BUFFER_SIZE 500


std::stringstream _logFileBuffer;
std::set<DebugKey> Log::_activeDebugKeys;
Log* Log::_instance = new Log;
int count = 0;

Logger::Logger()
{
	this->mode = INFO;
}

Logger::Logger(DebugKey key)
{
	this->mode = DEBUG;
	this->debugKey = key;
}
Logger::Logger(unsigned int periodicKey, DebugKey key)
{
	this->mode = DEBUG_PERIODIC;
	this->periodicKey = periodicKey;
	this->debugKey = key; 
}
Logger::Logger(std::vector<std::string(*)(std::vector<std::string>&)> functions, unsigned int periodicKey, DebugKey key)
{
	this->mode = DEBUG_AGGREGATION;
	this->functions = functions;
	this->periodicKey = periodicKey;
	this->debugKey = key;
}
Logger::Logger(unsigned int periodicKey)
{
	this->mode = INFO_PERIODIC;
}
Logger::Logger(std::vector<std::string(*)(std::vector<std::string>&)> functions, unsigned int periodicKey)
{
	this->mode = AGGREGATION;
	this->functions = functions;
	this->periodicKey = periodicKey;
}

std::ostream& operator<<(Logger &a, std::ostream &ss)
{
	std::stringstream stringstream;
	stringstream << ss.rdbuf();


	switch (a.mode)
	{
	case INFO:
		Log::info(stringstream.str());
		break;
	case DEBUG:
		Log::debug(stringstream.str(), a.debugKey);
		break;
	case INFO_PERIODIC:
		Log::periodic(stringstream.str(), a.periodicKey);
		break;
	case DEBUG_PERIODIC:
		Log::debugPeriodic(stringstream.str(), a.periodicKey, a.debugKey);
		break;
	case AGGREGATION:
		Log::periodicAggregate(stringstream.str(), a.functions, a.periodicKey);
		break;
	case DEBUG_AGGREGATION:
		Log::periodicAggregate(stringstream.str(), a.functions, a.periodicKey, a.debugKey);
		break;
	}

	return ss;
}

std::map<DebugKey, std::string> Log::getDebugKeyToString() {
	std::map<DebugKey, std::string> result =
	{
		{ DebugKey::LOGGING, "LOGGING" },
		{ DebugKey::CONFIGURATION, "CONFIGURATION" },
		{ DebugKey::EVENTS, "EVENTS" },
		{ DebugKey::OBJECT_CREATION, "OBJECT_CREATION" },
		{ DebugKey::OBJECT_DESTRUCTION, "OBJECT_DESTRUCTION" },
		{ DebugKey::COPY_CONSTRUCTORS, "COPY_CONSTRUCTORS" },
		{ DebugKey::RENDERING, "RENDERING" },
		{ DebugKey::ACCUMULATOR, "ACCUMULATOR" },
		{ DebugKey::GL_ERRORS, "GL_ERRORS" },
		{ DebugKey::SHADERS, "SHADERS" },
		{ DebugKey::MODEL_LOADING, "MODEL_LOADING" },
		{ DebugKey::TEXTURES, "TEXTURES" }
	};
	return result;
}

std::map<std::string, DebugKey> Log::getStringToDebugKey() {
	std::map<std::string, DebugKey> result =
	{
		{ "LOGGING", DebugKey::LOGGING },
		{ "CONFIGURATION", DebugKey::CONFIGURATION },
		{ "EVENTS", DebugKey::EVENTS },
		{ "OBJECT_CREATION", DebugKey::OBJECT_CREATION },
		{ "OBJECT_DESTRUCTION", DebugKey::OBJECT_DESTRUCTION },
		{ "COPY_CONSTRUCTORS", DebugKey::COPY_CONSTRUCTORS },
		{ "RENDERING", DebugKey::RENDERING },
		{ "ACCUMULATOR", DebugKey::ACCUMULATOR },
		{ "GL_ERRORS", DebugKey::GL_ERRORS },
		{ "SHADERS", DebugKey::SHADERS},
		{ "MODEL_LOADING", DebugKey::MODEL_LOADING},
		{ "TEXTURES", DebugKey::TEXTURES}
	};
	return result;
}

void Log::printToConsole(std::string msg)
{
	if (!this->_logToConsole) return;
	std::cout << msg;
}

void Log::printToLogFile(std::string msg)
{
	if (!this->_logToFile) return;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	_logFileBuffer << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << ":" << msg << std::endl;
	if (_logFileBuffer.rdbuf()->in_avail() > LOG_FILE_BUFFER_SIZE){
		std::ofstream outfile(this->_logFilePath, std::ios::app);
		outfile.seekp(outfile.end);
		outfile << _logFileBuffer.str();
		outfile.close();
		std::stringstream ss;
		ss << "Appended" << count << " logs to log file \n";
		if (_activeDebugKeys.find(DebugKey::LOGGING) != _activeDebugKeys.end())
		{
			std::cout << ss.str();
		}
		_logFileBuffer.str(std::string());
		count = 0;
	}
	else{
		count++;
	}
}


Log::Log()
{
	_logFilePath = Config::getStringProperty(LOG_FILE_PATH);
	_activeDebugKeys = Config::getActiveDebugKeys();
	_logToFile = Config::getMainConfig().isSet(LOG_FILE_PATH);
	this->_logToFile = true;
	this->_logToConsole = true;
	std::stringstream activeDebugKeysAsString;
	activeDebugKeysAsString << "- Active debug keys:\n\t";
	bool first = true;
	std::cout << "----------------------\n"
		<< "| Logger initialized |\n"
		<< "----------------------\n";
	if (_logToFile&&Config::isFlushLogFile())
	{

		int ret_code = std::remove(_logFilePath.c_str());
		std::stringstream ss;
		if (ret_code == 0)
		{
			ss << "- old log file was successfully deleted" <<std::endl;
			ss << "- logging to " << _logFilePath << std::endl;
			std::cout << ss.str();
		}
		else 
		{
			std::cerr << "- could not delete the old log file at "<< _logFilePath <<", ERROR: " << ret_code << '\n';
		}
	}
	else if (_logToFile)
	{
		std::stringstream ss;
		ss << "- appending to log file: " << _logFilePath << "\n";
		std::cout << ss.str();
	}
	for (DebugKey key : _activeDebugKeys) {
		if (!first){
			activeDebugKeysAsString << ",\n\t";
		}
		activeDebugKeysAsString << debugKeyAsString(key);
		first = false;
	}
	if (_logToFile) {
		std::cout << "- logging to console\n";
	}
	std::cout << activeDebugKeysAsString.str() <<std::endl;
}

Log::Log(std::string logFilePath)
{
	this->_logFilePath = logFilePath;
}


Log::~Log()
{
}

void Log::error(std::string err)
{
	std::stringstream message;
	message << "ERROR: " << err;
	_instance->printToConsole(message.str());
	_instance->printToLogFile(message.str());
}
void Log::warning(std::string warn)
{
	std::stringstream message;
	message << "WARNING: " << warn;
	_instance->printToConsole(message.str());
	_instance->printToLogFile(message.str());
}
void Log::info(std::string msg)
{
	std::stringstream message;
	message << "INFO: " << msg;
	_instance->printToConsole(message.str());
	_instance->printToLogFile(message.str());
}

void Log::periodic(std::string msg, int key)
{
	clock_t now = clock() / CLOCKS_PER_SEC;
	double last = _instance->_lastLogByKey[key];
	double period = _instance->_periodsByKey[key];
	if (now - last > period){
		std::stringstream message;
		message << "INFO: " << msg;
		_instance->printToLogFile(message.str());
		_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
	}
}

void Log::debug(std::string msg, DebugKey key)
{
	if (_instance->_activeDebugKeys.find(key) != _instance->_activeDebugKeys.end()){
		std::stringstream message;
		message << "DEBUG:";
		if (Config::isShowDebugKeys()){
			message << "/" << debugKeyAsString(key) << "/: ";
		}
		message << msg;
		if (Config::isDebugToFile())
		{
			_instance->printToLogFile(message.str());
		}
		if (Config::isDebugToConsole())
		{
			_instance->printToConsole(message.str());
		}
		_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
	}
}

void Log::debugPeriodic(std::string msg, int key, DebugKey dkey)
{
	if (_instance->_activeDebugKeys.find(dkey) != _instance->_activeDebugKeys.end()){
		clock_t now = clock() / CLOCKS_PER_SEC;
		double last = _instance->_lastLogByKey[key];
		double period = _instance->_periodsByKey[key];
		if (now - last > period){
			std::stringstream message;
			message << "DEBUG:";
			if (Config::isShowDebugKeys()){
				message << "/" << debugKeyAsString(dkey) << "/: ";
			}
			message << msg;
			if (Config::isDebugToFile())
			{
				_instance->printToLogFile(message.str());
			}
			if (Config::isDebugToConsole())
			{
				std::stringstream tempss;
				tempss << message.str() << std::endl;
				_instance->printToConsole(tempss.str());
			}
			_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
		}
	}
}

void  Log::periodicAggregate(std::string msg, std::vector<std::string(*)(std::vector<std::string>&)> functions, int key, DebugKey dkey)
{
	if (_instance->_activeDebugKeys.find(dkey) != _instance->_activeDebugKeys.end()){
		clock_t now = clock() / CLOCKS_PER_SEC;
		double last = _instance->_lastLogByKey[key];
		double period = _instance->_periodsByKey[key];

		Aggregate::populateParams(msg, _instance->_aggregationParamsByKey[key]);

		if (now - last > period){
			int paramNumber = 0;
			std::string temp = msg;
			for (int i = functions.size() - 1; i >= 0; i--)
			{
				temp = Aggregate::aggregate(temp, _instance->_aggregationParamsByKey[key], paramNumber++, functions[i]);
			}
			std::stringstream message;
			message << "DEBUG:";
			if (Config::isShowDebugKeys()){
				message << "/" << debugKeyAsString(dkey) << "/: ";
			}
			message << temp;
			if (Config::isDebugToFile())
			{
				_instance->printToLogFile(message.str());
			}
			if (Config::isDebugToConsole())
			{
				std::stringstream tempss;
				tempss << message.str() << std::endl;
				_instance->printToConsole(tempss.str());
			}
			_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
			_instance->_aggregationParamsByKey[key].clear();
		}
	}
}
void Log::periodicAggregate(std::string msg, std::vector<std::string(*)(std::vector<std::string>&)> functions, int key)
{
	clock_t now = clock() / CLOCKS_PER_SEC;
	double last = _instance->_lastLogByKey[key];
	double period = _instance->_periodsByKey[key];
	
	Aggregate::populateParams(msg, _instance->_aggregationParamsByKey[key]);
	
	if (now - last > period){
		int paramNumber = 0;
		std::string temp = msg;
		for (int i = functions.size() - 1; i >= 0; i--)
		{
			temp = Aggregate::aggregate(temp, _instance->_aggregationParamsByKey[key], paramNumber++, functions[i]);
		}
		std::stringstream message;
		message << "INFO:" << temp;
		if (Config::isDebugToFile())
		_instance->printToLogFile(message.str());
		_instance->printToConsole(message.str());
		_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
		_instance->_aggregationParamsByKey[key].clear();
	}
}

bool Log::isLogToConsole()
{
	return this->_logToConsole;
}

bool Log::isLogToFile()
{
	return this->_logToFile;
}

void Log::setLogToConsole(bool val)
{
	this->_logToConsole = val;
}

void Log::setLogToFile(bool val)
{
	this->_logToFile = val;
}

Log* Log::getInstance()
{
	if (_instance == nullptr)
		_instance = new Log;
	return _instance;
}

unsigned int Log::getLogPeriodicKey(double period)
{
	_periodsByKey[_lastLogPeriodicKey] = period;
	_lastLogByKey[_lastLogPeriodicKey] = clock() / CLOCKS_PER_SEC;
	return _lastLogPeriodicKey++;
}

std::string Log::debugKeyAsString(DebugKey key){
	return Log::getDebugKeyToString()[key];
}
DebugKey Log::debugKeyFromString(std::string keyAsString)
{
	return Log::getStringToDebugKey()[keyAsString];
}

void Log::flush() {
	if (!this->_logToFile) return;
	std::ofstream outfile(this->_logFilePath, std::ios::app);
	outfile.seekp(outfile.end);
	outfile << _logFileBuffer.str();
	outfile.close();
	std::stringstream ss;
	ss << "Appended" << count << " logs to log file \n";
	if (_activeDebugKeys.find(DebugKey::LOGGING) != _activeDebugKeys.end())
	{
		std::cout << ss.str();
	}
	_logFileBuffer.str(std::string());
	count = 0;
}
