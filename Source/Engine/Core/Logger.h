#pragma once
#include "Framework/Singleton.h"
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG

#define INFO_LOG(message)               { if (MEN::Logger::Instance().Log(MEN::LogLevel::Info, __FILE__, __LINE__))    { MEN::Logger::Instance() << message << "\n"; }}
#define WARNING_LOG(message)            { if (MEN::Logger::Instance().Log(MEN::LogLevel::Warning, __FILE__, __LINE__)) { MEN::Logger::Instance() << message << "\n"; }}
#define ERROR_LOG(message)              { if (MEN::Logger::Instance().Log(MEN::LogLevel::Error, __FILE__, __LINE__))   { MEN::Logger::Instance() << message << "\n"; }}
#define ASSERT_LOG(condition, message)  { if(!condition && MEN::Logger::Instance().Log(MEN::LogLevel::Assert, __FILE__, __LINE__))   { MEN::Logger::Instance() << message << "\n"; } assert(condition);}

#else
#define INFO_LOG(message)               {}
#define WARNING_LOG(message)            {}
#define ERROR_LOG(message)              {}
#define ASSERT_LOG(condition, message)  {}

#endif //_ DEBUG


namespace MEN
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>
	{
	public:
		Logger(LogLevel logLevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string fileName = "log.txt") :
			m_logLevel{logLevel},
			m_ostream{ ostream }
		{
			if (!fileName.empty()) m_fstream.open(fileName);
		}

		bool Log(LogLevel logLevel, const std::string& fileName, int line);

		template<typename T>
		Logger& operator << (T value);

	protected:

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};



	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		if(m_ostream) *m_ostream << value;
		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}
		return *this;
	}
}