#pragma once
#include <fstream>


namespace Amorphis {


	class Logger {
	private:
		static Logger* m_instance;
		Logger() {}
		std::ofstream m_ofs;
	public:
		static Logger* getInstance();
		void init();
		void log(const std::string &s);
		void warn(const std::string &s);
		void err(const std::string &s);
		~Logger();
	};


#define ALOG(X) Amorphis::Logger::getInstance()->log(X)
#define AWARN(X) Amorphis::Logger::getInstance()->warn(X)
#define AERR(X) Amorphis::Logger::getInstance()->err(X)


}


