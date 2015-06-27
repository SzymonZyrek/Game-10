#pragma once
#include <string>
#include <map>
#include <set>

#define DEBUG_KEYS "DEBUG_KEYS"
#define LOG_FILE_PATH "LOG_FILE_PATH"
#define ADDITIONAL_CONFIG_FILES "ADDITIONAL_CONFIG_FILES"
#define SHOW_DEBUG_KEY "SHOW_DEBUG_KEY"
#define DEBUG_TO_FILE "DEBUG_TO_FILE"
#define DEBUG_TO_CONSOLE "DEBUG_TO_CONSOLE"
#define FLUSH_LOGFILE "FLUSH_LOGFILE"
#define FULLSCREEN "FULLSCREEN"

#define DEFAULT_MODEL_FILE_NAME "DEFAULT_MODEL_FILE_NAME"
#define DEFAULT_TEXTURE_FILE_NAME "DEFAULT_TEXTURE_FILE_NAME"
#define DEFAULT_FRAGMENT_SHADER_FILE_NAME "DEFAULT_FRAGMENT_SHADER_FILE_NAME"
#define DEFAULT_VERTEX_SHADER_FILE_NAME "DEFAULT_VERTEX_SHADER_FILE_NAME"

enum DebugKey;

class Config {
public:
	// cosntructors
	Config(std::string path);
	~Config();
	// general-purpose methods
	static std::string getStringProperty(std::string key);
	static Config& getMainConfig();
	static std::set<DebugKey> getActiveDebugKeys();
	
	bool isSet(std::string key);
	std::map<std::string, std::string> getProperties();
	std::string getProperty(std::string key);

	std::string getLogFilePath();
	static bool isShowDebugKeys();
	static bool isDebugToFile();
	static bool isDebugToConsole();
	static bool isFlushLogFile();
private:
	Config();
	void registerConfig();
	std::map<std::string, std::string> _properties;
	static std::string Config::getMainConfigFilePath();
	static Config _mainConfig;
	static bool isConfigLoaded;
};