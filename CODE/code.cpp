#include <iostream>
#include <iomanip>
using namespace std;
//test
int main() {
    string name;
    float fanHours, lightHours, acHours, tvHours, pcHours;
    int laundryLoads, showerTime, fridgeHours, microwaveMins;
    char recycles, usesPublicTransport;

    // Device power usage in watts
    const float fanPower = 75;
    const float lightPower = 15;
    const float acPower = 1000;
    const float tvPower = 120;
    const float pcPower = 300;
    const float fridgePower = 150;         // assumed running average
    const float microwavePower = 1100;     // in watts

    cout << "?? Welcome to the Smart Living Impact Estimator ??\n";
    cout << "Please enter your name: ";
    getline(cin, name);

    cout << "\nHello, " << name << "! Please answer the following questions:\n";
    cout << "-----------------------------------------------------------\n";

    cout << "1. How many hours/day do you use a FAN? ";
    cin >> fanHours;

    cout << "2. How many hours/day do you use LIGHT BULBS? ";
    cin >> lightHours;

    cout << "3. How many hours/day do you use the AIR CONDITIONER? ";
    cin >> acHours;

    cout << "4. How many hours/day do you watch TELEVISION? ";
    cin >> tvHours;

    cout << "5. How many hours/day do you use your PERSONAL COMPUTER? ";
    cin >> pcHours;

    cout << "6. How many hours/day is your REFRIGERATOR running? (24 for always on): ";
    cin >> fridgeHours;

    cout << "7. How many MINUTES per day do you use the MICROWAVE? ";
    cin >> microwaveMins;

    cout << "8. How many LOADS of laundry do you do per week? ";
    cin >> laundryLoads;

    cout << "9. On average, how many MINUTES is your daily SHOWER? ";
    cin >> showerTime;

    cout << "10. Do you RECYCLE and use PUBLIC TRANSPORT often? (Y/N): ";
    cin >> recycles;

    // Energy calculations (convert watts to kWh)
    float dailyEnergyKWh = (
        (fanPower * fanHours) +
        (lightPower * lightHours) +
        (acPower * acHours) +
        (tvPower * tvHours) +
        (pcPower * pcHours) +
        (fridgePower * fridgeHours) +
        ((microwavePower * microwaveMins) / 60.0)
    ) / 1000.0;

    float weeklyLaundryKWh = 1.5 * laundryLoads;
    float dailyShowerLiters = showerTime * 9;
    float dailyCO2 = dailyEnergyKWh * 0.5; // kg CO2 per kWh

    cout << fixed << setprecision(2);
    cout << "\n?? Summary Report for " << name << ":\n";
    cout << "-----------------------------------------------------------\n";
    cout << "?? Total Daily Energy Use: " << dailyEnergyKWh << " kWh/day\n";
    cout << "?? Weekly Laundry Energy: " << weeklyLaundryKWh << " kWh/week\n";
    cout << "?? Daily Water Used in Shower: " << dailyShowerLiters << " liters/day\n";
    cout << "??? Estimated CO2 Emissions: " << dailyCO2 << " kg CO2/day\n";

    cout << "\n? Eco Tips Based on Your Input:\n";
    if (acHours > 4) cout << "- Reduce aircon time or increase the thermostat to 25-26 degrees Celsius.\n";
    if (showerTime > 10) cout << "- Try shorter showers to save water.\n";
    if (laundryLoads > 5) cout << "- Combine laundry loads and use eco-mode.\n";
    if (microwaveMins > 20) cout << "- Consider batch-heating to reduce microwave usage.\n";
    if (recycles == 'N' || recycles == 'n') cout << "- Start recycling and using public transport to reduce emissions.\n";

    cout << "\n?? Thank you, " << name << ", for contributing to a smarter, greener city!\n";

    return 0;
}

