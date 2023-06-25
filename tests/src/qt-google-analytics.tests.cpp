#include <catch2/catch_test_macros.hpp>
#include "qt-google-analytics.h"


TEST_CASE("QtGoogleAnalytics")
{
    SECTION("measurementId")
    {
        QtGoogleAnalytics empty;
        REQUIRE(empty.measurementId() == QString());

        empty.setMeasurementId("TEST");
        REQUIRE(empty.measurementId() == QString("TEST"));

        QtGoogleAnalytics already("ALREADY");
        REQUIRE(already.measurementId() == QString("ALREADY"));

        already.setMeasurementId("TEST");
        REQUIRE(already.measurementId() == QString("TEST"));
    }

    SECTION("userId")
    {
        QtGoogleAnalytics analytics;
        REQUIRE(analytics.userId() == QString());

        analytics.setUserId("TEST");
        REQUIRE(analytics.userId() == QString("TEST"));
    }

    SECTION("userProperties")
    {
        QtGoogleAnalytics analytics;
        REQUIRE(analytics.userProperties() == QVariantMap());

        QVariantMap userProperties;
        userProperties["some_prop"] = 123;

        analytics.setUserProperties(userProperties);
        REQUIRE(analytics.userProperties() == userProperties);
    }

    SECTION("debugModeEnabled")
    {
        QtGoogleAnalytics analytics;
        REQUIRE(analytics.debugModeEnabled() == false);

        analytics.setDebugModeEnabled(true);
        REQUIRE(analytics.debugModeEnabled() == true);

        analytics.setDebugModeEnabled(false);
        REQUIRE(analytics.debugModeEnabled() == false);
    }
}
