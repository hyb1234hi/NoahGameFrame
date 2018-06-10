// -------------------------------------------------------------------------




//
// -------------------------------------------------------------------------

#ifndef NFI_GAMESERVERNET_SERVERMODULE_H
#define NFI_GAMESERVERNET_SERVERMODULE_H

#include <iostream>
#include "NFIModule.h"
#include "NFINetModule.h"

class NFIGameServerNet_ServerModule
    : public NFIModule
{
public:

    struct GateBaseInfo
    {
		enum ERoleStatus
		{
			E_LOADING = 1,
			E_LOADED = 2,
		};

        GateBaseInfo()
        {
            nActorID = 0;
            nGateID = 0;
			eStatus = E_LOADING;
        }

        GateBaseInfo(const int gateID, const NFGUID xIdent)
        {
            nActorID = 0;
            nGateID = gateID;
            xClientID = xIdent;
        }

        int nActorID;
		int nGateID;
		ERoleStatus eStatus;
        NFGUID xClientID;
    };

    struct GateServerInfo
    {
        ServerData xServerData;

        std::map<NFGUID, NFSOCK> xRoleInfo;
    };

public:
	virtual void SendMsgPBToGate(const uint16_t nMsgID, google::protobuf::Message& xMsg, const NFGUID& self) = 0;
	virtual void SendMsgPBToGate(const uint16_t nMsgID, const std::string& strMsg, const NFGUID& self) = 0;
    virtual bool AddPlayerGateInfo(const NFGUID& nRoleID, const NFGUID& nClientID, const int nGateID) = 0;
    virtual bool RemovePlayerGateInfo(const NFGUID& nRoleID) = 0;
    virtual NF_SHARE_PTR<GateBaseInfo> GetPlayerGateInfo(const NFGUID& nRoleID) = 0;   
	virtual NF_SHARE_PTR<GateServerInfo> GetGateServerInfo(const int nGateID) = 0;
	virtual NF_SHARE_PTR<GateServerInfo> GetGateServerInfoBySockIndex(const NFSOCK nSockIndex) = 0;
};

#endif