<p align="center"><img src="readme-icon.png" alt="" /></p>
<h1 align="center">Qt Google Analytics</h1>

[![GitHub issues](https://img.shields.io/github/issues/Spark-NF/qt-google-analytics.svg)](https://github.com/Spark-NF/qt-google-analytics/issues)
[![Build Status](https://img.shields.io/github/actions/workflow/status/Spark-NF/qt-google-analytics/test.yml)](https://github.com/Spark-NF/qt-google-analytics/actions)
[![Code Coverage](https://img.shields.io/codecov/c/github/Spark-NF/qt-google-analytics.svg)](https://codecov.io/gh/Spark-NF/qt-google-analytics)
[![Project license](https://img.shields.io/github/license/Spark-NF/qt-google-analytics.svg)](https://raw.githubusercontent.com/Spark-NF/qt-google-analytics/master/LICENSE)

## About
This script allows you to send events from your Qt application to Google Analytics 4.

It supports sending events, setting user properties, as well as operating system detection.

Compatible with both Qt 5.10+ and Qt 6.

### Authors
* Nicolas Faure ([Spark-NF](https://github.com/Spark-NF))

### License
The script is licensed under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

## Usage

### Create a `QtGoogleAnalytics` instance
```cpp
#include "qt-google-analytics.h"

QtGoogleAnalytics analytics("G-XXXXXXXXXX");
```

Alternatively, you can set your [measurement ID](https://support.google.com/analytics/answer/12270356) using the `setMeasurementId` method:
```cpp
QtGoogleAnalytics analytics;
analytics.setMeasurementId("G-XXXXXXXXXX");
```

### (Optional) Set user information
You can set an [user ID](https://support.google.com/analytics/answer/3123662) using the `setUserId` method:
```cpp
analytics.setUserId("some-unique-user-id");
```

You can also set [user properties](https://support.google.com/analytics/answer/9355671) using the `setUserProperties` method:
```cpp
QVariantMap userProperties;
userProperties["some_property"] = 123;
analytics.setUserProperties(userProperties);
```

### (Optional) Enable debug mode
If you want to debug the events using the [DebugView](https://support.google.com/analytics/answer/7201382), you can use `setDebugModeEnabled`.

```cpp
analytics.setDebugModeEnabled(true);
```

### Send events
Once you're set up, you can send events using the `sendEvent` method:
```cpp
analytics.sendEvent("some_event");
```

You can also add [event parameters](https://support.google.com/analytics/answer/13675006) as a second argument to the method:
```cpp
QVariantMap eventParameters;
eventParameters["some_param"] = 123;
analytics.sendEvent("some_event_with_parameters", eventParameters);
```
