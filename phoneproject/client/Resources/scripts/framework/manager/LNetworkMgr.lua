LNetworkMgr = {}

function LNetworkMgr:onConnect()
		cclog("LNetworkMgr:onConnect");
end

function LNetworkMgr:onDisConnect()
		cclog("LNetworkMgr:onDisConnect");
end

function LNetworkMgr:onUnknownProtocol(ptype)
		cclog("LNetworkMgr:onUnknownProtocol ptype="..ptype);
end

function LNetworkMgr:onReceiveProtocol(pid)
		cclog("LNetworkMgr:onReceiveProtocol pid="..pid);
end

function LNetworkMgr:onGameDataSend(cmd)
		cclog("LNetworkMgr:onGameDataSend cmd="..cmd);
end

function LNetworkMgr:CloseServer()
end