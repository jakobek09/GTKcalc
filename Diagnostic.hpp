#ifndef REGIST_HPP
    #define REGIST_HPP



    #ifdef DIAG_ENABLE
        #include <iostream>
        #include <fstream>
        #include <string>
        #include <sstream>
        #include <stack>

        using namespace std;


        class regist
        {
        public:
            inline static stringstream buffer;
            inline static string indents;
            inline static stack<int> level_stack;
            inline static int DIAG_LEV;
            inline static int infoLEV;

            static void init()
            {
                indents = "";
                DIAG_LEV = 1;
            }

            static void Log(const std::string& msg)
            {
                if(infoLEV <= DIAG_LEV)
                {
                    setBuff(infoLEV,msg);
                    ofstream file("report.txt", std::ios_base::app);
                    file << buffer.str();
                    file.close();
                    buffer.str("");
                }
            }

            static void Log()
            {
                if(infoLEV <= DIAG_LEV)
                {
                    ofstream file("report.txt", std::ios_base::app);
                    file << buffer.str();
                    file.close();
                    buffer.str("");
                }
            }

            static void setBuff(int level,const std::string& msg)
            {
                infoLEV = level;
                if(infoLEV <= DIAG_LEV)
                    buffer << level << ", " << indents+msg << std::endl;

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
#endif // REGIST_HPP
