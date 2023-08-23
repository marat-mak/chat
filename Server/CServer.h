#pragma once
class CoreServer;
class CServer
{
public:

	void static StartListing(int port = 0, CoreServer* pCore = nullptr);
};

