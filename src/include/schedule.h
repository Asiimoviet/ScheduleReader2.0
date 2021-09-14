#pragma once

#include <string>
#include <vector>
#include <list>

#include "nlohmann/json.hpp"
#include "OpenXLSX.hpp"
#include "date/tz.h"
#include "date/date.h"
#include "calendar.h"
#include "args.h"
#include "logger.h"

using nlohmann::json;

class Schedule
{
public:
    struct Day
    {
        int day;
        std::string col, timeCol;
        Day(int d, std::string c, std::string tc): day(d), col(c), timeCol(tc) {};
    };

    struct Lesson
    {
        int start, end;
        Lesson(int s, int e): start(s), end(e) {};
    };

    OpenXLSX::XLDocument doc;
    OpenXLSX::XLWorksheet wks;
    
    std::vector<std::string> exclude;
    std::vector<std::string> exclude_all;
    std::vector<std::string> coursesTaken;
    std::vector<Day> days;
    std::vector<Lesson> lessons;
    std::vector<Event> events;

    std::list<std::string> all_lessons;
    
    std::string time_sep = "-";
    std::string hm_sep = ":";
    std::string wksName;
    std::string allLessonsPath;

    date::year_month_day monday = date::April/30/2004;

    bool isExclude = false, isExcludeAll = false, isAllLessons = false, haveClasses = false;
    int location_length = 4;

    logger* logger;

    Schedule(class logger* logger): logger(logger) {};

    void parseEvents();

    void openDoc(std::string path);
    void readConfig(json& config);
    void openWks();
    void readArgs(Args args);
    void exportAllLessons(std::string path);
    bool validate(std::string& content);
    bool taken(std::string& content);
};