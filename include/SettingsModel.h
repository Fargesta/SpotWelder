#pragma once

struct WeldSettings 
{
  int pulseCount, pulseDuration, pulseInterval, pulsePower;
};

bool operator==(const WeldSettings &lhs, const WeldSettings &rhs)
{
    return (lhs.pulseCount == rhs.pulseCount && 
            lhs.pulseDuration == rhs.pulseDuration &&
            lhs.pulseInterval == rhs.pulseInterval &&
            lhs.pulsePower == rhs.pulsePower);
}

bool operator!=(const WeldSettings &lhs, const WeldSettings &rhs)
{
    return (lhs.pulseCount != rhs.pulseCount ||
            lhs.pulseDuration != rhs.pulseDuration ||
            lhs.pulseInterval != rhs.pulseInterval ||
            lhs.pulsePower != rhs.pulsePower);
}
