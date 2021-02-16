#pragma once
#include <QString>

namespace TcpHttpConst
{
constexpr auto tcpServerPort = 9876;
const auto redirectUrl(QStringLiteral("http://localhost:%1").arg(tcpServerPort));
const auto paramCode(QStringLiteral("?code="));
const auto headerHttp(QStringLiteral("HTTP"));
}
