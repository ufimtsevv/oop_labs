#include <iostream>
#include <stdexcept>
using namespace std;

class SimpleWatch;
class Watch;

class Time {
    private:
        int hours, minutes, seconds;
        static int count; 

    public:
        Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
            if (h < 0 || m < 0 || s < 0) {
                throw invalid_argument("Negative values are not allowed for hours, minutes, or seconds.");
            }
            Normalize();
            count++; 
            cout << "Constructor is called. Current count: " << count << endl;
        }

        ~Time() noexcept {
            count--;
            cout << "Destructor is called. Current count: " << count << endl;
        }

        void Normalize() noexcept {
            if (seconds < 0) {
                int sec_from_min = (-seconds + 59) / 60;
                minutes -= sec_from_min;
                seconds += sec_from_min * 60;
            } else if (seconds > 59) {
                minutes += seconds / 60;
                seconds %= 60;
            }

            if (minutes < 0) {
                int min_from_hour = (-minutes + 59) / 60;
                hours -= min_from_hour;
                minutes += min_from_hour * 60;
            } else if (minutes > 59) {
                hours += minutes / 60;
                minutes %= 60;
            }

            if (hours > 23) {
                hours %= 24;
            }
        }

        int ToSeconds() const noexcept {
            return hours * 3600 + minutes * 60 + seconds;
        }

        void Print() const noexcept {
            cout << hours << ":" << minutes << ":" << seconds << endl;
        }

        Time operator-(const Time& other) const noexcept {
            int totalSec1 = ToSeconds();
            int totalSec2 = other.ToSeconds();
            int diff = totalSec1 - totalSec2;

            int newHours = (diff / 3600) % 24;
            diff %= 3600;
            int newMinutes = diff / 60;
            int newSeconds = diff % 60;

            return Time(newHours, newMinutes, newSeconds);
        }

        Time& operator-=(const Time& other) noexcept {
            *this = *this - other;
            return *this;
        }

        bool operator==(const Time& other) const noexcept {
            return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
        }

        static int GetCount() noexcept {
            return count;
        }

        friend class SimpleWatch;
        friend class Watch;
};

int Time::count = 0;

class SimpleWatch {
    public:
        void ShowTime(const Time& t) const {
            cout << "SimpleWatch: " << t.hours << ":" << t.minutes << ":" << t.seconds << endl;
        }

        void SetTime(Time& t, int h, int m, int s) {
            t.hours = h;
            t.minutes = m;
            t.seconds = s;
            t.Normalize();
        }
};

class Watch {
    private:
        bool is24HourFormat;

    public:
        Watch(bool format24 = true) : is24HourFormat(format24) {}

        void SetFormat(bool format24) {
            is24HourFormat = format24;
        }

        void ShowTime(const Time& t) const {
            int displayHours = t.hours;
            string period = "";

            if (!is24HourFormat) {
                period = displayHours >= 12 ? " PM" : " AM";
                displayHours = displayHours % 12;
                if (displayHours == 0) displayHours = 12;
            }

            cout << "Watch: " << displayHours << ":" << t.minutes << ":" << t.seconds << period << endl;
        }

        void SetTime(Time& t, int h, int m, int s) {
            t.hours = h;
            t.minutes = m;
            t.seconds = s;
            t.Normalize();
        }
};

class Clock {
    public:
        Time time;
        Clock(int h, int m, int s) : time(h, m, s) {
            cout << "Clock Constructor is called." << endl;
        }

        virtual ~Clock() {
            cout << "Clock Destructor is called." << endl;
        }

        virtual void ShowTime() const = 0;
};

class CuckooClock : public Clock {
    public:
        CuckooClock(int h, int m, int s) : Clock(h, m, s) {
            cout << "CuckooClock Constructor is called." << endl;
        }

        ~CuckooClock() {
            cout << "CuckooClock Destructor is called." << endl;
        }

        void ShowTime() const override {
            cout << "CuckooClock time: ";
            time.Print();
        }
};

class WallClock : public Clock {
    public:
        WallClock(int h, int m, int s) : Clock(h, m, s) {
            cout << "WallClock Constructor is called." << endl;
        }

        ~WallClock() {
            cout << "WallClock Destructor is called." << endl;
        }

        void ShowTime() const override {
            cout << "WallClock time: ";
            time.Print();
        }
};

class WristWatch : public Clock {
    public:
        WristWatch(int h, int m, int s) : Clock(h, m, s) {
            cout << "WristWatch Constructor is called." << endl;
        }

        ~WristWatch() {
            cout << "WristWatch Destructor is called." << endl;
        }

        void ShowTime() const override {
            cout << "WristWatch time: ";
            time.Print();
        }
};

class SmartWatch : public Clock {
    public:
        SmartWatch(int h, int m, int s) : Clock(h, m, s) {
            cout << "SmartWatch Constructor is called." << endl;
        }

        ~SmartWatch() {
            cout << "SmartWatch Destructor is called." << endl;
        }

        void ShowTime() const override {
            cout << "SmartWatch time: ";
            time.Print();
        }
};
