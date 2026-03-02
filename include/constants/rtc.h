#ifndef GUARD_CONSTANTS_RTC_H
#define GUARD_CONSTANTS_RTC_H

#define RTC_INIT_ERROR         0x0001
#define RTC_INIT_WARNING       0x0002

#define RTC_ERR_12HOUR_CLOCK   0x0010
#define RTC_ERR_POWER_FAILURE  0x0020
#define RTC_ERR_INVALID_YEAR   0x0040
#define RTC_ERR_INVALID_MONTH  0x0080
#define RTC_ERR_INVALID_DAY    0x0100
#define RTC_ERR_INVALID_HOUR   0x0200
#define RTC_ERR_INVALID_MINUTE 0x0400
#define RTC_ERR_INVALID_SECOND 0x0800

#define RTC_ERR_FLAG_MASK      0x0FF0

//Evening doesn't exist in Gen 2
#if OW_TIMES_OF_DAY == GEN_2
    #define MORNING_HOUR_BEGIN 4
    #define MORNING_HOUR_END   10

    #define DAY_HOUR_BEGIN     10
    #define DAY_HOUR_END       18

    #define EVENING_HOUR_BEGIN 0
    #define EVENING_HOUR_END   0

    #define NIGHT_HOUR_BEGIN   18
    #define NIGHT_HOUR_END     4
//Morning and evening don't exist in Gen 3
#elif OW_TIMES_OF_DAY == GEN_3
    #define MORNING_HOUR_BEGIN 0
    #define MORNING_HOUR_END   0

    #define DAY_HOUR_BEGIN     12
    #define DAY_HOUR_END       19

    #define EVENING_HOUR_BEGIN 19
    #define EVENING_HOUR_END   20

    #define NIGHT_HOUR_BEGIN   20
    #define NIGHT_HOUR_END     6

// TIMES_OF_DAY_COUNT must be last
enum TimeOfDay
{
    TIME_MORNING,
    TIME_DAY,
    TIME_EVENING,
    TIME_NIGHT,
    TIMES_OF_DAY_COUNT,
};

#define TIME_OF_DAY_DEFAULT    0

#endif // GUARD_CONSTANTS_RTC_H
