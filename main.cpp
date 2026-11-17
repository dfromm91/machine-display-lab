#include "decoder.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QStringList>

class Telemetry : public QObject {
    Q_OBJECT
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
public:
    double speed() const { return speedTenths / 10.0; }

    Q_INVOKABLE void advance() {
        const unsigned sample = (speedTenths + 175) % 1050;
        const auto decoded = decodeSpeed(speedFrame, {
            static_cast<std::uint8_t>(sample & 0xff),
            static_cast<std::uint8_t>(sample >> 8)
        });
        if (decoded && *decoded != speedTenths) {
            speedTenths = *decoded;
            emit speedChanged();
        }
    }

signals:
    void speedChanged();

private:
    unsigned speedTenths = 0;
};

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    Telemetry telemetry;
    QQmlApplicationEngine engine;
    engine.setInitialProperties({{"telemetry", QVariant::fromValue(&telemetry)}});
    engine.loadFromModule("MachineDisplay", "Main");
    if (engine.rootObjects().isEmpty()) return 1;
    if (app.arguments().contains("--smoke")) {
        auto* window = engine.rootObjects().constFirst();
        telemetry.advance();
        return window->property("displayedSpeed").toDouble() == 17.5 ? 0 : 1;
    }
    return app.exec();
}

#include "main.moc"
