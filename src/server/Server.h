#pragma once

#include <QObject>

namespace server {

class Server : public QObject {
	Q_OBJECT
	using Self = Server;
	using Super = QObject;

public:
	Server(Server const&) = delete;
	Server(Server&&) = delete;

	static Server& instance();

	void start();
	void stop();

signals:
	void started();
	void stopped();

private:
	Server() = default;
};

} // namespace server
