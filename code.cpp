#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace Wt;

class SmartLivingApp : public WApplication {
public:
    SmartLivingApp(const WEnvironment& env) : WApplication(env) {
        setTitle("Smart Living Impact Estimator");

        root()->addWidget(std::make_unique<WText>("<h2>🌱 Smart Living Quiz</h2>"));

        name = createInput("Your name:");
        fanHours = createInput("Fan hours/day:");
        lightHours = createInput("Light hours/day:");
        acHours = createInput("Air conditioner hours/day:");
        tvHours = createInput("TV hours/day:");
        pcHours = createInput("PC hours/day:");
        fridgeHours = createInput("Fridge hours/day:");
        microwaveMins = createInput("Microwave minutes/day:");
        laundryLoads = createInput("Laundry loads/week:");
        showerTime = createInput("Shower time (minutes/day):");
        recycles = createInput("Recycle and use public transport? (Y/N):");

        auto button = root()->addWidget(std::make_unique<WPushButton>("🚀 Calculate"));
        button->clicked().connect(this, &SmartLivingApp::calculate);

        result = root()->addWidget(std::make_unique<WText>());
    }

private:
    WLineEdit *name, *fanHours, *lightHours, *acHours, *tvHours, *pcHours;
    WLineEdit *fridgeHours, *microwaveMins, *laundryLoads, *showerTime, *recycles;
    WText *result;

    WLineEdit* createInput(const std::string& label) {
        root()->addWidget(std::make_unique<WText>(label));
        auto input = root()->addWidget(std::make_unique<WLineEdit>());
        root()->addWidget(std::make_unique<WBreak>());
        return input;
    }

    void calculate() {
        std::string userName = name->text().toUTF8();
        float fan = std::stof(fanHours->text().toUTF8());
        float light = std::stof(lightHours->text().toUTF8());
        float ac = std::stof(acHours->text().toUTF8());
        float tv = std::stof(tvHours->text().toUTF8());
        float pc = std::stof(pcHours->text().toUTF8());
        int fridge = std::stoi(fridgeHours->text().toUTF8());
        int micro = std::stoi(microwaveMins->text().toUTF8());
        int laundry = std::stoi(laundryLoads->text().toUTF8());
        int shower = std::stoi(showerTime->text().toUTF8());
        char recycle = recycles->text().toUTF8().empty() ? 'N' : recycles->text().toUTF8()[0];

        const float fanPower = 75, lightPower = 15, acPower = 1000, tvPower = 120;
        const float pcPower = 300, fridgePower = 150, microwavePower = 1100;

        float energy = (
            fan * fanPower + light * lightPower + ac * acPower + tv * tvPower +
            pc * pcPower + fridge * fridgePower + (micro * microwavePower / 60.0f)
        ) / 1000.0f;

        float laundryKWh = 1.5f * laundry;
        float showerLiters = shower * 9;
        float co2 = energy * 0.5f;

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "<h3>📊 Summary Report for " << userName << ":</h3>";
        oss << "<p>Total Daily Energy Use: " << energy << " kWh/day</p>";
        oss << "<p>Weekly Laundry Energy: " << laundryKWh << " kWh/week</p>";
        oss << "<p>Daily Water Used in Shower: " << showerLiters << " liters/day</p>";
        oss << "<p>Estimated CO2 Emissions: " << co2 << " kg CO2/day</p>";

        oss << "<h4>💡 Eco Tips:</h4><ul>";
        if (ac > 4) oss << "<li>Reduce aircon time or increase thermostat to 25-26°C.</li>";
        if (shower > 10) oss << "<li>Try shorter showers to save water.</li>";
        if (laundry > 5) oss << "<li>Combine laundry loads and use eco-mode.</li>";
        if (micro > 20) oss << "<li>Batch heat to reduce microwave use.</li>";
        if (recycle == 'N' || recycle == 'n') oss << "<li>Start recycling and use public transport.</li>";
        oss << "</ul><p>✅ Thank you, " << userName << ", for using the Smart Living Quiz!</p>";

        result->setText(oss.str());
    }
};

std::unique_ptr<WApplication> createApp(const WEnvironment& env) {
    return std::make_unique<SmartLivingApp>(env);
}

int main(int argc, char **argv) {
    return WRun(argc, argv, createApp);
}

