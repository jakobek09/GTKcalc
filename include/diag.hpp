#ifndef DIAG_HPP
    #define DIAG_HPP



    #ifdef DIAG_ENABLE
        #include <iostream>
        #include <fstream>
        #include <string>
        #include <sstream>
        #include <stack>


        class regist
        {
        public:
            inline static std::stringstream buffer;
            inline static std::string indents;
            inline static std::stack<int> level_stack;
            inline static int DIAG_LEV;
            inline static int infoLEV;

            static std::string currentTime()
            {
                // Pobranie aktualnego czasu
                std::time_t currentTime = std::time(nullptr);

                // Konwersja czasu na lokalny czas
                std::tm* localTime = std::localtime(&currentTime);

                // Utworzenie formatu daty i czasu
                char dateTimeFormat[50];
                std::strftime(dateTimeFormat, sizeof(dateTimeFormat), "%Y-%m-%d %H:%M:%S", localTime);

                // Konwersja formatu daty i czasu na string
                std::string currentDateTime(dateTimeFormat);

                return currentDateTime;
            }

            static void init()
            {
                indents = "";
                DIAG_LEV = 4;
            }

            static void Log(const std::string& msg)
            {
                if(infoLEV <= DIAG_LEV)
                {
                    setBuff(msg, infoLEV);
                    std::ofstream file("report.txt", std::ios_base::app);
                    file << buffer.str();
                    file.close();
                    buffer.str("");
                }
            }

            static void Log()
            {
                if(infoLEV <= DIAG_LEV)
                {
                    std::ofstream file("report.txt", std::ios_base::app);
                    file << buffer.str();
                    file.close();
                    buffer.str("");
                }
            }

            static void setBuff(const std::string& msg, int level)
            {
                infoLEV = level;
                if(infoLEV <= DIAG_LEV)
                    buffer << level << ", " << indents+msg << ", " << currentTime() << std::endl;

                //cout << indents+msg << endl;;
            }

            static void setIndents()
            {
                indents += '\t';
            }

            static void removeIndents()
            {
                indents.pop_back();
            }

            static void setLevel(int level)
            {
                level_stack.push(DIAG_LEV);
                DIAG_LEV = level;
            }

            static void restoreLevel()
            {
                if (!level_stack.empty()) {
                    DIAG_LEV = level_stack.top();
                    level_stack.pop();
                }
            }

        };
        #define DIAG(msg) regist::Log(msg)
        #define DIAG_BUFF(level,msg) regist::setBuff(level,msg)
        #define DIAG_OUT regist::Log()
        #define DIAG_INDP regist::setIndents()
        #define DIAG_INDM regist::removeIndents()
        #define DIAG_LEV_TEMPSET(level) regist::setLevel(level)
        #define DIAG_LEV_RESTORE regist::restoreLevel()

        #else

        #define DIAG(msg)
        #define DIAG_BUFF(msg)
        #define DIAG_OUT(msg)
        #define DIAG_INDP
        #define DIAG_INDM
        #define DIAG_LEV_TEMPSET(level)
        #define DIAG_LEV_RESTORE

    #endif // DIAG_ENABLE
#endif // DIAG_HPP
