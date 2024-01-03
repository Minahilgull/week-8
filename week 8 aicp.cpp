#include <iostream>
#include <iomanip>
using namespace std;
 int NUM_BOATS = 10;
int OPEN_HOUR = 10;
 int CLOSE_HOUR = 17;
 double HOURLY_RATE = 20.0;
  double HALF_HOUR_RATE = 12.0;

struct Boat {
    double totalMoney;
    double totalHours;
    int returnTime;
    bool isAvailable;
};

void initializeBoats(Boat boats[]) {
    for (int i = 0; i < NUM_BOATS; ++i) {
        boats[i].totalMoney = 0.0;
        boats[i].totalHours = 0.0;
        boats[i].returnTime = OPEN_HOUR;
        boats[i].isAvailable = true;
    }
}

void calculateDailyProfit(Boat boats[], int boatNumber, int currentTime) {
    if (currentTime < OPEN_HOUR || currentTime >= CLOSE_HOUR) {
        cout << "Boats can only be hired between 10:00 and 17:00." << std::endl;
        return;
    }

    int hireDuration;
    cout << "Enter the hire duration in minutes for Boat " << boatNumber << ": ";
    cin >> hireDuration;

    if (hireDuration == 30 || hireDuration == 60) {
        double rate = (hireDuration == 60) ? HOURLY_RATE : HALF_HOUR_RATE;
        double cost = rate * (hireDuration / 60.0);

        boats[boatNumber - 1].totalMoney += cost;
        boats[boatNumber - 1].totalHours += hireDuration / 60.0;
        boats[boatNumber - 1].returnTime = currentTime + hireDuration / 60;
        boats[boatNumber - 1].isAvailable = false;

        cout << "Boat " << boatNumber << " hired for $" << cost << std::endl;
    } else {
        cout << "Invalid hire duration. Please choose 30 minutes or 1 hour." << std::endl;
    }
}

void findNextAvailableBoat(Boat boats[], int currentTime) {
    int nextAvailableTime = CLOSE_HOUR;
    int availableBoats = 0;

    for (int i = 0; i < NUM_BOATS; ++i) {
        if (boats[i].isAvailable) {
            availableBoats++;
            if (boats[i].returnTime < nextAvailableTime) {
                nextAvailableTime = boats[i].returnTime;
            }
        }
    }

    if (availableBoats > 0) {
       cout << "Number of available boats: " << availableBoats << std::endl;
    } else {
    cout << "No boats available. Next available time is at " << nextAvailableTime << ":00" << std::endl;
    }
}

void calculateTotalDailyProfit(Boat boats[]) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int unusedBoats = 0;
    int mostUsedBoat = 0;

    for (int i = 0; i < NUM_BOATS; ++i) {
        totalMoney += boats[i].totalMoney;
        totalHours += boats[i].totalHours;

        if (boats[i].isAvailable) {
            unusedBoats++;
        } else if (boats[i].totalHours > boats[mostUsedBoat].totalHours) {
            mostUsedBoat = i;
        }
    }

    cout << "Total money taken for all boats: $" << totalMoney << std::endl;
  cout << "Total number of hours boats were hired: " << totalHours << " hours" << std::endl;
    cout << "Number of boats not used: " << unusedBoats << std::endl;
    cout << "Boat " << mostUsedBoat + 1 << " was used the most with " << boats[mostUsedBoat].totalHours << " hours." << std::endl;
}

int main() {
    Boat boats[NUM_BOATS];
    initializeBoats(boats);

    int currentTime;
   cout << "Enter the current time (in 24-hour format): ";
    cin >> currentTime;

    calculateDailyProfit(boats, 1, currentTime);
    calculateDailyProfit(boats, 2, currentTime);
    // Repeat for other boats as needed

    findNextAvailableBoat(boats, currentTime);

    // Assuming it's the end of the day
    calculateTotalDailyProfit(boats);

    return 0;
}
