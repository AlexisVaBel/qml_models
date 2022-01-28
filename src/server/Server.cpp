//
// Created by abel on 14.12.2021.
//

#include "Server.h"

using namespace server;

Server& Server::instance() {
	static Server s_server;
	return s_server;
}

void Server::start() {
	emit started();
}

void Server::stop() {
	emit stopped();
}
