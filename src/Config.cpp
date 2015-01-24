
#include "Config.h"
#include <fstream>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include "CPPLogger.h"

std::string Config::getMainConfigFilePath(){
	return "C:\\temp\\main.conf";
}

const static std::map<std::string, std::string> __defaults = {
		{ LOG_FILE_PATH, "E:\\temp\\game10.log"},
		{ SHOW_DEBUG_KEY, "NO" },
		{ FLUSH_LOGFILE, "NO"},
		{ DEFAULT_FRAGMENT_SHADER_FILE_NAME, "TextureFragmentShader"},
		{ DEFAULT_VERTEX_SHADER_FILE_NAME, "TransformVertexShader" },
		{ DEFAULT_MODEL_FILE_NAME, "monkey.obj"},
		{ DEFAULT_TEXTURE_FILE_NAME, "grass.jpg"},
		{ FULLSCREEN , "NO"}
};

Config Config::_mainConfig;
bool Config::_mainConfigLoaded = false;

bool parseYesNo(std::string val, std::string key)
{
	if (val == std::string("YES")) return true;
	else if (val == std::string("NO")) return false;
	else 
	{
		std::stringstream ss;
		ss << "Wrong value for " << key << ", should be: <YES/NO>, was: \"" << val << "\"" << std::endl;
		throw ss.str();
	}
}

std::vector<std::string> split(std::string s, std::string delim){
	std::string temp = s;
	std::vector<std::string> result;
	while (temp.find(delim)<temp.length()){
		result.push_back(temp.substr(0, temp.find(delim)));
		temp = temp.substr(temp.find(delim) + 1, temp.length());
	}
	result.push_back(temp);
	return result;
}

bool Config::isFlushLogFile()
{
	return parseYesNo(_mainConfig.getProperty(FLUSH_LOGFILE), FLUSH_LOGFILE);
}

bool Config::isDebugToFile()
{
	return parseYesNo(_mainConfig.getProperty(DEBUG_TO_FILE), DEBUG_TO_FILE);

}
bool Config::isDebugToConsole()
{
	return parseYesNo(_mainConfig.getProperty(DEBUG_TO_CONSOLE), DEBUG_TO_CONSOLE);
}

void Config::registerConfig()
{
	for (auto& pair : _properties)
	{
		_mainConfig.getProperties().emplace(pair.first, pair.second);
	}
}

Config::Config()
{
	if (!_mainConfigLoaded)
	{
		std::cout << "-------------------------\n"
			<< "| Loading configuration |\n"
			<< "-------------------------\n";
		std::string path = Config::getMainConfigFilePath();
		std::ifstream infile(path);
		std::string line;
		std::stringstream ss;

		ss << "- Loading defaults: " << std::endl;
		std::cout << ss.str() << std::endl;
		for (auto& pair : __defaults) {
			_properties[pair.first] = pair.second;
			std::stringstream ss2;
			ss2 << "\t[" << pair.first << "]\n\t\t=> \"" << pair.second << "\"" << std::endl;
			std::cout << ss2.str();
		}

		ss.str("");
		ss << "-Loading configuration from file: " << path << std::endl;
		std::cout << ss.str() << std::endl;
		while (infile >> line)
		{
			std::vector<std::string> pair = split(line, "=");
			if (pair.size() != 2){
				std::stringstream ss;
				ss << "Something went wrong while reading property file \"" << path << "\"";
				throw ss.str();
			}
			_properties[pair[0]] = pair[1];
			ss.str("");;
			ss << "\t[" << pair[0] << "]\n\t\t=> \"" << pair[1] << "\"" << std::endl;
			std::cout << ss.str();
		}
		if (isSet(ADDITIONAL_CONFIG_FILES))
		{
			std::vector<std::string> additionalFilesPaths = split(getProperty(ADDITIONAL_CONFIG_FILES), ",");
			for (std::string filePath : additionalFilesPaths)
			{
				Config additionalConfig(filePath);
				for (auto& pair : additionalConfig.getProperties())
				{
					_properties[pair.first] = pair.second;
				}
			}
		}
		_mainConfigLoaded = true;
	}
}

std::string Config::getStringProperty(std::string key)
{
	return _mainConfig.getProperty(key);
}

Config::Config(std::string path)
{
	std::ifstream infile(path);
	std::string line;
	std::stringstream ss;
	ss << "- Loading additional configuration from file: " << path << std::endl;
	std::cout << ss.str() << std::endl;
	while (infile >> line)
	{
		std::vector<std::string> pair = split(line, "=");
		if (pair.size() != 2){
			std::stringstream ss;
			ss << "Something went wrong while reading property file \"" << path << "\"";
			throw ss.str();
		}
		_properties[pair[0]] = pair[1];
		ss.str("");;
		ss << "\t[" << pair[0] << "]\n\t\t=> \"" << pair[1] << "\"" << std::endl;
		std::cout << ss.str();
	}
	registerConfig();
}
std::map<std::string, std::string> Config::getProperties()
{
	return this->_properties;
}

Config& Config::getMainConfig(){
	return Config::_mainConfig;
}

std::string Config::getProperty(std::string key) {
	if (_properties.find(key) != _properties.end())
	{
		return _properties[key];
	}
	else{
		std::stringstream ss;
		ss << "No such property: [" << key << "]" << std::endl;
		throw std::string(ss.str());
	}
}
std::set<DebugKey> Config::getActiveDebugKeys(){
	std::set <DebugKey> result;
	try {
		std::string debugKeysString = _mainConfig.getProperty(DEBUG_KEYS);
		std::vector<std::string> debugKeys = split(debugKeysString, ",");
		for (std::string debugKeyAsString : debugKeys)
		{
			result.insert(Log::debugKeyFromString(debugKeyAsString));
		}
	}
	catch (std::string err){
		std::stringstream ss;
		ss << "Could not set debug keys: reason:\n\t" << err;
		std::cout << "ERROR: " << ss.str();
	}
	return result;
}
bool Config::isSet(std::string key)
{
	if (_properties.find(key) != _properties.end()) return true;
	return false;
}
std::string Config::getLogFilePath()
{
	return getProperty(LOG_FILE_PATH);
}
bool Config::isShowDebugKeys(){
	return parseYesNo(_mainConfig.getProperty(SHOW_DEBUG_KEY),SHOW_DEBUG_KEY);
}
Config::~Config(){

}