#include "user-agent-client-hints.h"
#include <QNetworkRequest>
#include <QOperatingSystemVersion>
#include <QString>
#include <QSysInfo>

#ifdef Q_OS_ANDROID
	#include <QAndroidJniObject>
#endif


UserAgentClientHints::UserAgentClientHints()
	: m_osVersion(QOperatingSystemVersion::current())
{}


/**
 * Set the "Sec-CH-UA-*" HTTP headers for the given network request.
 */
void UserAgentClientHints::setRequestHeaders(QNetworkRequest &request) const
{
	request.setRawHeader("Sec-CH-UA-Arch", arch().toLatin1());
	request.setRawHeader("Sec-CH-UA-Bitness", bitness().toLatin1());
	request.setRawHeader("Sec-CH-UA-Form-Factor", formFactor().toLatin1());
	request.setRawHeader("Sec-CH-UA-Mobile", mobile() ? "?1" : "?0");
	request.setRawHeader("Sec-CH-UA-Model", model().toLatin1());
	request.setRawHeader("Sec-CH-UA-Platform", platform().toLatin1());
	request.setRawHeader("Sec-CH-UA-Platform-Version", platformVersion().toLatin1());
	request.setRawHeader("Sec-CH-UA-WoW64", wow64() ? "?1" : "?0");
}


/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-arch
 */
QString UserAgentClientHints::arch() const
{
	if (QSysInfo::currentCpuArchitecture().startsWith("arm")) {
		return "arm";
	}
	return "x86";
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-bitness
 */
QString UserAgentClientHints::bitness() const
{
	return QString::number(sizeof(void*) * 8);
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-form-factor
 */
QString UserAgentClientHints::formFactor() const
{
	switch (m_osVersion.type()) {
		case QOperatingSystemVersion::Android:
		case QOperatingSystemVersion::IOS:
			return "Mobile"; // TODO: Tablet

		case QOperatingSystemVersion::MacOS:
		case QOperatingSystemVersion::Windows:
			return ""; // Desktop // TODO: Windows Mobile / Surface

		case QOperatingSystemVersion::TvOS:
			return "TV";

		case QOperatingSystemVersion::WatchOS:
			return "Watch";

		default:
			return "Unknown";
	}
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-mobile
 */
bool UserAgentClientHints::mobile() const
{
	return m_osVersion.isAnyOfType({
		QOperatingSystemVersion::Android,
		QOperatingSystemVersion::IOS,
	});
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-model
 */
QString UserAgentClientHints::model() const
{
	#if defined(Q_OS_ANDROID)
		return QAndroidJniObject::getStaticObjectField<jstring>("android/os/Build", "MODEL").toString();
	#elif defined(Q_OS_IOS)
		return "iPhone"; // TODO: iPad
	#endif

	return "";
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-platform
 */
QString UserAgentClientHints::platform() const
{
	#if defined(Q_OS_LINUX)
		return "Linux";
	#endif

	return m_osVersion.name();
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-platform-version
 */
QString UserAgentClientHints::platformVersion() const
{
	#if defined(Q_OS_LINUX)
		return "";
	#endif

	switch (m_osVersion.type()) {
		case QOperatingSystemVersion::IOS:
			return ""; // TODO: (UIDevice currentDevice).systemVersion

		case QOperatingSystemVersion::Windows:
			if (m_osVersion.majorVersion() == 8 && m_osVersion.minorVersion() == 1) {
				return "0.3.0";
			}
			if (m_osVersion.majorVersion() == 8) {
				return "0.2.0";
			}
			if (m_osVersion.majorVersion() == 7) {
				return "0.1.0";
			}
			if (m_osVersion.majorVersion() < 7) {
				return "0.0.0";
			}
			return ""; // TODO: Windows.Foundation.UniversalApiContract

		case QOperatingSystemVersion::Android: // android.os.Build.VERSION.RELEASE
		case QOperatingSystemVersion::MacOS: // NSProcessInfo.operatingSystemVersion
		default:
			const int segmentCount = m_osVersion.segmentCount();
			if (segmentCount <= 0) {
				return "";
			}
			const int majorVersion = m_osVersion.majorVersion();
			const int minorVersion = segmentCount > 1 ? m_osVersion.minorVersion() : 0;
			const int microVersion = segmentCount > 2 ? m_osVersion.microVersion() : 0;
			return QString("%1.%2.%3").arg(QString::number(majorVersion), QString::number(minorVersion), QString::number(microVersion));
	}
}

/**
 * https://wicg.github.io/ua-client-hints/#sec-ch-ua-wow64
 */
bool UserAgentClientHints::wow64() const
{
	return false; // TODO
}
