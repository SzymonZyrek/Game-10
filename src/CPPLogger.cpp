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
		{ DebugKey::ACCUMULATOR, "ACCUMULATOR" }
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
		{ "ACCUMULATOR", DebugKey::ACCUMULATOR }
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
			_instance->printToLogFile(message.str());
			_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
		}
	}
}

void populateParams(std::string message, std::vector<std::vector<std::string>> &params)
{
	std::vector<std::string> paramsRow;
	//param is everyting surrounded with "[" and "]"
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");

	std::string temp = message;

	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
		paramsRow.push_back(extracted);
		temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);
	}

	params.push_back(paramsRow);
}

void Log::periodicAggregate(std::string msg, int key, std::vector<std::string(*)(std::string input, std::vector<std::vector<std::string>> &params, int paramNumber)> functions)
{
	clock_t now = clock() / CLOCKS_PER_SEC;
	double last = _instance->_lastLogByKey[key];
	double period = _instance->_periodsByKey[key];
	
	if (_instance->_aggregationSumByKey.find(key) == _instance->_aggregationSumByKey.end() || _instance->_aggregationSumByKey[key] == "")
	{
		populateParams(msg, _instance->_aggregationParamsByKey[key]);
		_instance->_aggregationSumByKey[key] = msg;
	}
	else
	{
		populateParams(msg, _instance->_aggregationParamsByKey[key]);
		int paramNumber = 0;
		std::string temp=msg;
		for (int i = functions.size()-1; i >= 0; i--)
		{
			temp = functions[i](temp, _instance->_aggregationParamsByKey[key], paramNumber++);
		}
		_instance->_aggregationSumByKey[key] = temp;
	}
	
	if (now - last > period){
		std::stringstream message;
		message << "AGGREGATE:" << _instance->_aggregationSumByKey[key] << std::endl;
		if (Config::isDebugToFile())
		_instance->printToLogFile(message.str());
		_instance->printToConsole(message.str());
		_instance->_lastLogByKey[key] = clock() / CLOCKS_PER_SEC;
		_instance->_aggregationSumByKey[key] = "";
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
